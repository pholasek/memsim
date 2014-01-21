#ifndef MEMSIMLIB_H
#define MEMSIMLIB_H

/*!
 * @file memsim.h
 * Basic header file of MemSim library routines.
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
#include <QDebug>
#include <QSharedPointer>

#if defined(MYSHAREDLIB_LIBRARY)
#  define MEMSIMLIB_EXPORT Q_DECL_EXPORT
#else
#  define MEMSIMLIB_EXPORT Q_DECL_IMPORT
#endif

const int HIT = 0;
const int FAULT = 1;

enum simstate {STOP = 0, RUNNING, STEP};

class MemTrace;
class MemSimulation;
class MemSimulationObj;

//! Interface declarations

class MEMSIMLIB_EXPORT MemTraceObj
{
    public:
	MemTraceObj(QString path);
	~MemTraceObj();
	QString dump_trace();
	friend class MemSimulationObj;
    private:
	::MemTrace *obj;
};

class MEMSIMLIB_EXPORT MemSimulationObj
{
    public:
	MemSimulationObj();
	~MemSimulationObj();
	void load_configuration();
	int run_trace(int trace_id);
	int load_trace(QString & path);
	void config_param(QString & object, QString & param, QString & value);
	void add_device(QString & name);
	void remove_device(QString & name);
	QString show_traces(void);
	QString show_stats(void);
	QString show_statsall(void);
	QString show_hierarchy(void);
    private:
	::MemSimulation *obj;
	QMap<int, QSharedPointer<MemTraceObj> > traces; //! Loaded traces
	QMap<int, QString> t_paths; //! Trace paths
	int trace_id;
};

#endif
