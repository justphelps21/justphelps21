#ifndef __ITERATOR__
#define __ITERATOR__
#include "Node.h"

class Iterator {
public:
	Iterator(Node* start);
	const int& operator*() const;
	int& operator*();
	Iterator& operator++();
	bool operator!=(const Iterator& other) const;
	bool is_item() const;

private:
	Node* current;
};

#endif