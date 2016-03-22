/*function declarations */

int directivesManager(Data * data, char * tag);
int entryDirectiveHandler(Data * data, char * tag);
int stringDirectiveHandler(Data * data, char * tag);
int externDirectiveHandler(Data * data, char * tag);
int dataDirectiveHandler(Data * data, char * tag);
void addDirective(Data * data, int directive);
void addExtern(Data * data, char * tag);
void addEntry(Data * data, char * tag);
