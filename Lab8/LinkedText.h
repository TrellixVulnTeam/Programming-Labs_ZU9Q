#pragma once
#include <string>
#include <istream>
#include <ostream>
#include <iterator>

typedef unsigned int number;

struct LinkedTextItem {
	LinkedTextItem() { before = nullptr; next = nullptr; }
	LinkedTextItem* before;
	std::string line;
	LinkedTextItem* next;	
};

class LinkedText
{
public:
	class iterator
	{
		friend class LinkedText;		//for use private fields for impl Linked Text method
	public:
		//for use STL next, advance and other
		using iterator_category = std::bidirectional_iterator_tag;		
		using value_type = LinkedTextItem;
		using difference_type = ptrdiff_t;
		using pointer = LinkedTextItem*;
		using reference = const LinkedTextItem&;

		iterator();
		iterator(const iterator&);
		iterator(LinkedTextItem*);
		iterator(LinkedTextItem&);		
		iterator& operator=(const iterator&);

		iterator& operator++();			//prefix
		iterator operator++(int none);	//postfix

		iterator& operator--();			//prefix
		iterator operator--(int);		//postfix
		
		bool operator==(const iterator&);
		bool operator!=(const iterator&);
		std::string& operator*();
		std::string* operator->();
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

