/* Contains the definition of the functions defined in 'instruction_mem.h' */
// Functions here are used to encode and decode instructions. 

#include "../include/instruction_mem.h"


//Defining the opcodes 
extern const char funct[][8]={"add","sub","slt","and","or","syscall","beq","lw","sw","li","move","j"};
extern const int opcode[]={ADD,SUB,SLT,AND,OR,SYSCALL,BEQ,LW,SW,LI,MOVE,J};

int* encode(char*input,int*coded,struct data_mem*dm,int num)
{
	char inst[10];		// Holds the instruction (like add,sub,move,b)
	int j,i=0;
	char*ptr;
	
	/****** BEFORING ENCODING TAKE CARE OF THE LABELS ****************/
			
	//If there is no ':', continue.	
	if(ptr=strchr(input,':'))
	{
		// For label, coded[0]=0 (this way it is not loaded into the instruction memory if this value doesn't change)
		coded[0]=0;
		int already_exists=0;			// Variable that indicates that the label is present in the memory
					// This is done in case a reference is provided to the label before its is encountered.
		for(;input[i]!=*ptr && input[i]!=32;i++)
			inst[i]=input[i];
		inst[i]='\x0';
		
		
		for(j=0;j<label_num;j++)
		{
			if(!strcmp(labels.label[j].name,inst))
			{
				if(labels.label[j].inst_num==-1)
				{
					already_exists=1;
					labels.label[j].inst_num=num;
					return;
				}
				else
				{
					printf("Label %s has been used more than once \n",inst);
					exit(4);		// Label re-use
				}
			}
		}
		
		if(!already_exists)		
		{
			strcpy(labels.label[label_num].name,inst);
			labels.label[label_num].inst_num=num;
			label_num++;	
		
			//printf("%d",i);
			for(;input[i]==32 || input[i]==':' || input[i]==9;i++);
		
			//printf("char=%c\n",input[i]);
		
			if(input[i]=='\n' || input[i]=='\x0' || input[i]=='#')
				return;
			
		}		
	}		
	/****************************************************************/
	
	
	for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=9;i++,j++)
	{
		//Copy the first word 
		inst[j]=input[i];
			
	}
	inst[j]='\x0';			// Add NULL at the end of the copied string
	
	for(j=0;j<=11;j++)
	{
		if(!strcmp(inst,funct[j]))
			break;
		
	}
	
	if(j<=11)
		coded[0]=opcode[j];	// Allots the opcode of the instruction as per the opcode array (in instruction_mem.h)
	else 
	{
		printf("Unknown Instruction : %s",inst);
		exit(3);
	}
		
	/***************** DEALING WITH R-TYPE INSTRUCTION (ADD/SUB/AND/OR/SLT)****************/
	if(coded[0]==ADD||coded[0]==SUB||coded[0]==AND||coded[0]==OR||coded[0]==SLT)
	{	
		// If the instruction is R-type
		// Get the first register input
		
		char reg[3];
		int j;	
	
			
	
		for(;input[i]==',' || input[i]==32 || input[i]=='$';i++);		// Move to the next register
		
		// It could be an immediate value or a register. If preceded by $, it is a register.
		if(input[i-1]!='$')	
		{
			int val=0;
			// Get the entire number.
			for(;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#';i++)
				val=val*10+(input[i]-'0');
		
			// To store the immediate values numbers greater than or equal to 32 are used.	
			coded[1]=32+val;
		}
		else
		{
			for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++)
			{	
				reg[j]=input[i];
			
			}	
			reg[j]='\x0';				// Add NULL character to terminate string
			coded[1]=reg_num(reg);
		}
		
		for(;input[i]==',' || input[i]==32 || input[i]=='$' ;i++);		// Move to the next register
		
		// It could be an immediate value or a register. If preceded by $, it is a register.
		if(input[i-1]!='$')	
			coded[2]=32+(input[i]-'0');
		else
		{
			for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++)
			{	
				reg[j]=input[i];
			
			}	
			reg[j]='\x0';				// Add NULL character to terminate string
			coded[2]=reg_num(reg);
		}
		
		for(;input[i]==',' || input[i]==32 || input[i]=='$';i++);		// Move to the next register
		
		// It could be an immediate value or a register. If preceded by $, it is a register.
		if(input[i-1]!='$')	
			coded[3]=32+(input[i]-'0');
		else
		{
			for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++)
			{	
				reg[j]=input[i];
				
			}	
			reg[j]='\x0';				// Add NULL character to terminate string
			coded[3]=reg_num(reg);
		}
		//printf ("%d %d %d %d",coded[0],coded[1],coded[2],coded[3]);	 
	}
	
	/******************** DEALING WITH Load Immediate *****************/
	else if(coded[0]==LI)
	{
		char reg[3];
		int j;	
		

		for(;input[i]==',' || input[i]==32 || input[i]=='$';i++);		// Move to the next register
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++)
		{	
			reg[j]=input[i];
		
		}	
		reg[j]='\x0';				// Add NULL character to terminate string
		coded[1]=reg_num(reg);
		
		
		// Next information is the value to be stored.
		for(;input[i]==',' || input[i]==32 || input[i]=='$';i++);		// Move to the next register
		
		coded[2]=0;
		for(;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++)
		{	
			coded[2]=coded[2]*10+(input[i]-'0');
		}	
		//printf ("%d %d %d",coded[0],coded[1],coded[2]);
	}
	
	else if (coded[0]==LW || coded[0]==SW)
	{
		/* These instructions have a register and then a memory destination */
		
		char reg[3],var_name[20];
		int j;	
	
		for(;input[i]==',' || input[i]==32 || input[i]=='$';i++);		// Move to the next register
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++)
		{	
			reg[j]=input[i];
		
		}	
		reg[j]='\x0';				// Add NULL character to terminate string
		coded[1]=reg_num(reg);
		
		for(;input[i]==',' || input[i]==32;i++);		// Move to the memory location given
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++)
		{	
			var_name[j]=input[i];
		
		}	
		var_name[j]='\x0';
		
		// Store the mem_location (in data memory)
		coded[2]=get_mem_location(var_name,dm);
		
		//printf ("%d %d %d",coded[0],coded[1],coded[2]);
	}
	/******************************************************************************/
	
	
	/************************* DEALING WITH MOVE *******************************/
	else if(coded[0]==MOVE)
	{
		char reg[3];
		int j;
	
		for(;input[i]==',' || input[i]==32 || input[i]=='$';i++);		// Move to the next register
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++)
		{	
			reg[j]=input[i];
		
		}	
		reg[j]='\x0';				// Add NULL character to terminate string
		coded[1]=reg_num(reg);
		
		for(;input[i]==',' || input[i]==32 || input[i]=='$';i++);		// Move to the next register
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++)
		{	
			reg[j]=input[i];
		
		}	
		reg[j]='\x0';				// Add NULL character to terminate string
		coded[2]=reg_num(reg);
	}
	/*************************************************************************************/
	
	/******************************* DEALING WITH beq AND j *****************************/
	
	else if(coded[0]==BEQ)
	{
		char reg[3];
		char label[20];
		
		int j;
	
		for(;input[i]==',' || input[i]==32 || input[i]=='$';i++);		// Move to the next register
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++)
		{	
			reg[j]=input[i];
		
		}	
		reg[j]='\x0';				// Add NULL character to terminate string
		coded[1]=reg_num(reg);
		
		for(;input[i]==',' || input[i]==32 || input[i]=='$';i++);		// Move to the next register
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++)
		{	
			reg[j]=input[i];
			
		}	
		reg[j]='\x0';				// Add NULL character to terminate string
		coded[2]=reg_num(reg);
		
		
		for(;input[i]==',' || input[i]==32;i++);		// Move to the label
		
		// Copy the label
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++)
		{
			label[j]=input[i];
			
		}	
		label[j]='\x0';				// Add NULL character to terminate string
		
		coded[3]=label_pos(label);
	}
	
	else if(coded[0]==J)
	{
		char label[20];
		int j;
		
		for(;input[i]==32;i++);		// Move to the label
		
		// Copy the label
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++)
		{
			label[j]=input[i];
		}	
		label[j]='\x0';				// Add NULL character to terminate string
		
		coded[1]=label_pos(label);
		
	
	}
	
	/**********************************************************************************/
	return coded;	
}	



