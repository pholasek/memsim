#ifndef MEMTRACE_H
#define MEMTRACE_H

/*!
 * @file memtrace.h
 * Header file of MemTrace class.
 *
 * \brief MemTrace is class encapsulates methods for working with MemTrace.
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memsimlib.h"
#include <QList>
#include <QString>

//! Implementation class declaration

enum ref_type {I = 0,L ,S };

class MemTraceEntry
{
        public:
                MemTraceEntry() : type('I'), address(0), size(0) {};
                MemTraceEntry(char t, long a, long s);
                char type;
                quint64 address;
                quint64 size;
};

typedef QList<MemTraceEntry>::const_iterator trace_it;

class MemTrace
{
    public:
            MemTrace(QString path);
            ~MemTrace();
            int get_size();
            const MemTraceEntry & at(int i) const;
	    const MemTraceEntry & current(void);
	    const MemTraceEntry & get_next(int * end);
	    void reset_trace();
	    QString dump_trace();
    private:
            QList<MemTraceEntry> trace;
            void process_line(QString line);
	    trace_it it;
};

#endif
