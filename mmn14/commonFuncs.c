#include "header.h"



/*----------------------------------------------------------*/
void substring(char* stringTo,char* stringFrom,int length){
    strncpy(stringTo, stringFrom,length);
}

/*----------------------------------------------------------------------------*/
int checkLetterOrNumber(char c){
    if (checkLetters(c) == 1){
        return 1;
    }
    if (((int)c >= 0)&&((int)c <= 9)){
        return 1;
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
/* move the file pointer to the start of the next line */
void eatLine(FILE * fp) {
	char c= fgetc(fp);
	while (c != '\n' && c!=EOF) {
		c=fgetc(fp);
	}
}
/*----------------------------------------------------------------------------*/
/* move the string pointer beyond all the spaces in the line */
void eatSpace(Data * data){
    while(isspace(*(data->line))){
        if (*(data->line)== '\n' || *(data->line) == EOF){
               return;
        }
        data->line++;
    }
}
/*----------------------------------------------------------------------------*/
int checkLetters(char c){
    int numOfLetters = 26;
    if (checkInLimit(c,FIRST_CAPITAL_LETTER_ASCII,numOfLetters) == 1){
        return 1;
    }
    if (checkInLimit(c,FIRST_LOWER_LETTER_ASCII,numOfLetters) == 1){
        return 1;
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
int checkUpperCase(char c){
    int numOfLetters = 26;
    if (checkInLimit(c,FIRST_CAPITAL_LETTER_ASCII,numOfLetters) == 1){
        return 1;
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
int checkInLimit(char c,int startLimit,int length){
    int index;
    for (index = 0; index < length;index++){
            if ((int)c == startLimit+index){
                return 1;
            }
        }
    return 0;
}


