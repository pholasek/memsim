/*
 * Module for MemSim CLI parsing
 * Author : Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include "memsim-cli.h"

int CmdParser::get_args(QString & input, int & command, QStringList & args)
{
	args = input.split(' ', QString::SkipEmptyParts);
	QString cmd = args[0];

	if (cmd == "config")
		command = CONFIG;
	else if (cmd == "load")
		command = LOAD;
	else if (cmd == "unload")
		command = UNLOAD;
	else if (cmd == "run")
		command = RUN;
	else if (cmd == "runparam")
		command = RUNPARAM;
	else if (cmd == "exit")
		command = EXIT;
	else if (cmd == "show")
		command = SHOW;
	else if (cmd == "help")
		command = HELP;
	else if (cmd == "add")
		command = ADD;
	else if (cmd == "remove")
		command = REMOVE;
	else
		return EINVALID;

	if (args.size() - 1 < argnum[command])
		return ETOOFEW;
	else if (args.size() - 1 > argnum[command])
		return ETOOMANY;
	else
		return OK;
}
