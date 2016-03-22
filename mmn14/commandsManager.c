#include "header.h"






/*----------------------------------------------------------------------------*/
/*
 * Description: parses and validates the commands from input
 * Input:       Data struct, string with tag names (might be null if no tag was found)
 * Output:		1 if successful, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int commandsManager(Data * data, char * tag){
    char command[5];

    int commandIndex;
    int operandnum[] = {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};

    if (sscanf(data->line, "%4s", command) == 0){
        printf("[Error] on line %d:- command error invalid \n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    commandIndex = getCommandIndex(command);

    if (commandIndex == -1){
        printf("[Error] on line %d:- command error not defined\n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    data->line+=strlen(command);

    if(!isspace(*(data->line))){
        printf("[Error] on line %d:- extra characters or no space after command name\n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    eatSpace(data);

    if(operandnum[commandIndex]==0){
        return checkZeroOperands(data,tag);
    }else if(operandnum[commandIndex]==1){
        return checkOneOperands(data, tag);
    }else if(operandnum[commandIndex]==2){
        return checkTwoOperands(data, tag);
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
int checkZeroOperands(Data * data, char * tag){
    if(*(data->line)=='\n' || *(data->line)==EOF){
        if(tag != NULL){
            addTag(data,tag,data->ic);
        }
        data->ic++;
            return 1;
        }
        return 0;
}
/*----------------------------------------------------------------------------*/
int checkTwoOperands(Data * data, char * tag){
    char operand1[MAX_TAG_LEN];
    char operand2[MAX_TAG_LEN];

    if(sscanf(data->line, "%30[^,\n ]s", operand1) == 0){
        printf("[Error] on line %d: no operands given - two operands required\n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    data->line+= strlen(operand1) + 1;
    eatSpace(data);

    if(sscanf(data->line, "%30s", operand2) == 0){
        printf("[Error] on line %d: second operand required\n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    data->line+= strlen(operand2);

    if(*(data->line) != '\n' || *(data->line) != EOF){
        printf("[Error] on line %d: invalid operands input \n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    if (isOperandValid(operand1) == 0){
        printf("[Error] on line %d: first operand is unvalid \n", data->lc);
        data->containError=TRUE;
        return 0;

    }

    if (isOperandValid(operand2) == 0){
        printf("[Error] on line %d: second operand is unvalid \n", data->lc);
        data->containError=TRUE;
        return 0;

    }


    data->ic+=3;
    return 1;

}
/*----------------------------------------------------------------------------*/
int checkOneOperands(Data * data, char * tag){
    char operand[MAX_TAG_LEN];
    if(sscanf(data->line, "%30s", operand) == 0){
        printf("[Error] on line %d: no operands given - one operand required\n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    data->line+= strlen(operand);
    eatSpace(data);
    if(*(data->line) != '\n' || *(data->line) != EOF){
        printf("[Error] on line %d: invalid operand input \n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    if (isOperandValid(operand) == 0){
        printf("[Error] on line %d: operand is unvalid \n", data->lc);
        data->containError=TRUE;
        return 0;

    }
    data->ic+=2;

    return 1;
}

/*----------------------------------------------------------------------------*/
int isOperandValid(char* operand){
    int index = 0;
    while(*(operand+index) != '\0'){
        if (checkLetterOrNumber(*(operand+index)) == 1){
            index++;
        }else if ((*(operand+index) == '*')||(*(operand+index) == '"') || (*(operand+index) == '#')
        ||(*(operand+index) == '-')){
            index++;
        }else{
            return 0;
        }


    }
    return 1;
}

/*----------------------------------------------------------------------------*/
int getCommandIndex(char* command){
    int numOfCommands = NUM_OF_COMMANDS;
    char * commandArr[] = {"mov", "cmp", "add", "sub", "lea", "not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
    int i;
    for (i=0;i<numOfCommands;i++){
        if (strcmp(commandArr[i],command)==0){
            return i;
        }
    }
    return -1;
}


/* TO DO: some method must call this one and then call isValidAddressingMethod(int method, char * command) */

int getAddressingMethod(Data * data, char * operand) {
    int rand_operand;
    if(isEmptyOperand(operand)==1){
        return EMPTY_OPERAND;
    }
    if(isImmediateOperand(operand)==1){
        return IMMEDIATE_OPERAND;
    }
    if(isRegisterOperand(operand)==1){
        return REGISTER_OPERAND;
    }
    rand_operand = isRandomOperand(operand);
    if(rand_operand>0){
        return rand_operand;
    }
    if(isTagOperand(operand)==1){
        return TAG_OPERAND;
    }

    return -1;
}
int isImmediateOperand(char * operand){
    int num;
    /* operand has a #  at the start*/
    if (*operand == '#') {
        /* operand has a plus or minus sign after the # at the start*/
        operand++;
        if (sscanf(operand, "%d", &num) == 0) {
            printf("[Error] on line %d:- malformed immediate addressing - no number after hashtag\n", data->lc);
            data->containError=TRUE;
            return 1;
        }
        /* get operand beyond what sscanf took in */
         if (*operand) == '-' || *operand == '+'){
            operand++;
        }
        while (isdigit(*operand)){
            *operand++;
        }
        operand = getCharPtrBeyondSpace(operand);

        if(*operand != '\n' && *operand != EOF){
            printf("[Error] on line %d:- malformed immediate addressing - extra characters after number\n", data->lc);
            data->containError=TRUE;
            return 1;
        }
        return 1;
    }
    /* it's  not immediate addressing method */
    return 0;
}
int isRegisterOperand(char * operand){
    char regArr[]={"r0","r1","r2","r3","r4","r5","r6","r7"}
    int i;
    for(i=0;i<8;i++){
        if(strcmp(operand,regArr[i])==0){
            return 1;
        }
    }
    return 0;
}
int isTagOperand( char * operand){
    if (checkLetters(*tag)== 0){
        return 0;
    }
    tag++;
    while(!isspace(*tag) && *tag != '\n' && *tag !=EOF){
        if (checkLetterOrNumber(*tag) == 0){
            return 0;
        }
        tag++;
    }
    return 1;
}
/*----------------------------------------------------------------------------*/
/*
 * Description: check if the operand is empty
 * Input:       char array containing the operand
 * Output:		1 if empty, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int isEmptyOperand(char * operand){
    operand = getCharPtrBeyondSpace(operand);
    if(*operand == '\n' || *operand==EOF){
        return 1;
    }
    return 0;
}
int isRandomOperand(char * operand){
    if(strcmp(operand,"*")==0){
        return ONE_STAR_RANDOM_OPERAND;
    }
    if(strcmp(operand,"**")==0){
        return TWO_STAR_RANDOM_OPERAND;
    }
    if(strcmp(operand,"***")==0){
        return THREE_STAR_RANDOM_OPERAND;
    }
    return 0;
}



