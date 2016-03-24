/*
 ====================================================================================
 Module:        outputManager
 Description: 	generates the output file and writes the code into them
 ====================================================================================
 */


 #include "header.h"


/*----------------------------------------------------------------------------*/
/*
 * Description: generates the output file and writes the code into them
 * Input:       Data struct
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void outputManager(Data * data, char * filename){
    char outputFileName[MAX_NAME_LEN];
    int instructionIndex;
    int dataIndex=0;
    int wordIndex=0;
    strcpy(outputFileName,filename);
    strcat(outputFileName, ".ob");


    /* write the instruction and data lengths to file */
    writeLengthsToFile(data, outputFileName);

    /* write all the instructions to file */
    for(instructionIndex=0;instructionIndex<data->ic;instructionIndex++){
        if(data->instArr[instructionIndex].group==0){
            createOutputZeroExtra(data, outputFileName,instructionIndex);
        }
        if(data->instArr[instructionIndex].group==1){
            createOutputOneExtra(data,outputFileName,instructionIndex, wordIndex);
            wordIndex++;

        }
        if(data->instArr[instructionIndex].group==2){
            createOutputTwoExtra(data,outputFileName, instructionIndex, wordIndex, wordIndex+1);
            wordIndex+=2;
        }
    }
    /* write the data to file */
    for(dataIndex=0;dataIndex<data->dc;dataIndex++){
        writeToOutputFile(decimalToBase32(data->tagArr[dataIndex].address), outputFileName);
    }

    /* remove the .ob extension */
    strcpy(outputFileName,filename);

    /* print externals to file */
    if(data->exc>0){
        strcat(outputFileName, ".ext");
        writeExternToFile(data,outputFileName);
    }

    /* remove the .ext extension */
    strcpy(outputFileName,filename);


    /* print entries to file */
    if(data->enc>0){
        strcat(outputFileName, ".ent");
        writeEntryToFile(data,outputFileName);
    }
}


/*----------------------------------------------------------------------------*/
/*
 * Description: generates the output file for an instruction with no extra words
 * Input:       Data struct, filename string
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void createOutputZeroExtra(Data * data, char * filename, int instructionIndex){
    unsigned long int output=0;
    char * base32output;
    output+=decimalToBinary(data->instArr[instructionIndex].e_r_a);
    output+=decimalToBinary(data->instArr[instructionIndex].destination_addressing)*100;
    output+=decimalToBinary(data->instArr[instructionIndex].source_addressing)*10000;
    output+=decimalToBinary(data->instArr[instructionIndex].opcode)*1000000;
    output+=decimalToBinary(data->instArr[instructionIndex].group)*10000000000;

    output = binaryToDecimal(output);

    base32output = decimalToBase32(output);
    writeToOutputFile(base32output, filename);
    free(base32output);
}


/*----------------------------------------------------------------------------*/
/*
 * Description: generates the output file for an instruction with one extra word
 * Input:       Data struct, filename string
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void createOutputOneExtra(Data * data, char * filename, int instructionIndex, int wordIndex ){
    unsigned long int output=0;
    char * base32output = NULL;

    /* write instruction to file */
    output+=decimalToBinary(data->instArr[instructionIndex].e_r_a);
    output+=decimalToBinary(data->instArr[instructionIndex].destination_addressing)*100;
    output+=decimalToBinary(data->instArr[instructionIndex].source_addressing)*10000;
    output+=decimalToBinary(data->instArr[instructionIndex].opcode)*1000000;
    output+=decimalToBinary(data->instArr[instructionIndex].group)*10000000000;

    output = binaryToDecimal(output);
    base32output = decimalToBase32(output);
    writeToOutputFile(base32output, filename);
    free(base32output);
    data->ic--;

    /* write extra word to file */
    output=0;
    output+=decimalToBinary(data->wordArr[wordIndex].e_r_a);
    output+= decimalToBinary(data->wordArr[wordIndex].word)*100;
    output = binaryToDecimal(output);
    base32output = decimalToBase32(output);
    writeToOutputFile(base32output, filename);
    free(base32output);
    data->wc--;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: generates the output file for an instruction with two extra words
 * Input:       Data struct, filename string
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void createOutputTwoExtra(Data * data,char * filename, int instructionIndex, int wordIndex1, int wordIndex2){
     unsigned long int output=0;
    char * base32output = NULL;

    /* write instruction to file */
    output+=decimalToBinary(data->instArr[instructionIndex].e_r_a);
    output+=decimalToBinary(data->instArr[instructionIndex].destination_addressing)*100;
    output+=decimalToBinary(data->instArr[instructionIndex].source_addressing)*10000;
    output+=decimalToBinary(data->instArr[instructionIndex].opcode)*1000000;
    output+=decimalToBinary(data->instArr[instructionIndex].group)*10000000000;
    output = binaryToDecimal(output);
    base32output = decimalToBase32(output);
    writeToOutputFile(base32output, filename);
    free(base32output);
    data->ic--;

    /* write first extra word to file */
    output=0;
    output+=decimalToBinary(data->wordArr[wordIndex1].e_r_a);
    output+= decimalToBinary(data->wordArr[wordIndex1].word)*100;
    output = binaryToDecimal(output);
    base32output = decimalToBase32(output);
    writeToOutputFile(base32output, filename);
    free(base32output);
    data->wc--;

    /* write second extra word to file */
    output=0;
    output+=decimalToBinary(data->wordArr[wordIndex2].e_r_a);
    output+= decimalToBinary(data->wordArr[wordIndex2].word)*100;
    output = binaryToDecimal(output);
    base32output = decimalToBase32(output);
    writeToOutputFile(base32output, filename);
    free(base32output);
    data->wc--;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: writes the output to file
 * Input:       output string, filename string
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void writeToOutputFile(char * output,char * filename) {
    FILE *file;

    if(*output=='\0'){
        return;
    }

    file = fopen(filename, "a");
    fseek(file, -1 , SEEK_END);
	/* Write instructions to file */
	fputs(output, file);
	/* code is seperated by a new line */
	fputc('\n', file);
	fclose(file);
}
/*----------------------------------------------------------------------------*/
/*
 * Description: writes the lengths at the start of the file
 * Input:       output string, filename string
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void writeLengthsToFile(Data * data, char * filename){
    FILE *file;
    char * base32InstructionLength = NULL;
    char * base32DataLength = NULL;

    file = fopen(filename, "w");

    /* Write instructions to file */
    base32InstructionLength = decimalToBase32(data->ic);
    fputs(base32InstructionLength, file);
    free(base32InstructionLength);

    /* seperate by space between instruction and data length */
	fputc(' ', file);

    /* Write data length to file */
    base32DataLength = decimalToBase32(data->dc);
	fputs(base32DataLength,file);
    free(base32DataLength);

    /* code is seperated by a new line */
	fputc('\n', file);

	fclose(file);

}
/*----------------------------------------------------------------------------*/
/*
 * Description: write all the entry variables to file
 * Input:       Data sturct, string filename
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void writeEntryToFile(Data * data,char * filename) {
    FILE *file;
    int i=0;

    file = fopen(filename, "w");
    for(i=0;i<data->enc;i++){
        fputs(data->entryArr[i].name, file);
        /* code is seperated by a new line */
        fputc('\n', file);
    }
	fclose(file);
}


