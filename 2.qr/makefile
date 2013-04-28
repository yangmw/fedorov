# Date created: 27 Apr 2013
# Last Modified: 28 Apr 2013 (23:54:46)
#
# Brief: 
# Input: 
# Output:
# 
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

CC = gcc             # Set compiler
CFLAGS = -O3 -Wall   # Set compiler flags for C
LDLIBS += -lm -lgc   # Extra libraries to link
HOST = $(shell hostname) # Am I on lifa?
#GRAPH = $(/usr/users/fedorov/bin/graph)

# Set default target (for make)
all: clean qr 
	@echo Run completed successfully 

qr: main
	./main > splot.dat 

# Linking the main program
main : main.o polinterp.o linterp.o qspline.o bsearch.o 
#	$(CC) -o main main.o linterp.o bsearch.o 

main.o: main.c	
#	$(CC) -c main.c -o main.o

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
	@rm -f main main.o 
	@echo Clean done

backup: interpolation.tgz

interpolation.tgz: makefile $(shell ls *.c)
	@tar --create --gzip --file=qr.tgz makefile plot.gpi *.c
	@tar --list --file=interpolation.tgz
	@echo Backup done
