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

#include "memsim.h"
#include "QStringList"

enum ref_type {I = 0,L ,S };

class MemTraceEntry
{
        public:
                MemTraceEntry() {};
                MemTraceEntry(char t, long a, long s);
                char type;
                quint64 address;
                quint64 size;
};

class MemTrace
{
    public:
            MemTrace() {};
            ~MemTrace();
            void get_trace(QString name);
            int get_size();
            const MemTraceEntry & at(int i) const;
    private:
            QList<MemTraceEntry> trace;
            void process_line(QString line);
};

#endif
