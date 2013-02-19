/*!
 * @file memtrace.cc
 * Source file of MemTrace class.
 *
 * \brief Memory traces used as input of simulation.
 *
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memtrace.h"

//! A constructors.
MemTraceEntry::MemTraceEntry(char t, long a, long s)
{
        type = t;
        address = a;
        size = s;
}

//! A destructors.
MemTrace::~MemTrace()
{
        trace.clear();
}

//! Method for parsing from file
void MemTrace::get_trace(QString name)
{
        QFile file(name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;

        trace.clear();
        while (!file.atEnd()) {
                QString line = file.readLine();
                process_line(line);
        }

        file.close();
}

const MemTraceEntry & MemTrace::at(int i) const
{
        return trace[i];
}

//! Size helper
int MemTrace::get_size()
{
        return trace.size();
}

//! Method for filling of lines
void MemTrace::process_line(QString line)
{
        QStringList res = line.split(" ");
        MemTraceEntry new_entry;
        if (res[0] == "")
                new_entry.type = res[1].at(0).toAscii();
        else
                new_entry.type = res[0].at(0).toAscii();
        res = res[2].split(",");
        new_entry.address = res[0].toULongLong(NULL, 16);
        new_entry.size = res[1].toLong();

        trace.append(new_entry);
}
