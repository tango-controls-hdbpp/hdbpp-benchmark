#!/usr/bin/env python
# example: run with
#./partition_manage.py -v -H srv-log-srf-02 -A fcslog-replica-01 -d hdbpp -a hdbpparchive -u root -y 2020
#./partition_manage.py -v --host srv-log-srf-02 --hostarchive fcslog-replica-01 --database hdbpp --databasearchive hdbpparchive -u root -y 2020

import sys
from os import path
from PyTango import *
from optparse import OptionParser
import time
import docker
import copy
import shutil

log = list()

def memlog(name,value,timestamp):
	#timestamp = int(time.time())
	global log
	#global metricprefix
	message = '{}.{} {} {}'.format(metricprefix, name, value, timestamp)
	log.append(message)

def printlog(fileprefix, options):
	filename = '{}_{}.txt'.format(fileprefix, int(time.time()))
	with open(filename, 'w') as file_handler:
		file_handler.write("#{}\n".format(options))
		for item in log:
			file_handler.write("{}\n".format(item))
	#print(*log, sep = "\n") 

def type2aname(scalar,atype,rw):
	ret=''
	if scalar in ["scalar","spectrum"]:
		ret += scalar
	else:
		print ('Wrong scalar type "', scalar, '"')
		sys.exit(-1)
	ret += '_'

	if atype in ["long","ulong64","double","ulong64","bool"]:
		ret += atype
	else:
		print ('Wrong tango type "', atype, '"')
		sys.exit(-1)
	ret += '_'
	if rw in ["ro","rw"]:
		ret += rw
	else:
		print ('Wrong rw type "', rw, '"')
		sys.exit(-1)
	return ret

def enable_types(evgen,evgennum,scalartype,atype,rwtype):
	for ii in range(evgennum):
		devname = '{}{}'.format(evgen, ii)
		print ('Entering enable_types with evgen=',devname)
		try:
			#print ('going to connect to proxy ',evgen)
			dev = DeviceProxy(devname)
		except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
			print ('ERROR connecting proxy(',evgen,'): ',e[0]['desc'])
			sys.exit(-1)
		att = 'enable_' + type2aname(scalartype,atype,rwtype)
		try:
			dev.write_attribute(att,True)
		except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
			print ('ERROR enabling attribute: ', att ,' err=',e[0])
			sys.exit(-1)

def humanize_bytes(bytesize, precision=2):
	"""
	Humanize byte size figures
	https://gist.github.com/moird/3684595
	"""
	abbrevs = (
		(1 << 50, 'PB'),
		(1 << 40, 'TB'),
		(1 << 30, 'GB'),
		(1 << 20, 'MB'),
		(1 << 10, 'kB'),
		(1, 'bytes')
		)
	if bytesize == 1:
		return '1 byte'
	for	factor, suffix in abbrevs:
		if bytesize >= factor:
			break
	if factor == 1:
		precision = 0
	return '%.*f %s' % (precision, bytesize / float(factor), suffix)

# this is taken directly from docker client:
#   https://github.com/docker/docker/blob/28a7577a029780e4533faf3d057ec9f6c7a10948/api/client/stats.go#L309
def calculate_cpu_percent(d):
	cpu_count = len(d["cpu_stats"]["cpu_usage"]["percpu_usage"])
	cpu_percent = 0.0
	cpu_delta = float(d["cpu_stats"]["cpu_usage"]["total_usage"]) - \
		float(d["precpu_stats"]["cpu_usage"]["total_usage"])
	system_delta = float(d["cpu_stats"]["system_cpu_usage"]) - \
		float(d["precpu_stats"]["system_cpu_usage"])
	if system_delta > 0.0:
		cpu_percent = cpu_delta / system_delta * 100.0 * cpu_count
	return cpu_percent

