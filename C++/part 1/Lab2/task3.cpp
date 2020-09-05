#include "Task.h"

void task3for(std::vector<int> data) {
	double prod = 0;
	for (int i = 0; i < data.size(); i++) {
		if (data[i] % 3 == 0) {
			if (prod != 0)
				prod *= data[i];
			else
				prod = data[i];
		}
	}
	if (prod != 0)
		std::cout << prod << std::endl;
	else
		std::cout << "Data have not number like 3n" << std::endl;
}

void task3while(std::vector<int> data) {
	double prod = 0;
	int i = 0;
	while (i < data.size()) {
		if (data[i] % 3 == 0) {
			if (prod != 0)
				prod *= data[i];
			else
				prod = data[i];
		}
		i++;
	}
	if (prod != 0)
		std::cout << prod << std::endl;
	else
		std::cout << "Data have not number like 3n" << std::endl;
}