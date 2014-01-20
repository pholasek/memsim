/*
 * @file memcalend.cc
 * Source file of MemSimCalend and other related classes.
 *
 * \brief Pending event set base class
 *
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memsim.h"
#include "memsimul.h"
#include "memtrace.h"
#include "memdevice.h"

//! class MemSimCalend

MemSimCalend::MemSimCalend()
{
        Time = 0;
}

MemSimCalend::~MemSimCalend()
{
	events.clear();
}

int MemSimCalend::do_next(void)
{
	int ret;
	MemSimCalendEvent * first;

	if (events.isEmpty())
		return -1;  //TODO vyjimky

	first = get_first();
	this->Time = first->get_time();
	ret = first->do_op();
	events.erase(events.begin());

	return ret;
}

MemSimCalendEvent MemSimCalend::get_first(void)
{
	qSort(events.begin(), events.end(), MemSimCalendEvent::event_time_cmp);
	return events.first();
}

void MemSimCalend::add_event(MemSimCalendEvent & ev)
{
	events.push_back(e);
}

void MemSimCalend::new_event(MemDevice * dev, mem_event op, unsigned long latency, unsigned long prio)
{
	dev_ev = MemDeviceEvent(dev, op);
	ev = MemSimCalendEvent(Time + latency, prio, dev_ev);
	this->add_event(ev);
}

void MemSimCalend::new_ref_event(MemDevice * dev, mem_event op, quint64 addr, unsigned long size, unsigned long latency, unsigned long prio)
{
	dev_ev = MemDeviceEvent(dev, op);
	dev_ev.set_info(addr, size);
	ev = MemSimCalendEvent(Time + latency, prio, dev_ev);
	this->add_event(ev);
}


//! class MemSimCalendEvent

MemSimCalendEvent::MemSimCalendEvent(unsigned int t = 0, int prio = 0, MemDeviceEvent ev)
{
	this->t = t;
	this->prio = prio;
	this->event = ev;
}

bool event_time_cmp(const MemSimCalendEvent &e1, const MemSimCalendEvent &e2)
{
	if (e1.t != e2.t)
		return e1.t < e2.t;
	else
		return e1.prio < e2.prio;
}



