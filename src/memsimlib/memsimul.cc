/*
 * @file memsimulation.cc
 * Source file of MemSimulation class.
 *
 * \brief Memory simulation base class
 *
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 *
 */

#include "memsimul.h"

//!
// Interface class implementation

MemSimulationObj::MemSimulationObj() : obj(MemSimulation::get_instance()), trace_id(0) { 
	load_configuration();
}

MemSimulationObj::~MemSimulationObj() {}

int MemSimulationObj::load_trace(QString & path)
{
	int ret = trace_id;

	QSharedPointer<MemTraceObj> new_trace = QSharedPointer<MemTraceObj>(new MemTraceObj(path));
	traces.insert(trace_id, new_trace);
	t_paths.insert(trace_id, path);
	trace_id++;

	return ret;
}

int MemSimulationObj::run_trace(int id)
{
	if (!traces.contains(id))
		throw UserInputBadTraceId();

	obj.sim_trace(*(traces.value(id)->obj));

	return 0;
}

int MemSimulationObj::run_trace_step(int id, int flush)
{
	int step;

	if (!traces.contains(id))
		throw UserInputBadTraceId();

	step = obj.sim_trace_step(traces.value(id)->obj, flush);

	return step;
}

void MemSimulationObj::config_param(QString & object, QString & param, QString value)
{
	obj.set_cfg_param(object, param, value);
}

QVariant MemSimulationObj::get_param(QString & object, QString & param)
{
	return obj.get_cfg_param(object, param);
}

void MemSimulationObj::load_configuration(void)
{
	obj.init_memsim();
}

QString MemSimulationObj::show_traces(void)
{
	QString traces;

	QMap<int, QString>::const_iterator i = t_paths.constBegin();
	while (i != t_paths.constEnd()) {
		traces.append(QString("%1:\t%2\n").arg(i.key()).arg(i.value()));
		++i;
	}

	return traces;
}

QString MemSimulationObj::show_hierarchy(void)
{
	return obj.show_devs();
}

QString MemSimulationObj::show_stats(void)
{
	return QString();
}

QString MemSimulationObj::show_statsall(int parseable)
{
	return obj.show_calendstats(parseable) + obj.show_statsall(parseable);
}

void MemSimulationObj::add_device(QString & name)
{
	obj.add_device(name);
}

void MemSimulationObj::remove_device(QString & name)
{
	obj.remove_device(name);
}

QStringListModel *MemSimulationObj::dump_trace(int idx)
{
	return traces.value(idx).data()->dump_trace();
}

bool MemSimulationObj::has_pg_table()
{
	return obj.has_pg_table();
}

void MemSimulationObj::set_l1split(bool val)
{
	obj.set_l1split(val);
}

void MemSimulationObj::clean_devs()
{
	obj.clean_devs();
}

quint64 * MemSimulationObj::get_acc(QString & name, long * sets, long * assoc)
{
	return obj.get_acc(name, sets, assoc);
}
//! Constructor
MemSimulation::MemSimulation() : settings(new QSettings("MemSim", "memsim"))
{
	this->state = STOP;
}

//! Destructor

MemSimulation::~MemSimulation()
{
	delete settings;
}

//! Methods
void MemSimulation::toggle_l1split()
{
	int latency;
	unsigned long long size, lsize, assoc;
	bool active;

	settings->beginGroup("l1");
	latency = settings->value("latency", DEF_CACHE_LATENCY).toInt();
	size = settings->value("size", DEF_CACHE_SIZE).toULongLong();
	lsize = settings->value("lsize", DEF_CACHE_LSIZE).toULongLong();
	assoc = settings->value("assoc", DEF_CACHE_ASSOC).toULongLong();
	active = settings->value("active", false).toBool();
	settings->endGroup();

	if (active) {
		if (l1split) {
			devs.add_cache(L1_I, latency, size, lsize, assoc);
		}
		devs.add_cache(L1_D, latency, size, lsize, assoc);
	}
}

