#ifndef MEMDEVICE_H
#define MEMDEVICE_H

//! Header file of base MemDevice class
/*!
 * \file memdevice.h
 *
 * MemDevice is abstraction for memory hierarchy entries.
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include <cmath>
#include "memsimlib.h"
#include "memtrace.h"

//! Policies of caches
enum policy_t {LRU = 0, MRU, RR};

//! Types of memory device events
enum mem_event {
	RREF = 0, /*< RREF - read memory reference */
	WREF, /*< WREF - write memory reference */
	INST /*< INST - cpu read instruction */
};

//! States of CPU - can be changed by cpu cycle
enum cpu_state {
	OFF = 0, /*< OFF - off */
	READY, /*< READY - can read instruction */
	BUSY /*< BUSY - busy with reading */
};

//! Type of memory devices which can be used in simulation model
enum mem_t {
	L1_D = 0, /*< L1 data cache */
	L1_I, /*< L1 inst cache */
	L2, /*< L2 cache */
	L3, /*< L3 cache */
	RAM, /*< RAM */
	SWAP, /*< Swap device */
	TLB, /*< TLB */
	PT, /*< Page table */
	GENERIC /*< Other (generic) device */
};

class MemDeviceCache;
class MemHierarchy;

//! Statistics related to abstract MemDevice
class MemDeviceStats
{
	public:
		//! Pure virtual destructor.
		virtual ~MemDeviceStats() {};
		//! Pure virtual member.
		virtual quint64 get_opts(void) = 0;
		//! Pure virtual member.
                virtual void reset_stats() = 0;
		//! Pure virtual member.
                virtual long get_ac() = 0;
		//! Pure virtual member.
                virtual long get_miss() = 0;
		//! Pure virtual member.
                virtual void inc_ac() = 0;
		//! Pure virtual member.
                virtual void inc_miss() = 0;
	protected:
		//! A protected constructor.
		MemDeviceStats() : opts(0) {};
		quint64 opts; /* !< number of operations */
};

//! Class containing cache stats
class MemDeviceCacheStats : public MemDeviceStats
{
        public:
		//! A constructor.
                MemDeviceCacheStats() : MemDeviceStats(), ac(0), miss(0) {};
		//! A destructor.
                ~MemDeviceCacheStats() {};
		//! Returns number of operations.
		quint64 get_opts(void) { return opts; }
		//! Reset cache statistics.
                void reset_stats();
		//! Returns number of cache accesses.
                long get_ac();
		//! Returns number of cache misses.
                long get_miss();
		//! Increments number of cache accesses.
                void inc_ac();
		//! Increments number of cache misses.
                void inc_miss();
        private:
		//! Cache acesses.
                long ac;
		//! Cache misses.
                long miss;
};

//! Class containing CPU stats
class MemDeviceCpuStats : public MemDeviceStats
{
	public:
		//! A constructor.
		MemDeviceCpuStats() : save(0), load(0), inst(0) {}
		//! Returns number of save instructions
		quint64 get_save();
		//! Returns number of load instructions
		quint64 get_load();
		//! Returns number of exec instructions
		quint64 get_inst();
		//! Increments number of save instructions
		void inc_save() {save++;}
		//! Increments number of load instructions
		void inc_load() {load++;}
		//! Increments number of exec instructions
		void inc_inst() {inst++;}
	private:
		//! Number of save instructions.
		quint64 save;
		//! Number of load instructions.
		quint64 load;
		//! Number of exec instructions.
		quint64 inst;

};

//! Class containing RAM stats
class MemDeviceRAMStats : public MemDeviceCacheStats
{
	public:
		//! A constructor.
                MemDeviceRAMStats() : MemDeviceCacheStats() {};
		//! A destructor.
		~MemDeviceRAMStats() {}
        private:
};

//! Class containing Swap stats
class MemDeviceSwapStats : public MemDeviceCacheStats
{
	public:
		//! A constructor.
                MemDeviceSwapStats() : MemDeviceCacheStats() {};
		//! A destructor.
		~MemDeviceSwapStats() {}
        private:
};

//! Abstract model class of memory device
class MemDevice
{
        public:
		//! Pure virtual member.
                virtual MemDeviceStats & get_stats() = 0;
		//! Pure virtual member.
                virtual int do_mem_ref(quint64 addr, quint64 size) = 0;
		//! Returns latency
                unsigned int get_latency() { return latency; }
		//! Set latency
		void set_latency(unsigned int lat) { latency = lat; }
		//! A destructor
                virtual ~MemDevice() {};
		//! Returns type of device.
		mem_t get_type() { return type; }
        protected:
		//! A protected constructor.
                MemDevice() {};
		//! A protected constructor.
                MemDevice(mem_t type, int latency);
		//! Latency of the device.
                unsigned int latency;
		//! Type of the device.
		mem_t type;
};

//! Class containing informations about memory access
class ev_info
{
	public:
		//! A constructor.
		ev_info() : addr(0), size(0) {}
		//! A constructor.
		ev_info(quint64 addr, quint64 size) : addr(addr), size(size) {}
		//! Address to be read or written.
		quint64 addr;
		//! Size/length of memory access.
		quint64 size;
};

