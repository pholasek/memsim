#ifndef MEMSIMUL_H
#define MEMSIMUL_H

/*!
 * @file memsimul.h
 * Header file of MemSimulation class
 *
 * \brief MemSimulation class encapsulates simulated memory hierarchy
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memtrace.h"
#include "memdevice.h"

enum simstate {STOP = 0, RUN, STEP};

class MemSimulation
{
        public:
                MemSimulation();
                ~MemSimulation();
		void init_memsim();
		void reset_memsim();
		void start_memsim();
		void stop_memsim();
                void dump_stats(); //TODO
                void sim_trace(QString f_name); // MOVE TO PRIV
        private:
		int simid;
		enum simstate state;
                MemTrace trace;
                MemDevice *root_data;
                MemDevice *root_inst;
};

#endif
