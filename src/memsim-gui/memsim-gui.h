#ifndef MEMSIMGUI_H
#define MEMSIMGUI_H
//! GUI memsim client base class
/*!
 * GUI client header file
 * \author Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

#include <QWidget>
#include <QtCore>
#include <QTextStream>
#include <QSharedPointer>
#include <QFileDialog>
#include <QMessageBox>
#include <QListView>
#include "../memsimlib/memsimlib.h"
#include "../memsimlib/memexcept.h"
#include "ui_memsim.h"

//! Class of the memsim windows
class MemSimGui : public QMainWindow
{
Q_OBJECT

public:
	//! A Constructor
	MemSimGui(QWidget *parent = 0);
	//! A destructor
	~MemSimGui();

	//! Read settings to GUI entities from config
	void read_settings();
	//! Writes message to QTextBrowser
	/*!
	 * \param[in] msg Message to write
        */
	void write_log(const QString & msg);
protected slots:
	//! Slot called for loading of trace
	void load_trace();
	//! Slot called for simulation of trace
	void run_trace();
	//! Slot called for step simulation of trace
	void run_trace_step();
	//! Slot called for the finish of simulation
	void finish();
	//! Writes settings from GUI entities to config
	void write_settings();

private:
	//! Refresh statistics in GUI
	void refresh_stats();
	Ui::MainWindow * ui;
	MemSimulationObj sim;
};

#endif
