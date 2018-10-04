#include <iostream>
#include "LinkedText.h"

using namespace std;

int main() {
	LinkedText text;
	text.AddLine("Linerg#rgfghgs 1");
	text.ConsolePrint();
	cout << endl;
	text.AddLine("Liine 2");
	text.ConsolePrint();
	cout << endl;
	text.AddLine("Liine 3");
	text.ConsolePrint();
	cout << endl;
	text.CopyLine(2, 1);
	text.ConsolePrint();
	cout << endl;
	text.CopyLine(2, 1);
	text.ConsolePrint();
	cout << endl;
	text.RemoveLine(3);
	text.ConsolePrint();
	cout << endl;
	text.SetName("Test text");	
	text.Save("text.txt");

	cout << "Text name: " << text.GetName() << endl;
	text.ConsolePrint();

	LinkedText text2;
	text2.Load("text.txt");
	cout << "Text2 name: " << text2.GetName() << endl;
	text2.ConsolePrint();

	number i, j = 0;
	text2.FindLetter('Z', i, j);
	cout << "First contains of letter i" << endl << "Row " << i << " Column " << j << endl;
	
	cout << "Row which contains maximum count letter i " << text2.GetLineWithMaxLetterContains('i') << endl;

	system("pause");
	return 0;
}