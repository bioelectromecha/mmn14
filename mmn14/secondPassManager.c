#include "header.h"



/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
void secondPassManager(FILE *file, Data * data){
    char lineHolder[MAX_LINE_LEN+1];
    data->ic = 0;
    fseek (file, 0, SEEK_SET);
    /* NULL means EOF. When we reach EOF it means we're done */
    while(fgets(lineHolder,MAX_LINE_LEN,file) != NULL ){
        data->line=lineHolder;
        if(lineHandlerSecondPass(&data)==0){
            printf("[Error] on line %d: Fatal Error, continuing to next file if exists\n",data->lc);
        }
        data->lc++;
    }
}

/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int lineHandlerSecondPass(Data * data, FILE * file){
    char tag[31];
    /*should do nothing if there's a tag at the start of the line*/
    if(lineEmptyCheck(data)==1){
        return 1;
    }
    if(lineCommentCheck(data)==1){
        return 1;
    }
    getTag(data,tag);
    if(*(data->line)=='.'){
        return 1;
    }

    return secondPassCommandManager(data);
}

/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int secondPassCommandManager(Data * data){
    int numOfOperands;
    char cmd[5];
    /* get the command */
    sscanf(data->line, "%4s", cmd);
    data->line+=strlen(command);
    /* get number of operands needed for this command */
    numOfOperands = getNumOfOperands(cmd;

    if(numOfOperands==0){
        return zeroOperandsCommandHandler(data,cmd);
    }else if(numOfOperands==1){
        return oneOperandsCommandHandler(data,cmd);
    }else if(numOfOperands==2){
        return twoOperandsCommandHandler(data,cmd);
    }
    returm 0;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/

int zeroOperandsCommandHandler(Data * data, char * cmd){
    addEmptyCommand(data,cmd);
}

/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int oneOperandsCommandHandler(Data * data, char * cmd){
    int addressingMethod;
    char operand[30];
    operand = getDestinationOperand(Data * data, operand);
    addressingMethod = getAddressingMethod(operand);
    if(checkDestinationOperandAddressing(addressingMethod,cmd)){
        printf("[Error] on line %d: illegal addressing for this command\n",data->lc);
        return 0;
    }
    if(addressingMethod == TAG_OPERAND){
        if(checkIfTagExists(data,operand)==0){
            printf("[Error] on line %d: tag does not exist\n",data->lc);
            return 0;
        }
         addTagCommand(data, cmd, operand);
    }
}
/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int twoOperandsCommandHandler(Data * data, char * cmd){
    int addressingMethod1;
    int addressingMethod2;
    char operand1[30];
    char operand2[30];
    operand1 = getSourceOperand(Data * data, operand1);
    operand2 = getDestinationOperand(Data * data, operand2)
    addressingMethod1 = getAddressingMethod(operand1);
    addressingMethod2 = getAddressingMethod(operand2);
    if(checkSourceOperandAddressing(addressingMethod1,cmd)){
        printf("[Error] on line %d: illegal addressing for this command\n",data->lc);
        return 0;
    }
    if(checkDestinationOperandAddressing(addressingMethod2,cmd)){
        printf("[Error] on line %d: illegal addressing for this command\n",data->lc);
        return 0;
    }
    if(addressingMethod1 == TAG_OPERAND){
        if(checkIfTagExists(data,operand)==0){
            printf("[Error] on line %d: tag does not exist\n",data->lc);
            return 0;
        }
    }
     if(addressingMethod2 == TAG_OPERAND){
        if(checkIfTagExists(data,operand)==0){
            printf("[Error] on line %d: tag does not exist\n",data->lc);
            return 0;
        }
    }
    addCommand(???);
}

typedef struct{
   unsigned int e_r_a : 2;
   unsigned int destination_addressing : 2;
   unsigned int source_addressing : 2;
   unsigned int opcode = 4;
   unsigned int group = 2;
   unsigned int rnd = 2;
   unsigned int unused =1;
} Instruction;

int addZeroOperandCommand(Data * data, char * cmd){
    int cmdIndex = getCommandIndex(cmd);
    data->instArray[data->ic].a_r_e = 0;
    data->instArray[data->ic].destination_addressing =0;
    data->instArray[data->ic].source_addressing = 0;
    data->instArray[data->ic].opcode = 0;
    data->instArray[data->ic].group= 0;
    data->instArray[data->ic].rnd = 0;
    data->instArray[data->ic].unused=0;
    data->ic++;
    return 1;
}
int addOneOperandCommand(Data * data, char * cmd, char * operand, int addressingMethod){
    int tagAddress;
    if(addressingMethod == TAG_OPERAND){
        tagAddress=getTagAddress(data, operand);
    }
}
int addOneOperandCommand(Data * data, char * cmd, char * operand, int addressingMethod){

}
int getTagAddress(char * tag){
    int i;
    for(i=0;i<data->tc;i++){
        if(strcmp(data->tagArr[i].name,tag)==0){
            return data->tagArr[i].address;
        }
    }
    return 0;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: checks if the tag already exists in the tag array
 * Input:       Data struct, operand string
 * Output:		1 if already exists, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int checkIfTagExists(Data * data, char * operand){
    int i;
    for(i=0;i<data->tc;i++){
        if(strcmp(operand,data->tagArr[i])==0){
            return 1;
        }
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int getSourceOperand(Data * data, char * operand){
    sscanf(data->line, "%30[^,\n ]s", operand);
    data->line+=strlen(operand);
    return 1;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int getDestinationOperand(Data * data, char * operand){
    if(*operand==','){
        operand++;
    }
    sscanf(data->line, "%30s", operand);
    data->line+=strlen(operand);
    return 1;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: returns if this addressing method is valid for this command type
 * Input:       addressing method, command string
 * Output:		1 if the addressing method is legal, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int checkSourceOperandAddressing(int method, char * cmd){
    int cmdIndex = getCommandIndex(command);
    if(cmdIndex==MOV){
        if(method == 0 || method == 1 method == 21 || method == 22 || method == 23 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == CMP){
        if(method == 0 || method == 1 method == 21 || method == 22 || method == 23 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == ADD){
        if(method == 0 || method == 1 method == 21 || method == 22 || method == 23 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == SUB){
        if(method == 0 || method == 1 method == 21 || method == 22 || method == 23 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == NOT){
        return 0;
    }
    if(cmdIndex == CLR){
        return 0;
    }
    if(cmdIndex == LEA){
        if(method == 1 || method == 23){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == INC){
        return 0;
    }
    if(cmdIndex == DEC){
        return 0;
    }
    if(cmdIndex == JMP){
        return 0;
    }
    if(cmdIndex == BNE){
        return 0;
    }
    if(cmdIndex == RED){
        return 0;
    }
    if(cmdIndex == PRN){
        return 0;
    }
    if(cmdIndex == JSR){
        return 0;
    }
    if(cmdIndex == RTS){
        return 0;
    }
     if(cmdIndex == STOP){
        return 0;
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: returns if this addressing method is valid for this command type
 * Input:       addressing method, command string
 * Output:		1 if the addressing method is legal, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int checkDestinationOperandAddressing(int method, char * cmd){
    int cmdIndex = getCommandIndex(command);
    if(cmdIndex==MOV){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == CMP){
        if(method ==0  || method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == ADD){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == SUB){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == NOT){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == CLR){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == LEA){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == INC){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == DEC){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == JMP){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == BNE){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == RED){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == PRN){
        if(method == 0 || method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == JSR){
        if(method == 1 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == RTS){
        return 0;
    }
     if(cmdIndex == STOP){
        return 0;
    }
    return 0;
}
/*
 * Description: Writes first line of ob file
 * Input:		1. IC value
 * 				2. DC value
 * 				3. Ob file handle
 */
void write_code_and_data_size_to_output_file(unsigned int ic, unsigned int dc, FILE* output_file) {
	char* number;

	/* Write ic to file */
	number = convert_base10_to_target_base(ic, TARGET_BASE, 0);
	fputs(number, output_file);
	free(number);

	fputc(HEADER_SEPARATOR, output_file);

	/* Write dc to file */
	number = convert_base10_to_target_base(dc, TARGET_BASE, 0);
	fputs(number, output_file);
	free(number);

	fputc(END_OF_LINE, output_file);

}

/*
 * Description: Converts a number in base 10 to wanted base
 * Input:		1. Number in base 10
 * 				2. Wanted base
 * 				3. Minimal length of returned word
 * Output:		Number in wanted base
 */
char* convert_base10_to_target_base(unsigned int base10_number, int target_base, int minimal_returned_length) {
	char* result = NULL;
	char* current_token = NULL;
	int result_length;
	int remainder = 0;

	result = allocate_string(1);

	if (result == NULL) {
		print_runtime_error("Could not allocate memory. Exit program");
	} else {
		result[0] = END_OF_STRING;
		result_length = 1;
	}

	/* Convert number to target base by :
	 * 	1) Dividing the whole number
	 * 	2) Take the reminder and append it to the result string
	 * */
	while (base10_number != 0) {
		int temp;

		temp = base10_number / target_base;
		remainder = base10_number - temp * target_base;
		base10_number = temp;

		current_token = allocate_string(result_length);

		if (current_token != NULL) {
			current_token[0] = '0' + remainder;
			current_token[1] = END_OF_STRING;

			strcat(current_token, result);

			free(result);
			result = current_token;
		} else {
			if (result != NULL) {
				free(result);
			}

			return NULL;
		}
	}

	/* Making sure that the returned result is with the right length and if not, add 0 to the right */
	result_length = strlen(result);

	/* Add zeros to the left if necessary */
	while (result_length < minimal_returned_length) {
		current_token = allocate_string(result_length);
		current_token[0] = '0';
		current_token[1] = END_OF_STRING;

		strcat(current_token, result);

		free(result);
		result = current_token;
		result_length++;
	}

	return result;
}

/*
 * Description: Allocates a string
 * Input:		Number of tokens in string
 * Output:		Allocated string
 */
char* allocate_string(int string_length) {
	return (char*)allocate_memory(sizeof(char) * (string_length + 1));
}

/*
 * Description: Allocates memory
 * Input:		Number of bytes to allocate
 * Output:		Pointer to number
 */
void* allocate_memory(int bytes) {
	void* result = (void*)malloc(bytes);

	if (result == NULL) {
		print_runtime_error("Could not allocate memory. Exit program");
	}

	return result;
}


