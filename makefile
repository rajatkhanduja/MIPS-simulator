OBJ=obj
INLCUDE=include
BIN=bin
SRC=src

all: clean ${OBJ}/instruct_mem.o ${OBJ}/file_functions.o ${OBJ}/registers.o ${OBJ}/operations.o ${OBJ}/data_mem.o ${OBJ}/main.o 
	gcc -g ${OBJ}/instruct_mem.o ${OBJ}/file_functions.o ${OBJ}/registers.o ${OBJ}/data_mem.o ${OBJ}/operations.o ${OBJ}/main.o -o ${BIN}/simulator

${OBJ}/data_mem.o: ${SRC}/data_mem.c
	gcc -g -c ${SRC}/data_mem.c -o ${OBJ}/data_mem.o

${OBJ}/instruct_mem.o: ${SRC}/instruct_mem.c
	gcc -g -c ${SRC}/instruct_mem.c -o ${OBJ}/instruct_mem.o
	
${OBJ}/file_functions.o: ${SRC}/file_functions.c
	gcc -g -c ${SRC}/file_functions.c -o ${OBJ}/file_functions.o

${OBJ}/registers.o: ${SRC}/registers.c
	gcc -g -c ${SRC}/registers.c -o ${OBJ}/registers.o

${OBJ}/operations.o: ${SRC}/operations.c
	gcc -g -c ${SRC}/operations.c -o ${OBJ}/operations.o

${OBJ}/main.o:${SRC}/main.c
	gcc -g -c ${SRC}/main.c -o ${OBJ}/main.o
	
clean:
	rm -f ${OBJ}/*