//! Class containing informations about scheduled memory access.
class MemDeviceEvent
{
	public:
		//! A constructor.
		MemDeviceEvent() : dev(NULL), info(ev_info()) {}
		//! A constructor for exec instruction.
		MemDeviceEvent(MemDevice * memdev, mem_event op);
		//! A constructor for load/save instruction.
		MemDeviceEvent(MemDevice * memdev, mem_event op, ev_info info);
		//! A destructor.
		~MemDeviceEvent();
		//! Sets address and size.
		void set_info(quint64 addr, quint64 size);
		//! Perform memory access
		/*!
		 * \return Return code of memory access
		 */
		int do_op();
		//! Returns type of memory operation
		mem_event get_op() const {return op;}
		//! Sets type of memory operation
		void set_op(mem_event op) {this->op = op;}
		//! Returns device where the event is scheduled.
		MemDevice * get_dev()  const {return dev;}
		//! Returns address and size of scheduled memory access.
		ev_info get_info() const {return info;}
		//! Sets address and size of scheduled memory access.
		void set_dev(MemDevice * memdev) {dev = memdev; }
	private:
		//! Type of memory operation.
		mem_event op;
		//! Pointer to memory device in model.
		MemDevice * dev;
		//! Address and size of scheduled memory access.
		ev_info info;
};

//! Class describing cache memory.
/*
 * Objects of this class are used for all types of caches in model.
 */
class MemDeviceCache : public MemDevice
{
        public:
		//! A constructor.
                MemDeviceCache();
		//! A destructor.
                virtual ~MemDeviceCache();
		//! A default constructor.
                MemDeviceCache(mem_t type, int lat, long size, long lsize, long assoc);
		//! Sets size of cache.
                void set_size(long size);
		//! Sets line size of cache.
                void set_lsize(long lsize);
		//! Sets associativity of cache.
                void set_assoc(long assoc);
		//! Sets used policy of cache.
                void set_policy(policy_t policy);
		//! Returns size of cache.
		long get_size() {return size;}
		//! Returns line size of cache.
		long get_lsize() {return lsize;}
		//! Returns associativy of the cache.
		long get_assoc() {return assoc;}
		//! Returns policy used in cache.
		policy_t get_policy() {return pol;}
		//! Clean and re-compute all cache variables.
		void refresh_cache();
		//! Returns cache stats
		/*
		 * \sa MemDeviceCacheStats
		 */
                virtual MemDeviceCacheStats & get_stats() { return stats; }
		//! Access memory in the cache.
		/*!
		 * \param[in] addr Address to access.
		 * \param[in] size Size of accessed memory.
		 */
                int do_mem_ref(quint64 addr, quint64 size);
		friend MemHierarchy;
        protected:
		//! Replacement policy used in cache.
                policy_t pol;
		//! Size of cache in bytes
                long size;
		//! Size of cache line
                long lsize;
		//! Associativy of the cache, i.e. how many n-way is cache
                long assoc;
		//! Number of sets.
                long sets;
		//! Bitmask helper.
                long sets_min_1;
		//! Bitmask helper
                long line_size_bits;
		//! Bitmask helper
                long tag_shift;
		//! Data in cache.
                unsigned long int *tags;
		//! Cache statistics.
                MemDeviceCacheStats stats;
};

//! Class implementating RAM memory.
class MemDeviceRAM : public MemDevice
{
	public:
		//!A constructor.
		MemDeviceRAM(int latency);
		//!A destructor.
		~MemDeviceRAM() {}
		//! Returns RAM memory statistics.
                MemDeviceRAMStats & get_stats() { return stats; }
		//! Do memory reference.
		/*!
		 * \param[in] addr Address to access.
		 * \param[in] size Size of memory access.
		 * \return Return value of memory access
		 */
		int do_mem_ref(quint64 addr, quint64 size);
		friend MemHierarchy;
	private:
		//! RAM statistics
                MemDeviceRAMStats stats;
};

//! Class implementating swap.
class MemDeviceSwap : public MemDevice
{
	public:
		//!A constructor.
		MemDeviceSwap(int latency);
		//!A destructor.
		~MemDeviceSwap() {}
		//! Returns swap statistics.
                MemDeviceSwapStats & get_stats() { return stats; }
		//! Do memory reference.
		/*!
		 * \param[in] addr Address to access.
		 * \param[in] size Size of memory access.
		 * \return Return value of memory access
		 */
		int do_mem_ref(quint64 addr, quint64 size);
		friend MemHierarchy;
	private:
		//! RAM statistics
                MemDeviceSwapStats stats;
};

//! Class implementating TLB
class MemDeviceTlb : public MemDeviceCache
{
	public:
		//!A constructor.
		MemDeviceTlb() : MemDeviceCache() {}
		//!An extended constructor
		MemDeviceTlb(long entries, long entrysize, long lat) : MemDeviceCache(TLB, lat, entries * entrysize * 4, entrysize, 4), entries(entries), entrysize(entrysize)  {}
		//!A destructor
		~MemDeviceTlb() {}
		void set_entries(long entries);
		long get_entries() { return entries; }
		void set_entrysize(long entrysize);
		long get_entrysize() { return entrysize; }
	private:
		//! Number of TLB entries
		long entries;
		//! Widht of TLB entry
		long entrysize;
};

//! Class implementating page table
class MemPageTable : public MemDevice {
	public:
		//! A constructor
		MemPageTable(long depth, int latency) : MemDevice(PT, latency), depth(depth) {}
		//! A destructor
		~MemPageTable() {}
		//! Page address translation
		/*!
		 * \param[in] addr Virtual address for translating
		 * \return Return HIT or MISS
		 */
		int do_mem_ref(quint64 addr);
	private:
		long depth;
};

//! Class implementating CPU
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
