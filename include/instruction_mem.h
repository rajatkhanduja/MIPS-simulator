#ifndef INSTRUCTION_MEM_H_INCLUDED
#define INSTRUCTION_MEM_H_INCLUDED


/* File contains the declarations of the functions and the struct of the instruction memory. 
 * The instruction memory is fed the instructions in the encoded format using functions in
 * 'file_functions.h'. 
 */
 
#include <stdio.h>
#include <string.h>
#include "data_mem.h"
#include "registers.h"
#include "operations.h"
#include "pc.h"

// Defining opcodes
#define ADD 0b100000		//ADD   => 32
#define SUB 0b100010		//SUB   => 34
#define AND 0b100100		//AND   => 36
#define SLT 0b101010		//SLT   => 42
#define OR 0b100101		//OR    => 37
#define LI 0b100001		//LI    => 33
#define SYSCALL 0b001100	//SYSCALL=>12
#define LW 0b100011		//LW    => 35
#define SW 0b101011		//SW    => 43
#define J 0b000010		//J     => 2
#define BEQ 0b000100		//BEQ   => 4		
#define MOVE 0b000110		//MOVE  => 6


struct instruct_mem_element
{
	int cod[4];
	char*c;
};


struct instruct_mem
{
	struct instruct_mem_element mem[1024];
	
};

struct label_table
{
	struct label_element{
		char name[20];
		int inst_num;	
	}label[100];
}labels;
int label_num;

/********* FUNCTIONS TO ENCODE-DECODE THE INSTRUCTION ************/

int* encode(char*input,int*coded,struct data_mem*dm,int num);	 //Function to convert text into opcodes.
void decode(int*encoded_inst,struct data_mem*dm);	// Decode and perform the instructions.

/*****************************************************************/


/********** FUNCTIONS TO LOAD & EXECUTE THE INSTRUCTIONS *********/

void load_instruct_mem(struct instruct_mem*im,int mem_pos,int*instruct);  //Function to load the instruction into the instruction memory. 
void execute(struct instruct_mem*im,int fin,struct data_mem*dm);

/*****************************************************************/

int label_pos(char*name);			// Returns the index of the label structure storing the label-name

 #endif //End of file
