#include "header.h"

void outputManager(Data * data){
    return;
}
/*
 * Description: Writes first line of ob file
 * Input:		1. IC value
 * 				2. DC value
 * 				3. Ob file handle
 */
void writeToOutputFile(Data * data, FILE* file) {
	char* number;

	/* Write instructions to file */
	number = convertBase10toOtherBase(data->ic, BASE32);
	fputs(number, file);
	free(number);

	fputc('\t', file);

	/* Write data to file */
	number = convertBase10toOtherBase(data->dc, BASE32);
	fputs(number, file);
	free(number);

	fputc(';', file);

}

/*
 * Description: Converts a number in base 10 to wanted base
 * Input:		1. Number in base 10
 * 				2. Wanted base
 * 				3. Minimal length of returned word
 * Output:		Number in wanted base
 */
char* convertBase10toOtherBase(int decNum, int otherBase) {
	char* result = NULL;
	char* current_token = NULL;
	int result_length;
	int remainder = 0;

	result = malloc(sizeof(char));

    result[0] = '\0';
    result_length = 1;

	/* Convert number to target base by :
	 * 	1) Dividing the whole number
	 * 	2) Take the reminder and append it to the result string
	 * */
	while (decNum != 0) {
		int temp;

		temp = decNum / otherBase;
		remainder = decNum - temp * otherBase;
		decNum = temp;

		current_token = malloc(sizeof(char) * (result_length + 1));

		if (current_token != NULL) {
			current_token[0] = '0' + remainder;
			current_token[1] = '\0';

			strcat(current_token, result);

			free(result);
			result = current_token;
		} else {
			if (result != NULL) {
				free(result);
			}

			return NULL;
		}
	}

	return result;
}
/*
 * Description: Writes encoding into output file
 * Input:		1. Address in base 10
 * 				2. Memory word value in base 10
 * 				3. Output file
 */
void print_encoding_to_file(unsigned int address, unsigned int value, FILE* p_file) {
	char* base4_value;

	/* Print Address base value */
	base4_value = convert_base10_to_target_base(address, TARGET_BASE, TARGET_MEMORY_ADDRESS_WORD_LENGTH);

	fputs(base4_value, p_file);
	fputc(COLUMN_SEPARATOR, p_file);

	free(base4_value);

	/* Print operation base value */
	base4_value = convert_base10_to_target_base(value, TARGET_BASE, TARGET_OPERATION_WORD_LENGTH);
	fputs(base4_value, p_file);

	free(base4_value);

	fputc(END_OF_LINE, p_file);
}
