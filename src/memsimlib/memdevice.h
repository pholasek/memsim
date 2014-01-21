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
#include "memsimlib.h"
#include "memtrace.h"

//! Policies of caches
enum policy_t {LRU = 0, MRU, RR};

//! Types of memory device events
// RREF - read memory reference
// WREF - write memory reference
// INST - cpu read instruction
enum mem_event {RREF = 0, WREF, INST};

//! States of CPU - can be changed by cpu cycle
// OFF - off
// READY - can read instruction
// BUSY - busy with reading
enum cpu_state {OFF = 0, READY, BUSY};

enum mem_t {L1_D = 0, L1_I, L2, L3, RAM, SWAP, GENERIC};

class MemDeviceCache;
class MemHierarchy;

class MemDeviceStats
{
	public:
		virtual ~MemDeviceStats() {};
		virtual quint64 get_opts(void) = 0;
                virtual void reset_stats() = 0; // TODO: templates
                virtual long get_ac() = 0;
                virtual long get_miss() = 0;
                virtual void inc_ac() = 0;
                virtual void inc_miss() = 0;
	protected:
		MemDeviceStats() : opts(0) {};
		quint64 opts; /* !< number of operations */
};

class MemDeviceCacheStats : public MemDeviceStats
{
        public:
                MemDeviceCacheStats() : MemDeviceStats(), ac(0), miss(0) {};
                ~MemDeviceCacheStats() {};
		quint64 get_opts(void) { return opts; }
                void reset_stats(); // TODO: templates
                long get_ac();
                long get_miss();
                void inc_ac();
                void inc_miss();
        private:
                long ac;
                long miss;
};

class MemDeviceCpuStats : public MemDeviceStats
{
	public:
		MemDeviceCpuStats() : save(0), load(0), inst(0) {}
		quint64 get_save();
		quint64 get_load();
		quint64 get_inst();
		void inc_save() {save++;}
		void inc_load() {load++;}
		void inc_inst() {inst++;}
	private:
		quint64 save;
		quint64 load;
		quint64 inst;

};

class MemDeviceRAMStats : public MemDeviceCacheStats
{
	public:
                MemDeviceRAMStats() : MemDeviceCacheStats() {};
		~MemDeviceRAMStats() {}
        private:
};

class MemDeviceSwapStats : public MemDeviceCacheStats
{
	public:
                MemDeviceSwapStats() : MemDeviceCacheStats() {};
		~MemDeviceSwapStats() {}
        private:
};

class MemDevice
{
        public:
                virtual MemDeviceStats & get_stats() = 0;
                virtual int do_mem_ref(quint64 addr, quint64 size) = 0;
                unsigned int get_latency() { return latency; }
		void set_latency(unsigned int lat) { latency = lat; }
                virtual ~MemDevice() {};
		mem_t get_type() { return type; }
        protected:
                MemDevice() {};
                MemDevice(mem_t type, int latency);
                unsigned int latency;
		mem_t type;
};

class ev_info
{
	public:
		ev_info() : addr(0), size(0) {}
		ev_info(quint64 addr, quint64 size) : addr(addr), size(size) {}
		quint64 addr;
		quint64 size;
};

//
// TODO1 memory access, tlbflush, ...
// TODO2 implemantovat pomoci memory pool
class MemDeviceEvent
{
	public:
		MemDeviceEvent() : dev(NULL), info(ev_info()) {}
		MemDeviceEvent(MemDevice * memdev, mem_event op);
		MemDeviceEvent(MemDevice * memdev, mem_event op, ev_info info);
		~MemDeviceEvent();
		void set_info(quint64 addr, quint64 size);
		int do_op();
		mem_event get_op() const {return op;}
		void set_op(mem_event op) {this->op = op;}
		MemDevice * get_dev()  const {return dev;}
		ev_info get_info() const {return info;}
		void set_dev(MemDevice * memdev) {dev = memdev; }
	private:
		mem_event op;
		MemDevice * dev;
		ev_info info;
};

class MemDeviceCache : public MemDevice
{
        public:
                MemDeviceCache();
                ~MemDeviceCache();
                MemDeviceCache(mem_t type, int lat, long size, long lsize, long assoc);
                void set_size(long size);
                void set_lsize(long lsize);
                void set_assoc(long assoc);
                void set_policy(policy_t policy);
		long get_size() {return size;}
		long get_lsize() {return lsize;}
		long get_assoc() {return assoc;}
		policy_t get_policy() {return pol;}
		void refresh_cache();
                virtual MemDeviceCacheStats & get_stats() { return stats; }
                int do_mem_ref(quint64 addr, quint64 size);
		friend MemHierarchy;
        private:
                policy_t pol;
                long size;
                long lsize;
                long assoc;
                long sets;
                long sets_min_1;
                long line_size_bits;
                long tag_shift;
                unsigned long int *tags;
                MemDeviceCacheStats stats;
};

class MemDeviceRAM : public MemDevice
{
	public:
		MemDeviceRAM(int latency);
		~MemDeviceRAM() {}
                MemDeviceRAMStats & get_stats() { return stats; }
		int do_mem_ref(quint64 addr, quint64 size);
		friend MemHierarchy;
	private:
                MemDeviceRAMStats stats;
};

class MemDeviceSwap : public MemDevice
{
	public:
		MemDeviceSwap(int latency);
		~MemDeviceSwap() {}
                MemDeviceSwapStats & get_stats() { return stats; }
		int do_mem_ref(quint64 addr, quint64 size);
		friend MemHierarchy;
	private:
                MemDeviceSwapStats stats;
};

//TODO
class MemDeviceCpu : public MemDevice
{
	public:
		MemDeviceCpu();
		~MemDeviceCpu();
		int do_mem_ref(quint64 addr, quint64 size);
		cpu_state get_state() { return state; }
		void state_watchdog(quint64 curr_t);
		quint64 get_fetch_t() { return fetch_t; }
		void set_fetch_t(quint64 ft) { fetch_t = ft; }
                MemDeviceCpuStats & get_stats(void) { return *stats; }
	private:
		//quint64 freq; TODO
		quint64 fetch_t;
		cpu_state state;
		quint64 freq;
                MemDeviceCpuStats *stats;
};


#endif
