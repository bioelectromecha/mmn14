#include "header.h"

/*----------------------------------------------------------------------------*/
void secondPassManager(FILE *file, Data * data){
    char lineHolder[MAX_LINE_LEN+1];
    data->ic = 0;
    fseek (file, 0, SEEK_SET);
    /* NULL means EOF. When we reach EOF it means we're done */
    while(fgets(lineHolder,MAX_LINE_LEN,file) != NULL ){
        data->line=lineHolder;
        lineHandlerSecondPass(&data);
    }
}
int lineHandlerSecondPass(Data * data){
    char tag[31];
    getTag(data,tag);

    if(lineLengthCheck(data, file)==0){
        return 0;
    }
    if(lineEmptyCheck(data)==1){
        return 1;
    }
    if(lineCommentCheck(data)==1){
        return 1;
    }
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
