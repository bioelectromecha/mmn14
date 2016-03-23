#include "header.h"
/*----------------------------------------------------------------------------*/
/*
 * Description: parses and validates the commands from input
 * Input:       Data struct, string with tag names (might be null if no tag was found)
 * Output:		1 if successful, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int firstPassCommandsManager(Data * data, char * tag){
    char command[5];
    int operandNum;
    int commandIndex;

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
    operandNum = getNumOfOperands(commandIndex);

    if(operandNum==0){
        return checkZeroOperands(data,tag);
    }else if(operandNum==1){
        return checkOneOperands(data, tag);
    }else if(operandNum==2){
        return checkTwoOperands(data, tag,command);
    }
    return 0;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: gives you the index number of the command
 * Input:       command string
 * Output:		int index of the command, -1 if it doesn't exist
 */
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


/*----------------------------------------------------------------------------*/
/*
 * Description: return the number of operands for the command
 * Input:       the index of the command
 * Output:		int number of operands
 */
/*----------------------------------------------------------------------------*/
int getNumOfOperands(int cmdIndex){
    int operandNum[] = {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    return operandNum[cmdIndex];
}


/*----------------------------------------------------------------------------*/
/*
 * Description: validate a command with zero operands
 * Input:       Data struct, tag string
 * Output:		1 if successful, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int checkZeroOperands(Data * data, char * tag){
    if(*(data->line)=='\n' || *(data->line)==EOF){
        if(tag != NULL){
            addTag(data,tag,data->ic);
        }
        data->ic++;
        return 1;
    }
    printf("[Error] on line %d: illegal arguments - command should have zero operands.\n", data->lc);
    data->containError=TRUE;
    return 0;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: validate a command with one operand
 * Input:       Data struct, tag string
 * Output:		1 if successful, 0 otherwise
 */
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
    /* shouldn't be any additional character or arguments after the operand */
    if(isEndOfLine(data->line) == 0){
        printf("[Error] on line %d: extra argument or characters after the operand \n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    if (isOperandValidSyntax(data,operand) == 0){
        printf("[Error] on line %d: operand is invalid \n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    /* what happens when IC and DC are the same? how does it diffrentiate address? is DC limited to 100? */
    if(tag != NULL){
        addTag(data,tag,data->ic);
    }
    /* there is one more instruction to allocate memory for at end of first pass */
    data->ic++;
    /* there is one more extra word to allocate memory for at end of first pass */
    data->wc++;
    return 1;
}
/*----------------------------------------------------------------------------*/
/*
 * Description: validate a command with two operands
 * Input:       Data struct, tag string, command string
 * Output:		1 if successful, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int checkTwoOperands(Data * data, char * tag,char* command){
    char operand1[MAX_TAG_LEN];
    char operand2[MAX_TAG_LEN];

    /* get the 1st operand*/
    if(sscanf(data->line, "%30[^,\n ]s", operand1) == 0){
        printf("[Error] on line %d: no operands given - two operands required\n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    /* check there's a comma between the two operands */
    data->line+= strlen(operand1);
    eatSpace(data);
    if(!(*data->line)==','){
        printf("[Error] on line %d: no comma between operands\n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    data->line++;

    /* get the 2nd operand*/
    if(sscanf(data->line, "%30s", operand2) == 0){
        printf("[Error] on line %d: second operand required\n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    data->line+= strlen(operand2);

    /* add a terminating character to the operand string */
    eatSpace(data);

    /* shouldn't be any additional character or arguments after the 2nd operand */
    if(isEndOfLine(data->line) == 0){
        printf("[Error] on line %d: extra characters after 2nd operand \n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    /* check the first operand is valid syntactically */
    if (isOperandValidSyntax(data,operand1) == 0){
        printf("[Error] on line %d: first operand is invalid \n", data->lc);
        data->containError=TRUE;
        return 0;

    }
    /* check the second operand is valid syntactically */
    if (isOperandValidSyntax(data,operand2) == 0){
        printf("[Error] on line %d: second operand is invalid \n", data->lc);
        data->containError=TRUE;
        return 0;

    }
    /* add the address under the tag if it was given */
    if(tag != NULL){
        addTag(data,tag,data->ic);
    }
    /* there is one more instruction to allocate memory for at end of first pass */
    data->ic++;
    /* there are two more extra memory words to allocate memory for at end of first pass */
    data->wc+=2;

    return 1;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: check if the syntax of the operand is valid
 * Input:       Data struct, tag string, command string
 * Output:		1 if valid, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int isOperandValidSyntax(Data * data, char * operand){
    if(getAddressingMethod(data,operand) != -1){
        return 1;
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: get the addressing method of the operand and check validity
 * Input:       Data struct, operand string
 * Output:		int addressing method code, -1 if invalid
 * NOTE:        might print out errors if invalid
 */
/*----------------------------------------------------------------------------*/
int getAddressingMethod(Data * data, char * operand) {
    int rand_operand;
    if(isEmptyOperand(operand)==1){
        return EMPTY_OPERAND;
    }
    if(isImmediateOperand(data,operand)==1){
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


/*----------------------------------------------------------------------------*/
/*
 * Description: check if the addressing method is immediate or not
 * Input:       Data struct, operand string
 * Output:		1 if immediate, 0 if not immediate
 * NOTE:        might be immediate but invalid, will print out error and still return 1
 */
/*----------------------------------------------------------------------------*/
int isImmediateOperand(Data* data, char * operand){
    int num;
    char tempOperand[30];
    char * c;
    strcpy(tempOperand,operand);
    strcat(tempOperand,"\n");
    c=tempOperand;

    /* operand hasn't got a #  at the start*/
    if (*c != '#') {
        /* it's  not immediate addressing method */
        return 0;
    }
    /* operand has a plus or minus sign after the # at the start*/
    c++;
    if (sscanf(c, "%d", &num) == 0) {
        printf("[Error] on line %d:- malformed immediate addressing - no number after hashtag\n", data->lc);
        data->containError=TRUE;
        return 1;
    }
    /* get operand beyond what sscanf took in */
     if (((*c) == '-') || (*c == '+')){
        c++;
    }
    while (isdigit(*c)){
        c++;
    }
    if(*c != '\n' && *c != EOF){
        printf("[Error] on line %d:- malformed immediate addressing - extra characters after number\n", data->lc);
        data->containError=TRUE;
        return 1;
    }
    return 1;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: check if the addressing method is register addressing or not
 * Input:       string operand
 * Output:		1 if register, 0 if not register
 */
/*----------------------------------------------------------------------------*/
int isRegisterOperand(char * operand){
    char* regArr[]={"r0","r1","r2","r3","r4","r5","r6","r7"};
    int i;
    for(i=0;i<8;i++){
        if(strcmp(operand,regArr[i])==0){
            return 1;
        }
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
/*
 * Description: check if the addressing method is register addressing or not
 * Input:       string operand
 * Output:		1 if register, 0 if not register
 */
/*----------------------------------------------------------------------------*/
int isTagOperand( char * operand){
    char tempOperand[30];
    char * c;
    strcpy(tempOperand,operand);
    strcat(tempOperand,"\n");

    c= tempOperand;

    if (checkLetters(*c)== 0){
        return 0;
    }
    operand++;
    while(!isspace(*c) && *c != '\n' && *c !=EOF){
        if (checkLetterOrNumber(*c) == 0){
            return 0;
        }
        c++;
    }
    return 1;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: check if the operand is empty or not
 * Input:       string operand
 * Output:		1 if empty, 0 if not empty
 */
/*----------------------------------------------------------------------------*/
int isEmptyOperand(char * operand){
    operand = getCharPtrBeyondSpace(operand);
    if(*operand == '\n' || *operand==EOF){
        return 1;
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
/*
 * Description: check if the addressing method is random addressing or not
 * Input:       string operand
 * Output:		1 if random, 0 if not random
 */
/*----------------------------------------------------------------------------*/
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
