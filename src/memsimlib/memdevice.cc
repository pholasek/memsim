/*!
 * @file memdevice.cc
 * Source file of MemDevice class.
 *
 * \brief Base class for memory devices in hierarchy
 *
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memdevice.h"

/*
 * MemDevice
 */

MemDevice::MemDevice(mem_t type = GENERIC, int latency = 1)
{
        this->latency = latency;
        this->type = type;
}

/*
 * MemDeviceCache
 */

MemDeviceCache::MemDeviceCache() : MemDevice(L1_D, 1) {}

MemDeviceCache::MemDeviceCache(mem_t type, int lat, quint64 size, long lsize, long assoc) :
        MemDevice(type, lat), tags(NULL)
{
        this->size = size;
        this->lsize = lsize;
        this->assoc = assoc;

        sets = (size / lsize) / assoc;
        sets_min_1 = sets - 1;
        line_size_bits = log2(lsize);
        tag_shift = line_size_bits + log2(sets);

	tags = new quint64[sets * assoc]; //! Guarantee of 64-bit space
	memset(tags, 0, sizeof(quint64) * sets * assoc);
	accmap = new quint64[sets * assoc]; //! Guarantee of 64-bit space
	memset(accmap, 0, sizeof(quint64) * sets * assoc);
}

MemDeviceCache::~MemDeviceCache()
{
	delete tags;
	delete accmap;
}

void MemDeviceCache::refresh_cache()
{
        sets = (size / lsize) / assoc;
        sets_min_1 = sets - 1;
        line_size_bits = log2(lsize);
        tag_shift = line_size_bits + log2(sets);

	if (!tags)
		delete tags;
	tags = new quint64[sets * assoc];
	memset(tags, 0, sizeof(quint64) * sets * assoc);
	if (!accmap)
		delete accmap;
	accmap = new quint64[sets * assoc];
	memset(accmap, 0, sizeof(quint64) * sets * assoc);
}

void MemDeviceCache::set_size(quint64 size)
{
	size = size;
	refresh_cache();
}

void MemDeviceCache::set_lsize(long lsize)
{
	lsize = lsize;
	refresh_cache();
}

void MemDeviceCache::set_assoc(long assoc)
{
	assoc = assoc;
	refresh_cache();
}

void MemDeviceCache::set_policy(policy_t policy) { pol = policy; }
/*
 * Most of the source in this method was copied from Cachegrind tool, cg_sim.c
 */

int MemDeviceCache::do_mem_ref(quint64 addr, quint64 size)
{
   unsigned int  set1 = (addr >> line_size_bits) & (sets_min_1);
   unsigned int  set2 = ((addr+size-1) >> line_size_bits) & (sets_min_1);
   unsigned long int tag = addr >> tag_shift;
   unsigned long int tag2;
   int i, j;
   bool is_miss = false;
   quint64* set;
   quint64* acc;

   stats.inc_ac();

   /* First case: word entirely within line. */
   if (set1 == set2) {

      set = &(tags[set1 * assoc]);
      acc = &(accmap[set1 * assoc]);

      /* This loop is unrolled for just the first case, which is the most */
      /* common.  We can't unroll any further because it would screw up   */
      /* if we have a direct-mapped (1-way) cache.                        */
      if (tag == set[0]) {
         acc[0] += 1;
         return HIT;
      }
      /* If the tag is one other than the MRU, move it into the MRU spot  */
      /* and shuffle the rest down.                                       */
      for (i = 1; i < assoc; i++) {
         if (tag == set[i]) {
	    acc[i] += 1;
            for (j = i; j > 0; j--) {
               set[j] = set[j - 1];
            }
            set[0] = tag;
            return HIT;
         }
      }

      /* A miss;  install this tag as MRU, shuffle rest down. */ //FIXME
      for (j = assoc - 1; j > 0; j--) {
         set[j] = set[j - 1];
      }
      set[0] = tag;
      stats.inc_miss();
      return FAULT;

   /* Second case: word straddles two lines. */
   /* Nb: this is a fast way of doing ((set1+1) % L.sets) */
   } else if (((set1 + 1) & (sets_min_1)) == set2) {
      set = &(tags[set1 * assoc]);
      acc = &(accmap[set1 * assoc]);
      if (tag == set[0]) {
	 acc[0] += 1;
         goto block2;
      }
      for (i = 1; i < assoc; i++) { //FIXME
         if (tag == set[i]) { /*HIT*/
	    acc[i] += 1;
            for (j = i; j > 0; j--) {
               set[j] = set[j - 1];
            }
            set[0] = tag;
            goto block2;
         }
      }
      for (j = assoc - 1; j > 0; j--) {
         set[j] = set[j - 1];
      }
      set[0] = tag;
      is_miss = true;
block2:
      set = &(tags[set2 * assoc]);
      acc = &(accmap[set2 * assoc]);
      tag2 = (addr+size-1) >> tag_shift;
      if (tag2 == set[0]) {
	 acc[0] += 1;
         goto miss_treatment;
      }
      for (i = 1; i < assoc; i++) { //FIXME
         if (tag2 == set[i]) { /*HIT*/
	    acc[i] += 1;
            for (j = i; j > 0; j--) {
               set[j] = set[j - 1];
            }
            set[0] = tag2;
            goto miss_treatment;
         }
      }
      for (j = assoc - 1; j > 0; j--) {
         set[j] = set[j - 1];
      }
      set[0] = tag2;
      is_miss = true;
miss_treatment:
      if (is_miss) {
	      stats.inc_miss();
	      return FAULT;
      }

   } else {
           //qDebug() << "Cache panic!";
   }
   return FAULT;
}

