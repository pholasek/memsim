#ifndef CMDPARSER_H
#define CMDPARSER_H
//! Command line arguments parser

/*!
 * Header of module for MemSim CLI parsing
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include "../memsimlib/memsimlib.h"
#include "../memsimlib/memexcept.h"

//! An enum containing all possible CLI commands
enum commands {
	LOAD,		/*!< number of arguments: 1 */
	CONFIG,		/*!< number of arguments: 3 */
	UNLOAD,		/*!< number of arguments: 1 */
	RUN,		/*!< number of arguments: 1 */
	RUNPARAM,	/*!< number of arguments: 0 */
	EXIT,		/*!< number of arguments: 0 */
	SHOW,		/*!< number of arguments: 1 */
	HELP,		/*!< number of arguments: 0 */
	ADD,		/*!< number of arguments: 1 */
	REMOVE		/*!< number of arguments: 1 */
};

//! An array storing number of arguments of each command
const int argnum[] = {1, 3, 1, 1, 0, 0, 1, 0, 1, 1};

//! Return values of command line argument parser
enum rets {OK = 0, ETOOMANY, ETOOFEW, EINVALID};

//! Class encapsulation command line parser
class CmdParser
{
	public:
		//! A constructor.
		CmdParser() {}
		//! A destructor
		~CmdParser() {}
		//! Parsing function
		/*!
		 * \param[in] input Input string
		 * \param[out] command Type of command
		 * \param[out] command arguments
		 */
		int get_args(QString & input, int & command, QStringList & args);
	private:
};

#endif
