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
#include "memtrace.h"

/*
 * MemDevice
 */

MemDevice::MemDevice(int latency = 0, MemDevice *parent = NULL)
{
        this->latency = latency;
        this->parent = parent;
}

/*
 * MemDeviceCache
 */

MemDeviceCache::MemDeviceCache() : MemDevice(0, NULL)
{
}

MemDeviceCache::MemDeviceCache(int lat, long size, long lsize, long assoc, MemDevice *parent) :
        MemDevice(lat, parent)
{
        this->size = size;
        this->lsize = lsize;
        this->assoc = assoc;

        sets =          (size / lsize) / assoc;
        sets_min_1 =    sets - 1;
        line_size_bits = log2(lsize);
        tag_shift =     line_size_bits + log2(sets);

        // if (assoc = 1) .. TODO - vypisy

        tags = (unsigned long int *) calloc(sets * assoc, sizeof(unsigned long int)); // should be zero-ed
}

MemDeviceCache::~MemDeviceCache()
{
        free(tags);
}

MemDeviceCacheStats MemDeviceCache::get_stats()
{
        return stats;
}

/*
 * Most of the source in this method was copied from Cachegrind tool, cg_sim.c
 */

void MemDeviceCache::do_mem_ref(quint64 addr, long size)
{
   unsigned int  set1 = (addr >> line_size_bits) & (sets_min_1);
   unsigned int  set2 = ((addr+size-1) >> line_size_bits) & (sets_min_1);
   unsigned long int tag = addr >> tag_shift;
   unsigned long int tag2;
   int i, j;
   bool is_miss = false;
   unsigned long int* set;

   stats.inc_ac();

   /* First case: word entirely within line. */
   if (set1 == set2) {

      set = &(tags[set1 * assoc]);

      /* This loop is unrolled for just the first case, which is the most */
      /* common.  We can't unroll any further because it would screw up   */
      /* if we have a direct-mapped (1-way) cache.                        */
      if (tag == set[0]) {
         return;
      }
      /* If the tag is one other than the MRU, move it into the MRU spot  */
      /* and shuffle the rest down.                                       */
      for (i = 1; i < assoc; i++) {
         if (tag == set[i]) {
            for (j = i; j > 0; j--) {
               set[j] = set[j - 1];
            }
            set[0] = tag;
            return;
         }
      }

      /* A miss;  install this tag as MRU, shuffle rest down. */
      for (j = assoc - 1; j > 0; j--) {
         set[j] = set[j - 1];
      }
      set[0] = tag;
      //MISS_TREATMENT;
      stats.inc_miss();
      if (child != NULL)
              child->do_mem_ref(addr, size);
      return;

   /* Second case: word straddles two lines. */
   /* Nb: this is a fast way of doing ((set1+1) % L.sets) */
   } else if (((set1 + 1) & (sets_min_1)) == set2) {
      set = &(tags[set1 * assoc]);
      if (tag == set[0]) {
         goto block2;
      }
      for (i = 1; i < assoc; i++) {
         if (tag == set[i]) {
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
      tag2 = (addr+size-1) >> tag_shift;
      if (tag2 == set[0]) {
         goto miss_treatment;
      }
      for (i = 1; i < assoc; i++) {
         if (tag2 == set[i]) {
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
              if (child != NULL)
                      child->do_mem_ref(addr, size);
      }

   } else {
           qDebug() << "Cache panic!";
   }
   return;
}

/*--------------------------------------------------------------------*/
/*--- end                                                 cg_sim.c ---*/
/*--------------------------------------------------------------------*/



void MemDeviceCacheStats::reset_stats()
{
        ac = 0;
        miss = 0;
}

long MemDeviceCacheStats::get_ac() { return ac; }
long MemDeviceCacheStats::get_miss() { return miss; }
void MemDeviceCacheStats::inc_ac() { ac++; }
void MemDeviceCacheStats::inc_miss() { miss++; }


/*
 * MemDeviceEvent
 */

MemDeviceEvent::MemDeviceEvent(MemDevice *memdev, mem_event op)
{
	this->op = op;
	dev = memdev;
}

MemDeviceEvent::do_op(void)
{
	int ret;

	switch (this->op) {
		case RREF:
		case WREF:
			dev->do_mem_ref();
	}
}



