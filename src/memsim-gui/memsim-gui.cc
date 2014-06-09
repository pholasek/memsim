/*!
 * GUI of MemSim simulator
 * \author : Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include "memsim-gui.h"


MemSimGui::MemSimGui(QWidget *parent) : QMainWindow(parent)
{
	ui = new Ui::MainWindow;
	ui->setupUi(this);
	connect(ui->action_Load_File, SIGNAL(triggered()), this, SLOT(load_trace()));
	connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(run_trace()));
	connect(ui->actionRun_stp, SIGNAL(triggered()), this, SLOT(run_trace_step()));
	connect(ui->step_button, SIGNAL(clicked()), this, SLOT(run_trace_step()));
	connect(ui->finish_button, SIGNAL(clicked()), this, SLOT(finish()));
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(write_settings()));
	connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(flush_sim()));

	sim.load_configuration();
	read_settings();
	refresh_vis();
}

MemSimGui::~MemSimGui()
{
	delete ui;
}

void MemSimGui::write_settings()
{
	QString obj, param;

	try {

	obj = QString("l1");
	param = QString("latency");
	sim.config_param(obj,param, QString().setNum(ui->l1miss->value()));
	ui->l1miss->setFocus();
	obj = QString("l1");
	param = QString("size");
	sim.config_param(obj,param, QString().setNum(ui->l1size->value()));
	ui->l1size->setFocus();
	obj = QString("l1");
	param = QString("assoc");
	sim.config_param(obj,param, QString().setNum(ui->l1assoc->value()));
	ui->l1assoc->setFocus();
	//if (ui->l1check->isChecked())
	//	sim.add_device(obj);
	//else
	//	sim.remove_device(obj);
	//sim.set_l1split(ui->anoldradio->isChecked());

	obj = QString("l2");
	param = QString("latency");
	sim.config_param(obj,param, QString().setNum(ui->l2miss->value()));
	ui->l2miss->setFocus();
	obj = QString("l2");
	param = QString("size");
	sim.config_param(obj,param, QString().setNum(ui->l2size->value()));
	ui->l2size->setFocus();
	obj = QString("l2");
	param = QString("assoc");
	sim.config_param(obj,param, QString().setNum(ui->l2assoc->value()));
	ui->l2assoc->setFocus();
	if (ui->l2check->isChecked())
		sim.add_device(obj);
	else
		sim.remove_device(obj);

	obj = QString("l3");
	param = QString("latency");
	sim.config_param(obj,param, QString().setNum(ui->l3miss->value()));
	ui->l3miss->setFocus();
	obj = QString("l3");
	param = QString("size");
	sim.config_param(obj,param, QString().setNum(ui->l3size->value()));
	ui->l3size->setFocus();
	obj = QString("l3");
	param = QString("assoc");
	sim.config_param(obj,param, QString().setNum(ui->l3assoc->value()));
	ui->l3assoc->setFocus();
	if (ui->l3check->isChecked())
		sim.add_device(obj);
	else
		sim.remove_device(obj);

	obj = QString("pt");
	param = QString("latency");
	sim.config_param(obj,param, QString().setNum(ui->pgtablemiss->value()));
	ui->pgtablemiss->setFocus();
	if (ui->pgtblcheck->isChecked())
		sim.add_device(obj);
	else
		sim.remove_device(obj);

	if (sim.has_pg_table()) {
		obj = QString("tlb");
		param = QString("latency");
		sim.config_param(obj,param, QString().setNum(ui->tlbmiss->value()));
		ui->tlbmiss->setFocus();
		obj = QString("tlb");
		param = QString("entries");
		sim.config_param(obj,param, QString().setNum(ui->tlbentries->value()));
		ui->tlbentries->setFocus();
		obj = QString("tlb");
		param = QString("assoc");
		sim.config_param(obj,param, QString().setNum(ui->tlbassoc->value()));
		ui->tlbassoc->setFocus();
		if (ui->tlbcheck->isChecked())
			sim.add_device(obj);
		else
			sim.remove_device(obj);

		obj = QString("swap");
		param = QString("latency");
		sim.config_param(obj,param, QString().setNum(ui->pgtablemiss->value()));
		ui->swapmiss->setFocus();
		if (ui->swapcheck->isChecked())
			sim.add_device(obj);
		else
			sim.remove_device(obj);
	}
	} catch (UserInputWrongConfigArg & ex) { QMessageBox messageBox;
		messageBox.critical(0,"Error","Focused setting is wrong. Please correct.");
		messageBox.setFixedSize(500,200);
		return; 
	} catch (UserInputBadArg & ex) { QMessageBox messageBox;
		messageBox.critical(0,"Error","Bad argument.");
		messageBox.setFixedSize(500,200);
		return;
	}

	refresh_vis();
}

void MemSimGui::read_settings()
{
	QString obj, param;

	obj = QString("model");
	param = QString("l1split");
	if ((sim.get_param(obj, param)).toBool())
		ui->neldradio->click();
	else
		ui->anoldradio->click();

	obj = QString("l1");
	param = QString("active");
	ui->l1check->setChecked((sim.get_param(obj, param)).toBool());
	obj = QString("l1");
	param = QString("latency");
	ui->l1miss->setValue((sim.get_param(obj, param)).toUInt());
	obj = QString("l1");
	param = QString("size");
	ui->l1size->setValue((sim.get_param(obj, param)).toUInt());
	obj = QString("l1");
	param = QString("assoc");
	ui->l1assoc->setValue((sim.get_param(obj, param)).toUInt());

	obj = QString("l2");
	param = QString("active");
	ui->l2check->setChecked((sim.get_param(obj, param)).toBool());
	obj = QString("l2");
	param = QString("latency");
	ui->l2miss->setValue((sim.get_param(obj, param)).toUInt());
	obj = QString("l2");
	param = QString("size");
	ui->l2size->setValue((sim.get_param(obj, param)).toUInt());
	obj = QString("l2");
	param = QString("assoc");
	ui->l2assoc->setValue((sim.get_param(obj, param)).toUInt());

	obj = QString("l3");
	param = QString("active");
	ui->l3check->setChecked((sim.get_param(obj, param)).toBool());
	obj = QString("l3");
	param = QString("latency");
	ui->l3miss->setValue((sim.get_param(obj, param)).toUInt());
	obj = QString("l3");
	param = QString("size");
	ui->l3size->setValue((sim.get_param(obj, param)).toUInt());
	obj = QString("l3");
	param = QString("assoc");
	ui->l3assoc->setValue((sim.get_param(obj, param)).toUInt());

	obj = QString("pt");
	param = QString("active");
	ui->tlbcheck->setChecked((sim.get_param(obj, param)).toBool());
	obj = QString("pt");
	param = QString("latency");
	ui->tlbmiss->setValue((sim.get_param(obj, param)).toUInt());

	obj = QString("tlb");
	param = QString("active");
	ui->tlbcheck->setChecked((sim.get_param(obj, param)).toBool());
	obj = QString("tlb");
	param = QString("latency");
	ui->tlbmiss->setValue((sim.get_param(obj, param)).toUInt());
	obj = QString("tlb");
	param = QString("entries");
	ui->tlbentries->setValue((sim.get_param(obj, param)).toUInt());
	obj = QString("tlb");
	param = QString("assoc");
	ui->tlbassoc->setValue((sim.get_param(obj, param)).toUInt());

	obj = QString("swap");
	param = QString("active");
	ui->swapcheck->setChecked((sim.get_param(obj, param)).toBool());
	obj = QString("swap");
	param = QString("latency");
	ui->swapmiss->setValue((sim.get_param(obj, param)).toUInt());

	if (!sim.has_pg_table()) {
		ui->tlbcheck->setCheckable(false);
		ui->swapcheck->setCheckable(false);
	}
}

void MemSimGui::write_log(const QString & msg)
{
	ui->plainTextEdit->appendPlainText(msg);
	//ui->plainTextEdit->appendPlainText(QString("\n"));
}

void MemSimGui::run_trace()
{
	int curr_trace;
	
	curr_trace = ui->tabWidget->indexOf(ui->tabWidget->currentWidget());
	try {
		sim.run_trace(curr_trace);
	} catch (UserInputBadTraceId &ex) { 
		QMessageBox messageBox;
		messageBox.critical(0,"Error","Non-existing trace file.");
		messageBox.setFixedSize(500,200);
		return;
	}
	write_log(QString("Simulation of trace %1 was completed.").arg(curr_trace));
	refresh_stats();
	refresh_vis();
}

void MemSimGui::run_trace_step()
{
	int curr_trace, step;
	
	curr_trace = ui->tabWidget->indexOf(ui->tabWidget->currentWidget());

	try {
		step = sim.run_trace_step(curr_trace,0);
	} catch (UserInputBadTraceId &ex) { 
		QMessageBox messageBox;
		messageBox.critical(0,"Error","Non-existing trace file.");
		messageBox.setFixedSize(500,200);
		return;
	}
	QListView * tv = qobject_cast<QListView*>(ui->tabWidget->currentWidget());
	QModelIndex new_index = tv->model()->index(step,0);
	tv->setCurrentIndex(new_index);
	refresh_stats();
	refresh_vis();
}

void MemSimGui::finish()
{
	int curr_trace, step;
	
	curr_trace = ui->tabWidget->indexOf(ui->tabWidget->currentWidget());

	try {
		step = sim.run_trace_step(curr_trace,1);
	} catch (UserInputBadTraceId &ex) { 
		QMessageBox messageBox;
		messageBox.critical(0,"Error","Non-existing trace file.");
		messageBox.setFixedSize(500,200);
		return;
	}
	QListView * tv = qobject_cast<QListView*>(ui->tabWidget->currentWidget());
	QModelIndex new_index = tv->model()->index(step,0);
	tv->setCurrentIndex(new_index);
	write_log(QString("Simulation of trace %1 was completed.").arg(curr_trace));
	refresh_stats();
	refresh_vis();
}

void MemSimGui::refresh_stats()
{
	QString stats = sim.show_statsall(1);

	QRegExp rx("time:(\\d+) allacc:(\\d+) l1acc:(\\d+) l1missratio:(\\d+[\\.\\d]*) l2acc:(\\d+) l2missratio:(\\d+[\\.\\d]*) l3acc:(\\d+) l3missratio:(\\d+[\\.\\d]*)"); // tlbacc:(\\d+) tlbmissratio:(\\d+[\\.\\d]*) ");

	int pos = rx.indexIn(stats);
	
	if (pos > -1)
	{
		ui->time->setText(rx.cap(1));
		ui->accesses->setText(rx.cap(2));
		ui->l1acc->setText(rx.cap(3));
		ui->l1missval->setText(rx.cap(4)+'%');
		ui->l2acc->setText(rx.cap(5));
		ui->l2missval->setText(rx.cap(6)+'%');
		ui->l3acc->setText(rx.cap(7));
		ui->l3missval->setText(rx.cap(8)+'%');
	} else {
		write_log(stats);
	}
}

void MemSimGui::refresh_vis()
{
	quint64 * accl1, *accl2, *accl3;
	long l1sets, l1assoc;
	long l2sets, l2assoc;
	long l3sets, l3assoc;
	QString l1("l1"), l2("l2"), l3("l3");

	accl1 = sim.get_acc(l1, &l1sets, &l1assoc);
	accl2 = sim.get_acc(l2, &l2sets, &l2assoc);
	accl3 = sim.get_acc(l3, &l3sets, &l3assoc);
	if (accl1) {
		ui->l1vis->set_assoc(l1assoc);
		ui->l1vis->set_sets(l1sets);
		ui->l1vis->set_values(accl1);
		ui->l1vis->update();
	}
	if (accl2) {
		ui->l2vis->set_assoc(l2assoc);
		ui->l2vis->set_sets(l2sets);
		ui->l2vis->set_values(accl2);
		ui->l2vis->update();
	}
	if (accl3) {
		ui->l3vis->set_assoc(l3assoc);
		ui->l3vis->set_sets(l3sets);
		ui->l3vis->set_values(accl3);
		ui->l3vis->update();
	}
}

void MemSimGui::flush_sim()
{
	sim.clean_devs();
}

void MemSimGui::load_trace()
{
	int ret;

	QString filename = QFileDialog::getOpenFileName(this, tr("Open trace"), ".", "Trace files (*.trc)");
	if (!filename.isNull()) {
		try {
			ret = sim.load_trace(filename);
		} catch (TraceIOFile &ex) { 
			QMessageBox messageBox;
			messageBox.critical(0,"Error","Unable to open the file.");
			messageBox.setFixedSize(500,200);
			return;
		} catch (TraceIOLine &ex) { 
			QMessageBox messageBox;
			messageBox.critical(0,"Error","Wrong trace file format.");
			messageBox.setFixedSize(500,200);
			return;
		}
		ui->tabWidget->insertTab(ret, new QListView, filename);
		ui->tabWidget->setCurrentIndex(ret);
		QListView * tv = qobject_cast<QListView*>(ui->tabWidget->currentWidget());
		tv->setModel(sim.dump_trace(ret));
		//tv->setSelectionMode(QAbstractItemView::NoSelection);
		tv->setSelectionBehavior(QAbstractItemView::SelectRows);
		write_log(QString("Successfully loaded trace id %1.").arg(ret));
	}
}


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MemSimGui *main = new MemSimGui;

	main->show();
	return app.exec();
}