# again taken directly from docker:
#   https://github.com/docker/cli/blob/2bfac7fcdafeafbd2f450abb6d1bb3106e4f3ccb/cli/command/container/stats_helpers.go#L168
# precpu_stats in 1.13+ is completely broken, doesn't contain any values
def calculate_cpu_percent2(d, previous_cpu, previous_system):
	# import json
	# du = json.dumps(d, indent=2)
	# logger.debug("XXX: %s", du)
	cpu_percent = 0.0
	cpu_total = float(d["cpu_stats"]["cpu_usage"]["total_usage"])
	cpu_delta = cpu_total - previous_cpu
	cpu_system = float(d["cpu_stats"]["system_cpu_usage"])
	system_delta = cpu_system - previous_system
	online_cpus = d["cpu_stats"].get("online_cpus", len(d["cpu_stats"]["cpu_usage"]["percpu_usage"]))
	if system_delta > 0.0:
		cpu_percent = (cpu_delta / system_delta) * online_cpus * 100.0
	return cpu_percent, cpu_system, cpu_total

def graceful_chain_get(d, *args):
	if not d:
		return None
	t = copy.deepcopy(d)
	for arg in args:
		try:
			t = t[arg]
		except (AttributeError, KeyError, TypeError):
			return None
	return t

def calculate_blkio_bytes(d):
	"""
	:param d:
	:return: (read_bytes, wrote_bytes), ints
	"""
	bytes_stats = graceful_chain_get(d, "blkio_stats", "io_service_bytes_recursive")
	if not bytes_stats:
		return 0, 0
	r = 0
	w = 0
	for s in bytes_stats:
		if s["op"] == "Read":
			r += s["value"]
		elif s["op"] == "Write":
			w += s["value"]
	return r, w


def calculate_network_bytes(d):
	"""
	:param d:
	:return: (received_bytes, transceived_bytes), ints
	"""
	networks = graceful_chain_get(d, "networks")
	if not networks:
		return 0, 0
	r = 0
	t = 0
	for if_name, data in networks.items():
		#logger.debug("getting stats for interface %r", if_name)
		r += data["rx_bytes"]
		t += data["tx_bytes"]
	return r, t

def docker_stats(timestamp):
	client = docker.from_env()
	cl = client.containers.list()
	for item in cl:
		name=item.name
		stats=item.stats(stream=False)
		cpuperc = calculate_cpu_percent(stats)
		if cpuperc < 0.01:
			continue
		metric='{}.cpuperc'.format(name)
		memlog(metric,cpuperc,timestamp)
		memuse=stats["memory_stats"]["usage"]
		metric='{}.memuse'.format(name)
		memlog(metric,memuse,timestamp)
		readio, writeio = calculate_blkio_bytes(stats)
		metric='{}.diskwrite'.format(name)
		memlog(metric,writeio,timestamp)


