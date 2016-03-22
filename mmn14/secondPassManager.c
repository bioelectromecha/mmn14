/*
 ====================================================================================
 Module:        secondPassManager
 Description: 	holds all the functions that implement the second pass algorithm
 ====================================================================================
 */


#include "header.h"


/*----------------------------------------------------------------------------*/
/*
 * Description: implements the second pass algorithm (from the course booklet)
 * Input:       Data struct from passManager, FILE pointer
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void secondPassManager( Data * data, FILE *file){
    char lineHolder[MAX_LINE_LEN+1];

    /* NULL means EOF. When we reach EOF it means we're done */
    while(fgets(lineHolder,MAX_LINE_LEN,file) != NULL ){
        data->line=lineHolder;
        if(lineHandlerSecondPass(data,file)==0){
            printf("[Error] on line %d: Fatal Error, continuing to next file if exists\n",data->lc);
        }
        data->lc++;
    }
}

/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       Assembly file names as command line arguments, without the .asm extension
 * Output:		machine code files (.o suffix), entry files, extern files
 */
/*----------------------------------------------------------------------------*/
int lineHandlerSecondPass(Data * data, FILE * file){
    char tag[31];
    /*should do nothing if there's a tag at the start of the line*/
    if(lineEmptyCheck(data)==1){
        return 1;
    }
    if(lineCommentCheck(data)==1){
        return 1;
    }
    getTag(data,tag);
    if(*(data->line)=='.'){
        return 1;
    }

    return secondPassCommandManager(data);
}


