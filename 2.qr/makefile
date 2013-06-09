# Date created: 27 Apr 2013
# Last Modified: 09 Jun 2013 (23:58:09)
#
# Brief: 
# 
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

# Set compiler
CC = cc      
# Set compiler flags for C
CFLAGS += -O3 -Wall --std=c99 -I/opt/local/include -I. -I$(HOME)/include/gc-7.2/include \
	  -I/usr/users/fedorov/include -I/usr/users/fedorov/lib
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

# Run the main program
run: main 
	./main

# Testing the QR algorithm:
test: clear_screen clean runtest set_premissions
#./runtest > test.out 
	./runtest
	@echo Test compiled and ended successfully 


# Linking the main program
main: main.o vector.o matrix.o qrdec.o qrback.o qrdet.o inverse.o lib.o
runtest: vector.o matrix.o qrdec.o qrback.o qrdet.o inverse.o lib.o

# Set read premissions using subshell (;)
set_premissions:
ifneq ($(HOST), ymwang ) 
	@(cd ../../../; chmod -R go+xr public_html)
	@echo Permissions set
endif

##########################################################

# Target clean all
clean: 
	@rm -f main runtest 
	@rm -f *.o
	@rm -f *.dat
	@rm -f *.out	
	@echo Clean done

