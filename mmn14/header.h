/*
 ====================================================================================
 Module:        header
 Description: 	declarations for the whole program
 ====================================================================================
 */


/*----------------------------------------------------------------------------*/
/*standard library imports */
/*----------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


/*----------------------------------------------------------------------------*/
/*constant definitions */
/*----------------------------------------------------------------------------*/

/* Danny said it's okay to assume there's a max length for a name variable, so this is it */
#define MAX_NAME_LEN 80

/* on the last page of mmn14 (page 40) it says we can assume a max program size. I've settled on 5000 lines max */
#define MAX_ASM_LINES 5000
/* max assembly line length is 80 */
#define MAX_LINE_LEN 80
/* maximum length of a tag is 30 */
#define MAX_TAG_LEN 30

/* these define the ascii codes 'a' and 'A' */
#define FIRST_CAPITAL_LETTER_ASCII 65
#define FIRST_LOWER_LETTER_ASCII 97

#define FALSE 0
#define TRUE 1

#define EXIT 0
#define GET_NUMBER 1
#define GET_COMMA 2


#define NUM_OF_COMMANDS 16

#define MOV 0
#define CMP 1
#define ADD 2
#define SUB 3
#define LEA 4
#define NOT 5
#define CLR 6
#define INC 7
#define DEC 8
#define JMP 9
#define BNE 10
#define RED 11
#define PRN 12
#define JSR 13
#define RTS 14
#define STOP 15

/* addressing methods */

#define IMMEDIATE_OPERAND 0
#define REGISTER_OPERAND 3
#define  ONE_STAR_RANDOM_OPERAND 20
#define TWO_STAR_RANDOM_OPERAND 21
#define THREE_STAR_RANDOM_OPERAND 22
#define TAG_OPERAND 1
#define EMPTY_OPERAND -1

#define BASE32 32

/* definitions for secondPassCommandManager */

#define ABSOLUTE 0
#define RELOCATABLE 2
#define EXTERNAL 1

#define NO_OPERANDS 0
#define ONE_OPERAND 1
#define TWO_OPERANDS 2

#define NOT_RANDOM 0
#define RANDOM_ONE 1
#define RANDOM_TWO 2
#define RANDOM_THREE 3

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7




/*----------------------------------------------------------------------------*/
/*data structures */
/*----------------------------------------------------------------------------*/

typedef struct{
   unsigned int e_r_a : 2;
   unsigned int destination_addressing : 2;
   unsigned int source_addressing : 2;
   unsigned int opcode : 4;
   unsigned int group : 2;
   unsigned int rnd : 2;
   unsigned int unused : 1;
} Instruction;

typedef struct{
   unsigned int e_r_a : 2;
   unsigned int word : 13;
} ExtraWord;


typedef struct{
    char name[MAX_TAG_LEN];
    int address;
    int external;
    int command;
} Tag;

typedef struct{
    char name[MAX_TAG_LEN];
} Entry;
typedef struct{
    char name[MAX_TAG_LEN];
} Extern;

typedef struct{
    char * line;
    /* tag counter */
    int tc;
    /* line counter */
    int lc;
    /* directive counter */
    int dc;
    /* instruction counter */
    int ic;
    /* extern counter */
    int exc;
    /* entry counter */
    int enc;
    /* extra words counter */
    int wc;

    Tag * tagArr;
    int * directiveArr;
    Extern * externArr;
    Entry * entryArr;
    Instruction * instArr;
    ExtraWord * wordArr;


     /* if there's an error, no need for a second pass */
    int containError;
} Data;


/*----------------------------------------------------------------------------*/
/* function declarations */
/*----------------------------------------------------------------------------*/


/*  passManager function declarations*/
int passManager(FILE *file ,char * );
void setDataFree(Data * data);
void initializeData(Data * data);
void allocateInstructionMemory(Data * data);


/* firstPassManager function declarations*/
int firstPassManager(Data * data,FILE *file);
int lineHandler(Data * data, FILE *file);
int lineLengthCheck(Data * data, FILE *file);
int tagDupCheck(Data *data, char *tag);
void addTag(Data * data, char * tag, int dirAddress);



/* firstPassCommandsManager function declarations */
int firstPassCommandsManager(Data * data, char * tag);
int getCommandIndex(char* command);
int checkTwoOperands(Data * data, char * tag,char* command);
int checkZeroOperands(Data * data, char * tag);
int checkOneOperands(Data * data, char * tag);
int isOperandValid(char* operand);
int isImmediateOperand(Data * data,char * operand);
int checkValidationOfTwoOperands(char* command,char* operand1,char* operand2,Data* data);
int isEmptyOperand(char * operand);
int isRegisterOperand(char * operand);
int isTagOperand( char * operand);
int isRandomOperand(char * operand);
int getNumOfOperands(int cmdIndex);
int isOperandValidSyntax(Data * data, char * operand);
int getAddressingMethod(Data * data, char * operand);


/* secondPassManager function declarations*/
void secondPassManager( Data * data, FILE * file);
int lineHandlerSecondPass(Data * data,FILE * file);




/* commmonFunc declarations*/
int lineCommentCheck(Data * data);
void getTag(Data * data,char * tagGet);
int lineEmptyCheck(Data * data);
void eatLine(FILE * fp);
void eatSpace(Data * data);
void substring(char* stringTo,char* stringFrom,int length);
int checkLetterOrNumber(char c);
int checkLetters(char c);
int checkUpperCase(char c);
int checkInLimit(char c,int startLimit,int length);
char* getCharPtrBeyondSpace(char* pString);
int isEndOfLine(char* pStr);


/* directivesManager function declarations */
int directivesManager(Data * data, char * tag);
int entryDirectiveHandler(Data * data, char * tag);
int stringDirectiveHandler(Data * data, char * tag);
int externDirectiveHandler(Data * data, char * tag);
int dataDirectiveHandler(Data * data, char * tag);
void addDirective(Data * data, int directive);
void addExtern(Data * data, char * tag);
void addEntry(Data * data, char * tag);


/* secondPassCommandManager function declarations*/
int secondPassCommandManager(Data * data);
int zeroOperandsCommandHandler(Data * data, char * cmd);
int oneOperandsCommandHandler(Data * data, char * cmd);
int twoOperandsCommandHandler(Data * data, char * cmd);
int addZeroOperandCommand(Data * data, char * cmd);
int addOneOperandCommand(Data * data, char * cmd, char * operand, int addressingMethod);
int addTwoOperandCommand(Data * data, char * cmd, char * operand1, char * operand2, int addressingMethod1, int addressingMethod2);
int getTagAddress(Data * data, char * tag);
int checkIfTagExists(Data * data, char * operand);
int getSourceOperand(Data * data, char * operand);
int getDestinationOperand(Data * data, char * operand);
int checkSourceOperandAddressing(int method, char * cmd);
int checkDestinationOperandAddressing(int method, char * cmd);
int getImmediateOperand(Data* data, char * operand);
int getRegisterOperand(Data * data,char * operand);
int getRandomOperand(Data* data,char * operand);


/* output manager */
void outputManager(Data * data, char *);
void createOutputZeroExtra(Data * data, char * filename);
void createOutputOneExtra(Data * data,char * );
void createOutputTwoExtra(Data * data,char * );
void writeToOutputFile(char * output,char *);
char* decimalToBase32(unsigned long int decNum);
int binaryToDecimal(int n);
int decimalToBinary(int n);
void writeLengthsToFile(Data * data, char * filename);




