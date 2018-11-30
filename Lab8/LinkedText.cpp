#include "LinkedText.h"
#include <iostream>
#include <fstream>

LinkedText::iterator::iterator(LinkedTextItem* node) {
	this->node = node;
}

LinkedText::iterator LinkedText::iterator::operator++() {
	node = node->next;
	return *this;
}

LinkedText::iterator LinkedText::iterator::operator++(int none) {
	LinkedTextItem* temp = node;
	node = node->next;

	return iterator(temp);
}

LinkedText::iterator LinkedText::iterator::operator+(number offset) {
	LinkedTextItem* current = node;
	while (offset > 0 && current) {
		current = current->next;
		offset--;
	}
	if (offset != 0)
		throw std::invalid_argument("Size overflow)");
	return iterator(current);
}

LinkedText::iterator LinkedText::iterator::operator+=(number offset) {
	return operator+(offset);
}

bool LinkedText::iterator::operator==(iterator iter) {
	return iter.node == this->node;
}

bool LinkedText::iterator::operator!=(iterator iter) {
	return !operator==(iter);
}

std::string& LinkedText::iterator::operator*() {
	return node->line;
}


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
	stream << endItem->line << std::endl;
}

void LinkedText::Load(std::istream& stream) {
	std::string line;
	while(std::getline(stream, line)){
		size_t pos = line.find_first_of("#");
		if (pos < line.size()) {
			if(pos > 0){
				line = line.substr(0, pos);
				AddLine(line);
			}			
			break;
		}
		AddLine(line);
	}
	if (firstItem->next != endItem) {		
		RemoveLine(begin());
	}		
}

void LinkedText::AddLine(std::string line)
{
	LinkedTextItem *add = new LinkedTextItem();
	size_t pos = line.find_first_of('#');
	if (pos < line.size())
		line = line.substr(0, pos);
	add->line = line;
	add->before = endItem->before;
	endItem->before->next = add;
	endItem->before = add;
	add->next = endItem;
}

void LinkedText::CopyLine(iterator what, iterator whereAfter)
{	
	if (!whereAfter.node || !what.node)
		throw std::invalid_argument("Iterator nodes do not exist");
	LinkedTextItem *newItem = new LinkedTextItem();
	newItem->line = *what;
	newItem->next = whereAfter.node->next;
	whereAfter.node->next->before = newItem;
	whereAfter.node->next = newItem;
	newItem->before = whereAfter.node;
}

void LinkedText::RemoveLine(LinkedText::iterator rem)
{	
	if (!rem.node)
		throw std::invalid_argument("Remove elem does not exist");
	rem.node->before->next = rem.node->next;
	rem.node->next->before = rem.node->before;
	if (rem == begin())
		firstItem = firstItem->next;
	delete rem.node;
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
		count = 0;
		for (auto strIt = (*it).begin(); strIt != (*it).end(); ++strIt) {
			if (*strIt == letter) {
				count++;
			}
		}		
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