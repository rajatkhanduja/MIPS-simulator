#ifndef REGISTERS_H_INCLUDED
#define REGISTERS_H_INCLUDED

/* File to declare the struct reg ; and delcare the functions that are used to manipulate registers. */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct reg
{
	char alt_name[4];			// Stores names like $t0, $fp, $at
	int val;
};


extern struct reg reg_file[32];


void init_reg_file();	   // To initialise the register file (This is has to be called before the first reference to registers)
int reg_num(char*alt_name);	// Returns the number of the register given the alternate name.

#endif 	// End of file

