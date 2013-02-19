/*
 * Basic program modul that launches the GUI
 * Author : Petr Holasek, xholas02@stud.fit.vutbr.cz
 */

//#include <QCoreApplication>
//#include <QApplication> 
//#include "ui_gui.h"
#include "memsim.h"
#include "memsimul.h"

int main(int argc, char * argv[])
{
   MemSimulation sim;
   if (argc < 1)
           return 1;
   sim.init_memsim();
   sim.start_memsim();
   sim.sim_trace(argv[1]);
   sim.dump_stats();
   return 0;
}
