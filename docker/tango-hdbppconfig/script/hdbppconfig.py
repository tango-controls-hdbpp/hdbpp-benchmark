#!/usr/bin/python
#
import sys,re
import time
from PyTango import *
from os import environ

host = environ['TANGO_HOST']

Device = False
Archiver = False
File = False	
for arg in sys.argv:
	word = '([a-zA-Z0-9\+\._\*\#]+)'
	path = '([a-zA-Z0-9\-\+\._\*\#/]+)'
	m = re.compile("--device=" + word + "/{0,1}" + word + "/{0,1}" + word).match(arg.lower())
	if m is not None:
		domain = m.groups()[0]
		family = m.groups()[1]
		member = m.groups()[2]
		Device = True
	m = re.compile("--archiver=" + word + "/{0,1}" + word + "/{0,1}" + word).match(arg.lower())
	if m is not None:
		adomain = m.groups()[0]
		afamily = m.groups()[1]
		amember = m.groups()[2]
		Archiver = True
	m = re.compile("--file=" + path).match(arg.lower())
	if m is not None:
		file_name = m.groups()[0]
		File = True

if Device:
	dev_name = domain + '/' + family + '/' + member
	try:
		print ('going to connect to proxy ',dev_name)
		dev = DeviceProxy(dev_name)
	except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
		print ('ERROR connecting proxy(',dev_name,'): "%s"',e[0]['desc'])
		sys.exit(-1)
	print ('connected to proxy ',dev_name)
	time.sleep(1)
	
if Archiver:
	archiver_name = adomain + '/' + afamily + '/' + amember

