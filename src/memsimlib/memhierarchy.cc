/*!
 * @file memhierarchy.cc
 * Source file of MemHierarchy
 *
 * \brief Wrapper class for memory devices in hierarchy
 *
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memhierarchy.h"

//! Constructor && destructor
MemHierarchy::MemHierarchy() :  sim_dev(NULL), first_inst(NULL), first_data(NULL), last_dev(NULL), l1_i(NULL), l1_d(NULL), l2(NULL), l3(NULL), ram(NULL), swap(NULL), tlb(NULL), pg_table(NULL)
{
	name2type.insert("l1", L1_D);
	name2type.insert("l2", L2);
	name2type.insert("l3", L3);
	name2type.insert("ram", RAM);
	name2type.insert("swap", SWAP);
	name2type.insert("tlb", TLB);
	name2type.insert("pt", PT);
	name2type.insert("model", GENERIC);
	type2name.insert(L1_D, "l1");
	type2name.insert(L2, "l2");
	type2name.insert(L3, "l3");
	type2name.insert(RAM, "ram");
	type2name.insert(SWAP, "swap");
	type2name.insert(TLB, "tlb");
	type2name.insert(PT, "pt");
	type2name.insert(GENERIC, "model");
}

MemHierarchy::~MemHierarchy()
{
	if (!dev_map[L1_D])
		delete l1_d;
	if (!dev_map[L1_I])
		delete l1_i;
	if (!dev_map[L2])
		delete l2;
	if (!dev_map[L3])
		delete l3;
	if (!dev_map[RAM])
		delete ram;
	if (!dev_map[SWAP])
		delete swap;
	if (!dev_map[TLB])
		delete tlb;
	if (!dev_map[PT])
		delete pg_table;
}

bool MemHierarchy::dev_map[dev_num] = {false, };

//! Helpers for hierarchy walking
mem_t MemHierarchy::get_type(QString & name)
{
	if (!name2type.contains(name))
		return GENERIC;
	else
		return name2type.value(name);
}

QString MemHierarchy::get_name(mem_t type)
{
	if (!type2name.contains(type))
		return QString();
	else
		return type2name.value(type);
}

//! Connect configured devices to proper first/last device pointers
void MemHierarchy::check_integrity()
{
	first_inst = NULL;
	first_data = NULL;
	last_dev = NULL;

	for (int i = 0; i < (mem_t) SWAP; i++) {
		MemDevice *p = assign_p((mem_t) i);

		if (p && i == L1_D)
			first_data = p;

		if (p && i == L1_I) { //! In case of non-splitted L1
			first_inst = p;
			if (!first_data)
				first_data = p;
		}

		if (p && i > L1_D && i > L1_I) {
			if (!first_inst)
				first_inst = p;
			if (!first_data)
				first_data = p;
		}

		if (p)
			last_dev = p;
	}

	if (!first_inst || !first_data || !last_dev)
		throw ConfigErrorEmptyHierarchy();
}

inline MemDevice * MemHierarchy::assign_p(mem_t type)
{
	switch(type) {
		case L1_D:
			return l1_d;
			break;
		case L1_I:
			return l1_i;
			break;
		case L2:
			return l2;
			break;
		case L3:
			return l3;
			break;
		case RAM:
			return ram;
			break;
		case SWAP:
			return swap;
			break;
		case TLB:
			return tlb;
			break;
		case PT:
			return pg_table;
			break;
		default:
			return NULL;
	}
}

int MemHierarchy::next_dev(void)
{
	MemDevice * next = NULL;
	int ret = 1;
	int i;

	if (!sim_dev || sim_dev == last_dev)
		return ret;

	mem_t type = sim_dev->get_type(); //! Getting type of the current device
	if ((mem_t) type >= SWAP)
		return ret;

	if (type == L1_D)
		i = type + 2;
	else
		i = type + 1;;

	while ((mem_t) i < SWAP) {
		if (dev_map[i] == true) {
			next = assign_p((mem_t) i);
			break;
		}
		i++;
	}

	if (next) {
		sim_dev = next;
		ret = 0;
	}

	return ret;
}

int MemHierarchy::on_last_dev(void)
{
	//qDebug() << "onlastdev" << sim_dev << "vs" << last_dev;
	return (sim_dev == last_dev);
}

void MemHierarchy::clean_caches()
{
	MemDeviceCache * ptr;

	for (int i = 0; i <= cache_num; i++) {
		ptr = (MemDeviceCache *) assign_p((mem_t) i);
		if (ptr) {
			ptr->refresh_cache();
			ptr->stats.reset_stats();
		}
	}
	if (tlb) {
		tlb->refresh_cache();
		ptr->stats.reset_stats();
	}
}

void MemHierarchy::reset_devs()
{
	sim_dev = NULL;
	first_inst = NULL;
	first_data = NULL;
	last_dev = NULL;
	clean_caches();
	//TODO ram, swap
}

void MemHierarchy::commit_changes(void)
{
	check_integrity();
}

/*! delete_cache(int type, MemDeviceCache *new_cache)
\brief Delete/modify cache of given type
\param type Type of cache for deleting
\param new_cache Pointer to the new cache object, otherwise NULL for deleting current
*/