def start_test(evgen,evgennum,archiver,archivernum,period,number):
	edevs=[]
	adevs=[]
	for ii in range(evgennum):
		devname = '{}{}'.format(evgen, ii)
		print ('Start test with evgen=',devname)
		try:
			edevs.append(DeviceProxy(devname))
		except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
			print ('ERROR connecting proxy(',devname,'): ',e[0]['desc'])
			sys.exit(-1)
	for ii in range(archivernum):
		devname = '{}{}'.format(archiver, ii)
		try:
			adevs.append(DeviceProxy(devname))
		except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
			print ('ERROR connecting proxy(',devname,'): ',e[0]['desc'])
			sys.exit(-1)
	disk_start = shutil.disk_usage('/data').used
	time_start = int(time.time())
	for ed in edevs:
		try:
			ed.command_inout("Start",[period,number])
		except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
			print ('ERROR starting EvGen: ',e[0]['desc'])
			sys.exit(-1)

	#arch_num = 'Archived: {}'.format(adev.read_attribute('AttributeList').value)
	#print(arch_num)

	try:
		max_count = 0
		error = 0
		old_max_pend = 0
		min_period = period
		while error == 0:
			statrunning = True
			for ed in edevs:
				statrunning = statrunning and (DevState.RUNNING == ed.read_attribute('State').value)
			while statrunning:
				pend=0
				max_pend=0
				for ad in adevs:
					pend = pend + ad.read_attribute('AttributePendingNumber').value
					max_pend = max_pend + ad.read_attribute('AttributeMaxPendingNumber').value
				timestamp = int(time.time())
				#print('Looping with period=',period,' pending number=', pend, ' max pending number=',max_pend)
				memlog('AttributePendingNumber',pend,timestamp)
				memlog('AttributeMaxPendingNumber',max_pend,timestamp)
				docker_stats(timestamp)
				memlog('EventRate',evgennum*1000000/period,timestamp)
				memlog('DiskUsed',shutil.disk_usage('/data').used-disk_start,timestamp)
				if max_pend > old_max_pend:
					old_max_pend = max_pend
					max_count += 1
				elif pend < 0.5*max_pend:
					min_period = period
					max_count = 0
					#old_max_pend = pend
					#max_pend = pend
				if max_count >= 6:
					error = 1
					break
				time.sleep(10)
				for ed in edevs:
					statrunning = statrunning and (DevState.RUNNING == ed.read_attribute('State').value)

			print('With period=',period,'us, EventRate=', evgennum*1000000/period,' max pending number=',max_pend,'(',pend,') max_count=',max_count)
			mean_freq=0
			num_freq=0
			tot_ev=0
			for ad in adevs:
				for freq in ad.read_attribute('AttributeRecordFreqList').value:
					if freq > 0:
						mean_freq += freq
						num_freq += 1
				for ev in ad.read_attribute('AttributeEventNumberList').value:
					if ev > 1:
						tot_ev += ev
			if num_freq != 0:
				mean_freq = mean_freq / num_freq

			arch_num = 'Archived:  FREQ={}ev/10s  COUNT={}\n'.format(mean_freq, tot_ev)
			print(arch_num)
			period = period * 0.9
			#to have constant time, increase number
			number = number / 0.9
			if period < 1000:
				break
			if pend < 0.5*max_pend:
				min_period = period
				max_count = 0
				#old_max_pend = pend
				#max_pend = pend
			for ed in edevs:
				ed.command_inout("Stop")
				ed.command_inout("Start",[period,number])

		for ed in edevs:
			ed.command_inout("Stop")
	except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
		print ('Exception during test: ',e)
		return
	print ('End test, max EventRate=',evgennum*1000000/min_period,' ev/s - disk used=', (shutil.disk_usage('/data').used-disk_start)/1024/1024, ' MB - elapsed time=', int(time.time()) - time_start, ' s')
	return				
			


def main(options):

	enable_types(options.evgen,options.evgennum,options.scalartype,options.atype,options.rwtype)

	start_test(options.evgen,options.evgennum,options.archiver,options.archivernum,options.period,options.number)

	printlog(options.fileprefix, options)

if __name__ == '__main__':

	parser = OptionParser()
	parser.add_option("-t", "--type", action = "store", type = "string", dest = "atype",
		help = "Tango attribute type (long, ulong64, double, bool)")
	parser.add_option("-s", "--scalartype", action = "store", type = "string", dest = "scalartype",
		help = "Tango attribute scalar/spectrum")
	parser.add_option("-w", "--rwtype", action = "store", type = "string", dest = "rwtype",
		help = "Tango attribute RW (ro, rw)")
	parser.add_option("-e", "--evgen", action = "store", type = "string", dest = "evgen",
		help = "Tango name of EvGen server")
	parser.add_option("-i", "--evgennum", action = "store", type = "int", dest = "evgennum",
		help = "Number of EvGen server")
	parser.add_option("-a", "--archiver", action = "store", type = "string", dest = "archiver",
		help = "Tango name of HdbEventSubscriber server")
	parser.add_option("-r", "--archivernum", action = "store", type = "int", dest = "archivernum",
		help = "Number of EvGen server")
	parser.add_option("-p", "--period", action = "store", type = "int", dest = "period",
		help = "EvGen events period")
	parser.add_option("-n", "--number", action = "store", type = "int", dest = "number",
		help = "EvGen events number")
	parser.add_option("-f", "--file", action = "store", type = "string", dest = "fileprefix",
		help = "File prefix where to store result")


	(options, args) = parser.parse_args()
	#print (options)
	#print (args)
	global metricprefix
	metricprefix = '{}.{}.{}.{}'.format(path.basename(options.fileprefix), options.scalartype, options.atype, options.rwtype)
	main(options)
