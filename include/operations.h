/* File contains the function to execute the instructions passed in the MIPS program. */
#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include "registers.h"
#include "pc.h"
#include "data_mem.h"
#include "instruction_mem.h"

// Arithmetic operations 
void add (int dest,int reg1,int reg2);		// Stores the sum of values in reg1 and reg2 in dest.
void sub (int dest,int reg1,int reg2);		// Stores the difference of values in reg1 and reg2 in dest.
void and_(int dest,int reg1,int reg2);		// Stores the 'and' of values in reg1 and reg2 in dest.
void slt (int dest,int reg1,int reg2);		// Stores the slt of values in reg1 and reg2 in dest.
void or_ (int dest,int reg1,int reg2);		// Stores the 'or' of values in reg1 and reg2 in dest.

// Load Immediate
void li(int dest,int val);

// Load/Store instruction
void load_word(int dest,int addr,struct data_mem*dm);
void store_word(int dest,int addr,struct data_mem*dm);

// Branch & Jump instructions
void jump(int num);


// Syscall
void syscall();

// Move instruction
void move(int dest,int src);
 #endif		//End of file
