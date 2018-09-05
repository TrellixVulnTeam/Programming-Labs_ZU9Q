#include <iostream>
#include <stack>
#include <cmath>

void add_task1(int b, int data) {	
	std::stack<int> q = std::stack<int>();
	while (data > b) {
		int temp = data % b;
		q.push(temp);
		data = data / b;		
	}
	std::cout << data;
	while(!q.empty())
	{
		auto temp = q.top();
		if ((temp > 9) && (temp < 16)) {
			switch (temp)
			{
			case 10:
				std::cout << "A";
				break;
			case 11:
				std::cout << "B";
				break;
			case 12:
				std::cout << "C";
				break;
			case 13:
				std::cout << "D";
				break;
			case 14:
				std::cout << "E";
				break;
			case 15:
				std::cout << "F";
				break;
			default:
				break;
			}
		}
		else
		{
			std::cout << temp;
		}	
		q.pop();
	}
}

void add_task2(int number) {

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

	

	add_task(16,31);

	return 0;
}