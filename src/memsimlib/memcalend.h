#ifndef MEMCALEND_H
#define MEMCALEND_H
//!Header file of MemSimCalend class
/*!
 * \file memsimul.h
 *
 * MemCalend class provides objects and methods for pending event set
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include <QtAlgorithms>
#include "memsimlib.h"
#include "memtrace.h"
#include "memdevice.h"

class MemSimCalendEvent;
//
//! Structure for returning calendar stats
class MemSimCalendStats
{
	public:
		//! A Constructor
		MemSimCalendStats(quint64 Time, quint64 ev_proc) : Time(Time), ev_proc(ev_proc) {}
		//! Value of model time
		quint64 Time;
		//! Number of processed memory accesses
		quint64 ev_proc;
};

//! next-event calendar class
/*!
 * A class encapsulating calendar of simulation events.
 * It is used by MemSimulation class.
 * \sa ::MemSimulation
 */
class MemSimCalend
{
        public:
		//! A constructor.
                MemSimCalend();
		//! A destructor.
                ~MemSimCalend();
		//! Scheduling new event of executing of instruction
		/*!
		 * \param[in] dev device in model where the instruction fetch event will be scheduled
		 * \param[in] op type of event
		 * \param[in] latency latency of device
		 * \param[in] prio priority of the event
		 * \todo Move latency deeper.
		 */
		void new_fetch_event(MemDevice * dev, mem_event op, unsigned long prio);
		//! Scheduling new event of memory read/write
		/*!
		 * \param[in] dev device in model where the instruction fetch event will be scheduled
		 * \param[in] op type of event
		 * \param[in] addr accessed address
		 * \param[in] size size of accessed memory
		 * \param[in] latency latency of device
		 * \param[in] prio priority of the event
		 */
		void new_ref_event(MemDevice * dev, mem_event op, quint64 addr, unsigned long size,  unsigned long prio);
		//! Do the next scheduled event
		/*!
		 * \return Result of access
		 */
		int do_next();
		//! Clone current event
		/*!
		 * It is used when memory event returned FAIL and we need to
		 * walk up in memory hierarchy model.
		 * \param dev[in] target MemoryDevice for cloning
		 */
		void clone_current(MemDevice * dev);
		//! Reset calendar state
		void reset_calend();
		//! Returns calendar statistics
		MemSimCalendStats get_stats();
        private:
		//! Add new event to calenda
		/*!
		 * \param[in] Reference to the new event
		 */
		void add_event(MemSimCalendEvent & e);
		//! Returns first scheduled event.
		/*!
		 * \return The first event in sorted calendar
		 */
		MemSimCalendEvent & get_first();
		//! Event-calendar.
		QList<MemSimCalendEvent> events;
		//! next-event calendar stats
		MemSimCalendStats stats;
};

//! Class which describe one single memory access event.
class MemSimCalendEvent
{
	public:
		//! A constructor.
		MemSimCalendEvent() : prio(0), t(0), event(MemDeviceEvent()) {}
		//! A constructor.
		MemSimCalendEvent(quint64 t, int prio, MemDeviceEvent ev);
		//! A destructor.
		~MemSimCalendEvent();
		//! Sets priority of event
		void set_prio(int prio) { this->prio = prio; }
		//! Gets priorirty of event
		int get_prio() const { return prio; }
		//! Sets execution time of event
		void set_time(unsigned long t) { this->t = t; }
		//! Gets execution time of event
		int get_time() const { return t; }
		//! Returns MemDeviceEvent
		MemDeviceEvent get_event() const { return event; }
		//! Perform scheduled event on simulation model
		/*!
		 * \return Return value event which has been executed on model
		 */
		int do_event();
	private:
		//! Priority of the event.
		int prio;
		//! Execution time of the event.
		quint64 t;
		//! Class encapsulating access data.
		MemDeviceEvent event;
};

#endif
