#ifndef CMDPARSER_H
#define CMDPARSER_H

/*
 * Header of module for MemSim CLI parsing
 * Author : Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include "../memsimlib/memsimlib.h"
#include "../memsimlib/memexcept.h"

enum commands {		// number of arguments
	LOAD,		// 1
	CONFIG,		// 3
	UNLOAD,		// 1
	RUN,		// 1
	RUNPARAM,	// 0
	EXIT,		// 0
	SHOW,		// 1
	HELP,		// 0
	ADD,		// 1
	REMOVE		// 1
};

const int argnum[] = {1, 3, 1, 1, 0, 0, 1, 0, 1, 1};

enum rets {OK = 0, ETOOMANY, ETOOFEW, EINVALID};

class CmdParser
{
	public:
		CmdParser() {}
		~CmdParser() {}
		int get_args(QString & input, int & command, QStringList & args);
	private:
};

#endif
