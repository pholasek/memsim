#ifndef MEMSIMCLI_H
#define MEMSIMCLI_H
//! CLI memsim client base class
/*!
 * Console client header file
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include <QtCore>
#include <QTextStream>
#include <QSharedPointer>
#include "../memsimlib/memsimlib.h"
#include "../memsimlib/memexcept.h"
#include "cmd-parser.h"

class MemSimCli : public QObject
{
    Q_OBJECT
public:
	//! A constructor of the class.
	/*! MemSimCli is a child of QObject object since running event loop */
	MemSimCli(QObject *parent = 0, int argc = 0, char **argv = NULL) : QObject(parent), argc(argc), argv(argv) {}
public slots:
	//! A slot and main function of the application triggering run of application
	void run();
signals:
	//! A signal emitted after finishing of application
	void finished();
private:
	//! A number of command line arguments
	int argc;
	//! An array of command line arguments
	char **argv;
	//! A function which process command line arguments
	/*!
	 * \param cmd a command type
	 * \param args list of arguments
	 */
	void process_command(int cmd, QStringList & args);
	//! A function which loads given trace
	/*!
	 * \param args name of trace to be loaded
	 */
	int load_trace(QStringList & args);
	//! A function which start simulation run of loaded trace
	/*!
	 * \param args id of trace for simulation
	 */
	int run_trace(QStringList & args);
	//! A function which can set config value of simulator or model
	/*!
	 * \param args list of parameter which would be configured and new value
	 */
	int config_param(QStringList & args);
	//! A function which adds new device into model
	/*!
	 * \param args name of the new device
	 */
	int add_device(QStringList & args);
	//! A function which delete device from model
	/*!
	 * \param args name of device for deleting
	 */
	int delete_device(QStringList & args);
	//! A function which can send various output to stdout
	/*!
	 * \param args what to show in the output
	 */
	QString show(QStringList & args);
	//! Interface class of MemSim library
	MemSimulationObj sim;
};

#endif
