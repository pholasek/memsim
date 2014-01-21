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

#include <QSettings>
#include "memtrace.h"
#include "memcalend.h"
#include "memsimlib.h"
#include "memhierarchy.h"
#include "memexcept.h"


class MemSimCalend;
class MemDevice;
class MemTrace;

class MemSimulation
{
        public:
                MemSimulation();
                ~MemSimulation();
		void init_memsim();
		void reset_memsim();
		void start_memsim();
		void stop_memsim();
                void sim_trace(MemTrace & trace);
		void set_cfg_param(QString & object, QString & param, QString & value);
		QVariant get_cfg_param(QString & object, QString & param);
		void add_device(QString & name);
		void remove_device(QString & name);
		QString show_devs();
		QString show_statsall();
        private:
		MemDevice * process_inst(const MemTraceEntry & e);
		void init_devices();
		void process_cache(QStringList & groups, QString name);
		void process_ram(QStringList & groups);
		void process_swap(QStringList & groups);
		void process_devices(QStringList & groups);
		void process_settings(QStringList & groups);
		void init_settings();
		enum simstate state;
		MemSimCalend cal;
		MemHierarchy devs;
		QSettings *settings;
};

#endif
