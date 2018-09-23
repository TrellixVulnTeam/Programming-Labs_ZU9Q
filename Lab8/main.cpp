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
	text.Save("text.txt");

	cout << "Text name: " << text.GetName() << endl;
	text.ConsolePrint();

	LinkedText text2;
	text2.Load("text.txt");
	cout << "Text2 name: " << text2.GetName() << endl;
	text2.ConsolePrint();

	system("pause");
	return 0;
}