void MemSimulation::process_cache(QStringList & groups, QString name)
{
	int latency;
	unsigned long long size, lsize, assoc;
	bool active;

	if (!(groups.filter(name).isEmpty())) {
		settings->beginGroup(name);
		latency = settings->value("latency", DEF_CACHE_LATENCY).toInt();
		size = settings->value("size", DEF_CACHE_SIZE).toULongLong();
		lsize = settings->value("lsize", DEF_CACHE_LSIZE).toULongLong();
		assoc = settings->value("assoc", DEF_CACHE_ASSOC).toULongLong();
		active = settings->value("active", false).toBool();
		settings->setValue("latency", latency);
		settings->setValue("size", size);
		settings->setValue("lsize", lsize);
		settings->setValue("assoc", assoc);
		settings->setValue("active", active);
		settings->endGroup();

		mem_t type = devs.get_type(name);
		if (active) {
			if ((mem_t) type == L1_D && l1split) {
				devs.add_cache(L1_I, latency, size, lsize, assoc);
			}
			devs.add_cache(type, latency, size, lsize, assoc);
		}
		groups.removeAt(groups.indexOf(name));
	}
}

void MemSimulation::process_tlb(QStringList & groups)
{
	int latency;
	unsigned long long entries, entrysize, assoc;
	bool active;

	if (!(groups.filter("tlb").isEmpty()) && devs.has_pg_table()) {
		settings->beginGroup("tlb");
		latency = settings->value("latency", DEF_TLB_LATENCY).toInt();
		entries = settings->value("entries", DEF_TLB_ENTRIES).toULongLong();
		entrysize = settings->value("entrysize", DEF_TLB_ENTRY_SIZE).toULongLong();
		assoc = settings->value("assoc", DEF_TLB_ASSOC).toULongLong();
		active = settings->value("active", false).toBool();
		settings->setValue("latency", latency);
		settings->setValue("entries", entries);
		settings->setValue("entrysize", entrysize);
		settings->setValue("assoc", assoc);
		settings->setValue("active", active);
		settings->endGroup();

		if (active)
			devs.add_tlb(entries, entrysize, latency);
		groups.removeAt(groups.indexOf("tlb"));
	}
}

//TODO
void MemSimulation::process_ram(QStringList & groups)
{
	int latency;
	bool active;

	if (!(groups.filter("ram").isEmpty())) {
		settings->beginGroup("ram");
		latency = settings->value("latency", DEF_RAM_LATENCY).toInt();
		active = settings->value("active", false).toBool();
		settings->setValue("latency", latency);
		settings->setValue("active", active);
		settings->endGroup();

		if (active)
			devs.add_ram(latency);
		groups.removeAt(groups.indexOf("ram"));
	}
}
//
//TODO
void MemSimulation::process_swap(QStringList & groups)
{
	int latency;
	bool active;

	if (!(groups.filter("swap").isEmpty()) && devs.has_pg_table()) {
		settings->beginGroup("swap");
		latency = settings->value("latency", DEF_SWAP_LATENCY).toInt();
		active = settings->value("active", false).toBool();
		settings->setValue("latency", latency);
		settings->setValue("active", active);
		settings->endGroup();

		if (active)
			devs.add_swap(latency);
		groups.removeAt(groups.indexOf("swap"));
	}
}

void MemSimulation::process_pg_table(QStringList & groups)
{
	int latency;
	unsigned long long depth;
	bool active;

	if (!(groups.filter("pt").isEmpty())) {
		settings->beginGroup("pt");
		latency = settings->value("latency", DEF_PT_LATENCY).toInt();
		depth = settings->value("depth", DEF_PT_DEPTH).toULongLong();
		active = settings->value("active", false).toBool();
		settings->setValue("latency", latency);
		settings->setValue("depth", depth);
		settings->setValue("active", active);
		settings->endGroup();

		if (active)
			devs.add_page_table(depth, latency);
		groups.removeAt(groups.indexOf("pt"));
	}
}

