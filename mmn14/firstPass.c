#include <stdio.h>
#include <stdlib.h>

/* on the last page of mmn14 (page 40) it says we can assume a max program size. I've settled on 5000 lines max */
#define MAX_ASM_LINES 5000
/* max assembly line length is 80 */
#define MAX_LINE_LEN 80



/*----------------------------------------------------------------------------*/

int checkLine(char* line);
char* tagOfStart(char* line);
int isFakeInstruction(char* line);
int isExternOrEntry(char* line);
int existLabel(char* line);
int checkIfLetters(char c);
int checkIfLeterOrNumber(char c);
int checkValidationOfLine(char* line,FILE *file);
int checkIfTagExist(char* tag);
char* substring(char* stringFrom,int length);

/*----------------------------------------------------------------------------*/
int firstPassCreator(FILE *file){
    int IC = 0;
    int DC = 0;

    char line[MAX_LINE_LEN+1];

    /* the tags table - an array of tag rows */
     /* no counter for tags */

    /* NULL means EOF. When we reach EOF it means we're done */
    while(fgets(line,MAX_LINE_LEN,file) != NULL ){

        if (checkValidationOfLine(line,file) == 1){
            checkLine(line);
        }
    }

    return 0;
}



/*----------------------------------------------------------------------------*/
int checkValidationOfLine(char *line,FILE *file){

    int line_loc = 0;


    /* check if a line is longer than MAX_LINE_LEN */
    if(strlen(line)>=MAX_LINE_LEN-1 && line[MAX_LINE_LEN-1] != EOF && line[MAX_LINE_LEN-1] != '\n'){
        printf("ERROR line is longer than %d chars\n", MAX_LINE_LEN);

        /* get rid of the rest of the line so we don't get the rest of it with fgets instead of a new one */
        line_eater(file);
        printf("%s\n",line);
        return 0;

    }

    if(line[line_loc]=='\n' || line[line_loc]==EOF){
        return 0;
    }
    /* if it's a comment line */
    if(line[line_loc]==';'){
        return 0;
    }
    return 1;

}

/*----------------------------------------------------------------------------*/
int checkLine(char* line){
    char* tag = tagOfStart(line);

    /* means it's start with tag*/
    if (tag != NULL){
        /*printf("%s\n",tag);*/
        if (checkIfTagExist(tag) == 1){
        printf("[Error]: you have the tag %s more then once.\n",tag);
            return 0;
        }
        /* dagel hit's semel
         lines 3-4*/

    }
    if (isFakeInstruction(line)==1){
        /*if contain semel enter to table semel, value = DC
         lines 6-7*/
        return 0;
    }
    if (isExternOrEntry(line)==1){
        /*lines 9-10*/

        return 0;
    }
    if (existLabel(line) == 1){
            /*lines 11*/

    }
    /*lines 12 - 13*/
    return 0;

}

/*----------------------------------------------------------------------------*/
int checkIfTagExist(char* tag){
    int index = 0;
    int static tagsArray[MAX_ASM_LINES];
    int static numOfTag = 0;

    for (index = 0; index< numOfTag;index++){
        if (strcmp(tagsArray[index],tag) == 0){
            return 1;
        }
    }
    tagsArray[numOfTag] = tag;
    numOfTag++;
    return 0;
}

/*----------------------------------------------------------------------------*/
char* tagOfStart(char* line){
    int ans = checkIfLetters(*line);
    int lengthOfString = 1;
    char *c = line+1;

    if (ans == 0){

        return NULL;
    }

    while((*(c) != ' ')&&(*(c) != '\t')&&(*(c) != ':')){
            if (checkIfLeterOrNumber(*c) == 0){
                return NULL;
            }
            c = c+1;
            lengthOfString++;
    }
    if (*(c) == ':'){
        return substring(line,lengthOfString);
    }
    return NULL;

}

/*----------------------------------------------------------------------------*/
int isFakeInstruction(char* line){
return 0;
}

/*----------------------------------------------------------------------------*/
int isExternOrEntry(char* line){
return 0;
}

/*----------------------------------------------------------------------------*/
int existLabel(char* line){
return 0;
}

