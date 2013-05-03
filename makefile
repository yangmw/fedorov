# Filename: makefile
# Date created: 30 Apr 2013
# Last Modified: 03 May 2013 (15:31:46)
#
# Brief: This is a makefile that takes backup and makes a zipfile of
# different folders
# Input:
# Output: Different zip folders
#
# License:copyleft
# Author:Yang Min Wang (ymwang@chem.au.dk)

w0 = test
w1 = 0.hello
w2 = 1.interpolation
w3 = 2.qr
w4 =
w5 = 
w6 = 
w7 =

all: clean backup 

clean:
	-rm -rf */.DS_Store
	-rm -f *.zip
	@(cd $(w0); make clean)
	@(cd $(w1); make clean)
	@(cd $(w2); make clean)
	@(cd $(w3); make clean)

backup:
	zip -r numeric.zip $(w0) $(w1) $(w2) $(w3) 
