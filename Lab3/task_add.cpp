#include "Task.h"
#include <stack>
#include <iostream>

std::stack<int> p1, p2, p3;

extern void move(int n, std::stack<int>&from, std::stack<int> &to, std::stack<int> &indep);

void print() {	
	std::cout << "Piramid 1" << std::endl;
	for (auto it = p1._Get_container().begin(); it != p1._Get_container().end(); it++){
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Piramid 2" << std::endl;
	for (auto it = p2._Get_container().begin(); it != p2._Get_container().end(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Piramid 3" << std::endl;
	for (auto it = p3._Get_container().begin(); it != p3._Get_container().end(); it++) {
		std::cout << *it << std::endl;
	}
}

void add_task(int n) {	
	for (int i = n; i > 0; i--) {
		p1.push(i);
	}
	std::cout << std::endl << "Start" << std::endl;
	print();
	move(n, p1, p3, p2);
	std::cout << std::endl << "End" << std::endl;
	print();
}

void move(int n, std::stack<int> &from, std::stack<int> &to, std::stack<int> &indep) {	
	if (n >= 1) {		
		move(n - 1, from, indep, to);
		if (to.empty() || (!to.empty() && to.top() > from.top())) {
			to.push(from.top());
			from.pop();
		}			
		move(n - 1, indep, to, from);		
	}	
}
