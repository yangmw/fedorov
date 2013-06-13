# Date created: 27 Apr 2013
# Last Modified: 12 Jun 2013 (17:02:39)
#
# Brief: 
# 
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

# Set compiler
CC = gcc
# Set compiler flags for C
CFLAGS += -O3 -Wall --std=c99 -I/opt/local/include -I. -I$(HOME)/include/gc-7.2/include \
	  -I/usr/users/fedorov/include -I/usr/users/fedorov/lib
# Extra libraries to link
LDLIBS += -lm -L/opt/local/lib -lgsl -lgslcblas -L$(HOME)/include/gc-7.2  
# Am I on lifa?
HOST = $(findstring ymwang, $(shell hostname)) 

N = 2 10 50 100 200 300 400 500 600 700 800 900 1000

#Set default target (for make)
all: clear_screen clean plotB.svg set_premissions 
	@echo Compiled and Run completed successfully 

# Clean screen
clear_screen:
	clear 
	clear

# Run the main program
plotB.svg: plotB.gpl time.dat
	gnuplot plotB.gpl

time.dat: main makefile 
	@echo "#Timings for qr and qr_gsl algorithm" > time_qr.dat 
	@echo "#N t_qr[s] t_qr_gsl[s]" >> time_qr.dat
	@$(foreach var, $(N), ./main $(var) 2>> time_qr.dat;)
   
# Testing the QR algorithm:
test: clear_screen clean runtest set_premissions
	./runtest > test.dat
	@echo 
	@echo Test compiled and ended successfully, see test.dat 

# Linking the main program
main: vector.o matrix.o qrdec.o qrback.o qrdet.o inverse.o lib.o
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
	@rm -f *.svg
	@rm -f *.o
	@rm -f *.dat
	@rm -f *.out	
	@echo Clean done

