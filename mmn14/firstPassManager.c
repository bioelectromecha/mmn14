#include "firstPassManager.h"
#include "commonFuncs.h"
#include "directivesManager.h"
#include "commandsManager.h"
/*----------------------------------------------------------------------------*/
/*
 * Description: implements the first pass algorithm (from the course booklet)
 * Input:       FILE pointer to assembly language file
 * Output:		1 if successful, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int firstPassManager(FILE *file){

    char lineHolder[MAX_LINE_LEN+1];
    Data data;

    initializeData(&data);

    /* NULL means EOF. When we reach EOF it means we're done */
    while(fgets(lineHolder,MAX_LINE_LEN,file) != NULL ){
        printf("%s\n",lineHolder);
        data.line=lineHolder;
        data.lc++;
        lineHandler(&data,file);
    }
    while(data.dc>0){
        printf("%d\n", data.directiveArr[data.dc]);
        data.dc--;
    }
    printf("SET IT FREE!!!!");

    setDataFree(&data);
    return 0;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: does basic line parsing and assigns input to other function for further parsing
 * Input:       pointer to Data struct, FILE pointer to assembly language file
 * Output:		1 if successful, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int lineHandler(Data * data,FILE *file){
    char tag[MAX_TAG_LEN];

    if(lineLengthCheck(data, file)==0){
        return 0;
    }
    if(lineEmptyCheck(data)==1){
        return 1;
    }
    if(lineCommentCheck(data)==1){
        return 1;
    }
    getTag(data,tag);
    /* there's a tag at the start of the line */
    if (tag != NULL){
        /*printf("%s\n",tag);*/
        if (tagDupCheck (data, tag) == 1){
            printf("[Error] on line %d: you have the tag %s more then once.\n",data->lc, tag);
            data->containError=TRUE;
            return 0;
        }
        eatSpace(data);
    }
    if(*(data->line)=='.'){
        return  directivesManager(data, tag);
    }
    if(checkUpperCase(*(data->line))==0){
        return commandsManager(data,tag);
    }
    printf("[Error] on line %d: line isn't valid a input\n",data->lc);
    data->containError=TRUE;
    return 0;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: check if a line is longer than MAX_LINE_LEN
 * Input:       pointer to Data struct, FILE pointer to assembly language file
 * Output:		1 if not longer, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int lineLengthCheck(Data * data, FILE *file){
    if(strlen(data->line)>=MAX_LINE_LEN-1 && (data->line)[MAX_LINE_LEN-1] != EOF && (data->line)[MAX_LINE_LEN-1] != '\n'){
        printf("[Error] on line %d: line is longer than %d chars\n", data->lc,MAX_LINE_LEN);
        data->containError=TRUE;
        /* get rid of the rest of the line so we don't get the rest of it with fgets instead of a new one */
        eatLine(file);
        return 0;
    }
    return 1;
}





/*----------------------------------------------------------------------------*/
/*
 * Description: check whether a tag already exists
 * Input:       pointer to Data struct, pointer to a character array
 * Output:		1 if duplicate, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int tagDupCheck(Data * data, char * tag){
    int index;
    for (index = 0; index< data->tc;index++){
        if (strcmp(data->tagArr[index].name,tag) == 0){
            return 1;
        }
    }
    return 0;
}




/*----------------------------------------------------------------------------*/
/*
 * Description: initializes the variables in the Data struct
 * Input:       pointer to Data struct
 * Output:	    nothing
 */
/*----------------------------------------------------------------------------*/
void initializeData(Data * data){
    data->tc = 0;
    data->lc = 0;
    data->dc = 0;
    data->ic = 0;
    data->exc = 0;
    data->enc = 0;
    data->containError=FALSE;
    data->tagArr=NULL;
    data->directiveArr=NULL;
    data->entryArr=NULL;
    data->externArr=NULL;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: adds a tag to the tag array inside the Data struct
 * Input:       pointer to Data struct, tag name pointer, address to point tag at
 * Output:	    nothing
 */
/*----------------------------------------------------------------------------*/
void addTag(Data * data, char * tag, int dirAddress){
	data->tagArr = realloc(data->tagArr, sizeof(Tag)*(data->tc+1));
	strcpy(data->tagArr[data->tc].name,tag);
	data->tagArr[data->tc].address=dirAddress;
	data->tc++;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: frees all the dynamically allocated memory in the Data struct
 * Input:       pointer to Data struct
 * Output:	    nothing
 */
/*----------------------------------------------------------------------------*/
void setDataFree(Data * data){
    free(data->tagArr);
    free(data->directiveArr);
    free(data->externArr);
    free(data->entryArr);
}
