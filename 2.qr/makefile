# Date created: 27 Apr 2013
# Last Modified: 29 Apr 2013 (16:48:00)
#
# Brief: 
# Input: 
# Output:
# 
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

CC = cc             		          # Set compiler
CFLAGS += -O3 -Wall `gsl-config --cflags` # Set compiler flags for C
LDLIBS += `gsl-config --libs` 		  # Extra libraries to link
HOST = $(shell hostname) 		  # Am I on lifa?
#GRAPH = $(/usr/users/fedorov/bin/graph)

# Set default target (for make)
all: clean matrix 
	@echo Run completed successfully 

qr: main matrix
	./matrix

# Linking the main program
main : main.o 
#	$(CC) -o main main.o linterp.o bsearch.o 

main.o: main.c

matrix: matrix.o

matrix.o: matrix.c
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
