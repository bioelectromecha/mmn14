#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FIRST_CAPITAL_LETTER_ASCII 65
#define FIRST_LOWER_LETTER_ASCII 97

int checkIfLetters(char c);
int checkIfInLimit(char c,int startLimit,int length);

char* substring(char* stringFrom,int length){
    char *newString=(char*)malloc(sizeof(char)*length);
    strncpy(newString, stringFrom,length);
    return newString;
}

/*----------------------------------------------------------------------------*/
int checkIfLeterOrNumber(char c){
    if (checkIfLetters(c) == 1){
        return 1;
    }
    if (((int)c >= 0)&&((int)c <= 9)){
        return 1;
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
void line_eater(FILE * fp) {
	char c= fgetc(fp);
	while (c != '\n' && c!=EOF) {
		c=fgetc(fp);
	}
}
/*----------------------------------------------------------------------------*/
int checkIfLetters(char c){
    int numOfLetters = 26;

    if (checkIfInLimit(c,FIRST_CAPITAL_LETTER_ASCII,numOfLetters) == 1){
        return 1;
    }
    if (checkIfInLimit(c,FIRST_LOWER_LETTER_ASCII,numOfLetters) == 1){
        return 1;
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
int checkIfInLimit(char c,int startLimit,int length){
    int index;
    for (index = 0; index < length;index++){
            if ((int)c == startLimit+index){
                return 1;
            }

        }

    return 0;

}


