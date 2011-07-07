# Author : Rajat Khanduja
# Date : 17/2/11
# MIPS program to multiply two numbers
# Variables used 
#
# t1 : first number
# t2 : second number
# t3 : result
# t4 : temporary variable (counter)
# v0 : syscall variable	
#

	.data
	num1:	.word 23
	num2:	.word 3 
	num3:	.word 0
	
	.text
	
main :	############ ACCEPT INTEGERS ###################
	# Accept an integer
#	li $v0,5		# $v0 = read_int 
#	syscall			# system call to read integer
	
	# load first integer
	lw $t1,num1		# $t1=num1
	
	# Move integer accepted to $t1
#	move $t1,$v0		# $t1 = $v0
	
	
	# Accept an integer
#	li $v0,5		# $v0 = read_int 
#	syscall			# system call to read integer


	#load second integer
	lw $t2,num2		# $t2 = num2
			
	# Move integer accepted to $t2
#	move $t2,$v0		# $t2 = $v0
	##################################################
	
	
	
	#### SET COUNTER = 0 AND RESULT VARIABLE = 0 ###### 
	
	# Load 0 in t4 ( this is a temporary variable acting like a counter)
	li $t4,0		# $t4 = 0
	
	# Set t3 = 0 
	li $t3,0		# $t3 = 0
	
	#####################################################
	
	################# MULTIPLY #########################
	# Start multiplication (by repetitive adding t1 t2 times)
begin :	beq $t4,$t2, end	# if t4=t2, go to end 
	add $t3,$t3,$t1		# $t3 = $t3 + $t1
	add $t4,$t4,1		# $t4 = $t4 + 1
	j begin			# goto begin
	
	#####################################################
end : 
	################ PRINT RESULT #####################
	# Print the result in $t3 
	li $v0,1		# load print_int in $v0
	move $a0,$t3		# $a0 = $t3
	syscall  
	###################################################

	############## STORE RESULT IN MEM #############
	sw $t3 num3		# num3 = $t3

	################### Exit ######################
	li $v0,10		# $v0 = 10 (exit code)
	syscall			# exits the program
	##############################################	
