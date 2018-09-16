#include <iostream>
#include "Task.h"
#include "ReferenceBook.h"
#include <string>

using namespace std;

int main() {

	cout << endl << "Hard task" << endl;

	ReferenceBook rb;

	string k1_1 = "Oleh Shkalikov";
	string v1_1 = "KB12222608";

	string k1_2 = "Oleh Shkalikov";
	string v1_2 = "PC13525689";

	string k2 = "Oleh Halikov";
	string v2 = "0971864353";

	rb.AddData(k1_1, v1_1);
	rb.AddData(k1_2, v1_2);
	rb.AddData(k2, v2);

	cout << "Reference Book keys" << endl << endl;
	auto keys = rb.GetAllKey();
	for (auto it = keys.cbegin(); it != keys.cend(); it++)
		cout << *it << endl;

	cout << endl << "Value for any Oleh Shkalikov" << endl;
	auto values = rb.GetDataFor("Oleh Shkalikov");
	for (auto it = values.cbegin(); it != values.cend(); it++)
		cout << *it << endl;

	cout << endl << "Value for Oleh Halikov" << endl;
	values = rb.GetDataFor("Oleh Halikov");
	for (auto it = values.cbegin(); it != values.cend(); it++)
		cout << *it << endl;
	
	system("pause");
	return 0;
}