#include <iostream>
#include "Altrernative.h"

extern void task1();
extern void task2();

int main() {

	task1();
	
	task2();
	
	//alt_task2();

	return 0;
 }

void task1() {
	double a, b;
	std::cout << "Enter a ";
	std::cin >> a;
	std::cout << "Enter b ";
	std::cin >> b;
	if (a != b)
		std::cout << "min " << ((a > b) ? b : a) << std::endl;
	else
		std::cout << "You must enter different number";
}

void task2() {
	std::cout << "Please choose menu item" << std::endl;
	for (int i = 1; i <= 9; i++)
		std::cout << "Menu item " << i << " enter " << i << "\t";
	std::cout << std::endl;

	char command;
	std::cout << "Enter command ";
	std::cin >> command;

	double x;
	std::cout << "Enter number ";
	std::cin >> x;	

	switch (command)
	{
		case '1':
			std::cout << x;
			break;
		case '2':
			std::cout << x * x;
			break;
		case '3':
			std::cout << x * x * x;
			break;
		case '4':
			std::cout << std::pow(x, 4);
			break;
		case '5':
			std::cout << std::pow(x, 5);
			break;
		case '6':
			std::cout << std::pow(x, 6);
			break;
		case '7':
			std::cout << std::pow(x, 7);
			break;
		case '8':
			std::cout << std::pow(x, 8);
			break;
		case '9':
			std::cout << std::pow(x, 9);
			break;		
	default:
		std::cout << "You enter incorrect command";
		break;
	}

	std::cout << std::endl;
}