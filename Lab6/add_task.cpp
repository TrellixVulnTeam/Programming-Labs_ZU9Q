#include <string>
#include <iostream>

void printPart_add_task(std::string string) {
	std::string res = string.substr(0, string.find_first_of('*'));
	for (auto it = res.cbegin(); it != res.cend(); it++)
		std::cout << *it;
	std::cout << std::endl;
}