void MemSimulation::process_model(QStringList & groups)
{
	bool l1split;

	if (!(groups.filter("model").isEmpty())) {
		settings->beginGroup("model");
		l1split = settings->value("l1split", DEF_L1SPLIT).toBool();
		settings->setValue("l1split", l1split);
		settings->endGroup();

		groups.removeAt(groups.indexOf("model"));
	}
}

void MemSimulation::process_settings(QStringList & groups)
{
	process_model(groups);
}

void MemSimulation::process_devices(QStringList & groups)
{
	process_cache(groups, QString("l1"));
	process_cache(groups, QString("l2"));
	process_cache(groups, QString("l3"));
	process_ram(groups);
	process_pg_table(groups);
	process_swap(groups);
	process_tlb(groups);
	//devs.commit_changes();
}

void MemSimulation::init_settings()
{

	if (settings->status() != QSettings::NoError)
		throw ConfigErrorFileAccess();

	QStringList groups = settings->childGroups();
	process_settings(groups); //! Process other settings
	process_devices(groups); //! Process device hierarchy related settings
	settings->sync();
}

void MemSimulation::init_memsim()
{
	init_settings();
}

void MemSimulation::start_memsim()
{
	this->state = STOP;
}

void MemSimulation::stop_memsim()
{
	this->state = STOP;
}

void MemSimulation::reset_memsim()
{
}

mem_t MemSimulation::search_vm(const MemTraceEntry & e)
{
	int ret = FAULT;

	/* Search in TLB */
	if (devs.has_tlb()) {
		cal.new_ref_event(devs.get_tlb(), RREF, e.address, e.size, 0);
		ret = cal.do_next();
	}
	if (ret == HIT)
		return TLB;
	else if (ret == FAULT && devs.has_pg_table()) { /* We need to translate address in page table */
		cal.new_ref_event(devs.get_pg_table(), RREF, e.address, e.size, 0);
		/* Search in page table*/
		ret = cal.do_next();
	}
	if (ret == HIT)
		return PT;
	else if (ret == FAULT && devs.has_swap()) { /* We need to fetch data from swap. Swap is mandatory here. */
		cal.new_ref_event(devs.get_swap(), RREF, e.address, e.size, 0);
		ret = cal.do_next();
	}

	return SWAP;
}

/*
 * Returns starting device (D/I) for simulation
 */

MemDevice * MemSimulation::process_inst(const MemTraceEntry & e)
{
	 MemDevice * start_dev = NULL;

         switch(e.type) {
		 case 'I':
			 cal.new_ref_event(devs.get_first_inst(), INST, e.address, e.size, 0);
			 start_dev = devs.get_first_inst();
			 break;
		 case 'L':
			 cal.new_ref_event(devs.get_first_data(), RREF, e.address, e.size, 0);
			 start_dev = devs.get_first_data();
			 break;
		 case 'S':
			 cal.new_ref_event(devs.get_first_data(), WREF, e.address, e.size, 0);
			 start_dev = devs.get_first_data();
			 break;
		default:
			 throw TraceIOLine();
			 break;
	 }

	 return start_dev;
}

void MemSimulation::clean_devs()
{
	devs.reset_devs();
}

void MemSimulation::sim_instr(const MemTraceEntry & e)
{
	mem_t found;
	int ret = HIT;

	if (devs.has_pg_table()) //! If VM is turned on - address translation
		found = search_vm(e);
	devs.set_sim_dev(process_inst(e)); //! Process the line

	while (1) { //! Search for address in ascendant order
		ret = cal.do_next(); //! Do next action scheduled in calendar
		if (ret == HIT || devs.on_last_dev()) //! Break and go to the next traceline
			break;
		if (!devs.next_dev()) //! Insert next action to calendar
			cal.clone_current(devs.get_sim_dev());
	}
}

