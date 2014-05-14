######################################
# Makefile of MemSim application     #
# ################################## #
# Author: Petr Holasek, 	     #
# 	xholas02@stud.fit.vutbr.cz   #
######################################

PATH := /usr/lib64/qt4/bin/:$(PATH)

.PHONY:	docs memsim

all: memsim

memsim:
	cd src && qmake && cd -
	make -C src

clean:	clean-docs
	cd src && qmake
	make -C src clean
	cd -
tags:
	cd src/
	ctags *.cc *.h
	cd ..
docs:
	doxygen Doxyfile

clean-docs:
	rm -rf docs/*



