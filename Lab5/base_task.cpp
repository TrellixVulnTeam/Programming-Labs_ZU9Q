#include <fstream>

bool sum_base_task(const char* path) {
	std::ifstream input(path);
	if (input) {
		double a, b;
		input >> a;
		input >> b;
		std::ofstream output("test.out");
		if (output) {
			output << a + b;
		}
		else {
			input.close();
			return false;
		}
			
		return true;
	}
	else {
		input.close();
		return false;
	}		
}