/*
	SCOPE: decode any number of base64 codes
	USAGE: gcc base64.c -o base64
	SYNTAX: ./base64 [-v] code1 code2 code3 ... (valid codes)
	-v = verbose (it shows what char was and wasn't valid and their respective codes - for debugging)
*/   
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 100

char* decode(char* encoded){
	char* decoded;
	decoded = (char*)malloc(sizeof(char) * (MAX_SIZE + 1) );
	int i, j, k = 0;
	
	int bitstream = 0;
	
	int bit_count = 0;
	
	for(i = 0; encoded[i] != '\0'; i += 4){
		bitstream = 0;
		bit_count = 0;
		for(j = 0; j < 4; ++j){
			if(encoded[i + j] != '='){
				bitstream = bitstream << 6;
				bit_count = bit_count +  6;
			}
			
			if(encoded[i + j] >= 'A' && encoded[i+j] <= 'Z')
				bitstream = bitstream | (encoded[i + j] - 'A');
			else if(encoded[i + j] >= 'a' && encoded[i + j] <= 'z')
				bitstream = bitstream | (encoded[i + j] - 'a' + 26);
			else if(encoded[i + j] >= '0' && encoded[i + j] <= '9')
				bitstream = bitstream | (encoded[i + j] - '0' + 52);
			else if(encoded[i + j] == '+')
				bitstream = bitstream | 62;
			else if(encoded[i + j] == '/')
				bitstream = bitstream | 63;
			else {
				bitstream = bitstream >> 2;
				bit_count = bit_count -  2;
			}
		}
		while(bit_count != 0){
			bit_count = bit_count - 8;
			decoded[k++] = (bitstream >> bit_count) & 255;
		}	
	}
	decoded[k] = '\0';

	return decoded;
}

bool verbose = false;

bool check_argument(char* argument){
	bool* invalid;
	invalid = (bool*)malloc(sizeof(bool) * 6);
	for(int i = 0; argument[i] != '\0'; ++i){
		bool valid = false;
		if(argument[i] < 'A' || argument[i] > 'Z') invalid[0] = true;
		if(argument[i] < '0' || argument[i] > '9') invalid[1] = true;
		if(argument[i] < 'a' || argument[i] > 'z') invalid[2] = true;
		if(argument[i] != 43) invalid[3] = true;
		if(argument[i] != 47) invalid[4] = true;
		if(argument[i] != 61) invalid[5] = true;
		
		for(int j = 0; j < 6; ++j){
			if(invalid[j] == false) 
				valid = true;
			invalid[j] = false;
		}
		if(verbose == true)	
			printf("Char: %d Valid: %d \n", argument[i], valid); 
		if(valid == false)
			return false;
	}
	return true;
}

int stringlen (char* arr){
	int size = 0;
	int i = 0;
	while(arr[i++] != '\0') ++size;
	return size;
}

int main(int argc, char** argv){
	int startindex = 1;
	if(argc < 2){
		printf("Syntax: ./base64 code1 code2...\n");
		return 0;
	}
	if(argv[1][0] == '-' && argv[1][1] == 'v'){
		verbose = true;
		startindex = 2;
	}
	for(int i = startindex; i < argc; ++i)
	{
		if(check_argument(argv[i]) == false)
			printf("This is invalid base64.\n");
		else {
			if(stringlen(argv[i]) % 4 != 0)
				printf("This is invalid base64 (it needs to have a multiple of 4 chars)\n");
			else printf("%s\n", decode(argv[i])); 
		}
	}
	return 0;
}
