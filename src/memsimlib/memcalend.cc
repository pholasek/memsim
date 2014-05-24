/*
 * @file memcalend.cc
 * Source file of MemSimCalend and other related classes.
 *
 * \brief Pending event set base class
 *
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memcalend.h"

static inline bool event_time_cmp(const MemSimCalendEvent & e1, const MemSimCalendEvent & e2)
{
	if (e1.get_time() != e2.get_time())
		return e1.get_time() < e2.get_time();
	else
		return e1.get_prio() < e2.get_prio();
}

MemSimCalend::MemSimCalend() : Time(0), curr_ev(NULL), ev_proc(0) {}

MemSimCalend::~MemSimCalend() {}

int MemSimCalend::do_next(void)
{
	int ret;

	if (events.isEmpty()) {
		qDebug() << "MemSimCalend calendar is empty O_o.";
		return -1;
	}

	qDebug() << events.size();

	if (ev_proc > 0) {
		events.erase(events.begin()); // removes processed event which was the first in calendar
	}

	MemSimCalendEvent & first = get_first();
	Time = first.get_time();
	ret = first.do_event();

	ev_proc++;

	return ret;
}

void MemSimCalend::clone_current(MemDevice * new_dev)
{
	MemDeviceEvent ev_curr = (events.begin())->get_event();

	ev_curr.set_dev(new_dev);
	MemSimCalendEvent ev_new(Time + new_dev->get_latency(), 0, ev_curr);

	add_event(ev_new);
}

MemSimCalendEvent & MemSimCalend::get_first(void)
{
	qSort(events.begin(), events.end(), event_time_cmp);
	//qDebug() << "Calendar size: " << events.size();
	return events.first();
}

void MemSimCalend::add_event(MemSimCalendEvent & ev)
{
	events.push_back(ev);
}

void MemSimCalend::new_fetch_event(MemDevice * dev, mem_event op, unsigned long latency, unsigned long prio)
{
	MemSimCalendEvent ev(Time + latency, prio, MemDeviceEvent(dev, op));
	add_event(ev);
}

void MemSimCalend::new_ref_event(MemDevice * dev, mem_event op, quint64 addr, unsigned long size, unsigned long latency, unsigned long prio)
{
	MemSimCalendEvent ev(Time + latency, prio, MemDeviceEvent(dev, op, ev_info(addr, size)));
	this->add_event(ev);
}

//! class MemSimCalendEvent

MemSimCalendEvent::MemSimCalendEvent(quint64 t, int prio, MemDeviceEvent ev) : prio(prio), t(t), event(ev) {}

MemSimCalendEvent::~MemSimCalendEvent() {}

int MemSimCalendEvent::do_event()
{
	return event.do_op();
}


