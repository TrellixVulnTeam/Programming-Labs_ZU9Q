#include "Task.h"
#include <vector>
#include <iostream>
#include <math.h>

void task3for(std::vector<int> data) {
	double prod = data[0];
	for (int i = 1; i < data.size(); i++) {
		prod *= data[i];
		if (data[i] % 3 == 0) {
			std::cout << prod << std::endl;
			return;
		}
	}
	std::cout << "Data have not number like 3n" << std::endl;
}

void task3while(std::vector<int> data) {
	double prod = data[0];
	int i = 1;
	while (i < data.size()) {
		prod *= data[i];
		if (data[i] % 3 == 0) {
			std::cout << prod << std::endl;
			return;
		}
		i++;
	}
	std::cout << "Data have not number like 3n" << std::endl;
}

void alt_task3while(std::vector<int> data) {
	double prod = data[0];
	int i = 1;
	while (data[i] % 3 != 0) {
		try {
			prod *= data[i];
		}
		catch (...) {
			std::cout << "Data have not number like 3n" << std::endl;
		}
		i++;
	}
	prod *= data[i];
	std::cout << prod << std::endl;
}