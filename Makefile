######################################
# Makefile of MemSim application     #
# ################################## #
# Author: Petr Holasek, 	     #
# 	xholas02@stud.fit.vutbr.cz   #
######################################

PATH := /usr/lib64/qt4/bin/:$(PATH)

all: memsim

memsim: 
	cd src && qmake && cd -
	make -C src
clean:
	rm -rf doc/html
	cd src && qmake && cd -
	make -C src clean
	rm -f src/memsim
run: memsim
	cd src && ./memsim test/lackey.out 2> /dev/null


