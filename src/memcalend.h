#ifndef MEMSIMUL_H
#define MEMSIMUL_H

/*!
 * @file memsimul.h
 * Header file of MemSimCalend class
 *
 * \brief MemCalend class provides objects and methods for pending event set
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memtrace.h"
#include "memdevice.h"

class MemSimCalend
{
        public:
                MemSimCalend();
                ~MemSimCalend();
        private:
                long unsigned int Time;
		QList<MemSimCalendEvent> events;
};

class MemSimCalendEvent //TODO 1 vlakno cte vstup, druhe bezi simulaci
{
	public:
		MemSimCalendEvent
		set_prio(int prio);	
		get_prio(int prio);	
		set_time(unsigned long Time);
		get_time(unsigned long Time);
	private:
		int priority;
		unsigned long Time;
		MemDeviceEvent event;
}

#endif
