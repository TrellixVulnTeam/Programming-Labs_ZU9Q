#include <cstdio>
#include <iostream>

void to8(unsigned int* data);

bool dump8_medium_task(const char* path) {
	FILE* file = std::fopen(path, "r");
	if (!file)
		return false;	
	int i = 0;
	bool is_end = false;
	char data[4];
	while ((data[0] = getc(file)) != EOF)  {
		i++;		
		unsigned int data2[4];		
		std::fread(data+1, 1, 3, file);
		std::cout << "Result:" << std::endl;
		for (int i = 0; i < 4; i++) {
			if (data[i] == '0')
				data2[i] = 0;
			else if (data[i] == '1')
				data2[i] = 1;
		}				
		to8(data2);		
	}	
	return true;
}

void to8(unsigned int* data) {
	if (data[0] == 1)
		std::cout << "1";
	int sum = 0;
	for (int i = 1; i < 4; i++) {
		sum += data[i] * pow(2, 4 - i - 1);
	}
	std::cout << sum << std::endl;
}