/*--------------------------------------------------------------------*/
/*--- end                                                 cg_sim.c ---*/
/*--------------------------------------------------------------------*/

void MemDeviceTlb::set_entries(long entries)
{
	this->entries = entries;
	this->size = entries * entrysize * 4;
	refresh_cache();
}

void MemDeviceTlb::set_entrysize(long entrysize)
{
	this->entrysize = entrysize;
	this->size = entries * entrysize * 4;
	refresh_cache();
}

void MemDeviceCacheStats::reset_stats()
{
        ac = 0;
        miss = 0;
}

long MemDeviceCacheStats::get_ac() { return ac; }
long MemDeviceCacheStats::get_miss() { return miss; }
void MemDeviceCacheStats::inc_ac() { ac++; }
void MemDeviceCacheStats::inc_miss() { miss++; }
void MemDeviceCacheStats::inc_opts() { opts++; }


/*
 * MemDeviceEvent
 */

MemDeviceEvent::MemDeviceEvent(MemDevice * memdev, mem_event op) : op(op), dev(memdev), info() {}

MemDeviceEvent::MemDeviceEvent(MemDevice * memdev, mem_event op, ev_info info) : op(op), dev(memdev), info(info) {}

MemDeviceEvent::~MemDeviceEvent() {}

void MemDeviceEvent::set_info(quint64 addr, quint64 size)
{
	info = ev_info(addr, size);
}

int MemDeviceEvent::do_op()
{
	int ret = 0;

	if (info.size == 0 && (op == RREF || op == WREF))
		return -1; //TODO vyjimky

	switch (op) {
		case RREF:
		case WREF:
			ret = dev->do_mem_ref(info.addr, info.size);
			break;
		case INST:
			ret = dev->do_mem_ref(info.addr, info.size);
			break;
	}

	return ret;
}

/*
 * MemDeviceRAM
 */

MemDeviceRAM::MemDeviceRAM(int latency) : MemDevice(RAM, latency) {}

int MemDeviceRAM::do_mem_ref(quint64 addr, quint64 size)
{
	stats.inc_ac();
	return HIT;
}

/*
 * MemDeviceSwap
 */
MemDeviceSwap::MemDeviceSwap(int latency) : MemDevice(SWAP, latency) {}

int MemDeviceSwap::do_mem_ref(quint64 addr, quint64 size)
{
	stats.inc_ac();
	return HIT;
}

/*
 * MemDeviceCpu
 */

int MemDeviceCpu::do_mem_ref(quint64 addr, quint64 size)
{
	return 0;
}

void MemDeviceCpu::state_watchdog(quint64 curr_t)
{
	if (!curr_t || curr_t % freq != 0)
		return;

	/*
	switch (state) {
		case BUSY:
	}
	*/
}

/*
 * MemPageTable
 */

int MemPageTable::do_mem_ref(quint64 addr, quint64 size)
{
	stats.inc_opts();

	return qrand() % 2 ? HIT : FAULT;
}
