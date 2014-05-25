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
#include "memexcept.h"
//
//! Interface class implementation

MemTraceObj::MemTraceObj(QString path) : obj(new ::MemTrace(path))
{
	trace_model = new QStringListModel(obj->dump_trace()) ;
};

MemTraceObj::~MemTraceObj() { delete obj; delete trace_model; }

QStringListModel *MemTraceObj::dump_trace() { return trace_model; }

//! A constructors.
MemTraceEntry::MemTraceEntry(char t, long a, long s)
{
        type = t;
        address = a;
        size = s;
}

MemTrace::MemTrace(QString path)
{
        QFile file(path); //TODO mmap
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		throw TraceIOFile();

        trace.clear();
        while (!file.atEnd()) {
                QString line = file.readLine();
		trace_model += line.remove('\n');
                process_line(line);
        }

	it = trace.begin();
}

//! A destructors.
MemTrace::~MemTrace()
{
        trace.clear();
}

const MemTraceEntry & MemTrace::at(int i) const
{
        return trace[i];
}

void MemTrace::reset_trace()
{
	it = trace.begin();
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

const MemTraceEntry & MemTrace::current(void)
{
	return *it;
}

const MemTraceEntry & MemTrace::get_next(int * end)
{
	if (it != trace.constEnd() - 1) {
		*end = 0;
		return *(it++);
	} else {
		*end = 1;
		return *it; 
	}
}

//! Dump raw trace
QStringList MemTrace::dump_trace()
{
	/*QStringList trace_dump;

	for (trace_it i = trace.begin(); i != trace.end(); ++i) {
		MemTraceEntry e = *i;
		trace_dump.append(QString("%1 %2 %3\n").arg(e.type).arg(e.address).arg(e.size));
	}

	return trace_dump;*/
	return trace_model;
}

