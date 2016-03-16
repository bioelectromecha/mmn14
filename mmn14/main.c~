#include <stdio.h>
#include <stdlib.h>

int space_eater(char *);
void line_eater(FILE *fp);
int firstParse(FILE *fp);

/* Danny said it's okay to assume there's a max length for a name variable, so this is it */
#define MAX_NAME_LEN 80

int firstPassCreator(FILE *file);

int main(int argc, char* argv[]){

    /* debug code
    int main(int argc, char* argv[]){

---------------------*/
*(argv+1) = "check";
argc = 2;


/*-------------------*/


    /* string to hold a filename after addition of the ".as" suffix */
	/* we add 3 to the array size to hold the ".as" suffix, which is not received as input and will be included later on */
    char filename[MAX_NAME_LEN+3];
	/* increment variable */
    int i;
	/* pointer to current file */
    FILE *fp;


	/* check if the program was ran with 0 arguments */
    if(argc==1)
    {
        printf("ERROR No files to compile\n");
        return 1;
    }
	/*go through the file names array*/
	/* there's no check if the user entered a name with an extension, i.e because (e.g) tuna.as.as is a valid filname */
    for(i=1; i<argc; i++){
        if( MAX_NAME_LEN<=(strlen(argv[i])) ){
            printf("ERROR Invalid file name - max filename length is 80 characters\n");
            continue;
        }
	/* copy the file name to a bigger char array so we could add the ".asm" suffix to the name */
        strcpy(filename,argv[i]);
	/* add the ".as" suffix */
        strcat(filename,".as");
	/* open the file in read mode */
        fp = fopen (filename, "r");
	/* check if file was opened successfully (i.e if it exists); */
        if (!fp){
            printf("ERROR The file named %s %s doesn't exist\n",argv[0],filename);
            continue;
        }
        firstPassCreator(fp);
        /* close the file after playing around with it */
        fclose(fp);
      }
    return 0;
}