void load_instruct_mem(struct instruct_mem*im,int mem_pos,int*instruct)
{
	//printf("\ninside_load_inst :%d %d %d %d",instruct[0],instruct[1],instruct[2],instruct[3]);
	int j=0;
	for(j=0;j<4;j++)
		im->mem[mem_pos].cod[j]=instruct[j];
	
	//printf("\n%d %d %d %d ",im->mem[mem_pos].cod[0],im->mem[mem_pos].cod[1],im->mem[mem_pos].cod[2],im->mem[mem_pos].cod[3]);
}



void decode(int*encoded_inst,struct data_mem*dm)
{
	//printf("%d %d %d %d\n",encoded_inst[0],encoded_inst[1],encoded_inst[2],encoded_inst[3]);
	switch(encoded_inst[0])
	{
		case ADD :	
				add(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
				break;
		case SUB :
				sub(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
				break;
		case AND :
				and_(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
				break;
		case OR  :
				or_(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
				break;		
		case SLT :
				slt(encoded_inst[1],encoded_inst[2],encoded_inst[3]);	
				break;
		
		case LI	 : 	li(encoded_inst[1],encoded_inst[2]);
				break; 
		
		case SYSCALL : 
				syscall();
				break;
		case MOVE :
				move(encoded_inst[1],encoded_inst[2]);
				break;
		case LW   :
				load_word(encoded_inst[1],encoded_inst[2],dm);
				break;
		case SW   :
				store_word(encoded_inst[1],encoded_inst[2],dm);
				break;
		case J	  :	
				jump(encoded_inst[1]);
				break;
		case BEQ  :
		
				beq(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
				break;
				
		default   :	printf("Unknown instruction");
				pc++;
				//exit(3);			// Exit code 3 => unknown instruction
	}
	return;
}


int label_pos(char*name)
{
	int i;
	
	for(i=0;i<=label_num;i++)
	{
		if(!strcmp(labels.label[i].name,name))
			return i;
	}
	
	// This means the reference has not been found yet. Store it in the array 
	strcpy(labels.label[label_num].name,name);
	labels.label[label_num].inst_num=-1;
	
	return label_num++;
	
}


void execute(struct instruct_mem*im,int fin,struct data_mem*dm)
{
	pc = 0;			// Starts with the program counter at zero
	char a;
	while(pc<=fin)
	{
		printf("pc=%d\n",pc);
		decode(im->mem[pc].cod,dm);	
		//scanf("%c",&a);
	}
}
