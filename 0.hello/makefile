# Filename: makefile
# Date created: 27 Apr 2013
# Last Modified: 10 May 2013 (16:25:24)
#
# Brief: makefile for the helloworld program 
# Input: N/A
# Output: print out "hello, ymwang" and redirects into file
#
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

CC = cc              # Set compiler
CFLAGS = -O3 -Wall   # Set compiler flags for C

HOST = $(findstring ymwang, $(shell hostname)) # Am I on lifa?

# Set default targets (for make)
all: A B set_permissions 
	@echo Run completed successfully 

A: out.A.txt

out.A.txt: hellouser
	./hellouser > out.A.txt

hellouser: hellouser.c

B: out.B.txt

out.B.txt: main
	./main > out.B.txt

# Linking the main program
main: main.o hello.o user.o

# These three lines may be omitted (Make will figure out)
main.o: main.c
hello.o: hello.c
user.o: user.c

# Set read premissions using subshell (;)
set_permissions:
ifneq ($(HOST), ymwang ) 
	@(cd ../../../; chmod -R go+xr public_html)
	@echo Permissions set
endif

##########################################################

# Target clean all
clean: cleanA cleanB
	-rm -f *.tgz
	@echo Clean done

cleanA: 
	-rm -f hellouser out.A.txt
cleanB: 
	-rm -f main out.B.txt
	-rm -f *.o

cheack: checkA checkB

checkA: out.A.txt
	@echo "checking target A"
	@printf "hello, ymwang" > correct.txt
	@diff --brief correct.txt out.A.txt
	@echo "target A seems to be ok"
	@rm -f correct.txt

checkB: out.B.txt
	@echo "checking target B"
	@printf "hello, ymwang" > correct.txt
	@diff --brief correct.txt out.B.txt
	@echo "target B seems to be ok"
	@rm -f correct.txt 

backup: hello.tgz
	ssh $(shell whoami)@lifa.phys.au.dk \
	'base64 $(shell pwd)/hello.tgz \
	| mailx -s "hello backup" $(shell whoami)@phys.au.dk'

hello.tgz: makefile $(shell ls *.c)
	tar --create --gzip --file=hello.tgz makefile *.c
	tar --list --file=hello.tgz

	
