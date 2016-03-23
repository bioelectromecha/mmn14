/*
 ====================================================================================
 Module:        secondPassCommandManager
 Description: 	functions that implement the second pass instruction algorithm
 ====================================================================================
 */


#include "header.h"


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
    int commandIndex;

    /* get the command */
    sscanf(data->line, "%4s", cmd);
    data->line+=strlen(cmd);
    commandIndex = getCommandIndex(cmd);

    /* get number of operands needed for this command */
    numOfOperands = getNumOfOperands(commandIndex);

    if(numOfOperands==0){
        return zeroOperandsCommandHandler(data,cmd);
    }else if(numOfOperands==1){
        return oneOperandsCommandHandler(data,cmd);
    }else if(numOfOperands==2){
        return twoOperandsCommandHandler(data,cmd);
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
int zeroOperandsCommandHandler(Data * data, char * cmd){
    addZeroOperandCommand(data,cmd);
    return 1;
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
    getDestinationOperand(data, operand);
    addressingMethod = getAddressingMethod(data,operand);
    if(checkDestinationOperandAddressing(addressingMethod,cmd)){
        printf("[Error] on line %d: illegal addressing for this command\n",data->lc);
        return 0;
    }
    if(addressingMethod == TAG_OPERAND){
        if(checkIfTagExists(data,operand)==0){
            printf("[Error] on line %d: tag does not exist\n",data->lc);
            return 0;
        }
    }
    addOneOperandCommand(data,cmd,operand,addressingMethod);
    return 1;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .as
 */
/*----------------------------------------------------------------------------*/
int twoOperandsCommandHandler(Data * data, char * cmd){
    int addressingMethod1;
    int addressingMethod2;
    char operand1[30];
    char operand2[30];

    eatSpace(data);
    getSourceOperand(data, operand1);
    (data->line)++;

    getDestinationOperand(data, operand2);
    addressingMethod1 = getAddressingMethod(data,operand1);
    addressingMethod2 = getAddressingMethod(data,operand2);
    if(checkSourceOperandAddressing(addressingMethod1,cmd) == 0){
        printf("[Error] on line %d: illegal addressing for this command\n",data->lc);
        return 0;
    }
    if(checkDestinationOperandAddressing(addressingMethod2,cmd) == 0){
        printf("[Error] on line %d: illegal addressing for this command\n",data->lc);
        return 0;
    }
    if(addressingMethod1 == TAG_OPERAND){
        if(checkIfTagExists(data,operand1)==0){
            printf("[Error] on line %d: tag does not exist\n",data->lc);
            return 0;
        }
    }

    if(addressingMethod2 == TAG_OPERAND){
         if(checkIfTagExists(data,operand2)==0){
            printf("[Error] on line %d: tag does not exist\n",data->lc);
            return 0;
        }
    }

    addTwoOperandCommand(data,cmd,operand1,operand2,addressingMethod1, addressingMethod2);
    return 1;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int addZeroOperandCommand(Data * data, char * cmd){
    int cmdIndex = getCommandIndex(cmd);
    data->instArr[data->ic].e_r_a = ABSOLUTE;
    data->instArr[data->ic].destination_addressing =0;
    data->instArr[data->ic].source_addressing = 0;
    data->instArr[data->ic].opcode = cmdIndex;
    data->instArr[data->ic].group= NO_OPERANDS;
    data->instArr[data->ic].rnd = NOT_RANDOM;
    data->instArr[data->ic].unused=0;
    data->ic++;
    return 1;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int addOneOperandCommand(Data * data, char * cmd, char * operand, int addressingMethod){
    int cmdIndex = getCommandIndex(cmd);

    data->instArr[data->ic].e_r_a = ABSOLUTE;
    data->instArr[data->ic].destination_addressing =addressingMethod;
    data->instArr[data->ic].source_addressing = 0;
    data->instArr[data->ic].opcode = cmdIndex;
    data->instArr[data->ic].group=  ONE_OPERAND;
    data->instArr[data->ic].rnd = NOT_RANDOM;
    data->instArr[data->ic].unused=0;
    data->ic++;

    if(addressingMethod == TAG_OPERAND){

        data->wordArr[data->wc].e_r_a = RELOCATABLE;
        data->wordArr[data->wc].word = getTagAddress(data, operand);
        data->wc++;
        return 1;
    }
    if(addressingMethod == IMMEDIATE_OPERAND){
        data->wordArr[data->wc].e_r_a = ABSOLUTE;
        data->wordArr[data->wc].word =getImmediateOperand(data,operand);
        data->wc++;
        return 1;
    }
    if(addressingMethod == REGISTER_OPERAND){
        data->wordArr[data->wc].e_r_a = ABSOLUTE;
        data->wordArr[data->wc].word =getRegisterOperand(data,operand);
        data->wc++;
        return 1;
    }
    if(addressingMethod == ONE_STAR_RANDOM_OPERAND || addressingMethod == TWO_STAR_RANDOM_OPERAND || addressingMethod==THREE_STAR_RANDOM_OPERAND){
        data->wordArr[data->wc].e_r_a = ABSOLUTE;
        data->wordArr[data->wc].word =getRandomOperand(data,operand);
        data->wc++;
        return 1;
    }

    return 1;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int addTwoOperandCommand(Data * data, char * cmd, char * operand1, char * operand2, int addressingMethod1, int addressingMethod2){
    int cmdIndex = getCommandIndex(cmd);

    data->instArr[data->ic].e_r_a = ABSOLUTE;
    data->instArr[data->ic].destination_addressing =addressingMethod1;
    data->instArr[data->ic].source_addressing = addressingMethod2;
    data->instArr[data->ic].opcode = cmdIndex;
    data->instArr[data->ic].group=  TWO_OPERANDS;
    data->instArr[data->ic].rnd = NOT_RANDOM;
    data->instArr[data->ic].unused=0;
    data->ic++;

    /*add first operand */
    if(addressingMethod1 == TAG_OPERAND){
        if(checkIfTagExists(data,operand1)==0){
            printf("[Error] on line %d: tag does not exist\n",data->lc);
            return 0;
        }
        data->wordArr[data->wc].e_r_a = RELOCATABLE;
        data->wordArr[data->wc].word = getTagAddress(data, operand1);
        data->wc++;
        return 1;
    }
    if(addressingMethod1 == IMMEDIATE_OPERAND){
        data->wordArr[data->wc].e_r_a = ABSOLUTE;
        data->wordArr[data->wc].word =getImmediateOperand(data,operand1);
    }else if(addressingMethod1 == REGISTER_OPERAND){
        data->wordArr[data->wc].e_r_a = ABSOLUTE;
        data->wordArr[data->wc].word =getRegisterOperand(data,operand1);
    }else if(addressingMethod1 == ONE_STAR_RANDOM_OPERAND || addressingMethod1 == TWO_STAR_RANDOM_OPERAND || addressingMethod1==THREE_STAR_RANDOM_OPERAND){
        data->wordArr[data->wc].e_r_a = ABSOLUTE;
        data->wordArr[data->wc].word =getRandomOperand(data,operand1);
    }
    data->wc++;

    /*add second operand */
    if(addressingMethod2 == TAG_OPERAND){
        if(checkIfTagExists(data,operand2)==0){
            printf("[Error] on line %d: tag does not exist\n",data->lc);
            return 0;
        }
        data->wordArr[data->wc].e_r_a = RELOCATABLE;
        data->wordArr[data->wc].word = getTagAddress(data, operand2);
        data->wc++;
        return 1;
    }
     if(addressingMethod2 == IMMEDIATE_OPERAND){
        data->wordArr[data->wc].e_r_a = ABSOLUTE;
        data->wordArr[data->wc].word =getImmediateOperand(data,operand2);
    }else if(addressingMethod2 == REGISTER_OPERAND){
        data->wordArr[data->wc].e_r_a = ABSOLUTE;
        data->wordArr[data->wc].word =getRegisterOperand(data,operand2);
    }else if(addressingMethod2 == ONE_STAR_RANDOM_OPERAND || addressingMethod2 == TWO_STAR_RANDOM_OPERAND || addressingMethod2 == THREE_STAR_RANDOM_OPERAND){
        data->wordArr[data->wc].e_r_a = ABSOLUTE;
        data->wordArr[data->wc].word =getRandomOperand(data,operand2);
    }
    data->wc++;

    return 1;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int getTagAddress(Data * data, char * tag){
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
        if(strcmp(operand,data->tagArr[i].name)==0){
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
    int cmdIndex = getCommandIndex(cmd);
    if(cmdIndex==MOV){
        if(method == 0 || method == 1 || method == 21 || method == 22 || method == 23 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == CMP){
        if(method == 0 || method == 1 || method == 21 || method == 22 || method == 23 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == ADD){
        if(method == 0 || method == 1 || method == 21 || method == 22 || method == 23 || method == 3){
            return 1;
        }
        return 0;
    }
    if(cmdIndex == SUB){
        if(method == 0 || method == 1 || method == 21 || method == 22 || method == 23 || method == 3){
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
    int cmdIndex = getCommandIndex(cmd);
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
/*----------------------------------------------------------------------------*/
/*
 * Description: get the number from an immediate operand
 * Input:       Data struct, operand string
 * Output:		integer
 */
/*----------------------------------------------------------------------------*/
int getImmediateOperand(Data* data, char * operand){
    int num;
    char tempOperand[30];
    char * c;
    strcpy(tempOperand,operand);
    strcat(tempOperand,"\n");
    c=tempOperand;
    c++;
    sscanf(c, "%d", &num);
    return num;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: get the register address
 * Input:       string operand
 * Output:		int register
 */
/*----------------------------------------------------------------------------*/
int getRegisterOperand(Data * data,char * operand){
    char* regArr[]={"r0","r1","r2","r3","r4","r5","r6","r7"};
    int i;
    for(i=0;i<8;i++){
        if(strcmp(operand,regArr[i])==0){
            return i;
        }
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
/*
 * Description: get a random number
 * Input:       string operand
 * Output:		integer
 */
/*----------------------------------------------------------------------------*/
int getRandomOperand(Data* data,char * operand){
int a = (rand()%8) - 1;
    int numberRand = isRandomOperand(operand);
    if (numberRand == ONE_STAR_RANDOM_OPERAND){
        data->instArr[data->ic].rnd = 1;

        return (rand()%8) - 1;
    }else if (numberRand == TWO_STAR_RANDOM_OPERAND){
        data->instArr[data->ic].rnd = 2;
        return (rand()%8000) +7;
    }else if (numberRand == THREE_STAR_RANDOM_OPERAND){
        data->instArr[data->ic].rnd = 3;
        int num = data->dc;
        int rand2 = rand() % num;
        return data-> tagArr[rand2+1].address;
    }
    return 0;
}
