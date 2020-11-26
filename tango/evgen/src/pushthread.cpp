//
// file :         pushthread.cpp
//
// description :  events pushing thread
//
// project :      TANGO Device Server
//
//
// copyleft :   Sincrotrone Trieste S.C.p.A.
//              Strada Statale 14 - km 163,5 in AREA Science Park
//              34012 Basovizza, Trieste ITALY
//

#include "pushthread.h"
#include "EvGen.h"
#include <math.h>


namespace EvGen_ns
{

static inline timespec timespec_diff(struct timespec *a, struct timespec *b)
{
	struct timespec result;
	result.tv_sec  = a->tv_sec  - b->tv_sec;
	result.tv_nsec = a->tv_nsec - b->tv_nsec;
	if (result.tv_nsec < 0)
	{
		--result.tv_sec;
		result.tv_nsec += 1000000000L;
	}
	if(result.tv_sec < 0)
	{
		result.tv_sec = 0;
		result.tv_nsec = 1000;
	}
	return result;
}

//+------------------------------------------------------------------
//
//	method:			pushthread::pushthread()
//
//	description:	pushthread constructor
//
//-------------------------------------------------------------------
pushthread::pushthread(Tango::DeviceImpl* devImpl):Tango::LogAdapter(devImpl)
{ 
	DEBUG_STREAM << "pushthread::" << __func__ << ": entering... " << endl;
	device = devImpl;
}

//+------------------------------------------------------------------
//
//	method:			pushthread::~pushthread()
//
//	description:	pushthread destructor
//
//-------------------------------------------------------------------
pushthread::~pushthread()
{
	DEBUG_STREAM << "pushthread::" << __func__ << ": entering... " << endl;
}

//+------------------------------------------------------------------
//
//	method:			pushthread::run()
//
//	description:	Run
//
//-------------------------------------------------------------------
void pushthread::run(void *)
{
	DEBUG_STREAM << "pushthread::" << __func__ << ": running... " << endl;
	timespec now, start_push, end_push, period, time_to_sleep;
	clock_gettime(CLOCK_MONOTONIC, &now);
	uint64_t counter=now.tv_sec;
	double old_doubleattr1 = 0;
	double old_doubleattr2 = 0;
	double doubleattr1_abs = 0.01;
	double doubleattr2_abs = 0.01;
	
	EvGen *_device = static_cast<EvGen *>(device);
	abortflag = false;

	while (!abortflag)
	{
		period.tv_sec = _device->period / 1000000;
		period.tv_nsec = (_device->period % 1000000) * 1000;
		while(_device->get_state() != Tango::RUNNING)
		{
			nanosleep(&period, NULL);
			counter = 0;
		}
		
		clock_gettime(CLOCK_MONOTONIC, &start_push);
		//simple pseudo random values:
		*(_device->attr_scalar_double_ro_read) = (double)counter/start_push.tv_nsec;
		*(_device->attr_scalar_double_rw_read) = *(_device->attr_scalar_double_ro_read);
		*(_device->attr_scalar_long_ro_read) = counter;
		*(_device->attr_scalar_long_rw_read) = *(_device->attr_scalar_long_ro_read);
		*(_device->attr_scalar_ulong64_ro_read) = counter;
		*(_device->attr_scalar_ulong64_rw_read) = *(_device->attr_scalar_ulong64_ro_read);
		*(_device->attr_scalar_bool_ro_read) = counter%2;
		*(_device->attr_scalar_bool_rw_read) = *(_device->attr_scalar_bool_ro_read);
		for(size_t i=0; i<_device->spectrumSize; ++i)
		{
			(_device->attr_spectrum_double_ro_read)[i] = (double)(counter+i)/start_push.tv_nsec;
			(_device->attr_spectrum_double_rw_read)[i] = (_device->attr_spectrum_double_ro_read)[i];
			(_device->attr_spectrum_long_ro_read)[i] = counter+i;
			(_device->attr_spectrum_long_rw_read)[i] = (_device->attr_spectrum_long_ro_read)[i];
			(_device->attr_spectrum_ulong64_ro_read)[i] = counter+i;
			(_device->attr_spectrum_ulong64_rw_read)[i] = (_device->attr_spectrum_ulong64_ro_read)[i];
			(_device->attr_spectrum_bool_ro_read)[i] = (counter*i)%2;
			(_device->attr_spectrum_bool_rw_read)[i] = (_device->attr_spectrum_bool_ro_read)[i];
		}

		counter++;

		try
		{
			if(*_device->attr_enable_scalar_double_ro_read)
				_device->push_archive_event("scalar_double_ro",_device->attr_scalar_double_ro_read);
			if(*_device->attr_enable_scalar_double_rw_read)
				_device->push_archive_event("scalar_double_rw",_device->attr_scalar_double_rw_read);
			if(*_device->attr_enable_scalar_long_ro_read)
				_device->push_archive_event("scalar_long_ro",_device->attr_scalar_long_ro_read);
			if(*_device->attr_enable_scalar_long_rw_read)
				_device->push_archive_event("scalar_long_rw",_device->attr_scalar_long_rw_read);
			if(*_device->attr_enable_scalar_bool_ro_read)
				_device->push_archive_event("scalar_bool_ro",_device->attr_scalar_bool_ro_read);
			if(*_device->attr_enable_scalar_bool_rw_read)
				_device->push_archive_event("scalar_bool_rw",_device->attr_scalar_bool_rw_read);
			if(*_device->attr_enable_scalar_ulong64_ro_read)
				_device->push_archive_event("scalar_ulong64_ro",_device->attr_scalar_ulong64_ro_read);
			if(*_device->attr_enable_scalar_ulong64_rw_read)
				_device->push_archive_event("scalar_ulong64_rw",_device->attr_scalar_ulong64_rw_read);
			if(*_device->attr_enable_spectrum_double_ro_read)
				_device->push_archive_event("spectrum_double_ro",_device->attr_spectrum_double_ro_read,_device->spectrumSize);
			if(*_device->attr_enable_spectrum_double_rw_read)
				_device->push_archive_event("spectrum_double_rw",_device->attr_spectrum_double_rw_read,_device->spectrumSize);
			if(*_device->attr_enable_spectrum_long_ro_read)
				_device->push_archive_event("spectrum_long_ro",_device->attr_spectrum_long_ro_read,_device->spectrumSize);
			if(*_device->attr_enable_spectrum_long_rw_read)
				_device->push_archive_event("spectrum_long_rw",_device->attr_spectrum_long_rw_read,_device->spectrumSize);
			if(*_device->attr_enable_spectrum_bool_ro_read)
				_device->push_archive_event("spectrum_bool_ro",_device->attr_spectrum_bool_ro_read,_device->spectrumSize);
			if(*_device->attr_enable_spectrum_bool_rw_read)
				_device->push_archive_event("spectrum_bool_rw",_device->attr_spectrum_bool_rw_read,_device->spectrumSize);
			if(*_device->attr_enable_spectrum_ulong64_ro_read)
				_device->push_archive_event("spectrum_ulong64_ro",_device->attr_spectrum_ulong64_ro_read,_device->spectrumSize);
			if(*_device->attr_enable_spectrum_ulong64_rw_read)
				_device->push_archive_event("spectrum_ulong64_rw",_device->attr_spectrum_ulong64_rw_read,_device->spectrumSize);
		}
		catch(Tango::DevFailed &e)
		{
			INFO_STREAM << "pushthread::" << __func__ << ": exception pushing events: " << e.errors[0].desc << endl;
		}
		if(counter >= _device->number_of_events)
			_device->set_state(Tango::OFF);
		clock_gettime(CLOCK_MONOTONIC, &end_push);
		time_to_sleep = timespec_diff(&end_push, &start_push);
		time_to_sleep = timespec_diff(&period, &time_to_sleep);
		nanosleep(&time_to_sleep, NULL);

	}
	DEBUG_STREAM << "pushthread::" << __func__ << ": exiting... " << endl;
}


}


