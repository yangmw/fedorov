// Filename: lib.c
// Date created: 03 Jun 2013
// Last Modified: 08 Jun 2013 (17:42:47)
//
// Brief:
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <lib.h>
#include <string.h>

void title(char *s){
    static const char padder[] = "----------------------------\n";
    printf(padder);
    printf("%s \n",s);
    printf(padder);
    printf("\n");
}
