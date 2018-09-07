#include <iostream>

int main() {
	
	double a, b;
	std::cout << "Enter a ";
	std::cin >> a;
	std::cout << "Enter b ";
	std::cin >> b;
	if (a != b)
		std::cout << "min " << ((a > b) ? b : a) << std::endl;
	else
		std::cout << "You must enter different number";

	return 0;
 }