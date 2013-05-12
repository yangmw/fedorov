# Date created: 27 Apr 2013
# Last Modified: 12 May 2013 (23:28:49)
#
# Brief: 
# Input: 
# Output:
# 
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

# Set compiler
CC = cc      
# Set compiler flags for C
CFLAGS += -O3 -Wall --std=c99 -I/opt/local/include -I. -I$(HOME)/include/gc-7.2  
# Extra libraries to link
LDLIBS += -lm -L/opt/local/lib -lgsl -lgslcblas -L$(HOME)/include/gc-7.2  
# Am I on lifa?
HOST = $(findstring ymwang, $(shell hostname)) 

# Set default target (for make)
all: clear_screen clean run set_premissions 
	@echo Compiled and Run completed successfully 

# Clean screen
clear_screen:
	clear 
	clear

# Run 
run: main test
	./main	

# Linking the main program
main: main.o vector.o matrix.o qrdec.o qrback.o qrdet.o
test: test.o vector.o matrix.o qrdec.o qrback.o qrdet.o

# Makefile will do this automatically
#main.o: main.c
#test.o: test.c
#qrdec.o: qrdec.c 

# Linking header files
#main.c:   vector.h matrix.h qrlib.h 
#test.c:   vector.h matrix.h
#qrdec.c:  vector.h matrix.h

# Set read premissions using subshell (;)
set_premissions:
ifneq ($(HOST), ymwang ) 
	@(cd ../../../; chmod -R go+xr public_html)
	@echo Permissions set
endif

##########################################################

# Target clean all
clean: 
	@rm -f main test 
	@rm -f *.o 
	@echo Clean done

backup: qr.tgz

qr.tgz: makefile $(shell ls *.c)
	@tar --create --gzip --file=qr.tgz makefile plot.gpi *.c
	@tar --list --file=qr.tgz
	@echo Backup done
