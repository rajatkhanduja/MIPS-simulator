/* Contains the definitions of the functions used to read the MIPS code from a file */


// TODO : Introduce string


#include "../include/file_functions.h"
#include <string.h>

int first_char(char*line)
{
	// Function to find the position of the first character (other than space,tab and enter)
	// and return the position
	// Return values (ret)
	// 0 (or greater) => position of the first character in the string
	// -1 		  => '\n' is the only character
	
	int i;
 	for(i=0;(line[i]==32 || line[i]==9) && line[i]!='\x0';i++);	// '\t'=9, 32 => <space>
	
	if(line[i]==10)
		return -1;
	else
	 	return i;
	// The return statement could have also been framed as 
	// return (line[i]=='\n')?-1:i;	
		
}

int read_file(FILE*file,struct instruct_mem*im,struct data_mem*dm)
{	
	// Function to read the file and modifies the input instruction memory (struct instruction_mem)
	// This function uses 'encode_to_opcode' function from the instruction_mem library.
	// This function also allocates space for the variables declared in the .data segment of the memory
	
	char line[100],temp[100];
	int i,k,j,line_num,val,dm_pos;
	line_num=i=k=j=dm_pos=0;
	
	int data_text=0;		// 0=> text , 1 => data (data_text is used to identify the segment of text and of data)
	
	while(!feof(file))
	{	
		line_num++;
		//Reads the file repeatedly (until end of file)
		fgets(line,99,file);
		i=first_char(line);
		
		//printf("%s",line);
		// If i=-1 or line[i]='#' (the line is a comment), skip the line
		if(i==-1 || line[i]=='#')
			continue;
			
		
		if(line[i]=='.')
		{
			i++;
			for(j=0;line[i]!=32 && line[i]!='\x0' && line[i]!=10 && line[i]!=9 && line[i]!='\n';i++,j++)
			{
				temp[j]=line[i];
				
			}
			
			temp[j]='\x0';
			
			if(!strcmp("data",temp))
				data_text=1;
			else if(!strcmp("text",temp))
				data_text=0;
			else
			{
				fprintf(stderr,"Syntax error at line number %d",line_num);
				exit(1);
			}
			
			continue;
		}
		
		if(data_text==0)
		{
			// Create a copy of the part of the string containing the instruction
		
			for(j=0;line[i]!='#' && line[i]!='\x0' && line[i]!='\n'; i++,j++)
				temp[j]=line[i];	      //Copies the string from the first character uptil '#' or end of line 	
			//Attach NULL at the end of temp
			temp[j]='\x0';
			
						
			//Encode the instruction using opcodes and register information
			int coded[5];		// Integer array that contains the encoded form of the instruction
			
			encode(temp,coded,dm,k);
			//printf("%d\n",coded[0]);
			if(coded[0])
			{	//printf("Loaded : %s",temp);
				//printf("\n%d %d %d %d",coded[0],coded[1],coded[2],coded[3]);
				load_instruct_mem(im,k,coded);
				k++;
				//printf("\n%d %d %d %d ",im->mem[k].cod[0],im->mem[k].cod[1],im->mem[k].cod[2],im->mem[k].cod[3]);
				//printf("k=%d\n",j);
			}
			
			//printf("k=%d\n",k);
				
		}
		
		else if(data_text==1)
		{
			val=0;
			// Presently only integer is handled
			for(j=0;line[i]!='#' && line[i]!='\x0' && line[i]!='\n' && line[i]!=32 && line[i]!=':'; i++,j++)
				temp[j]=line[i];	      //Copies the string from the first character uptil '#' or end of line 		
			temp[j]='\x0';
			for(;line[i]==32 || line[i]==':'; i++,j++);		// To read past the colon and spaces	
			for(;!(line[i]>='0' && line[i]<='9') && line[i]!='\x0';i++);	// To read till the end of the next word (which is 'word')
			
			if(line[i]!='\x0')
			{	//printf("%d",val);
				for(;line[i]>='0' && line[i]<='9';i++)
					val=val*10+(line[i]-'0');
						
			}
			//printf("%d",val);
			//printf("data_segment : %s %d\n",temp,val);
			store(dm_pos,dm,temp,val);
	
			dm_pos++;
				
		}	
		
	}
	return k;
}


