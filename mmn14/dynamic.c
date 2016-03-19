#include "header.h"



/*----------------------------------------------------------------------------*/
void addTag(Data * pdata, char * ptag, int dirAddress){
	if(data->tagArr==NULL){
        data->tagArr= (Tag)malloc(sizeof(Tag));
        return;
	}
	data->tagArr = (Tag *) realoc(data->tagArr, sizeof(Tag)*(data->tc+1));
	strcpy(data->tagArr[data->tc].name,tag);
	data->tagArr[data->tc].address=dirAddress;
	data->tc++;
}

void addDirective(Data * data, int directive){
	if(data->directiveArr==NULL){
        data->directiveArr= (int * )malloc(sizeof(int));
        return;
	}
	data->directiveArr = (int *) realoc(data->directiveArr, sizeof(int)*(data->dc+1));
	data->directiveArr[data->dc]=directive;
	data->tc++;
}

void addExtern(Data * data, char * tag){
    if(data->externArr==NULL){
        data->externArr= (Extern)malloc(sizeof(Extern));
        return;
	}
	data->externArr = (Extern *) realoc(data->externArr, sizeof(Extern)*(data->exc+1));
	strcpy(data->externArr[data->exc].name,tag);
	data->exc++;
}
void addEntry(Data * data, char * tag){
    if(data->entryArr==NULL){
        data->entryArr= (Entry)malloc(sizeof(Entry));
        return;
	}
	data->entryArr = (Entry *) realoc(data->entryArr, sizeof(Entry)*(data->enc+1));
	strcpy(data->entryArr[data->enc].name,tag);
	data->enc++;
}
void setDataFree(Data * data){
    free(data->tagArr);
    free(data->directiveArr);
    free(data->externArr);
    free(data->entryArr);
}

