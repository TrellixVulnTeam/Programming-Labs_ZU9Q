#include <iostream>
#include "LinkedText.h"

using namespace std;

int main() {
	LinkedText text;
	text.AddLine("Line 1");
	text.AddLine("Line 2");
	text.CopyLine(2, 1);
	text.CopyLine(2, 1);
	text.RemoveLine(3);
	text.SetName("Test text");

	cout << "Text name: " << text.GetName() << endl;
	text.ConsolePrint();

	system("pause");
	return 0;
}