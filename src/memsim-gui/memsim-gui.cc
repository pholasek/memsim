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

	sim.load_configuration();
}

MemSimGui::~MemSimGui()
{
	delete ui;
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
			messageBox.critical(0,"Error","Soubor trace se nepodařilo načíst.");
			messageBox.setFixedSize(500,200);
		}
	}
	ui->tabWidget->insertTab(ret, new QListView, filename);
	ui->tabWidget->setCurrentIndex(ret);
	QListView * tv = qobject_cast<QListView*>(ui->tabWidget->currentWidget());
	tv->setModel(sim.dump_trace(ret));
	write_log(QString("Successfully loaded trace id %1.").arg(ret));
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MemSimGui *main = new MemSimGui;

	main->show();
	return app.exec();
}
