#ifndef MEMTRACE_H
#define MEMTRACE_H

//! Header file of MemTrace class.
/*!
 * \file memtrace.h
 *
 * MemTrace is class encapsulates methods for working with MemTrace.
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memsimlib.h"
#include <QList>
#include <QString>

//! Types of memory references.
enum ref_type {
	I = 0, /*< Instruction reference. */
	L, /*< Load reference. */
	S /*< Store reference. */
};

//! Class containing parsed trace line.
class MemTraceEntry
{
        public:
		//! A constructor.
                MemTraceEntry() : type('I'), address(0), size(0) {};
		//! A constructor.
                MemTraceEntry(char t, long a, long s);
		//! Type of reference.
                char type;
		//! Address.
                quint64 address;
		//! Size of access.
                quint64 size;
};

//! Custom STD-style iterator for the trace object.
typedef QList<MemTraceEntry>::const_iterator trace_it;

//! Internal libray trace representation.
class MemTrace
{
    public:
	    //! A constructor.
            MemTrace(QString path);
	    //! A destructor.
            ~MemTrace();
	    //! Returns number of trace lines.
            int get_size();
	    //! Indexing interator.
            const MemTraceEntry & at(int i) const;
	    //! Returns current position in the trace.
	    const MemTraceEntry & current(void);
	    //! Returns next entry in the trace.
	    /*!
	     * \param[out] end Set to 1 when the pointer reached the end of the trace.
	     * \returns Next trace line.
	     */
	    const MemTraceEntry & get_next(int * end);
	    //! Returns trace pointer to the beginning.
	    void reset_trace();
	    //! \return QString containing trace.
	    QString dump_trace();
    private:
	    //! trace itself.
            QList<MemTraceEntry> trace;
	    //! Function for parsing trace line.
            void process_line(QString line);
	    //! Trace pointer.
	    trace_it it;
};

#endif
