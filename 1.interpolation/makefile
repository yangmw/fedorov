# Date created: 27 Apr 2013
# Last Modified: 10 Jun 2013 (00:46:24)
#
# Brief: "make" will compile and run a linear interpolation of 
# a given data set which will be produced from "main.c" and read
# into splot.dat. Gnuplot will then run the script splot.gpi and
# plot the data from splot.dat
# Input: n points (x,y)
# Output: plot of interpolant(s) and the points to be interpolated
# 
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

CC = cc              			 # Set compiler
CFLAGS += -O3 -Wall --std=c99 -I.        # Set compiler flags for C
LDLIBS += -lm        			 # Extra libraries to link
HOST = $(findstring ymwang, $(shell hostname)) # Am I on lifa?

# Set default target (for make)
all: clean run makeplots set_permissions
	@echo Run completed successfully 

makeplots:
	@rm -f *.o
	gnuplot plotA.gpl plotBC.gpl

run: main
	./main 1> plotA.dat 2> plotBC.dat 

# Linking the main program
main: main.o polinterp.o linterp.o cspline.o qspline.o bsearch.o 

set_permissions:
ifneq ($(HOST), ymwang-MBPro.local ) 
	@(cd ../../../; chmod -R go+xr public_html)
	@echo Permissions set
else
	@echo No Permissions set
endif

clean: 
	@rm -f main 
	@rm -f *.o
	@rm -f *.dat
	@rm -f *.svg
	@echo Clean done

backup: interpolation.tgz

interpolation.tgz: makefile $(shell ls *.c)
	@tar --create --gzip --file=interpolation.tgz makefile splot.gpi *.c
	@tar --list --file=interpolation.tgz
	@echo Backup done
