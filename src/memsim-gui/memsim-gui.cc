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

	sim.load_configuration();
	read_settings();
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
	sim.config_param(obj,param, QString().setNum(ui->l1size->value()));
	ui->l1assoc->setFocus();
	if (ui->l1check->isChecked())
		sim.add_device(obj);
	else
		sim.remove_device(obj);
	sim.set_l1split(ui->anoldradio->isChecked());

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

	if (sim.has_pg_table()) {
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
	} else {
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
	sim.run_trace(curr_trace);
	write_log(QString("Simulation of trace %1 was completed.").arg(curr_trace));
	refresh_stats();
}

void MemSimGui::run_trace_step()
{
	int curr_trace, step;
	
	curr_trace = ui->tabWidget->indexOf(ui->tabWidget->currentWidget());

	step = sim.run_trace_step(curr_trace,0);
	QListView * tv = qobject_cast<QListView*>(ui->tabWidget->currentWidget());
	QModelIndex new_index = tv->model()->index(step,0);
	tv->setCurrentIndex(new_index);
	refresh_stats();
}

void MemSimGui::finish()
{
	int curr_trace, step;
	
	curr_trace = ui->tabWidget->indexOf(ui->tabWidget->currentWidget());

	step = sim.run_trace_step(curr_trace,1);
	QListView * tv = qobject_cast<QListView*>(ui->tabWidget->currentWidget());
	QModelIndex new_index = tv->model()->index(step,0);
	tv->setCurrentIndex(new_index);
	write_log(QString("Simulation of trace %1 was completed.").arg(curr_trace));
	refresh_stats();
}

void MemSimGui::refresh_stats()
{
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
