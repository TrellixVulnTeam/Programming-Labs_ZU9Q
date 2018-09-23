#include "LinkedText.h"
#include <iostream>
#include <fstream>

LinkedText::LinkedText()
{
	firstItem = new LinkedTextItem();
	endItem = new LinkedTextItem();	
	firstItem->before = endItem;
	firstItem->next = endItem;
	endItem->next = firstItem;
	endItem->line = "#";
	endItem->before = firstItem;
}


LinkedText::~LinkedText()
{
	LinkedTextItem *current = firstItem;	
	while (current != endItem) {
		current = current->next;
		delete current->before;
	}	
	delete endItem;
}

void LinkedText::Save(const char* path)
{
	std::ofstream stream(path);
	LinkedTextItem *current = firstItem;
	while (current != endItem) {		
		stream << current->line << "\n";
		current = current->next;
	}
	stream << endItem->line;
	stream.close();
}

void LinkedText::Load(const char* path)
{
	const int max_size = 256;	
	FILE* file;
	fopen_s(&file, path, "r");
	char line[max_size];
	std::string temp;
	while (!feof(file)) {
		fgets(line, max_size, file);
		temp = line;
		size_t l = temp.find_last_of("\n\0");
		temp = temp.substr(0, l);		
		l = temp.find_first_of("#");
		if (l <= temp.size()) {
			temp = temp.substr(0, l);
			AddLine(temp);
			break;
		}		
		AddLine(temp);
	}
	if (firstItem->next != endItem)
	{
		firstItem->line = firstItem->next->line;
		RemoveLine(1);	
	}
	if (endItem->before->line.empty()) {
		auto before_before = endItem->before->before;
		before_before->next = endItem;		
		delete endItem->before;
		endItem->before = before_before;
	}
	fclose(file);
}

void LinkedText::AddLine(std::string line)
{
	LinkedTextItem *add = new LinkedTextItem();
	add->line = line;
	add->before = endItem->before;
	endItem->before->next = add;
	endItem->before = add;
	add->next = endItem;
}

void LinkedText::CopyLine(number where_after, number from)
{
	LinkedTextItem* where = firstItem->next;
	LinkedTextItem* what = firstItem->next;
	try {
		for (int i = 1; i < where_after; i++)
		{
			if (where->next != endItem)
				where = where->next;
			else
				throw "Incorrect where argument";
		}
		for (int i = 1; i < from; i++) {
			if (what->next != endItem)
				what = what->next;
			else
				throw "Incorrect from argument";
		}
		LinkedTextItem *newItem = new LinkedTextItem();
		newItem->line = what->line;
		newItem->next = where->next;
		newItem->next->before = newItem;
		where->next = newItem;
		newItem->before = where;
	}
	catch (const char* er) {
		std::cout << er << std::endl;
	}
}

void LinkedText::RemoveLine(number rem)
{
	LinkedTextItem* remItem = firstItem->next;
	try {
		for (int i = 1; i < rem; i++)
		{
			if (remItem->next != endItem)
				remItem = remItem->next;
			else
				throw "Incorrect number of remove item";
		}
		remItem->before->next = remItem->next;
		remItem->next->before = remItem->before;
		delete remItem;
	}
	catch (const char *er) {
		std::cout << er << std::endl;
	}
}

void LinkedText::FindLetter(char letter, number &, number &)
{
}

number LinkedText::GetLineWithMaxLetterContains(char letter)
{
	return number();
}

void LinkedText::ConsolePrint()
{
	LinkedTextItem *current = firstItem->next;
	while (current != endItem) {
		std::cout << current->line << std::endl;
		current = current->next;
	}
}

std::string LinkedText::GetName()
{
	return firstItem->line;
}

void LinkedText::SetName(std::string name)
{
	firstItem->line = name;
}
