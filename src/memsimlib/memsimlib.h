#ifndef MEMSIMLIB_H
#define MEMSIMLIB_H
//! Interface of header of memsimlib
/*!
 * A basic interface header file of MemSim library routines.
 * \file memsim.h
 *
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include <QtCore/QtGlobal>
#include <Qt>
#include <QString>
#include <QDir>
#include <QApplication>
#include <QFile>
#include <QStringListModel>
#include <QDebug>
#include <QSharedPointer>

#if defined(MYSHAREDLIB_LIBRARY)
#  define MEMSIMLIB_EXPORT Q_DECL_EXPORT
#else
#  define MEMSIMLIB_EXPORT Q_DECL_IMPORT
#endif

//! Return value when address has been hit
const int HIT = 0;
//! Return value when address has been missed
const int FAULT = 1;

//! An enum including possible states of simulator
enum simstate {STOP = 0, RUNNING, STEP};

class MemTrace;
class MemSimulation;
class MemSimulationObj;


//! Interface description of loaded memory trace
/*!
 * Library user won't need to touch it directly most likely
 */

class MEMSIMLIB_EXPORT MemTraceObj
{
    public:
	//! A constructor.
	/*!
	 * \param[in] path A path of trace file
	 */
	MemTraceObj(QString path);
	//! A destructor.
	~MemTraceObj();
	//! Dump processed trace to QString
	/*!
	 * \return QStringList that includes trace
	 */
	QStringListModel *dump_trace();
	friend class MemSimulationObj;
    private:
	//! Library internal MemTrace class
	/*!
	 * \sa ::MemTrace
	 */
	::MemTrace *obj;
	//! Trace model for MVR scheme
	QStringListModel *trace_model;
};

//! Interface classdeclaration.
/*!
 * Simulator interfaces should access all library routines through this
 * interface.
 */
class MEMSIMLIB_EXPORT MemSimulationObj
{
    public:
	//! A constructor.
	MemSimulationObj();
	//! A destructor.
	~MemSimulationObj();
	//! Initialize existing configuration.
	/*!
	 * \sa MemSimulation::settings
	 */
	void load_configuration();
	//! Start simulation of a trace
	/*!
	 * \param[in] trace_id id of loaded trace
	 * \see show_traces(void)
	 */
	int run_trace(int trace_id);
	//! Loads trace file into memory
	/*!
	 * \param[in] path path to trace file
	 */
	int load_trace(QString & path);
	//! Configure given parameter of the simulation
	/*!
	 * \param[in] object object of memory hierarchy described by name
	 * \param[in] param parameter of object to configure
	 * \param[in] value new value of parameter of object
	 */
	void config_param(QString & object, QString & param, QString value);
	//! Get given parameter of the simulation
	/*!
	 * \param[in] object object of memory hierarchy described by name
	 * \param[in] param parameter of object to configure
	 * \return QVarint value of parameter
	 */
	QVariant get_param(QString & object, QString & param);
	//! Add device to model
	/*!
	 * \param[in] name Name of the device for adding
	 */
	void add_device(QString & name);
	//! Remove device from model
	/*!
	 * \param[in] name Name of the device for removal
	 */
	void remove_device(QString & name);
	//! Returns all loaded traces
	/*!
	 * \return List of all traces in formated QString
	 */
	QString show_traces(void);
	//! Returns stats of model components
	/*!
	 * \return Statistics in formated QString
	 */
	QString show_stats(void);
	//! Returns stats of model components
	/*!
	 * \return Statistics in formated QString
	 */
	QString show_statsall(void);
	//! Returns list of components of model
	/*!
	 * \return List of model components
	 */
	QString show_hierarchy(void);
	//! Returns raw trace
	QStringListModel *dump_trace(int idx);
	//! Return state of page table in model
	bool has_pg_table();
	//! Split/unsplit L1 cache
	void set_l1split(bool val);
    private:
	//! Core MemSimulation object
	/*!
	 * \sa ::MemSimulation
	 */
	::MemSimulation *obj;
	//! Traces loaded into simulator
	QMap<int, QSharedPointer<MemTraceObj> > traces;
	//! Paths of trace files
	QMap<int, QString> t_paths;
	//! Counter for assigning trace IDs
	int trace_id;
};

#endif
