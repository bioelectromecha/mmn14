/*
 ====================================================================================
 Module:        directivesManager
 Description: 	responsible for handling all the directive code lines during the first pass
 ====================================================================================
 */

#include "header.h"

/*----------------------------------------------------------------------------*/
int directivesManager(Data * data, char * tag){
    char s[6];
    data->line++;
    sscanf((data->line),"%s",s);
    data->line+=strlen(s)+1;

    eatSpace(data);

    if(strcmp(s,"data")==0){
        return dataDirectiveHandler(data,tag);
    }
    if(strcmp(s,"string")==0){
        return stringDirectiveHandler(data,tag);
    }
    if(strcmp(s,"entry")==0){
        return entryDirectiveHandler(data,tag);
    }
    if(strcmp(s,"extern")==0){
        return externDirectiveHandler(data,tag);
    }
    printf("[Error] on line %d: %s is not a valid directive\n",data->lc, s);
    data->containError=TRUE;
    return 0;
}

/*----------------------------------------------------------------------------*/
int dataDirectiveHandler(Data * data, char * tag){
    int i=0;
    int num;
    int dcounter=0;
    int numberArray[80];
    /* state 1 means check number, state 2 means check comma, state 0 means exit */
    int state =1;
    /* check for an empty data directive */
    if(*(data->line)== '\n' || *(data->line)==EOF){
        printf("[Error] on line %d: malformed data directive - empty directive parameters \n", data->lc);
        data->containError=TRUE;
        return 0;
    }
    while(state != EXIT){
        eatSpace(data);
        if(state==GET_NUMBER){
            if (sscanf(data->line, "%d", &num) == 0) {
                printf("[Error] on line %d:- malformed data directive - missing number \n", data->lc);
                data->containError=TRUE;
                return 0;
            }
            numberArray[dcounter]= num;
            dcounter++;
            /* get the line location pointer (line_loc) beyond what sscanf took in */
             if (*(data->line) == '-' || *(data->line) == '+'){
                data->line++;
            }
            while (isdigit(*(data->line))){
                data->line++;
            }
            state=GET_COMMA;
        }else if(state==GET_COMMA){
            eatSpace(data);
            if (*(data->line) != ',' && *(data->line) != '\n' && *(data->line) !=EOF) {
                printf("[Error] on line %d: - malformed data directive - unidentified characters in addition to numeric parameters\n", data->lc);
                data->containError=TRUE;
                return 0;
            }
            if (*(data->line) == '\n' || *(data->line) == EOF) {
                state=EXIT;
            }else{
                state=GET_NUMBER;;
                data->line++;
            }
        }
    }
    if(tag != NULL){
        addTag(data,tag, data->dc);
    }
    for(i=0;i<dcounter;i++){
        addDirective(data, numberArray[i]);
    }
    return 1;
}
/*----------------------------------------------------------------------------*/
int stringDirectiveHandler(Data * data, char * tag){
    int i=0;
    int counter=0;
    char charArray[80];

    if(*(data->line) =='\n' || *(data->line)==EOF){
         printf("[Error] on line %d: empty directive\n",data->lc);
         data->containError=TRUE;
            return 0;
    }
    /* check for beggining character of the string (") */
    if(*(data->line)=='"'){
        /* put all the characters of the string into the directives table*/
        data->line++;
        while(*(data->line)!='"' && *(data->line)!='\n' && *(data->line)!=EOF){
            charArray[counter]=*(data->line);
            counter++;
            data->line++;
        }
        /* if the last character of the string is not a closing quotation mark - it's an invalid string*/
        if(*(data->line)!='"'){
            printf("[Error] on line %d:malformed string directive - no ending quotation mark in string\n",data->lc);
            data->containError=TRUE;
            return 0;
        }
        data->line++;
        /* check for extra characters after the string ending (it's not a valid string directive that way) */
        eatSpace(data);
        if ((*(data->line) != '\n') && (*(data->line) != EOF)) {
            printf("[Error] on line %d: malformed string directive - extra characters after string ending\n",data->lc);
            data->containError=TRUE;
            return 0;
        }
    /* if the string directive contains no string - it's an invalid directive */
    }else{
        printf("[Error] on line %d: malformed string directive - no leading quotation mark in string\n",data->lc);
        data->containError=TRUE;
        return 0;
    }

    if(tag != NULL){
        addTag(data,tag, data->dc);
    }
    for(i=0;i<counter;i++){
        addDirective(data,charArray[i]);
    }
    addDirective(data,0);
    return 1;
}
/*----------------------------------------------------------------------------*/
int externDirectiveHandler(Data * data, char * tag){
    char* tagName ="";
    int i=0;
    if(tag != NULL){
        printf("[Error] on line %d: a .extern directive can't start with a tag\n",data->lc);
        data->containError=TRUE;
        return 0;
    }
    if(*(data->line) =='\n' || *(data->line)==EOF){
        printf("[Error] on line %d: empty directive\n",data->lc);
        data->containError=TRUE;
        return 0;
    }
    getTag(data,tagName);
    if(tagName==NULL){
        printf("[Error] on line %d: malformed .extern directive\n",data->lc);
        data->containError=TRUE;
        return 0;
    }
    for(i=0;i<=(data->enc);i++){
        if(strcmp(data->entryArr[data->enc].name,tagName)==0){
            printf("[Error] on line %d: .extern directive name already defined as .entry\n",data->lc);
            data->containError=TRUE;
            return 0;
        }
    }
     for(i=0;i<=(data->enc);i++){
        if(strcmp(data->externArr[data->enc].name,tagName)==0){
            printf("[Error] on line %d: .extern directive name already exists\n",data->lc);
            data->containError=TRUE;
            return 0;
        }
    }
    addExtern(data,tagName);
    return 1;
}
/*----------------------------------------------------------------------------*/
int entryDirectiveHandler(Data * data, char * tag){
    char tagName[MAX_TAG_LEN];
    int i=0;
    if(tag != NULL){
        printf("[Error] on line %d: a .entry directive can't start with a tag\n",data->lc);
        data->containError=TRUE;
        return 0;
    }
    if(*(data->line) =='\n' || *(data->line)==EOF){
        printf("[Error] on line %d: empty directive\n",data->lc);
        data->containError=TRUE;
        return 0;
    }
    getTag(data,tagName);
    if(tagName==NULL){
        printf("[Error] on line %d: malformed .entry directive\n",data->lc);
        data->containError=TRUE;
        return 0;
    }
    for(i=0;i<=(data->enc);i++){
        if(strcmp(data->entryArr[data->enc].name,tagName)==0){
            printf("[Error] on line %d: .entry directive name already exists\n",data->lc);
            data->containError=TRUE;
            return 0;
        }
    }
     for(i=0;i<=(data->enc);i++){
        if(strcmp(data->externArr[data->enc].name,tagName)==0){
            printf("[Error] on line %d: .entry directive name already defined as .extern\n",data->lc);
            data->containError=TRUE;
            return 0;
        }
    }
    addEntry(data,tagName);
    return 1;
}

/*----------------------------------------------------------------------------*/
void addDirective(Data * data, int directive){
	data->directiveArr = realloc(data->directiveArr, sizeof(int)*(data->dc+1));
	data->directiveArr[data->dc]=directive;
	data->dc++;
}
/*----------------------------------------------------------------------------*/
void addExtern(Data * data, char * tag){
	data->externArr = realloc(data->externArr, sizeof(Extern)*(data->exc+1));
	strcpy(data->externArr[data->exc].name,tag);

	data->exc++;
}
/*----------------------------------------------------------------------------*/
void addEntry(Data * data, char * tag){
	data->entryArr = realloc(data->entryArr, sizeof(Entry)*(data->enc+1));
	strcpy(data->entryArr[data->enc].name,tag);
	data->enc++;
}