void MemHierarchy::delete_cache(mem_t type, MemDeviceCache *new_cache)
{
	MemDeviceCache *old_ptr = NULL;

	switch (type) {
		case L1_D:
			old_ptr = l1_d;
			l1_d = new_cache;
			break;
		case L1_I:
			old_ptr = l1_i;
			l1_i = new_cache;
			break;
		case L2:
			old_ptr = l2;
			l2 = new_cache;
			break;
		case L3:
			old_ptr = l3;
			l3 = new_cache;
			break;
		default:
			break;
	}

	if (old_ptr)
		delete old_ptr;

	if (!new_cache)
		dev_map[type] = false;
}

void MemHierarchy::add_cache(mem_t type, int latency, long size, long lsize, long assoc)
{
	MemDeviceCache * new_cache;

	try {
		new_cache = new MemDeviceCache(type, latency, size, lsize, assoc);
	} catch (std::bad_alloc & ex) {
		throw MemErrorAlloc();
	}

	delete_cache(type, new_cache);
	dev_map[type] = true;
}

//TODO
void MemHierarchy::delete_ram(MemDeviceRAM *new_ram)
{
	if (ram)
		delete ram;

	ram = new_ram;

	if (!new_ram)
		dev_map[RAM] = false;
}

void MemHierarchy::add_ram(int latency)
{
	MemDeviceRAM * new_ram;

	try {
		new_ram = new MemDeviceRAM(latency);
	} catch (std::bad_alloc & ex) {
		throw MemErrorAlloc();
	}

	delete_ram(new_ram);
	dev_map[RAM] = true;
}

//TODO
void MemHierarchy::delete_swap(MemDeviceSwap *new_swap)
{
	if (swap)
		delete swap;

	swap = new_swap;

	if (!new_swap)
		dev_map[SWAP] = false;
}

void MemHierarchy::add_swap(int latency)
{
	MemDeviceSwap * new_swap;

	try {
		new_swap = new MemDeviceSwap(latency);
	} catch (std::bad_alloc & ex) {
		throw MemErrorAlloc();
	}

	delete_swap(new_swap);
	dev_map[SWAP] = true;
}

void MemHierarchy::delete_tlb(MemDeviceTlb *new_tlb)
{
	if (tlb)
		delete tlb;

	tlb = new_tlb;

	if (!new_tlb)
		dev_map[TLB] = false;
}

void MemHierarchy::add_tlb(long entries, long entrysize, int latency)
{
	MemDeviceTlb * new_tlb;

	try {
		new_tlb = new MemDeviceTlb(entries, entrysize, latency);
	} catch (std::bad_alloc & ex) {
		throw MemErrorAlloc();
	}

	delete_tlb(new_tlb);
	dev_map[TLB] = true;
}

void MemHierarchy::delete_page_table(MemPageTable *new_pg_table)
{
	if (pg_table)
		delete pg_table;

	pg_table = new_pg_table;

	if (!new_pg_table)
		dev_map[PT] = false;
}

void MemHierarchy::add_page_table(long depth, int latency)
{
	MemPageTable * new_pg_table;

	try {
		new_pg_table = new MemPageTable(depth, latency);
	} catch (std::bad_alloc & ex) {
		throw MemErrorAlloc();
	}

	delete_page_table(new_pg_table);
	dev_map[PT] = true;
}

void MemHierarchy::config_cache(mem_t type, QString & param, long value)
{
	MemDeviceCache *cache = (MemDeviceCache *) assign_p(type);

	if (param == "size")
		cache->set_size(value);
	else if (param == "lsize")
		cache->set_lsize(value);
	else if (param == "assoc")
		cache->set_assoc(value);
	else if (param == "latency")
		cache->set_latency(value);
	else
		throw UserInputBadArg();
}

void MemHierarchy::config_ram(QString & param, long value)
{
	if (param == "latency")
		ram->set_latency(value);
}

void MemHierarchy::config_swap(QString & param, long value)
{
	if (param == "latency")
		swap->set_latency(value);
}

void MemHierarchy::config_tlb(QString & param, long value)
{
	if (param == "latency")
		tlb->set_latency(value);
	else if (param == "entries")
		tlb->set_entries(value);
	else
		config_cache(TLB, param, value);
}

void MemHierarchy::config_page_table(QString & param, long value)
{
}

QString MemHierarchy::show_cache_stats(mem_t type, int parseable)
{
	MemDeviceCache *ptr = NULL;

	ptr = (MemDeviceCache *) assign_p(type);

	if (!ptr)
		return QString();

	MemDeviceCacheStats stats = ptr->get_stats();

	float hit_ratio;
	if (stats.get_ac())
		hit_ratio = (1 - static_cast<float>(stats.get_miss())/stats.get_ac())*100.0f;
	else
		hit_ratio = 0.0f;

	if (!parseable)
		return QString("%1:\n\taccess:%2\n\tmiss:%3\n\thit ratio:%4\%\n")
			.arg(get_name(type))
			.arg(stats.get_ac())
			.arg(stats.get_miss())
			.arg(hit_ratio);
	else
		return QString("%1acc:%2 %1missratio:%3 ").arg(get_name(type)).arg(stats.get_ac()).arg(hit_ratio);
}

