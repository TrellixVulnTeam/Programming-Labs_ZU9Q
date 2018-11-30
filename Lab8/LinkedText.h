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
	class iterator {
		friend class LinkedText;
	public:
		iterator(LinkedTextItem*);
		iterator operator++(); //prefix
		iterator operator++(int none); //postfix
		iterator operator+(number);
		iterator operator+=(number);
		bool operator==(iterator);
		bool operator!=(iterator);
		std::string& operator*();
	private:
		LinkedTextItem* node;
	};

	iterator begin();
	iterator end();

	LinkedText();
	~LinkedText();
	
	void Write(std::ostream&);
	void Load(std::istream&);
	
	void AddLine(std::string);
	void CopyLine(iterator, iterator);
	void RemoveLine(iterator);
	
	void FindLetter(char, number &, number &);
	iterator GetLineWithMaxLetterContains(char);
		
	std::string GetName();
	void SetName(std::string);
private:
	LinkedTextItem *firstItem;
	LinkedTextItem *endItem;
};

