/*
 ====================================================================================
 Module:        passManager
 Description: 	manages data allocation and first and second passes
 ====================================================================================
 */

#include "header.h"
/*----------------------------------------------------------------------------*/
/*
 * Description: manages the first and second pass, and file creation
 * Input:       pointer to the current file being read
 * Output:	    1 if successful, 0 otherwise
 */
/*----------------------------------------------------------------------------*/
int passManager(FILE *file, char * filename){

    /* create and initialize the data structures */
    Data data;
    initializeData(&data);

    /* go over the code for the first time*/
    firstPassManager(&data,file);

    /* if there's an error, don't continue */
    if(data.containError==TRUE){
        return 0;
    }

    /*reset the file pointer to beggining of file */
    fseek (file, 0, SEEK_SET);

    /* allocate memory for all the instructions */
    allocateInstructionMemory(&data);

    /* reset instruction counter to 0 */
    data.ic = 0;

    /* reset instruction counter to 0 */
    data.wc=0;

    /* go over the code for a second time*/
    secondPassManager(&data,file);

    /* if there's an error, don't continue */
    if(data.containError==TRUE){
        return 0;
    }

    /* create the output files and write the machine code into them */
    outputManager(&data, filename);

    /* free the data that was allocated during the run */
    setDataFree(&data);
    return 1;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: initializes the variables in the Data struct
 * Input:       pointer to Data struct
 * Output:	    nothing
 */
/*----------------------------------------------------------------------------*/
void initializeData(Data * data){

    /* initialize all the data in the data struct */
    data->tc = 0;
    data->lc = 0;
    data->dc = 0;
    data->ic = 0;
    data->exc = 0;
    data->enc = 0;
    data->wc =0;
    data->containError=FALSE;
    data->tagArr=NULL;
    data->directiveArr=NULL;
    data->entryArr=NULL;
    data->externArr=NULL;
    data->instArr=NULL;
    data->wordArr=NULL;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: frees all the dynamically allocated memory in the Data struct
 * Input:       pointer to Data struct
 * Output:	    nothing
 */
/*----------------------------------------------------------------------------*/
void setDataFree(Data * data){
    /* free all the data in the data struct */
    free(data->tagArr);
    free(data->directiveArr);
    free(data->externArr);
    free(data->entryArr);
    free(data->instArr);
    free(data->wordArr);
}


/*----------------------------------------------------------------------------*/
/*
 * Description: allocates memory for the instruction array
 * Input:       pointer to Data struct
 * Output:	    nothing
 */
/*----------------------------------------------------------------------------*/
void allocateInstructionMemory(Data * data){
    data->instArr = malloc(sizeof(Instruction)*(data->ic));
}
/*----------------------------------------------------------------------------*/
/*
 * Description: allocates memory for the extra words array
 * Input:       pointer to Data struct
 * Output:	    nothing
 */
/*----------------------------------------------------------------------------*/
void allocateExtraWordMemory(Data * data){
     data->wordArr = malloc(sizeof(Instruction)*(data->wc));
}



