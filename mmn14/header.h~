




/*-------------------------------------------*/
/*standard library imports */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/*-------------------------------------------*/
/*constant definitions */

/* Danny said it's okay to assume there's a max length for a name variable, so this is it */
#define MAX_NAME_LEN 80

/* on the last page of mmn14 (page 40) it says we can assume a max program size. I've settled on 5000 lines max */
#define MAX_ASM_LINES 5000
/* max assembly line length is 80 */
#define MAX_LINE_LEN 80

/* these define the ascii codes 'a' and 'A' */
#define FIRST_CAPITAL_LETTER_ASCII 65
#define FIRST_LOWER_LETTER_ASCII 97

#define FALSE 0
#define TRUE 1

#define EXIT 0
#define GET_NUMBER 1
#define GET_COMMA 2

/*-------------------------------------------*/
/*data structures */
typedef struct{
    char name[30];
    int address;
    int external;
    int command;
} Tag;

typedef struct{
    char name[30];
} Entry;
typedef struct{
    char name[30];
} Extern;

typedef struct
{
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

    Tag * tagArr;
    int * directiveArr;
    Extern * externArr;
    Entry * entryArr;
} Data;

/*-------------------------------------------*/
/*function declarations */
int firstPassManager(FILE *file);

int lineValidator(Data * data,FILE *file);
int lineHandler(Data * data);
int directiveHandler(Data * data, char * tag);
int tagDupCheck(Data *data, char *tag);
void getTag(Data * data,char * tagGet);
int entryDirectiveHandler(Data * data, char * tag);
int commandHandler(Data * data);
int stringDirectiveHandler(Data * data, char * tag);
int externDirectiveHandler(Data * data, char * tag);
int dataDirectiveHandler(Data * data, char * tag);

void eatLine(FILE * fp);
void eatSpace(Data * data);
void substring(char* stringTo,char* stringFrom,int length);
int checkLetterOrNumber(char c);
int checkLetters(char c);
int checkUpperCase(char c);
int checkInLimit(char c,int startLimit,int length);

