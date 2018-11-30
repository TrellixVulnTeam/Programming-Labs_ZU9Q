#include "LinkedText.h"
#include <iostream>
#include <fstream>

LinkedText::iterator LinkedText::begin() {
	return iterator(firstItem);
}

LinkedText::iterator LinkedText::end() {
	return iterator(endItem);
}

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

void LinkedText::Write(std::ostream& stream) {
	auto current = firstItem;
	while (current != endItem) {
		stream << current->line << std::endl;
		current = current->next;
	}
}

void LinkedText::Load(std::istream& stream) {
	std::string line;
	while(std::getline(stream, line)){
		size_t pos = line.find_first_of("#");
		if (pos < line.size()) {
			line = line.substr(0, pos);
			AddLine(line);
			break;
		}
		AddLine(line);
	}
}

void LinkedText::AddLine(std::string line)
{
	LinkedTextItem *add = new LinkedTextItem();
	size_t pos = line.find_first_of('#');
	if (pos < line.size)
		line = line.substr(0, pos);
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
	
	for (number i = 1; i < where_after; i++) {
		if (where->next != endItem)
			where = where->next;
		else
			throw "Incorrect where argument";
	}
	
	for (number i = 1; i < from; i++) {
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

void LinkedText::RemoveLine(number rem)
{
	LinkedTextItem* remItem = firstItem->next;			
	
	for (number i = 1; i < rem; i++) {
		if (remItem->next != endItem)
			remItem = remItem->next;
		else
			throw "Incorrect number of remove item";
	}
	
	remItem->before->next = remItem->next;
	remItem->next->before = remItem->before;
	delete remItem;
}

void LinkedText::FindLetter(char letter, number &row, number &column)
{
	LinkedTextItem* temp = firstItem->next;
	number irow = 1;
	bool isFind = false;
	while (temp != endItem && !isFind) {
		number icolumn = 1;
		for (auto it = temp->line.cbegin(); it != temp->line.cend(); it++)
		{			
			if (*it == letter)
			{
				row = irow;
				column = icolumn;
				isFind = true;
				break;
			}
			icolumn++;
		}
		temp = temp->next;
		irow++;
	}
}

LinkedText::iterator LinkedText::GetLineWithMaxLetterContains(char letter)
{	
	LinkedTextItem* temp = firstItem->next;
	number i = 1;
	std::pair<iterator, number> maxPair = std::make_pair(begin(), 0);
	number count;
	for (auto it = begin(); it != end(); ++it) {
		for (auto strIt = (*it).begin(); strIt != (*it).end(); ++strIt) {
			if (*strIt == letter) {
				count++;
			}
		}
		count = 0;
		if (count > maxPair.second) {
			maxPair.first = it;
			maxPair.second = count;
		}
	}
	if (maxPair.second == 0)
		throw std::invalid_argument("Letter does not contains");
	return maxPair.first;
}

std::string LinkedText::GetName()
{
	return firstItem->line;
}

void LinkedText::SetName(std::string name)
{
	firstItem->line = name;
}