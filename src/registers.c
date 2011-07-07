#include "../include/registers.h"
// TODO Complete the register file 

struct reg reg_file[32];

void init_reg_file()
{
	// Initialises the register file. This function should be called 
	// before the first time the registerfile is accessed.	


	strcpy(reg_file[0].alt_name,"zero");
	strcpy(reg_file[1].alt_name,"at");
	strcpy(reg_file[2].alt_name,"v0");
	strcpy(reg_file[3].alt_name,"v1");
	strcpy(reg_file[4].alt_name,"a0");
	strcpy(reg_file[5].alt_name,"a1");
	strcpy(reg_file[6].alt_name,"a2");
	strcpy(reg_file[7].alt_name,"a3");
	strcpy(reg_file[8].alt_name,"t0");
	strcpy(reg_file[9].alt_name,"t1");
	strcpy(reg_file[10].alt_name,"t2");
	strcpy(reg_file[11].alt_name,"t3");
	strcpy(reg_file[12].alt_name,"t4");
	strcpy(reg_file[13].alt_name,"t5");
	strcpy(reg_file[14].alt_name,"t6");
	strcpy(reg_file[15].alt_name,"t7");
	strcpy(reg_file[16].alt_name,"s0");
	strcpy(reg_file[17].alt_name,"s1");
	strcpy(reg_file[18].alt_name,"s2");
	strcpy(reg_file[19].alt_name,"s3");
	strcpy(reg_file[20].alt_name,"s4");
	strcpy(reg_file[21].alt_name,"s5");
	strcpy(reg_file[22].alt_name,"s6");
	strcpy(reg_file[23].alt_name,"s7");
	strcpy(reg_file[24].alt_name,"t8");
	strcpy(reg_file[25].alt_name,"t9");
	strcpy(reg_file[26].alt_name,"k0");
	strcpy(reg_file[27].alt_name,"k1");
	strcpy(reg_file[28].alt_name,"gp");
	strcpy(reg_file[29].alt_name,"sp");
	strcpy(reg_file[30].alt_name,"fp");
	strcpy(reg_file[31].alt_name,"ra");
	
	return;
}

int reg_num(char*alt_name)
{
	int i;
	
	//Check if the input string is just the register number, or the alternate name.
	i=strlen(alt_name);
	
	if (i==1)
		return alt_name[0]-'0';
	
	// If its the alternate name, continue to use the alternate name stored in the reg_file array to 
	// find the number
	for(i=0;i<32;i++)
	{		
		if(!strcmp(reg_file[i].alt_name,alt_name))
			break;
	}
	
	if(i!=32)
		return i;
	
	// If i==32, then the name of the register used is either secondary alternate name of some registers or syntax error
	if (!strcmp(alt_name,"s8"))
		return 30;
	else 
	{
		printf("Syntax error. %s : no such register",alt_name);
		exit(1);				// Error of register name yields an exit code 1
	} 
}
