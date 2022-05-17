#ifndef __LIST__
#define __LIST__

#include "Node.h"
#include "Iterator.h"

class List {
public:
	List();
	~List();
	void push_front(const int& item);
	void push_back(const int& item);
	void remove(const int& item);
	Iterator begin() const;
	Iterator end() const;
	int size() const;
	void PrintList() const;

private:
	Node* head;
	int numElements;
};

#endif