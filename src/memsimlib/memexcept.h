#ifndef MEMEXCEPT_H
#define MEMEXCEPT_H

/*!
 * \file memexcept.h
 *
 * \brief This file contains source of MemSim exception classes.
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include <stdexcept>

class TraceIO : public std::runtime_error {
	public:
		TraceIO() : std::runtime_error("TraceIO error:") {}
};

class TraceIOFile : public TraceIO {};

class TraceIOLine : public TraceIO {};

class UserInput: public std::runtime_error {
	public:
		UserInput() : std::runtime_error("User input error:") {}
};

class UserInputBadTraceId : public UserInput {};

class UserInputBadArg : public UserInput {};

class UserInputWrongConfigArg : public UserInput {
	public:
		UserInputWrongConfigArg(QString param, quint64 value) : param(param), value(value) {}
		~UserInputWrongConfigArg() throw() {};
		QString param;
		quint64 value;
};

class MemError : public std::runtime_error {
	public:
		MemError() : std::runtime_error("Allocation error:") {}
};

class MemErrorAlloc : public MemError {};

class ConfigError : public std::runtime_error {
	public:
		ConfigError() : std::runtime_error("Configuration error:") {}
};

class ConfigErrorFileAccess : public ConfigError {};

class ConfigErrorWrongDevice : public ConfigError {};

class ConfigErrorEmptyHierarchy : public ConfigError {};

class ConfigErrorNoPageTable : public ConfigError {};

#endif
