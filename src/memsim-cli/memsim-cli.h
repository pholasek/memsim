#ifndef MEMSIMCLI_H
#define MEMSIMCLI_H
/*
 * Console client header file
 * Author : Petr Holasek, xholas02@stud.fit.vutbr.cz
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
	MemSimCli(QObject *parent = 0, int argc = 0, char **argv = NULL) : QObject(parent), argc(argc), argv(argv) {}
public slots:
	void run();
signals:
	void finished();
private:
	int argc;
	char **argv;
	void process_command(int cmd, QStringList & args);
	int load_trace(QStringList & args);
	int run_trace(QStringList & args);
	int config_param(QStringList & args);
	int add_device(QStringList & args);
	int delete_device(QStringList & args);
	QString show(QStringList & args);
	MemSimulationObj sim;
};

#endif
