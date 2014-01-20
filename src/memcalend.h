#ifndef MEMCALEND_H
#define MEMCALEND_H

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

class MemSimCalendEvent;

class MemSimCalend
{
        public:
                MemSimCalend();
                ~MemSimCalend();
		void new_event(MemDevice * dev, mem_event op, unsigned long latency, unsigned long prio);
		void new_ref_event(MemDevice * dev, mem_event op, quint64 addr, unsigned long size, unsigned long latency, unsigned long prio);
		int do_next();
        private:
		void add_event(MemSimCalendEvent &e);
		MemSimCalendEvent get_first();
                long unsigned int Time;
		QList<MemSimCalendEvent> events;
};

class MemSimCalendEvent //TODO 1 vlakno cte vstup, druhe bezi simulaci
{
	public:
		MemSimCalendEvent(unsigned int t, int prio, MemDeviceEvent ev);
		void set_prio(int prio);
		int get_prio();
		void set_time(unsigned long T);
		int get_time();
		bool event_time_cmp(const MemSimCalendEvent &e1, const MemSimCalendEvent &e2);
	private:
		int prio;
		unsigned long t;
		MemDeviceEvent event;
};

#endif
