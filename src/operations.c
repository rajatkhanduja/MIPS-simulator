/* This file defines the functions to perform the operations on the register file and the data memory. 
 * The action performed by each instruction is taken care of here 
 */
 
#include "../include/operations.h"

// NOTE : The case such as add $t0 $t0 1 (where immediate values are used) has been taken care of by alloting the space for the third register the value
// 32+immediate value (here the case of negative immediate values is ignored )

void add(int dest,int reg1,int reg2)
{	
//	if(reg1<32)
//		printf("Reading R[%d] ... R[%d]=%d\n",reg1,reg1,reg_file[reg1].val);
//	if(reg1<32)
//		printf("Reading R[%d] ... R[%d]=%d\n",reg1,reg1,reg_file[reg1].val);	
	
	int a=(reg1<32)?reg_file[reg1].val:reg1-32;
	int b=(reg2<32)?reg_file[reg2].val:reg2-32;
	reg_file[dest].val=a+b;
	pc++;
//	printf("Adding .. %d %d\n",a,b);
//	printf("Result in R[%d] = %d\n",dest,reg_file[dest].val);
	
	return;
}

 
void sub(int dest,int reg1,int reg2)
{	
//	if(reg1<32)
//		printf("Reading R[%d] ... R[%d]=%d\n",reg1,reg1,reg_file[reg1].val);
//	if(reg1<32)
//		printf("Reading R[%d] ... R[%d]=%d\n",reg1,reg1,reg_file[reg1].val);	
		
	int a=(reg1<32)?reg_file[reg1].val:reg1-32;
	int b=(reg2<32)?reg_file[reg2].val:reg2-32;
	
	reg_file[dest].val=a-b;
	pc++;
	
//	printf("Subtracting .. %d %d\n",a,b);
//	printf("Result in R[%d] = %d\n",dest,reg_file[dest].val);

	return;
}

void and_(int dest,int reg1,int reg2)
{	
//	if(reg1<32)
//		printf("Reading R[%d] ... R[%d]=%d\n",reg1,reg1,reg_file[reg1].val);
//	if(reg1<32)
//		printf("Reading R[%d] ... R[%d]=%d\n",reg1,reg1,reg_file[reg1].val);	
	

	int a=(reg1<32)?reg_file[reg1].val:reg1-32;
	int b=(reg2<32)?reg_file[reg2].val:reg2-32;
	
	reg_file[dest].val=a & b;
	pc++;
//	printf("\'And\'ing .. %d %d\n",a,b);
//	printf("Result in R[%d] = %d\n",dest,reg_file[dest].val);

	return;
}
 


void or_(int dest,int reg1,int reg2)
{
		
//	if(reg1<32)
//		printf("Reading R[%d] ... R[%d]=%d\n",reg1,reg1,reg_file[reg1].val);
//	if(reg1<32)
//		printf("Reading R[%d] ... R[%d]=%d\n",reg1,reg1,reg_file[reg1].val);
			
	int a=(reg1<32)?reg_file[reg1].val:reg1-32;
	int b=(reg2<32)?reg_file[reg2].val:reg2-32;
	
	reg_file[dest].val=a | b;
	pc++;
	
//	printf("\'Or\'ing .. %d %d\n",a,b);
//	printf("Result in R[%d] = %d\n",dest,reg_file[dest].val);
	
	return;
}
 
void slt(int dest,int reg1,int reg2)
{	
//	if(reg1<32)
//		printf("Reading R[%d] ... R[%d]=%d\n",reg1,reg1,reg_file[reg1].val);
//	if(reg1<32)
//		printf("Reading R[%d] ... R[%d]=%d\n",reg1,reg1,reg_file[reg1].val);

	int a=(reg1<32)?reg_file[reg1].val:reg1-32;
	int b=(reg2<32)?reg_file[reg2].val:reg2-32;
	
	reg_file[dest].val=(a<b)?1:0;
	pc++;
	
//	printf("\'SLT\'ing .. %d %d\n",a,b);
//	printf("Result in R[%d] = %d\n",dest,reg_file[dest].val);

	return;
}


void li(int dest,int val)
{
	
	reg_file[dest].val=val;
	pc++;
	
//	printf("Loading immediate value .. %d into R[%d]\n",val,dest);
//	printf("Result in R[%d] = %d\n",dest,reg_file[dest].val);
		
	return;
}


void move(int dest,int src)
{
//	printf("Moving from R[%d] to R[%d]\n",src,dest);
	
	reg_file[dest].val=reg_file[src].val;
	pc++;
	
//	printf("Result in R[%d] = %d\n",dest,reg_file[dest].val);	
	
	return;
}

void load_word(int dest,int addr,struct data_mem*dm)
{
//	printf("Loading word %s to R[%d]\n",dm->mem[addr].var_name,dest);
	
	reg_file[dest].val=(dm->mem[addr].val);
	pc++;
//	printf("Result in R[%d] = %d\n",dest,reg_file[dest].val);
	return;
}

void store_word(int dest,int addr,struct data_mem*dm)
{
//	printf("Storing R[%d] to word %s \n",dest,dm->mem[addr].var_name);
	dm->mem[addr].val=reg_file[dest].val;
	pc++;
	return;	
}
void jump(int pc_dest)
{	
//	printf("PC before JUMP : %d\n",pc);
	pc=labels.label[pc_dest].inst_num;
//	printf("PC after JUMP : %d\n",pc);
	return;
}

void beq(int reg1,int reg2,int pc_dest)
{
//	printf("PC before BEQ : %d\n",pc);
	if(reg_file[reg1].val==reg_file[reg2].val)
		pc=labels.label[pc_dest].inst_num;
	else
		pc++;
		
//	printf("PC after BEQ : %d\n",pc);	
	
	return;
}

void syscall()
{

	// Implementing only read_int and print_int features 

//	printf("IMPLEMENTING SYSCALL\n");
	if(reg_file[2].val==1)
	{
//		printf("Printing value in R[4]\n");
		printf("%d\n",reg_file[4].val);		// Prints the value in register $a0
	}
	else if(reg_file[2].val==5)
	{
		scanf("%d",&reg_file[2].val);
//		printf("Input %d being stored in R[2]\n",reg_file[2].val);
	}
	else if(reg_file[2].val==10)
	{
//		printf("Exiting program ...\n");
		exit(0);
	}	
	//printf("$v0=%d\n",reg_file[2].val);
	pc++;
	return;	
}
