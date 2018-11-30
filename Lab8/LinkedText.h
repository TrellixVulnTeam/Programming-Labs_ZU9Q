#pragma once
#include <string>
#include <istream>
#include <ostream>

typedef unsigned int number;

struct LinkedTextItem {
	LinkedTextItem* before;
	std::string line;
	LinkedTextItem* next;	
};

struct LinkedText
{
public:
	LinkedText();
	~LinkedText();
	void Save(const char*);
	void Write(std::ostream&);
	void Load(const char*);
	void Load(std::istream&);
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

