#include "header.h"

/*----------------------------------------------------------------------------*/
void secondPassManager(FILE *file, Data * data){

    char lineHolder[MAX_LINE_LEN+1];

    data->ic = 0;
    fseek (file, 0, SEEK_SET);


    /* NULL means EOF. When we reach EOF it means we're done */
    while(fgets(lineHolder,MAX_LINE_LEN,file) != NULL ){
        lineHandlerSecoundRound(&data);
    }

    saveData(&data);

}
int lineHandlerSecoundRound(Data * data){
    char tag[31];
    getTag(data,tag);

    /* there's a tag at the start of the line */
    if (tag != NULL){
        return 0;
    }
    if(*(data->line)=='.'){
        return  directiveHandlerSecondPass(data, tag);
    }

    swapInstruction(data);
    handleOperands(data);

    return 0;
}

/*----------------------------------------------------------------------------*/
int directiveHandlerSecondPass(Data * data, char * tag){
    char s[6];
    data->line++;
    sscanf((data->line),"%s",s);
    data->line+=strlen(s)+1;

    eatSpace(data);

    if(strcmp(s,"data")==0){
        return 0;
    }
    if(strcmp(s,"string")==0){
        return 0;
    }
    if(strcmp(s,"entry")==0){
        return entryDirectiveSecondPassHandler(data,tag);
    }
    if(strcmp(s,"extern")==0){
        return externDirectiveSecondPassHandler(data,tag);
    }
    return 0;
}

int entryDirectiveSecondPassHandler(Data* data,char* tag){
}

int externDirectiveSecondPassHandler(Data* data,char* tag){
}

int swapInstruction(Data * data){

}
void saveData (Data* data){
}


