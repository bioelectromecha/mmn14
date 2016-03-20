#include "header.h"



/*----------------------------------------------------------------------------*/
/*
 * Description: checks if character is a letter or number
 * Input:       character
 * Output:		1 if letter or number, 0 otherwise
 */
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
/*
 * Description: move the file pointer to the start of the next line
 * Input:       FILE pointer to assembly language file
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void eatLine(FILE * fp) {
	char c= fgetc(fp);
	while (c != '\n' && c!=EOF) {
		c=fgetc(fp);
	}
}
/*----------------------------------------------------------------------------*/
/*
 * Description: ove the string pointer beyond all the spaces in the line
 * Input:       pointer to Data struct
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void eatSpace(Data * data){
    while(isspace(*(data->line))){
        if (*(data->line)== '\n' || *(data->line) == EOF){
               return;
        }
        data->line++;
    }
}

/*----------------------------------------------------------------------------*/
/*
 * Description: check whether a character is a capital or lowercase letter
 * Input:       character
 * Output:		1 if letter, 0 otherwise
 */
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
/*
 * Description: check whether a character is a lowercase letter
 * Input:       character
 * Output:		1 if lowercase letter, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int checkLowerCase(char c){
    int numOfLetters = 26;
    if (checkInLimit(c,FIRST_LOWER_LETTER_ASCII,numOfLetters) == 1){
        return 1;
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
/*
 * Description: check whether a character is an uppercase letter
 * Input:       character
 * Output:		1 if uppercase letter, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int checkUpperCase(char c){
    int numOfLetters = 26;
    if (checkInLimit(c,FIRST_CAPITAL_LETTER_ASCII,numOfLetters) == 1){
        return 1;
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: check if a char ascii value is between the limits
 * Input:       character, lower limit, length
 * Output:		1 if in limit, 0 otherwise
 */
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


