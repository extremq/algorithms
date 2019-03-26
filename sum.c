#include <stdio.h>
#include <stdbool.h>

int string_to_int(char* _param){
	int _returnval = 0;
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
				printf("%d %d %d", i, j, _argv[i][j]);
				return false;
			}
		}
	}
	return true;
}

int main(int argc, char** argv){
	if(argc < 3){
		printf("./sum a b c ...\n");
		return 0;
	}
	if(check_arguments(argc ,argv) == false){
		printf("Enter numbers!\n");
		return 0;
	}
	int _sum = 0;
	for(int i = 1; i < argc; ++i){
		_sum = _sum + string_to_int(argv[i]);
	}
	printf("%d\n", _sum);
	return 0;
}

	
