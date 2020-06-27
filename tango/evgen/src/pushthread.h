//
// file :         pushthread.h
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


#ifndef pushthread_H
#define pushthread_H

#include <omnithread.h>
#include <tango.h>
#include <inttypes.h>

namespace EvGen_ns
{

class pushthread : public omni_thread, public Tango::LogAdapter
{	
	private:
		Tango::DeviceImpl* device;

				
	public:
		
		pushthread(Tango::DeviceImpl* devImpl);
		~pushthread();

		bool abortflag;
					
	protected:
		void run(void *);
		
};	/* end class pushthread() */

}

#endif

/* EOF */
