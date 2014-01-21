#ifndef MEMHIERARCHY_H
#define MEMHIERARCHY_H

/*!
 * @file memhierarchy.h
 * Header file of MemHierarchy class
 *
 * \brief MemHierarchy encapsulates memory devices used in simulation.
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include <QScopedPointer>
#include "memdevice.h"
#include "memsimlib.h"
#include "memtrace.h"
#include "memexcept.h"

//enum mem_t {L1_D = 0, L1_I, L2, L3, RAM, SWAP, GENERIC};

const int dev_num = 6;
const int cache_num = 3;

const quint64 DEF_CACHE_LATENCY = 1;
const quint64 DEF_CACHE_SIZE = 65535;
const quint64 DEF_CACHE_LSIZE = 512;
const quint64 DEF_CACHE_ASSOC = 2;
const quint64 DEF_RAM_LATENCY = 1;
const quint64 DEF_SWAP_LATENCY = 1;

class MemHierarchy
{
	public:
		MemHierarchy();
		~MemHierarchy();
                void dump_cache_stats();
		int on_last_dev(void);
		int next_dev(void);
		void reset_devs();
		void add_cache(mem_t type, int latency, long size, long lsize, long assoc);
		void delete_cache(mem_t type, MemDeviceCache * new_cache);
		void add_ram(int latency);
		void delete_ram(MemDeviceRAM *new_ram);
		void add_swap(int latency);
		void delete_swap(MemDeviceSwap *new_swap);
		void config_cache(mem_t type, QString & param, long value);
		void config_ram(QString & param, long value);
		void config_swap(QString & param, long value);
		void commit_changes(void);
		void set_sim_dev(MemDevice * dev) { sim_dev = dev; }
		QString show_devs();
		QString show_stats();
		mem_t get_type(QString & name);
		QString get_name(mem_t type);
		MemDevice * assign_p(mem_t type);
		MemDevice * get_first_inst() { return first_inst; }
		MemDevice * get_first_data() { return first_data; }
		MemDevice * get_sim_dev() { return sim_dev; }
	private:
		MemDevice *sim_dev;
                MemDevice *first_inst;
                MemDevice *first_data;
		MemDevice *last_dev;
		MemDeviceCache * l1_i, *l1_d;
		MemDeviceCache * l2;
		MemDeviceCache * l3;
		MemDeviceRAM * ram;
		MemDeviceSwap * swap;
		void clean_caches();
		void check_integrity();
		QString show_cache(mem_t type);
		QString show_ram();
		QString show_swap();
		QString show_cache_stats(mem_t type);
		QString show_ram_stats();
		QString show_swap_stats();
		static bool dev_map[dev_num];
		QMap<QString,mem_t> name2type;
		QMap<mem_t,QString> type2name;
};

#endif
