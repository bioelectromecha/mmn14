/*
 ====================================================================================
 Module:        secondPassCommandManager
 Description: 	holds all the functions that implement the managment of instruction/command in the second pass
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
    /* addEmptyCommand(data,cmd);*/
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
      /*   addTagCommand(data, cmd, operand); */
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
int twoOperandsCommandHandler(Data * data, char * cmd){
    int addressingMethod1;
    int addressingMethod2;
    char operand1[30];
    char operand2[30];
    getSourceOperand(data, operand1);
    getDestinationOperand(data, operand2);
    addressingMethod1 = getAddressingMethod(data,operand1);
    addressingMethod2 = getAddressingMethod(data,operand2);
    if(checkSourceOperandAddressing(addressingMethod1,cmd)){
        printf("[Error] on line %d: illegal addressing for this command\n",data->lc);
        return 0;
    }
    if(checkDestinationOperandAddressing(addressingMethod2,cmd)){
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
     /* addCommand(???); */
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
    data->instArr[data->ic].e_r_a = 0;
    data->instArr[data->ic].destination_addressing =0;
    data->instArr[data->ic].source_addressing = 0;
    data->instArr[data->ic].opcode = cmdIndex;
    data->instArr[data->ic].group= 0;
    data->instArr[data->ic].rnd = 0;
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
    int tagAddress;
    if(addressingMethod == TAG_OPERAND){
        tagAddress=getTagAddress(data, operand);
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
