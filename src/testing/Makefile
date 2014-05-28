####################################
# Makefile for testing programs of #
# MemSim simulator		   #
# ##################################
#

CC=gcc
CFLAGS=-std=c99 -O2

all: quicksort cache_flush matrix_good matrix_bad

quicksort: quicksort.c
	$(CC) $(CFLAGS) $< -o $@

matrix_good: matrix_good.c
	$(CC) $(CFLAGS) $< -o $@

matrix_bad: matrix_bad.c
	$(CC) $(CFLAGS) $< -o $@

cache_flush: cache_flush.c
	$(CC) $(CFLAGS) $< -o $@
