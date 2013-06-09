# Filename: makefile
# Date created: 13 May 2013
# Last Modified: 29 May 2013 (14:40:08)
#
# Brief: Makefile for running least squre fit
# Input:
# Output:
#
# License: copyleft
# Author: Yang Min Wang (ymwang@chem.au.dk)

# Set compiler
CC = cc      
# Set compiler flags for C
CFLAGS += -O3 -Wall --std=c99 -I/opt/local/include -I. -I$(HOME)/include/gc-7.2  
# Extra libraries to link
LDLIBS += -lm -L/opt/local/lib -lgsl -lgslcblas -L$(HOME)/include/gc-7.2  
# Am I on lifa?
HOST = $(findstring ymwang, $(shell hostname)) 

# Set default target (for make)
all: clear_screen clean run plotA plot set_premissions 
	@echo Compiled and Run completed successfully 

# Clean screen
clear_screen:
	clear 
	clear

# PlotA
plotA: 
	gnuplot plotA.gpi 

plot:
	gnuplot plot.gpi

# Run 
run: main 
	./main > plotA.dat	

# Linking the main program
main: main.o vector.o matrix.o 
test: test.o vector.o matrix.o

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
	@rm -f *.svg
	@rm -f plotA.dat 
	@echo Clean done

