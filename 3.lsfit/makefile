# Filename: makefile
# Date created: 13 May 2013
# Last Modified: 17 Jun 2013 (17:08:28)
#
# Brief: Makefile for running least squre fit
# Input:
# Output:
#
# License: copyleft
# Author: Yang Min Wang (ymwang@chem.au.dk)

# Set compiler
#CC = cc
# Set compiler flags for C
CFLAGS += --std=c99 -Wall -O `gsl-config --cflags`
LDLIBS += `gsl-config --libs`
OBJ     = matrix.o vector.o lsfit.o qrdec.o qrback.o qrinverse.o lib.o

# Extra libraries to link
LDLIBS += `gsl-config --libs`
#LDLIBS += -lm -L/opt/local/lib -lgsl -lgslcblas 

#Set default target (for make)
all: plotA.svg set_premissions 
	@echo Compiled and Run completed successfully 

# Run the main program
plotA.svg: plotA.gpl lsfit.dat
	gnuplot plotA.gpl

lsfit.dat: main makefile
	./main > lsfit.dat 

# Testing the QR algorithm:
test: runtest set_premissions
	./runtest 
	@echo 
	@echo Test compiled and ended successfully, see test.dat 

# Linking
main: $(OBJ)
runtest: $(OBJ)

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
	@rm -f *.svg
	@rm -f *.dat 
	@echo Clean done

