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
	cd src && qmake
	make -C src clean
	cd -
tags:
	cd src/
	ctags *.cc *.h
	cd ..

#run: memsim
#	cd src && ./memsim test/lackey.out.reduced


