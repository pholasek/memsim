#ifndef MEMHIERARCHY_H
#define MEMHIERARCHY_H

//! Header file of MemHierarchy class
/*!
 * \file memhierarchy.h
 *
 * MemHierarchy encapsulates memory devices used in simulation.
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include <QScopedPointer>
#include "memdevice.h"
#include "memsimlib.h"
#include "memtrace.h"
#include "memexcept.h"

//! Max number of possible devices in simulation model.
const int dev_num = 8;
//! Max number of possible caches in simulation model.
const int cache_num = 3;

const quint64 DEF_CACHE_LATENCY = 1;
const quint64 DEF_CACHE_SIZE = 65535;
const quint64 DEF_CACHE_LSIZE = 512;
const quint64 DEF_CACHE_ASSOC = 2;
const quint64 DEF_RAM_LATENCY = 1;
const quint64 DEF_SWAP_LATENCY = 1;
const quint64 DEF_TLB_LATENCY = 1;
const quint64 DEF_TLB_ENTRY_SIZE = sizeof(unsigned long int);
const quint64 DEF_TLB_ENTRIES = 150;
const quint64 DEF_PT_DEPTH = 4;
const quint64 DEF_PT_LATENCY = 4;
const quint64 DEF_PAGE_SIZE = 4096;

//! This class providing access to simulation model of memory hierarchy.
class MemHierarchy
{
	public:
		//! A constructor.
		MemHierarchy();
		//! A destructor.
		~MemHierarchy();
		//! Shows cache statistics.
                void dump_cache_stats();
		//! Determines the exact position of single address access in model.
		int on_last_dev(void);
		//! Move address access to the next device in model.
		int next_dev(void);
		//! Reset all devices in model.
		void reset_devs();
		//! Adds new cache to model.
		/*!
		 * \param[in] type Type of the cache.
		 * \param[in] latency Latency of the cache.
		 * \param[in] size Size of the cache
		 * \param[in] assoc Associativiy of the cache.
		 */
		void add_cache(mem_t type, int latency, long size, long lsize, long assoc);
		//! Removes cache from model.
		/*
		 * \param[in] type Type of cache.
		 * \param[in] new_cache New cache replacing the current one or NULL.
		 */
		void delete_cache(mem_t type, MemDeviceCache * new_cache);
		//! Adds new ram into the model.
		void add_ram(int latency);
		//! Delete ram from model.
		void delete_ram(MemDeviceRAM *new_ram);
		//! Adds new swap device to model.
		/*!
		 * \param[in] latency Latency of the swap device.
		 */
		void add_swap(int latency);
		//! Removes swap from model.
		/*
		 * \param[in] new_swap New swap replacing the current one or NULL.
		 */
		void delete_swap(MemDeviceSwap *new_swap);
		//! Adds new tlb device to model.
		/*!
		 * \param[in] entries Number of TLB entries
		 * \param[in] entrysize Size of TLB entry
		 * \param[in] latency Latency of the TLB device.
		 */
		void add_tlb(long entries, long entrysize, int latency);
		//! Removes tlb from model.
		/*
		 * \param[in] new_tlb New tlb replacing the current one or NULL.
		 */
		void delete_tlb(MemDeviceTlb *new_tlb);
		//! Adds new page table to model.
		/*!
		 * \param[in] depth Depth of the page table.
		 */
		void add_page_table(long depth);
		//! Removes page_table from model.
		/*
		 * \param[in] new_ New tlb replacing the current one or NULL.
		 */
		void delete_page_table(MemPageTable *new_pg_table);
		//! Configures the cache option.
		/*!
		 * \param[in] type Type of the cache.
		 * \param[in] param Parameter of the cache.
		 * \param[in] value New value of the parameter.
		 */
		void config_cache(mem_t type, QString & param, long value);
		//! Configures the ram option.
		/*!
		 * \param[in] param Parameter of the ram.
		 * \param[in] value New value of the parameter.
		 */
		void config_ram(QString & param, long value);
		//! Configures the swap option.
		/*!
		 * \param[in] param Parameter of the swap.
		 * \param[in] value New value of the parameter.
		 */
		void config_swap(QString & param, long value);
		//! Configures the tlb option.
		/*!
		 * \param[in] param Parameter of the swap.
		 * \param[in] value New value of the parameter.
		 */
		void config_tlb(QString & param, long value);
		//! Configures the page_table option.
		/*!
		 * \param[in] param Parameter of the swap.
		 * \param[in] value New value of the parameter.
		 */
		void config_page_table(QString & param, long value);
		//! Checks simulation model integrity.
		void commit_changes(void);
		//! Set device used for simulation.
		void set_sim_dev(MemDevice * dev) { sim_dev = dev; }
		//! Dumps all devices in model.
		QString show_devs();
		//! Dumps statistics of all devices in the model.
		QString show_stats();
		//! Get type of device
		/*!
		 * \param[in] name Name of the device.
		 * \returns type of the device.
		 */
		mem_t get_type(QString & name);
		//! Get name of device
		/*!
		 * \param[in] type Type of the device.
		 * \returns Name of the device.
		 */
		QString get_name(mem_t type);
		//! Returns pointer to the device.
		/*!
		 * \param[in] type Type of the device.
		 * \returns Pointer to the assigned MemDevice.
		 */
		MemDevice * assign_p(mem_t type);
		//! Returns first device used for instruction exec access in model.
		MemDevice * get_first_inst() { return first_inst; }
		//! Returns first device used for data access in model.
		MemDevice * get_first_data() { return first_data; }
		//! Returns current device used for memory access in model.
		MemDevice * get_sim_dev() { return sim_dev; }
		//! Returns pointer to tlb device.
		MemDevice * get_tlb() { return tlb; }
		//! Returns pointer to page table.
		MemDevice * get_pg_table() { return pg_table; }
		//! Returns presence of tlb in hierarchy
		bool has_tlb() { return tlb ? true : false; }
	private:
		//! Current simulation device in model.
		MemDevice *sim_dev;
		//! First device used for instruction access.
                MemDevice *first_inst;
		//! First device used for data access.
                MemDevice *first_data;
		//! Last device in hierarchy.
		MemDevice *last_dev;
		//! L1i and L1d caches.
		MemDeviceCache * l1_i, *l1_d;
		//! L2 cache pointer.
		MemDeviceCache * l2;
		//! L3 cache pointer.
		MemDeviceCache * l3;
		//! RAM cache pointer.
		MemDeviceRAM * ram;
		//! Swap cache pointer.
		MemDeviceSwap * swap;
		//! TLB cache pointer.
		MemDeviceTlb * tlb;
		//! Page table object pointer.
		MemPageTable * pg_table;
		//! Clear content of all caches in model.
		void clean_caches();
		//! Checks integrity of the model.
		void check_integrity();
		//! Shows attributes of given cache.
		QString show_cache(mem_t type);
		//! Shows attributes of ram.
		QString show_ram();
		//! Shows attributes of swap.
		QString show_swap();
		//! Shows attributes of tlb.
		QString show_tlb();
		//! Shows attributes of page_table.
		QString show_page_table();
		//! Shows statistics of give cache.
		QString show_cache_stats(mem_t type);
		//! Shows statistics of ram memory.
		QString show_ram_stats();
		//! Shows statistics of swap memory.
		QString show_swap_stats();
		//! Shows statistics of tlb memory.
		QString show_tlb_stats();
		//! Shows statistics of pg_table.
		QString show_page_table_stats();
		//! An array containing info about presence of devices in current simulation model
		static bool dev_map[dev_num];
		//! A mapping between name and type.
		QMap<QString,mem_t> name2type;
		//! A mapping between type and name.
		QMap<mem_t,QString> type2name;
};

#endif
