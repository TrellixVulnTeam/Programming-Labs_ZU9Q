#include <iostream>

void add_task(int data) {
	while ((data / 2) > 0) {
		std::cout << data % 2;
		data = data / 2;
	}
}

int main() {
	double x;
	double y;
	double r;

	std::cout << "Enter r: ";
	std::cin >> r;	
	std::cout << "Enter x: ";
	std::cin >> x;
	std::cout << "Enter y: ";
	std::cin >> y;

	if ((x == y)&&(x == r/2))
	{
		std::cout << "Yes";
	}
	else
	{
		std::cout << "False";
	}	
	std::cout << std::endl;

	add_task(8, 31);

	return 0;
}