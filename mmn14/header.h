




/*-------------------------------------------*/
/*standard library imports */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


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

/*-------------------------------------------*/
/*data structures */
typedef struct
{
    char name[30];
    int address;
    int external;
    int command;
} Tag;

typedef struct
{
    char * line;
    int lc;
    int dc;
    int ic;
    Tag tag[MAX_ASM_LINES];
} Data;

/*-------------------------------------------*/
/*function declarations */



