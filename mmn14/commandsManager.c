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
    char * commandArr[] = {"mov", "cmp", "add", "sub", "lea", "not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
    int commandIndex;
    int operandnum[] = {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    printf("this line is a command\n");
    eatSpace(data);

    if (sscanf(data->line, "%4s", command) == 0){
        printf("[Error] on line %d:- command error invalid \n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    commandIndex = getCommandIndex(command,commandArr);
    if (commandIndex == -1){
        printf("[Error] on line %d:- command error not defined\n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    data->line+=strlen(command)+1;

    if(!isspace(*(data->line)){
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
int checkOneOperands(Data * data, char * tag){
    char operand[MAX_TAG_LEN];
    int regNum = 8;
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
    char * registerArr[]={"r0","r1","r2","r3","r4","r5","r6","r7"};
    w
}
int check

/*----------------------------------------------------------------------------*/
int getCommandIndex(char* command, char * commandArr[]){
    int i;
    for (i=0;i<numOfCommands;i++){
        if (strcmp(commandArr[i],command)==0){
            return i;
        }
    }
    return -1;
}
