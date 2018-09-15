#include "Task.h"
#include <iostream>

using namespace std;

int main() {
	cout << "Base task" << endl << endl;	
	if (!sum_base_task("test.in"))
		cout << "Error in base task" << endl;
	if (!dump8_medium_task("binary.txt"))
		cout << "Error in medium task" << endl;
	return 0;
}