/*----------------------------------------------------------------------------*/
/*
 * Description: write all the external variables to file
 * Input:       Data sturct, string filename
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void writeExternToFile(Data * data,char * filename) {
    FILE *file;
    int i=0;

    file = fopen(filename, "w");
    for(i=0;i<data->exc;i++){
        fputs(data->externArr[i].name, file);
        /* code is seperated by a new line */
        fputc('\n', file);
    }
	fclose(file);
}


/*----------------------------------------------------------------------------*/
/*
 * Description: convert a number in base 10 to a string in base32
 * Input:       int
 * Output:		string
 */
/*----------------------------------------------------------------------------*/
char* decimalToBase32(unsigned long int decNum){
	char * output = NULL;
	int remainder = 0;
	int tempNum;
	int counter=0;

    /* special handling in case of 0, because it won't go into while loop */
	if(decNum==0){
        output = realloc(output,sizeof(char));
        *output = '0';
	}


	while (decNum != 0) {
		output = realloc(output,sizeof(char) * (counter+1));
		tempNum=decNum / BASE32;
		remainder = decNum - tempNum * BASE32;
		decNum = tempNum;

        /* ascii numbers and characters are not a continuious */
		if(remainder>9){
            /* 'A' is ascii 65 */
            output[counter]='A'+remainder-10;
		}else{
            /* '0' is ascii 48 */
             output[counter]='0'+remainder;
		}

        counter++;
	}
	output = realloc(output,sizeof(char) * (counter+1));
	output[counter]='\0';
	return output;
}

/*----------------------------------------------------------------------------*/
/*
 * Description: convert a binary represeting integer to decimal
 * Input:       int
 * Output:		int
 */
/*----------------------------------------------------------------------------*/
unsigned long int binaryToDecimal(unsigned long int n){
    unsigned long int decimal=0;
    int i=0;
    int rem;

    while (n!=0){
        rem = n%10;
        n/=10;
        decimal += rem*pow(2,i);
        ++i;
    }
    return decimal;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: convert a  decimal to a int representign a binary
 * Input:       int
 * Output:		int
 */
/*----------------------------------------------------------------------------*/
unsigned long int decimalToBinary(unsigned long int n){
    unsigned long int binary=0;
    int rem;
    int i=1;
    while (n!=0){
        rem=n%2;
        n/=2;
        binary+=rem*i;
        i*=10;
    }
    return binary;
}