QString MemHierarchy::show_ram_stats(int parseable)
{
	MemDeviceRAM *ptr = ram;

	if (!ptr)
		return QString();

	MemDeviceRAMStats & stats = ptr->get_stats();

	if (!parseable)
		return QString("%1:\n\taccess:%2\n\tmiss:%3\n")
			.arg("ram")
			.arg(stats.get_ac())
			.arg(stats.get_miss());
	else
		return QString("ramacc:%1 rammissratio:%2 ").arg(stats.get_ac()).arg(stats.get_miss());
}

QString MemHierarchy::show_swap_stats(int parseable)
{
	MemDeviceSwap *ptr = swap;

	if (!ptr)
		return QString();

	MemDeviceSwapStats & stats = ptr->get_stats();

	if (!parseable)
		return QString("%1:\n\taccess:%2\n\tmiss:%3\n")
			.arg("swap")
			.arg(stats.get_ac())
			.arg(stats.get_miss());
	else
		return QString("swapacc:%1 swapmissval:%2 ").arg(stats.get_ac()).arg(stats.get_miss());
}

QString MemHierarchy::show_tlb_stats(int parseable)
{
	return show_cache_stats(TLB, parseable);
}

QString MemHierarchy::show_page_table_stats(int parseable)
{
	MemPageTable *ptr = pg_table;

	if (!ptr)
		return QString();

	MemPageTableStats & stats = ptr->get_stats();

	if (!parseable)
		return QString("%1:\n\topts:%2")
			.arg("page_table")
			.arg(stats.get_opts());
	else
		return QString("pgtableopts:%1 ").arg(stats.get_opts());
}

QString MemHierarchy::show_stats(int parseable)
{
	QString out;

	for (int i = 0; i < dev_num; i++) {
		switch ((mem_t) i) {
			case L1_D:
			case L1_I:
			case L2:
			case L3:
				out += show_cache_stats((mem_t) i, parseable);
				break;
			case RAM:
				out += show_ram_stats(parseable);
				break;
			case SWAP:
				out += show_swap_stats(parseable);
				break;
			case TLB:
				out += show_tlb_stats(parseable);
				break;
			case PT:
				out += show_page_table_stats(parseable);
				break;
			default:
				break;
		}
	}

	return out;
}

QString MemHierarchy::show_cache(mem_t type)
{
	MemDeviceCache *ptr = NULL;

	ptr = (MemDeviceCache *) assign_p(type);

	if (!ptr)
		return QString();
	
	return QString("%1:\n\tlatency:%2\n\tsize:%3\n\tlsize:%4\n\tassoc:%5\n")
			.arg(get_name(type))
			.arg(ptr->get_latency())
			.arg(ptr->get_size())
			.arg(ptr->get_lsize())
			.arg(ptr->get_assoc());
}

QString MemHierarchy::show_ram()
{
	MemDeviceRAM *ptr = ram;

	if (!ptr)
		return QString();

	return QString ("ram:\n\tlatency:%1\n")
			.arg(ptr->get_latency());
}

QString MemHierarchy::show_swap()
{
	MemDeviceSwap *ptr = swap;

	if (!ptr)
		return QString();

	return QString("swap:\n\tlatency:%1\n")
			.arg(ptr->get_latency());
}

QString MemHierarchy::show_tlb()
{
	MemDeviceTlb *ptr = tlb;

	if (!ptr)
		return QString();

	return QString("tlb:\n\tlatency:%1\n\tmax_entries:%2\n")
			.arg(ptr->get_latency())
			.arg(ptr->get_entries());
}

QString MemHierarchy::show_page_table()
{
	MemPageTable *ptr = pg_table;

	if (!ptr)
		return QString();

	return QString("pg_table:\n\tlatency:%1\n\tdepth:%2\n")
			.arg(ptr->get_latency())
			.arg(ptr->get_depth());
}


QString MemHierarchy::show_devs()
{
	QString out;

	for (int i = 0; i < dev_num; i++) {
		switch ((mem_t) i) {
			case L1_D:
			case L1_I:
			case L2:
			case L3:
				out += show_cache((mem_t) i);
				break;
			case RAM:
				out += show_ram();
				break;
			case SWAP:
				out += show_swap();
				break;
			case TLB:
				out += show_tlb();
				break;
			case PT:
				out += show_page_table();
				break;
			default:
				break;
		}
	}

	return out;
}

quint64 * MemHierarchy::get_acc(mem_t type, long * sets, long * assoc)
{
	MemDeviceCache * cache = (MemDeviceCache *) assign_p(type);

	if (!cache)
		return NULL;

	*sets = cache->get_sets();
	*assoc = cache->get_assoc();
	return cache->accmap;
}
