/*
 * CLI of MemSim simulator
 * Author : Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include "memsim-cli.h"

const char *welcome_msg =
"\n ******************************\n\
 *                            *\n\
 *	MemSim CLI	      *\n\
 *	2014 (c)	      *\n\
 *			      *\n\
 ******************************\n\n";

const char *err_msg[] = {
	"Ok",
	"Too many aguments.\n",
	"Too few arguments.\n",
	"Unknown command.\n",
};

const char *help_msg = {"\
\tloadtrace <path>\tLoads trace into memory and assign id to it.\n\
\trun <id>\tRuns trace with given id.\n\
\tconfig <param> <value>\tConfigure simulation options and devices.\n\
\tadd <dev>\tAdd device to hierarchy.\n\
\tremove <dev>\tRemove device from hierarchy.\n\
\tTODO\n"
};

static QString get_input(void)
{
	QString input;
	QTextStream in(stdin);
	QTextStream out(stdout);

	out << QString("memsim>");
	out.flush();
	input = in.readLine();

	return input;
}

// Wrappers for library calls

int MemSimCli::load_trace(QStringList & args)
{
	return sim.load_trace(args[1]);
}

int MemSimCli::run_trace(QStringList & args)
{
	return sim.run_trace(args[1].toInt());
}

int MemSimCli::config_param(QStringList & args)
{
	sim.config_param(args[1], args[2], args[3]);

	return 0;
}

int MemSimCli::add_device(QStringList & args)
{
	sim.add_device(args[1]);

	return 0;
}

int MemSimCli::delete_device(QStringList & args)
{
	sim.remove_device(args[1]);

	return 0;
}

QString MemSimCli::show(QStringList & args)
{
	if (args[1] == "traces") {
		return sim.show_traces();
	} else if (args[1] == "stats") {
		return sim.show_stats();
	} else if (args[1] == "statsall") {
		return sim.show_statsall();
	} else if (args[1] == "devices") {
		return sim.show_hierarchy();
	} else {
		throw UserInputBadArg();
	}

	return QString(); // compiler objections
}

void MemSimCli::process_command(int cmd, QStringList & args)
{
	int ret = 0;
	QString retmsg;
	QTextStream out(stdout);

	try {
		switch (cmd) {
			case LOAD:
				ret = load_trace(args);
				out << "Successfully loaded trace id: " << ret;
				break;
			case RUN:
				ret = run_trace(args);
				out << "Simulation completed.";
				break;
			case CONFIG:
				ret = config_param(args);
				out << QString("%1.%2 = %3").arg(args[1]).arg(args[2]).arg(args[3]);
				break;
			case ADD:
				ret = add_device(args);
				out << QString("Device %1 has been added.").arg(args[1]);
				break;
			case REMOVE:
				ret = delete_device(args);
				out << QString("Device %1 has been removed.").arg(args[1]);
				break;
			case HELP:
				out << help_msg;
				break;
			case SHOW:
				out << show(args);
				break;

		}
	} catch (const TraceIOFile &ex) {
		out << ex.what() << " trace file error.";
	} catch (const UserInputBadTraceId &ex) {
		out << ex.what() << " non-existing trace ID.";
	} catch (const UserInputBadArg &ex) {
		out << ex.what() << " Wrong input argument.";
	} catch (const MemErrorAlloc &ex) {
		out << ex.what() << " Allocation error.";
	} catch (const ConfigErrorFileAccess &ex) {
		out << ex.what() << " Configuration file access failure.";
	} catch (const ConfigErrorWrongDevice &ex) {
		out << ex.what() << " Non-existing device has been chosen.";
	} catch (const ConfigErrorEmptyHierarchy &ex) {
		out << ex.what() << " There are no active devices for simulation.";
	} catch (const TraceIOLine &ex) {
		out << ex.what() << " Wrong format of trace line.";
	}

	out << " \n";
	out.flush();
}

void MemSimCli::run()
{
	QString line;
	CmdParser parser;
	QTextStream out(stdout);

	out << welcome_msg;
	out.flush();

	do {
		int ret;
		int command;
		QStringList args;

		line = get_input();
		if (line.isEmpty())
			continue;


		ret = parser.get_args(line, command, args);
		if (ret == OK) {
			process_command(command, args);
		} else {
			out << err_msg[ret];
			out.flush();
		}

	} while (!line.isNull());

	out << "\n";
	out.flush();

	emit finished();
}

int main(int argc, char *argv[])
{
    //! Qt-related console init bits
    QCoreApplication a(argc, argv);
    MemSimCli *task = new MemSimCli(&a, argc, argv);
    QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, task, SLOT(run()));

    return a.exec();
}
