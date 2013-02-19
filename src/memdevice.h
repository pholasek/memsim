#ifndef MEMDEVICE_H
#define MEMDEVICE_H

/*!
 * @file memdevice.h
 * Header file of base MemDevice class
 *
 * \brief MemDevice is abstraction for memory hierarchy entries.
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include <cmath>
#include "memsim.h"

//! Policies of caches
enum policy {LRU = 0, MRU, RR};

//! Types of memory device events
enum mem_event {RREF = 0, WREF};

class MemDeviceCacheStats
{
        public:
                MemDeviceCacheStats() {};
                void reset_stats(); // TODO: templates
                long get_ac();
                long get_miss();
                void inc_ac();
                void inc_miss();
        private:
                long ac;
                long miss;
};

class MemDevice
{
        public:
                MemDevice() {};
                MemDevice(int latency, MemDevice *parent);
                virtual ~MemDevice() {};
                //virtual void set_latency(int lat) = 0;
                virtual MemDeviceCacheStats get_stats() = 0;
                //virtual void write_to_dev(quint64 addr, long size) = 0; TODO - i R/W
                //virtual void read_from_dev(quint64 addr, long size) = 0;
                virtual void do_mem_ref(quint64 addr, long size) = 0;
                void set_parent(MemDevice *parent) { this->parent = parent; }
                void set_child(MemDevice *child) { this->child = child; }
                MemDevice *get_child() { return child; }
                MemDevice *get_parent() { return parent; }
        protected:
                int latency;
                MemDevice *parent;
                MemDevice *child;

};

class MemDeviceCache : public MemDevice
{
        public:
                MemDeviceCache();
                ~MemDeviceCache();
                MemDeviceCache(int lat, long size, long lsize, long assoc, MemDevice *parent);
                void set_size(long size);
                void set_line_size(long lsize);
                void set_assoc(long assoc);
                void set_policy(enum policy);
                void set_latency(int lat);
                MemDeviceCacheStats get_stats(void);
                void do_mem_ref(quint64 addr, long size);
        private:
                enum policy pol;
                long size;
                long lsize;
                long assoc;
                long sets;
                long sets_min_1;
                long line_size_bits;
                long tag_shift;
                char descr[128];
                unsigned long int *tags;
                MemDeviceCacheStats stats;
};

// memory access, tlbflush, ...
class MemDeviceEvent
{
	public:
		MemDeviceEvent(MemDevice *memdev, mem_event op);
		~MemDeviceEvent() {};
		int do_op();
	private:
		mem_event op;
		MemDevice *dev;
};

#endif
