#include "header.h"



/*----------------------------------------------------------------------------*/
int firstPassManager(FILE *file){
    char lineHolder[MAX_LINE_LEN+1];
    Data data;
    data.tc=0;
    data.lc=0;
    data.dc=0;
    data.ic=0;
    /* NULL means EOF. When we reach EOF it means we're done */
    while(fgets(lineHolder,MAX_LINE_LEN,file) != NULL ){
        data.line=lineHolder;
        data.lc++;
        if (lineValidator(&data,file) == 1){
            lineHandler(&data);
        }
    }
    return 0;
}



/*----------------------------------------------------------------------------*/
int lineValidator(Data * data,FILE *file){
    /* check if a line is longer than MAX_LINE_LEN */
    if(strlen(data->line)>=MAX_LINE_LEN-1 && (data->line)[MAX_LINE_LEN-1] != EOF && (data->line)[MAX_LINE_LEN-1] != '\n'){
        printf("ERROR line is longer than %d chars\n", MAX_LINE_LEN);
        /* get rid of the rest of the line so we don't get the rest of it with fgets instead of a new one */
        eatLine(file);
        printf("%s\n",data->line);
        return 0;
    }
    /* check if it's an empty line */
    eatSpace(data);
    if(*(data->line)=='\n' || *(data->line)==EOF){
        return 0;
    }
    /* if it's a comment line */
    if(*(data->line)==';'){
        return 0;
    }
    return 1;
}

/*----------------------------------------------------------------------------*/
int lineHandler(Data * data){
    char * tag;
    int tagstate = FALSE;
    tag = getTag(data);

    /* there's a tag at the start of the line */
    if (tag != NULL){
        /*printf("%s\n",tag);*/
        if (tagDupCheck(tag) == 0){
        printf("[Error] on line %d: you have the tag %s more then once.\n",data->lc, tag);
            return 0;
        }
        tagstate = TRUE;
        eatSpace(data);
    }
    if(*(data->line)=='.'){
        return  directiveHandler(Data * data, tag)l
    }
    if(checkUpperCase(*(data->line))==1){
        return commandHandler(Data * data);
    }
    printf("[Error] on line %d: line isn't valid a input\n",data->lc);
    return 0;
}
/*----------------------------------------------------------------------------*/
/* check whether a tag already exists */
int tagDupCheck(Data * data, char * tag){
    int index;
    for (index = 0; index< data->tc;index++){
        if (strcmp(data->tagArr[index].name,tag) == 0){
            return 0;
        }
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
char * getTag(Data * data){
    static char tag[30];
    int counter=0;
    char * c = data->line+1;
    if (checkLetters(*(data->line))== 0){
        return NULL;
    }
    while(!isspace(*c) && (*c != ':')){
        if (checkLetterOrNumber(*c) == 0){
            return NULL;
        }
        counter++;
        c++;
    }
    if (*c == ':'){
        while(counter>=0){
            *tag=*(data->line);
            data->line++;
            tag++;
            counter--;
        }
        *tag='\0';
        data->line++;
    }
    return tag;
}
/*----------------------------------------------------------------------------*/
int directiveHandler(Data * data, char * tag){
    char s[6];
    sscanf((data->line+1),"%s",s);
    data->line+1+=strlen(s)+1;

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
        return 0;
    }
    while(state != EXIT){
        eatSpace(data);
        if(state==GET_NUMBER){
            if (sscanf(data->line, "%d", &num)>0) {
                printf("[Error] on line %d:- malformed data directive - missing number \n", data->lc);
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
        strcpy(data->tagArr[data->tc].name,tag);
        data->tagArr[data->tc].address=data->dc;
        data->tc++;
    }
    for(i=0;i<=dcounter;i++){
        data->directiveArr[data->dc]=numberArray[dcounter];
        dc++;
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
            return 0;
        }
        data->line++;
        /* check for extra characters after the string ending (it's not a valid string directive that way) */
        eatSpace(data);
        if(letter!='\n' && letter!=EOF){
            printf("[Error] on line %d: malformed string directive - extra characters after string ending\n",data->lc);
            return 0;
        }
    /* if the string directive contains no string - it's an invalid directive */
    }else{
        printf("[Error] on line %d: malformed string directive - no leading quotation mark in string\n",data->lc);
        return 0;
    }
        if(tag != NULL){
        strcpy(data->tagArr[data->tc].name,tag);
        data->tagArr[data->tc].address=data->dc;
        data->tc++;
    }
    for(i=0;i<=counter;i++){
        data->directiveArr[data->dc]=charArray[counter];
        data->dc++;
    }
    data->directiveArr[data->dc]=0;
    data->dc++;
    return 1;
}
/*----------------------------------------------------------------------------*/
int externHandler(Data * data, char * tag){
    char tagName[30];
    int i=0;
    if(tag != NULL){
        printf("[Error] on line %d: a .extern directive can't start with a tag\n",data->lc);
        return 0;
    }
    if(*(data->line) =='\n' || *(data->line)==EOF){
        printf("[Error] on line %d: empty directive\n",data->lc);
        return 0;
    }
    tagName=getTag(data);
    if(tagName==NULL){
        printf("[Error] on line %d: malformed .extern directive\n",data->lc);
        return 0;
    }
    for(i=0;i<=(data->enc);i++){
        if(strcmp(data->entryArr[enc],tagName)==0){
            printf("[Error] on line %d: .extern directive name already defined as .entry\n",data->lc);
            return 0;
        }
    }
     for(i=0;i<=(data->enc);i++){
        if(strcmp(data->externArr[enc],tagName)==0){
            printf("[Error] on line %d: .extern directive name already exists\n",data->lc);
            return 0;
        }
    }
    data->exc++;
    strcpy(data->externArr[data->exc],tagName);
    return 1;
}
/*----------------------------------------------------------------------------*/
int entryHandler(Data * data, char * tag){
    char tagName[30];
    int i=0;
    printf("[Error] on line %d: a .entry directive can't start with a tag\n",data->lc);
        return 0;
    }
    if(*(data->line) =='\n' || *(data->line)==EOF){
        printf("[Error] on line %d: empty directive\n",data->lc);
        return 0;
    }
    tagName=getTag(data);
     if(tagName==NULL){
        printf("[Error] on line %d: malformed .extern directive\n",data->lc);
        return 0;
    }
    for(i=0;i<=(data->enc);i++){
        if(strcmp(data->entryArr[enc],tagName)==0){
            printf("[Error] on line %d: .entry directive name already exists\n",data->lc);
            return 0;
        }
    }
     for(i=0;i<=(data->enc);i++){
        if(strcmp(data->externArr[enc],tagName)==0){
            printf("[Error] on line %d: .entry directive name already defined as .extern\n",data->lc);
            return 0;
        }
    }
    data->enc++;
    strcpy(data->entryArr[data->enc],tagName);
    return 1;
}

