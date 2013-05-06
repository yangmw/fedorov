# Date created: 27 Apr 2013
# Last Modified: 06 May 2013 (09:08:52)
#
# Brief: 
# Input: 
# Output:
# 
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

CC = cc             		               # Set compiler
CFLAGS += -O3 -Wall -std=c99 -I/opt/local/include -I.        # Set compiler flags for C
LDLIBS += -lm -L/opt/local/lib -lgsl -lgslcblas    # Extra libraries to link
HOST = $(findstring ymwang, $(shell hostname)) # Am I on lifa?
#GRAPH = $(/usr/users/fedorov/bin/graph)

# Set default target (for make)
all: clear_screen clean run set_premissions 
	@echo Compiled and Run completed successfully 

# Clean screen
clear_screen:
	clear 
	clear

#qr: main 
	#./main

# RUN 
run: main test
	./test
	./main

# Linking the main program
main: main.o vector.o matrix.o qrdec.o
test: test.o vector.o matrix.o

#	$(CC) -o main main.o linterp.o bsearch.o 
main.o: main.c
test.o: test.c
qrdec.o: qrdec.c 

# Linking header files
main.c: vector.h matrix.h qr.h
test.c: vector.h matrix.h
qrdec.c: vector.h matrix.h
# Set read premissions using subshell (;)
set_premissions:
ifneq ($(HOST), ymwang ) 
	@(cd ../../../; chmod -R go+xr public_html)
	@echo Permissions set
endif

##########################################################

# Target clean all
clean: 
	@rm -f main main.o vector.o matrix.o qrdec.o
	@rm -f test test.o
	@echo Clean done


backup: qr.tgz

qr.tgz: makefile $(shell ls *.c)
	@tar --create --gzip --file=qr.tgz makefile plot.gpi *.c
	@tar --list --file=qr.tgz
	@echo Backup done
