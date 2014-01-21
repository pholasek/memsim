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

#include <QtAlgorithms>
#include "memsimlib.h"
#include "memtrace.h"
#include "memdevice.h"

class MemSimCalendEvent;

class MemSimCalend
{
        public:
                MemSimCalend();
                ~MemSimCalend();
		void new_fetch_event(MemDevice * dev, mem_event op, unsigned long latency, unsigned long prio);
		void new_ref_event(MemDevice * dev, mem_event op, quint64 addr, unsigned long size, unsigned long latency, unsigned long prio);
		int do_next();
		void clone_current(MemDevice * dev); //! Called when data haven't been found in lower layer
        private:
		void add_event(MemSimCalendEvent & e);
		MemSimCalendEvent & get_first();
                long unsigned int Time;
		QList<MemSimCalendEvent> events;
		MemSimCalendEvent * curr_ev;
		unsigned long ev_proc; // number of total procecessed events
};

class MemSimCalendEvent //TODO 1 vlakno cte vstup, druhe bezi simulaci
{
	public:
		MemSimCalendEvent() : prio(0), t(0), event(MemDeviceEvent()) {}
		//MemSimCalendEvent(MemSimCalendEvent const & cev);
		~MemSimCalendEvent();
		MemSimCalendEvent(unsigned int t, int prio, MemDeviceEvent ev);
		void set_prio(int prio) { this->prio = prio; }
		int get_prio() const { return prio; }
		void set_time(unsigned long t) { this->t = t; }
		int get_time() const { return t; }
		MemDeviceEvent get_event() const { return event; }
		int do_event();
	private:
		int prio;
		unsigned long t;
		MemDeviceEvent event;
};

#endif
