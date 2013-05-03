# Date created: 27 Apr 2013
# Last Modified: 30 Apr 2013 (14:58:20)
#
# Brief: 
# Input: 
# Output:
# 
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

CC = gcc             		          # Set compiler
CFLAGS += -O3 -I/opt/local/include # Set compiler flags for C
LDLIBS += -L/opt/local/lib -lgsl -lgslcblas  # Extra libraries to link
HOST = $(findstring ymwang, $(shell hostname)) # Am I on lifa?
#GRAPH = $(/usr/users/fedorov/bin/graph)

# Set default target (for make)
all: clean qr set_premissions 
	@echo Compiled and Run completed successfully 

qr: main 
	./main

# Linking the main program
main: main.o 
#	$(CC) -o main main.o linterp.o bsearch.o 
main.o: main.c

# Set read premissions using subshell (;)
set_premissions:
ifneq ($(HOST), ymwang ) 
	@(cd ../../../; chmod -R go+xr public_html)
	@echo Permissions set
endif

##########################################################

# Target clean all
clean: 
	@rm -f main main.o  
	@echo Clean done

backup: interpolation.tgz

interpolation.tgz: makefile $(shell ls *.c)
	@tar --create --gzip --file=qr.tgz makefile plot.gpi *.c
	@tar --list --file=qr.tgz
	@echo Backup done