if File:
	ind = 0
	print ('Going to parse file ',file_name)
	for line in open(file_name):
		#attr_name = 'tango://'+ '([a-zA-Z0-9:\-\+\._\*\#]+)' + '/' + '([a-zA-Z0-9\-\+\._\*\#]+)' + "/{0,1}" + '([a-zA-Z0-9\-\+\._\*\#]+)' + "/{0,1}" + '([a-zA-Z0-9\-\+\._\*\#]+)' + "/{0,1}" + '([a-zA-Z0-9\-\+\._\*\#]+)'
		attr_name = '([a-zA-Z0-9\-\+\._\*\#]+)' + "/{0,1}" + '([a-zA-Z0-9\-\+\._\*\#]+)' + "/{0,1}" + '([a-zA-Z0-9\-\+\._\*\#]+)' + "/{0,1}" + '([a-zA-Z0-9\-\+\._\*\#]+)'
		num_int = '([0-9]*)'
		num_float = '([0-9.]*)'
		word_spaces = '([a-zA-Z0-9\._\*\#\s]*)'
		word_strategy = '([a-zA-Z0-9\._\*\#|]*)'
		spaces = '([,\s]*)'
		m = re.compile(attr_name + ", ABSOLUTE: "+num_float + ", RELATIVE: None, PERIOD: " + num_int + ", strategy=" + word_strategy + "; ttl=" + num_int).match(line)
		if m is not None:
			attr = m.groups()[0]+"/" + m.groups()[1]+"/" + m.groups()[2]+"/" + m.groups()[3]
			absolute = m.groups()[4]
			periodic = m.groups()[5]
			strategy = m.groups()[6]
			ttl = m.groups()[7]
			
			if attr[0] == '#':
				continue
			if attr[0] == '-':
				continue

			try:
				dev.write_attribute('SetArchiver',archiver_name)
			except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
				print ('     ---> ERROR SetArchiver: ',e[0])
				time.sleep(5)
				continue
			time.sleep(0.02)
			try:
				dev.write_attribute('SetAttributeName',attr)
			except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
				print ('     ---> ERROR SetAttributeName: ',e[0])
				time.sleep(5)
				continue
			time.sleep(0.02)
			try:
				dev.write_attribute('SetCodePushedEvent',1)
			except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
				print ('     ---> ERRORSetCodePushedEvent : ',e[0])
				time.sleep(5)
				continue
			time.sleep(0.02)
			try:
				dev.write_attribute('SetAbsoluteEvent',float(absolute))
			except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
				print ('     ---> ERROR SetAbsoluteEvent: ',e[0])
				time.sleep(5)
				continue
			time.sleep(0.02)
			try:
				dev.write_attribute('SetPeriodEvent',int(periodic))
			except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
				print ('     ---> ERROR SetPeriodEvent: ',e[0])
				time.sleep(5)
				continue
			time.sleep(0.02)
			try:
				dev.write_attribute('SetStrategy',strategy)
			except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
				print ('     ---> ERROR SetStrategy: ',e[0])
				time.sleep(5)
				continue
			time.sleep(0.02)
			try:
				dev.write_attribute('SetTTL',int(ttl))
			except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
				print ('     ---> ERROR SetTTL: ',e[0])
				time.sleep(5)
				continue
			time.sleep(0.02)

			try:
				dev.command_inout('AttributeAdd')
			except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
				print ('->->->->->->-> Error command_inout(AttributeAdd): ',e[0])
				time.sleep(0.5)
				continue
			ind += 1
			time.sleep(1)
		else:
			m1 = re.compile(attr_name + ", ABSOLUTE: None, RELATIVE: "+num_float + ", PERIOD: " + num_int + ", strategy=" + word_strategy + "; ttl=" + num_int).match(line)
			if m1 is not None:
				attr = m1.groups()[0]+"/" + m1.groups()[1]+"/" + m1.groups()[2]+"/" + m1.groups()[3]
				relative = m1.groups()[4]
				periodic = m1.groups()[5]
				strategy = m1.groups()[6]
				ttl = m1.groups()[7]

				if attr[0] == '#':
					continue
				if attr[0] == '-':
					continue
	
				try:
					dev.write_attribute('SetArchiver',archiver_name)
				except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
					print ('     ---> ERROR SetArchiver: ',e[0])
					time.sleep(5)
					continue
				time.sleep(0.02)
				try:
					dev.write_attribute('SetAttributeName',attr)
				except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
					print ('     ---> ERROR SetAttributeName: ',e[0])
					time.sleep(5)
					continue
				time.sleep(0.02)
				try:
					dev.write_attribute('SetCodePushedEvent',1)
				except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
					print ('     ---> ERRORSetCodePushedEvent : ',e[0])
					time.sleep(5)
					continue
				time.sleep(0.02)
				try:
					dev.write_attribute('SetRelativeEvent',float(relative))
				except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
					print ('     ---> ERROR SetAbsoluteEvent: ',e[0])
					time.sleep(5)
					continue
				time.sleep(0.02)
				try:
					dev.write_attribute('SetPeriodEvent',int(periodic))
				except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
					print ('     ---> ERROR SetPeriodEvent: ',e[0])
					time.sleep(5)
					continue
				time.sleep(0.02)
				try:
					dev.write_attribute('SetStrategy',strategy)
				except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
					print ('     ---> ERROR SetStrategy: ',e[0])
					time.sleep(5)
					continue
				time.sleep(0.02)
				try:
					dev.write_attribute('SetTTL',int(ttl))
				except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
					print ('     ---> ERROR SetTTL: ',e[0])
					time.sleep(5)
					continue
				time.sleep(0.02)
	
				try:
					dev.command_inout('AttributeAdd')
				except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
					print ('->->->->->->-> Error command_inout(AttributeAdd): ',e[0])
					time.sleep(0.5)
					continue
				ind += 1
				time.sleep(1)
			else:
				m2 = re.compile(attr_name + ", ABSOLUTE: "+num_float + ", RELATIVE: "+num_int + ", PERIOD: " + num_int + ", strategy=" + word_strategy + "; ttl=" + num_int).match(line)
				if m2 is not None:
					attr = m2.groups()[0]+"/" + m2.groups()[1]+"/" + m2.groups()[2]+"/" + m2.groups()[3]
					absolute = m2.groups()[4]
					relative = m2.groups()[5]
					periodic = m2.groups()[6]
					strategy = m2.groups()[7]
					ttl = m2.groups()[8]

					if attr[0] == '#':
						continue
					if attr[0] == '-':
						continue
		
					try:
						dev.write_attribute('SetArchiver',archiver_name)
					except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
						print ('     ---> ERROR SetArchiver: ',e[0])
						time.sleep(5)
						continue
					time.sleep(0.02)
					try:
						dev.write_attribute('SetAttributeName',attr)
					except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
						print ('     ---> ERROR SetAttributeName: ',e[0])
						time.sleep(5)
						continue
					time.sleep(0.02)
					try:
						dev.write_attribute('SetCodePushedEvent',1)
					except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
						print ('     ---> ERRORSetCodePushedEvent : ',e[0])
						time.sleep(5)
						continue
					time.sleep(0.02)
					try:
						dev.write_attribute('SetAbsoluteEvent',float(absolute))
					except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
						print ('     ---> ERROR SetAbsoluteEvent: ',e[0])
						time.sleep(5)
						continue
					time.sleep(0.02)
					try:
						dev.write_attribute('SetRelativeEvent',float(relative))
					except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
						print ('     ---> ERROR SetAbsoluteEvent: ',e[0])
						time.sleep(5)
						continue
					time.sleep(0.02)
					try:
						dev.write_attribute('SetPeriodEvent',int(periodic))
					except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
						print ('     ---> ERROR SetPeriodEvent: ',e[0])
						time.sleep(5)
						continue
					time.sleep(0.02)
					try:
						dev.write_attribute('SetStrategy',strategy)
					except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
						print ('     ---> ERROR SetStrategy: ',e[0])
						time.sleep(5)
						continue
					time.sleep(0.02)
					try:
						dev.write_attribute('SetTTL',int(ttl))
					except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
						print ('     ---> ERROR SetTTL: ',e[0])
						time.sleep(5)
						continue
					time.sleep(0.02)
		
					try:
						dev.command_inout('AttributeAdd')
					except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
						print ('->->->->->->-> Error command_inout(AttributeAdd): ',e[0])
						time.sleep(0.5)
						continue
					ind += 1
					time.sleep(1)
				else:
					m3 = re.compile(attr_name + ", ABSOLUTE: None, RELATIVE: None, PERIOD: " + num_int + ", strategy=" + word_strategy + "; ttl=" + num_int).match(line)
					if m3 is not None:
						attr = m3.groups()[0]+"/" + m3.groups()[1]+"/" + m3.groups()[2]+"/" + m3.groups()[3]
						periodic = m3.groups()[4]
						strategy = m3.groups()[5]
						ttl = m3.groups()[6]

						if attr[0] == '#':
							continue
						if attr[0] == '-':
							continue
		
						try:
							dev.write_attribute('SetArchiver',archiver_name)
						except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
							print ('     ---> ERROR SetArchiver: ',e[0])
							time.sleep(5)
							continue
						time.sleep(0.02)
						try:
							dev.write_attribute('SetAttributeName',attr)
						except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
							print ('     ---> ERROR SetAttributeName: ',e[0])
							time.sleep(5)
							continue
						time.sleep(0.02)
						try:
							dev.write_attribute('SetCodePushedEvent',1)
						except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
							print ('     ---> ERRORSetCodePushedEvent : ',e[0])
							time.sleep(5)
							continue
						time.sleep(0.02)
						try:
							dev.write_attribute('SetPeriodEvent',int(periodic))
						except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
							print ('     ---> ERROR SetPeriodEvent: ',e[0])
							time.sleep(5)
							continue
						time.sleep(0.02)
						try:
							dev.write_attribute('SetStrategy',strategy)
						except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
							print ('     ---> ERROR SetStrategy: ',e[0])
							time.sleep(5)
							continue
						time.sleep(0.02)
						try:
							dev.write_attribute('SetTTL',int(ttl))
						except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
							print ('     ---> ERROR SetTTL: ',e[0])
							time.sleep(5)
							continue
						time.sleep(0.02)
	
						try:
							dev.command_inout('AttributeAdd')
						except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
							print ('->->->->->->-> Error command_inout(AttributeAdd): ',e[0])
							time.sleep(0.5)
							continue
						ind += 1
						time.sleep(1)
					else:
						m4 = re.compile(attr_name + ", ABSOLUTE: "+num_float + ", RELATIVE: None, PERIOD: None, strategy=" + word_strategy + "; ttl=" + num_int).match(line)
						if m4 is not None:
							attr = m4.groups()[0]+"/" + m4.groups()[1]+"/" + m4.groups()[2]+"/" + m4.groups()[3]
							absolute = m4.groups()[4]
							strategy = m4.groups()[5]
							ttl = m4.groups()[6]

							if attr[0] == '#':
								continue
							if attr[0] == '-':
								continue
				
							try:
								dev.write_attribute('SetArchiver',archiver_name)
							except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
								print ('     ---> ERROR SetArchiver: ',e[0])
								time.sleep(5)
								continue
							time.sleep(0.02)
							try:
								dev.write_attribute('SetAttributeName',attr)
							except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
								print ('     ---> ERROR SetAttributeName: ',e[0])
								time.sleep(5)
								continue
							time.sleep(0.02)
							try:
								dev.write_attribute('SetCodePushedEvent',1)
							except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
								print ('     ---> ERRORSetCodePushedEvent : ',e[0])
								time.sleep(5)
								continue
							time.sleep(0.02)
							try:
								dev.write_attribute('SetAbsoluteEvent',float(absolute))
							except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
								print ('     ---> ERROR SetAbsoluteEvent: ',e[0])
								time.sleep(5)
								continue
							time.sleep(0.02)
							try:
								dev.write_attribute('SetStrategy',strategy)
							except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
								print ('     ---> ERROR SetStrategy: ',e[0])
								time.sleep(5)
								continue
							time.sleep(0.02)
							try:
								dev.write_attribute('SetTTL',int(ttl))
							except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
								print ('     ---> ERROR SetTTL: ',e[0])
								time.sleep(5)
								continue
							time.sleep(0.02)
				
							try:
								dev.command_inout('AttributeAdd')
							except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
								print ('->->->->->->-> Error command_inout(AttributeAdd): ',e[0])
								time.sleep(0.5)
								continue
							ind += 1
							time.sleep(1)
						else:
							m5 = re.compile(attr_name + ", ABSOLUTE: None, RELATIVE: None, PERIOD: None, strategy=" + word_strategy + "; ttl=" + num_int).match(line)
							if m5 is not None:
								attr = m5.groups()[0]+"/" + m5.groups()[1]+"/" + m5.groups()[2]+"/" + m5.groups()[3]
								strategy = m5.groups()[4]
								ttl = m5.groups()[5]

								if attr[0] == '#':
									continue
								if attr[0] == '-':
									continue
					
								try:
									dev.write_attribute('SetArchiver',archiver_name)
								except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
									print ('     ---> ERROR SetArchiver: ',e[0])
									time.sleep(5)
									continue
								time.sleep(0.02)
								try:
									dev.write_attribute('SetAttributeName',attr)
								except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
									print ('     ---> ERROR SetAttributeName: ',e[0])
									time.sleep(5)
									continue
								time.sleep(0.02)
								try:
									dev.write_attribute('SetCodePushedEvent',1)
								except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
									print ('     ---> ERRORSetCodePushedEvent : ',e[0])
									time.sleep(5)
									continue
								time.sleep(0.02)
								try:
									dev.write_attribute('SetStrategy',strategy)
								except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
									print ('     ---> ERROR SetStrategy: ',e[0])
									time.sleep(5)
									continue
								time.sleep(0.02)
								try:
									dev.write_attribute('SetTTL',int(ttl))
								except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
									print ('     ---> ERROR SetTTL: ',e[0])
									time.sleep(5)
									continue
								time.sleep(0.02)
					
								try:
									dev.command_inout('AttributeAdd')
								except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
									print ('->->->->->->-> Error command_inout(AttributeAdd): ',e[0])
									time.sleep(0.5)
									continue
								ind += 1
								time.sleep(1)
							else:
								m6 = re.compile(attr_name + ", ABSOLUTE: None, RELATIVE: "+num_float + ", PERIOD: None, strategy=" + word_strategy + "; ttl=" + num_int).match(line)
								if m6 is not None:
									attr = m6.groups()[0]+"/" + m6.groups()[1]+"/" + m6.groups()[2]+"/" + m6.groups()[3]
									relative = m6.groups()[4]
									strategy = m6.groups()[5]
									ttl = m6.groups()[6]

									if attr[0] == '#':
										continue
									if attr[0] == '-':
										continue
						
									try:
										dev.write_attribute('SetArchiver',archiver_name)
									except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
										print ('     ---> ERROR SetArchiver: ',e[0])
										time.sleep(5)
										continue
									time.sleep(0.02)
									try:
										dev.write_attribute('SetAttributeName',attr)
									except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
										print ('     ---> ERROR SetAttributeName: ',e[0])
										time.sleep(5)
										continue
									time.sleep(0.02)
									try:
										dev.write_attribute('SetCodePushedEvent',1)
									except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
										print ('     ---> ERRORSetCodePushedEvent : ',e[0])
										time.sleep(5)
										continue
									time.sleep(0.02)
									try:
										dev.write_attribute('SetRelativeEvent',float(relative))
									except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
										print ('     ---> ERROR SetAbsoluteEvent: ',e[0])
										time.sleep(5)
										continue
									time.sleep(0.02)
									try:
										dev.write_attribute('SetStrategy',strategy)
									except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
										print ('     ---> ERROR SetStrategy: ',e[0])
										time.sleep(5)
										continue
									time.sleep(0.02)
									try:
										dev.write_attribute('SetTTL',int(ttl))
									except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
										print ('     ---> ERROR SetTTL: ',e[0])
										time.sleep(5)
										continue
									time.sleep(0.02)
						
									try:
										dev.command_inout('AttributeAdd')
									except (DevFailed,ConnectionFailed,EventSystemFailed) as e:
										print ('->->->->->->-> Error command_inout(AttributeAdd): ',e[0])
										time.sleep(0.5)
										continue
									ind += 1
									time.sleep(1)
								else:
									print ('Error parsing: ', line)
	print('Configured for archiving ',ind,' attributes')




if len(sys.argv) < 3:
	print ('Usage:', sys.argv[0], '"--device=hdb++cm device name --archiver=hdb++es device name --file=filename"\n')
	print ('Examples:')
	print ('\t', sys.argv[0], '--device=archiving/hdb++manager2/0 --archiver=archiving/hdb++archiver2/sl --file=lista_hdb++.txt')

	sys.exit(-1)




# EOF
