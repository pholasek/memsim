#ifndef MEMSIMUL_H
#define MEMSIMUL_H

//! Header file of MemSimulation class
/*!
 * \file memsimul.h
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

//! Class implementing basic simulator routines.
class MemSimulation
{
        public:
		//! A constructor.
                MemSimulation();
		//! A destructor.
                ~MemSimulation();
		//! Initialize simulator.
		void init_memsim();
		//! Put simulator to init state.
		void reset_memsim();
		//! Start simulation.
		void start_memsim();
		//! Stop simulation.
		void stop_memsim();
		//! Run simulation of given trace.
		/*!
		 * \param[in] trace Trace object for simulation.
		 * \sa ::MemTrace
		 */
                void sim_trace(MemTrace & trace);
		//! Set parameter of object to value
		/*!
		 * \param[in] object Configured object.
		 * \param[in] param Parameter to be configured.
		 * \param[in] value New value of parameter.
		 */
		void set_cfg_param(QString & object, QString & param, QString & value);
		//! Get parameter of object.
		/*!
		 * \param[in] object Object in model.
		 * \param[in] param Parameter of object.
		 * \returns Value of param.
		 */
		QVariant get_cfg_param(QString & object, QString & param);
		//! Adds new device to model.
		/*!
		 * \param[in] name Name of device.
		 */
		void add_device(QString & name);
		//! Remove device from model.
		/*!
		 * \param[in] name Name of device.
		 */
		void remove_device(QString & name);
		//! Enable device
		/*!
		 * \param[in] name Name of device.
		 */
		void enable_device(QString & name);
		//! Disable device
		/*!
		 * \param[in] name Name of device.
		 */
		void disable_device(QString & name);
		//! Shows all devices in model
		/*!
		 * \return List of deviced by QString.
		 */
		QString show_devs();
		//! Shows all devices stats in model
		/*!
		 * \return List of all statistics of devices in model.
		 */
		QString show_statsall();
		//! Shows calendar statistics
		/*!
		 * \return Calendar statistics
		 */
		QString show_calendstats();
		//! Set split of L1 cache
		void set_l1split(bool val) { l1split = val; toggle_l1split(); }
		//! Return state of pg_table
		bool has_pg_table() { return devs.has_pg_table(); }
        private:
		//! Valid corectness of config parameter
		/*!
		 * \param[in] type mem_t object
		 * \param[in] param Parameter
		 * \param[in] value New value of parameter
		 */
		void valid_cfg_param(mem_t type, QString & param, quint64 value);
		//! Process single trace line
		/*
		 * \param[in] e Parsed trace line.
		 * \return MemDevice where will be the access scheduled.
		 */
		MemDevice * process_inst(const MemTraceEntry & e);
		//! Part of simulation of VM model
		mem_t search_vm(const MemTraceEntry & e);
		//! Init devices in model.
		void init_devices();
		//! Set caches in model according to existing settings.
		/*!
		 * \param[in,out] groups Groups of keys in QSettings.
		 * \param[in] name Name of cache.
		 */
		void process_cache(QStringList & groups, QString name);
		//! Set RAM in model according to existing settings.
		void process_ram(QStringList & groups);
		//! Set swap in model according to existing settings.
		void process_swap(QStringList & groups);
		//! Set tlb in model according to existing settings.
		void process_tlb(QStringList & groups);
		//! Set page table in model according to existing settings.
		void process_pg_table(QStringList & groups);
		//! Set devices in model according to existing settings.
		void process_devices(QStringList & groups);
		//! Set other attributes of simulator to existing settings.
		void process_settings(QStringList & groups);
		//! Set other model settings
		void process_model(QStringList & groups);
		//! Init settings.
		void init_settings();
		//! Renew L1 caches according to l1split value
		void toggle_l1split();
		//! State of the simulation.
		enum simstate state;
		//! Simulation calendar.
		MemSimCalend cal;
		//! Simulation model.
		MemHierarchy devs;
		//! Simulator settings.
		QSettings *settings;
		//! L1 split
		bool l1split;
};

#endif
