#include <iostream>
#include <stack>
#include <cmath>

void add_task(int b, int data) {	
	std::stack<int> q = std::stack<int>();
	while (data > b) {
		int temp = data % b;
		if ((temp > 9) && (temp < 16)) {
			
		}
		q.push(temp);
		data = data / b;		
	}
	std::cout << data;
	while(!q.empty())
	{
		std::cout << q.top();
		q.pop();
	}
}

using namespace std;

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

	

	add_task(2,31);

	return 0;
}