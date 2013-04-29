# Date created: 27 Apr 2013
# Last Modified: 29 Apr 2013 (16:55:15)
#
# Brief: "make" will compile and run a linear interpolation of 
# a given data set which will be produced from "main.c" and read
# into splot.dat. gnuplot will then run the script splot.gpi and
# plot the data from splot.dat
# Input: n points (x,y)
# Output: plot of interpolant(s) and the points to be interpolated
# 
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

CC = gcc             # Set compiler
CFLAGS = -O3 -Wall   # Set compiler flags for C
LDLIBS += -lm        # Extra libraries to link
HOST = $(shell hostname) # Am I on lifa?
#GRAPH = $(/usr/users/fedorov/bin/graph)

# Set default target (for make)
all: clean spline.dat makeplot set_permissions
	@echo Run completed successfully 

makeplot:
	gnuplot splot.gpi

spline.dat: main
	./main > splot.dat 

# Linking the main program
main : main.o polinterp.o linterp.o qspline.o bsearch.o 
#	$(CC) -o main main.o linterp.o bsearch.o 

main.o: main.c	
#	$(CC) -c main.c -o main.o

linterp.o: linterp.c bsearch.c  
#	$(CC) -c linterp.c -o linterp.o bsearch.o 

qspline.o: qspline.c bsearch.c
#	$(CC) -c $< -o 

bsearch.o: bsearch.c
#	$(CC) -c $< -o $@

polyinterp.o: polinter.c

# Set read premissions using subshell (;)
set_permissions:
ifneq ($(HOST), ymwang-MBPro.local ) 
	@(cd ../../../; chmod -R go+xr public_html)
	@echo Permissions set
else
	@echo No Permissions set
endif

##########################################################

# Target clean all
clean: 
	@rm -f main main.o linterp.o qspline.o bsearch.o polinterp.o
	@rm -f splot.dat
	@rm -f plot.svg
	@echo Clean done

backup: interpolation.tgz

interpolation.tgz: makefile $(shell ls *.c)
	@tar --create --gzip --file=interpolation.tgz makefile splot.gpi *.c
	@tar --list --file=interpolation.tgz
	@echo Backup done