int MemSimulation::sim_trace_step(MemTrace * trace, int flush)
{
	static MemTrace * trc = NULL;
	static int end = 0;
	static int step = 0;

	if (trc != trace) {
		trc = trace;
		end = 0;
		step = 0;
	}

	if (!step) {
		devs.reset_devs();
		devs.commit_changes();
		cal.reset_calend();
		this->state = RUNNING;
	}


	if (!trc->get_size())
		return 0;

	if (!end) {
		if (!flush) {
			const MemTraceEntry & e = trc->get_next(&end);
			sim_instr(e);
			step++;
		} else {
			do {
				const MemTraceEntry & e = trc->get_next(&end); //! Get next line from trace
				sim_instr(e);
				step++;
			} while (!end);
		}
		return step;
	}

	this->state = STOP;

	trc->reset_trace();
	step = 0;

	return trc->get_size()-1;
}

void MemSimulation::sim_trace(MemTrace & trace)
{
	int end = 0;

	devs.reset_devs();
	devs.commit_changes();
	cal.reset_calend();

	if (!trace.get_size())
		return;

	do {
		const MemTraceEntry & e = trace.get_next(&end); //! Get next line from trace

		sim_instr(e);
	} while (!end);

	trace.reset_trace();
}

void MemSimulation::valid_cfg_param(mem_t type, QString & param, quint64 value)
{
	if (param == "active")
		return;

	switch (type) {
		case L1_D:
		case L1_I:
		case L2:
		case L3:
		case TLB:
			//if (param != "latency" && (log2l(value)) - trunc(log2l(value)) > 0.0) {
				//qDebug() << param << trunc(log2l(value));
			//	throw UserInputWrongConfigArg();
			//}
			if (param == "assoc" && value > 64)
				throw UserInputWrongConfigArg(param, value);
		case RAM:
		case SWAP:
		case PT:
			if (value == 0) {
				throw UserInputWrongConfigArg(param, value);
			}
			break;
		default:
			throw UserInputBadArg();
			break;
	}
}

void MemSimulation::set_cfg_param(QString & object, QString & param, QString & value)
{
	if (param == "active")
		return;

	mem_t type = devs.get_type(object);

	valid_cfg_param(type, param, value.toUInt());

	switch (type) {
		case L1_D:
		case L1_I:
		case L2:
		case L3:
			devs.config_cache(type, param, value.toULong());
			break;
		case RAM:
			devs.config_ram(param, value.toULong());
			break;
		case SWAP:
			devs.config_swap(param, value.toULong());
			break;
		case TLB:
			devs.config_tlb(param, value.toULong());
			break;
		case PT:
			devs.config_page_table(param, value.toULong());
			break;
		default:
			throw UserInputBadArg();
			break;
	}

	settings->beginGroup(object);
	settings->setValue(param, QVariant(value));
	settings->endGroup();
	settings->sync();
}

QVariant MemSimulation::get_cfg_param(QString & object, QString & param)
{
	QVariant val;

	settings->sync();
	settings->beginGroup(object);
	if (settings->contains(param))
		val = settings->value(param);
	settings->endGroup();

	return val; //! Return invalid QVariant if parameter wouldn't exist.
}

