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
