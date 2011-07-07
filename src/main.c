#include<stdio.h>
#include "../include/file_functions.h"
#include "../include/instruction_mem.h"
#include "../include/registers.h"


int main(int argc,char*args[])
{
	init_reg_file();		// Initialize the register file
	label_num=0;
	
	FILE*f;
	f=fopen(args[1],"r");
	struct instruct_mem *im=calloc(sizeof(struct instruct_mem),1);
	struct data_mem *dm=calloc(sizeof(struct data_mem),1);
	int len=read_file(f,im,dm);	// len stores the largest possible value of pc.
	
	fclose(f);
	execute(im,len,dm);
	
	return 0;
}