void MemSimulation::add_device(QString & name)
{
	mem_t type = devs.get_type(name);
	unsigned long long size, lsize, assoc, latency, entries, entrysize, depth;

	switch (type) {
		case L1_D:
			settings->beginGroup("l1");
			latency = settings->value("latency", DEF_CACHE_LATENCY).toUInt();
			size = settings->value("size", DEF_CACHE_SIZE).toUInt();
			lsize = settings->value("lsize", DEF_CACHE_LSIZE).toUInt();
			assoc = settings->value("assoc", DEF_CACHE_ASSOC).toUInt();
			if (l1split)
				devs.add_cache(L1_I,latency,size,lsize,assoc);
			devs.add_cache(L1_D,latency,size,lsize,assoc);
			settings->setValue("latency", latency);
			settings->setValue("size", size);
			settings->setValue("lsize", lsize);
			settings->setValue("assoc", assoc);
			settings->endGroup();
			break;
		case L2:
		case L3:
			settings->beginGroup(name);
			latency = settings->value("latency", DEF_CACHE_LATENCY).toUInt();
			size = settings->value("size", DEF_CACHE_SIZE).toUInt();
			lsize = settings->value("lsize", DEF_CACHE_LSIZE).toUInt();
			assoc = settings->value("assoc", DEF_CACHE_ASSOC).toUInt();
			devs.add_cache(type,latency,size,lsize,assoc);
			settings->setValue("latency", latency);
			settings->setValue("size", size);
			settings->setValue("lsize", lsize);
			settings->setValue("assoc", assoc);
			settings->endGroup();
			break;
		case RAM:
			settings->beginGroup("ram");
			latency = settings->value("latency", DEF_RAM_LATENCY).toUInt();
			devs.add_ram(latency);
			settings->setValue("latency", latency);
			settings->endGroup();
			break;
		case SWAP:
			if (!devs.has_pg_table())
				throw ConfigErrorNoPageTable();
			settings->beginGroup("swap");
			latency = settings->value("latency", DEF_SWAP_LATENCY).toUInt();
			devs.add_swap(latency);
			settings->setValue("latency", latency);
			settings->endGroup();
			break;
		case TLB:
			if (!devs.has_pg_table())
				throw ConfigErrorNoPageTable();
			settings->beginGroup("tlb");
			latency = settings->value("latency", DEF_TLB_LATENCY).toUInt();
			entries = settings->value("entries", DEF_TLB_ENTRIES).toUInt();
			assoc = settings->value("assoc", DEF_TLB_ASSOC).toUInt();
			devs.add_tlb(entries, 8, latency);
			settings->setValue("latency", latency);
			settings->setValue("entries", entries);
			settings->setValue("assoc", assoc);
			settings->endGroup();
			break;
		case PT:
			settings->beginGroup("pt");
			latency = settings->value("latency", DEF_PT_LATENCY).toUInt();
			latency = settings->value("depth", DEF_PT_DEPTH).toUInt();
			devs.add_page_table(depth, latency);
			settings->setValue("latency", latency);
			settings->setValue("depth", depth);
			settings->endGroup();
			break;
		default:
			throw ConfigErrorWrongDevice();
			break;
	}

	enable_device(name);
}

void MemSimulation::remove_device(QString & name)
{
	mem_t type = devs.get_type(name);

	switch (type) {
		case L1_D:
			if (l1split)
				devs.delete_cache(L1_I,NULL);
			devs.delete_cache(L1_D,NULL);
		case L2:
		case L3:
			devs.delete_cache(type, NULL);
			break;
		case RAM:
			devs.delete_ram(NULL);
			break;
		case SWAP:
			devs.delete_swap(NULL);
			break;
		case PT :
			devs.delete_page_table(NULL); /* Also deactivate TLB and swap */
			devs.delete_tlb(NULL);
			devs.delete_swap(NULL);
			{ QString tlb("tlb"); disable_device(tlb); }
			{ QString swap("swap"); disable_device(swap); }
			break;
		case TLB:
			devs.delete_tlb(NULL);
			break;
		default:
			throw ConfigErrorWrongDevice();
			break;
	}

	disable_device(name);
}

void MemSimulation::enable_device(QString & name)
{
	settings->beginGroup(name);
	settings->setValue("active", true);
	settings->endGroup();
	settings->sync();
}

void MemSimulation::disable_device(QString & name)
{
	settings->beginGroup(name);
	settings->setValue("active", false);
	settings->endGroup();
	settings->sync();
}

QString MemSimulation::show_devs()
{
	return devs.show_devs();
}

QString MemSimulation::show_statsall(int parseable)
{
	return devs.show_stats(parseable);
}

QString MemSimulation::show_calendstats(int parseable)
{
	MemSimCalendStats stats = cal.get_stats();
	
	if (!parseable)
		return QString("Calendar stats:\n\tTime (cpu cycles) of simulation: %1\n\tNumber of memory accesses:%2\n")
		.arg(stats.Time)
		.arg(stats.ev_proc);
	else
		return QString("time:%1 allacc:%2 ")
		.arg(stats.Time)
		.arg(stats.ev_proc);

}

quint64 * MemSimulation::get_acc(QString & name, long * sets, long * assoc)
{
	mem_t type = devs.get_type(name);

	return devs.get_acc(type, sets, assoc);
}
