/*
 * @file memsimulation.cc
 * Source file of MemSimulation class.
 *
 * \brief Memory simulation base class
 *
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memsim.h"
#include "memsimul.h"
#include "memtrace.h"
#include "memdevice.h"

//! Constructor

MemSimulation::MemSimulation() //TODO settings in constructor CPUID recognize
{
	this->state = STOP;
}

//! Destructor

MemSimulation::~MemSimulation()
{
        delete root_data->get_child();
        delete root_data;
        delete root_inst; // TODO delete whole hierarchy
}

//! Methods
void MemSimulation::init_memsim()
{
	MemDevice *LL;

        root_data = new MemDeviceCache(0, 65536, 64, 2 ,NULL); //TODO - inicializace hierarchie zarizeni - prepracovat
        root_inst = new MemDeviceCache(0, 65536, 64, 2 ,NULL);
        LL = new MemDeviceCache(0, 262144, 64, 8, root_data);
        root_data->set_child(LL);
        root_inst->set_child(LL);
}

void MemSimulation::start_memsim()
{
	this->state = RUN;
}

void MemSimulation::stop_memsim()
{
	this->state = STOP;
}

void MemSimulation::reset_memsim()
{
}

void MemSimulation::sim_trace(QString f_name)
{
   trace.get_trace(f_name); // TODO 
   for (int i = 0; i < trace.get_size(); ++i) {
         MemTraceEntry e = trace.at(i);
         qDebug() << e.type << "-" << e.address << "-" << e.size;
         if (e.type == 'I')
                 cal.new_ref_event(root_inst, WREF, e.address, e.size, root_inst->get_latency(), 0);
         else if (e.type == 'L')
                 cal.new_ref_event(root_inst, RREF, e.address, e.size, root_inst->get_latency(), 0);
         else
		 qDebug() << "Invalid trace line.";
   }
}

void MemSimulation::dump_stats()
{
   // TODO - walk through devices
   MemDeviceCacheStats stats_L1d = root_data->get_stats();
   MemDeviceCacheStats stats_L1i = root_inst->get_stats();
   MemDeviceCacheStats stats_LL = root_data->get_child()->get_stats();

   // TODO - statistiky
   qDebug() << "L1d : ref = " << stats_L1d.get_ac() << " , miss = " << stats_L1d.get_miss() << " , miss ratio = " << (float)stats_L1d.get_miss() / (float)stats_L1d.get_ac();
   qDebug() << "L1i : ref = " << stats_L1i.get_ac() << " , miss = " << stats_L1i.get_miss() << " , miss ratio = " << (float)stats_L1i.get_miss() / (float)stats_L1i.get_ac();
   qDebug() << "LL : ref = " << stats_LL.get_ac() << " , miss = " << stats_LL.get_miss() << " , miss ratio = " << (float)stats_LL.get_miss() / (float)stats_LL.get_ac();
}




