#include "Altrernative.h"
#include <iostream>

void alt_task2() {
	std::cout << "Please choose command = power" << std::endl;

	char command;
	std::cout << "Enter command ";
	std::cin >> command;
	const char* c = &command;

	double x;
	std::cout << "Enter number ";
	std::cin >> x;

	std::cout << std::pow(x, atoi(c)) << std::endl;
	
}