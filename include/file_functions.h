#ifndef FILE_FUNC_INCLUDED
#define FILE_FUNC_INCLUDED

/* This file contains the declarations of the functions that are used in the program to manipulate files and 
 * read from the files. The input file is read for the MIPS code which is later executed (with the help of other files/modules)
 */


#include <stdio.h>
#include <string.h>
#include <malloc.h>

// Including libraries declaring the instruction memory and data memory structures
#include "instruction_mem.h"
#include "data_mem.h"

int read_file(FILE*file,struct instruct_mem*im,struct data_mem*dm);   //Reads the file and includes the necessary instructions into the Instruction Memory
					   //in the encoded form. 
void put_to_file(FILE*file,struct instruct_mem*im,int len,struct data_mem*dm);
char* int2bin(int input,int len,char*bin);

#endif 		//End of file
