/* This file defines the functions to handle store/retrieve operations on data memory */

#include "../include/data_mem.h"

void store(int pos,struct data_mem *dm,char*var_name,int val)
{
	if(pos>=1024)
	{
		printf("Not enough space");
		exit(2);				// exit code 2 => not enough space.
	}
	
	//printf("%d",val);
	strcpy(dm->mem[pos].var_name,var_name);
	dm->mem[pos].val=val;
	//printf("%d",(dm->mem[pos].val));
	return;
}

int get_mem_location(char*var_name,struct data_mem *dm)
{
	int i;
	for(i=0;i<1024;i++)
	{
		if(!strcmp(var_name,dm->mem[i].var_name))
			return i;
	}
	
	// If no string matches, hence there's an incorrect reference to an address. Show error
	printf("Undefined reference : %s", var_name);
}


