#pragma once
#include <string>

typedef unsigned int number;

struct LinkedTextItem {
	LinkedTextItem* before;
	std::string line;
	LinkedTextItem* next;
};

class LinkedText
{
public:
	LinkedText();
	~LinkedText();
	void Save(std::string);
	void Load(std::string);
	void AddLine(std::string);
	void CopyLine(number, number);
	void RemoveLine(number);
	void FindLetter(char, number &, number &);
	number GetLineWithMaxLetterContains(char);
	void ConsolePrint();
	std::string GetName();
	void SetName(std::string);
private:
	LinkedTextItem *firstItem;
	LinkedTextItem *endItem;
};

