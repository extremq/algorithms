/*
	SCOPE: nothing much but it calculates the sum of all numbers you specify using argv 
	USAGE: gcc -Wall sum.c -o sum
	From there, you simply run the executable with ./sum n1 n2 n3 where ni is an integer (may be negative)
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

int64_t string_to_int(char* _param){
	int64_t _returnval = 0;
	bool _isnegative = false;
	int i = 0;
	if(_param[i] == '-'){
		_isnegative = true;
		++i;
	}
	for(; _param[i] != '\0'; ++i){
		_returnval = _returnval * 10 + _param[i] - '0';
	}
	if(_isnegative == true)
		_returnval = -_returnval;
	return _returnval;
}

bool check_arguments(int _argc, char** _argv){
	for(int i = 1; i < _argc; ++i){
		for(int j = 0; _argv[i][j] != '\0'; ++j){
			if((_argv[i][j] < 48 || _argv[i][j] > 57) && _argv[i][j] != '-'){
				return false;
			}
		}
	}
	return true;
}

int main(int argc, char** argv){
	if(argc < 3){
		printf("Syntax: ./sum n1 n2 n3 ...\n");
		return 0;
	}
	if(check_arguments(argc ,argv) == false){
		printf("Enter numbers!\n");
		return 0;
	}
	int64_t _sum = 0;
	for(int i = 1; i < argc; ++i){
		_sum = _sum + string_to_int(argv[i]);
	}
	printf("%" PRId64 "\n", _sum);
	return 0;
}

	
