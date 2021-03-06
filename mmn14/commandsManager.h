#define IMMEDIATE_OPERAND 0
#define REGISTER_OPERAND 3
#define  ONE_STAR_RANDOM_OPERAND 20
#define TWO_STAR_RANDOM_OPERAND 21
#define THREE_STAR_RANDOM_OPERAND 22
#define TAG_OPERAND 1
#define EMPTY_OPERAND -1

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

/*function declarations */
int commandsManager(Data * data, char * tag);
int getCommandIndex(char* command);//, char * commandArr[],int numOfCommands);
int checkTwoOperands(Data * data, char * tag);
int checkZeroOperands(Data * data, char * tag);
int checkOneOperands(Data * data, char * tag);
int isOperandValid(char* operand);
int isImmediateOperand(char * operand, Data* data);
