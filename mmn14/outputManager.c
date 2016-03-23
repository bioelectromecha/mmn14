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
    strcpy(outputFileName,filename);
    strcat(outputFileName, ".ob");


    /* write the instruction and data lengths to file */
    writeLengthsToFile(data, outputFileName);
    while(data->ic>=0){
        if(data->instArr[data->ic].group==0){
            createOutputZeroExtra(data, outputFileName);
        }
        if(data->instArr[data->ic].group==1){
            createOutputOneExtra(data,outputFileName);

        }
        if(data->instArr[data->ic].group==2){
            createOutputTwoExtra(data,outputFileName);
        }
    }

}


/*----------------------------------------------------------------------------*/
/*
 * Description: generates the output file for an instruction with no extra words
 * Input:       Data struct, filename string
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void createOutputZeroExtra(Data * data, char * filename){
    unsigned long int output=0;
    char * base32output;
    output+=decimalToBinary(data->instArr[data->ic].e_r_a);
    output+=decimalToBinary(data->instArr[data->ic].destination_addressing)*100;
    output+=decimalToBinary(data->instArr[data->ic].source_addressing)*10000;
    output+=decimalToBinary(data->instArr[data->ic].opcode)*1000000;
    output+=decimalToBinary(data->instArr[data->ic].group)*10000000000;

    output = binaryToDecimal(output);

    base32output = decimalToBase32(output);
    writeToOutputFile(base32output, filename);
    free(base32output);
    data->ic--;
}


/*----------------------------------------------------------------------------*/
/*
 * Description: generates the output file for an instruction with one extra word
 * Input:       Data struct, filename string
 * Output:		nothing
 */
/*----------------------------------------------------------------------------*/
void createOutputOneExtra(Data * data, char * filename){
    unsigned long int output=0;
    char * base32output = NULL;

    /* write instruction to file */
    output+=decimalToBinary(data->instArr[data->ic].e_r_a);
    output+=decimalToBinary(data->instArr[data->ic].destination_addressing)*100;
    output+=decimalToBinary(data->instArr[data->ic].source_addressing)*10000;
    output+=decimalToBinary(data->instArr[data->ic].opcode)*1000000;
    output+=decimalToBinary(data->instArr[data->ic].group)*10000000000;
    output = binaryToDecimal(output);
    base32output = decimalToBase32(output);
    writeToOutputFile(base32output, filename);
    free(base32output);
    data->ic--;

    /* write extra word to file */
    output=0;
    output+=decimalToBinary(data->wordArr[data->wc].e_r_a);
    output+= decimalToBinary(data->wordArr[data->wc].word)*100;
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
void createOutputTwoExtra(Data * data,char * filename){
     unsigned long int output=0;
    char * base32output = NULL;

    /* write instruction to file */
    output+=data->instArr[data->ic].e_r_a;
    output+=decimalToBinary(data->instArr[data->ic].destination_addressing)*100;
    output+=decimalToBinary(data->instArr[data->ic].source_addressing)*10000;
    output+=decimalToBinary(data->instArr[data->ic].opcode)*1000000;
    output+=decimalToBinary(data->instArr[data->ic].group)*10000000000;
    output = binaryToDecimal(output);
    base32output = decimalToBase32(output);
    writeToOutputFile(base32output, filename);
    free(base32output);
    data->ic--;

    /* write first extra word to file */
    output=0;
    output+=decimalToBinary(data->wordArr[data->wc].e_r_a);
    output+= decimalToBinary(data->wordArr[data->wc].word)*100;
    output = binaryToDecimal(output);
    base32output = decimalToBase32(output);
    writeToOutputFile(base32output, filename);
    free(base32output);
    data->wc--;

    /* write second extra word to file */
    output=0;
    output+=decimalToBinary(data->wordArr[data->wc].e_r_a);
    output+= decimalToBinary(data->wordArr[data->wc].word)*100;
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

/*
 * Description: Converts a number in base 10 to wanted base
 * Input:		1. Number in base 10
 * 				2. Wanted base
 * 				3. Minimal length of returned word
 * Output:		Number in wanted base
 */
char* decimalToBase32(unsigned long int decNum){
	char * output = NULL;
	int remainder = 0;
	int tempNum;
	int counter=0;
	/* Convert number to target base by :
	 * 	1) Dividing the whole number
	 * 	2) Take the reminder and append it to the result string
	 * */
	while (decNum != 0) {
		output = realloc(output,sizeof(char) * (counter+1));
		tempNum=decNum / BASE32;
		remainder = decNum - tempNum * BASE32;
		decNum = tempNum;
		/* '0' is ascii 48 */
        output[counter]='0'+remainder;
        counter++;
	}
	output = realloc(output,sizeof(char) * (counter+1));
	output[counter]='\0';
	return output;
}
/* Function to convert binary to decimal*/
int binaryToDecimal(int n){
    int decimal=0;
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
 /* Function to convert decimal to binary.*/
int decimalToBinary(int n){
    int rem, i=1, binary=0;
    while (n!=0){
        rem=n%2;
        n/=2;
        binary+=rem*i;
        i*=10;
    }
    return binary;
}
