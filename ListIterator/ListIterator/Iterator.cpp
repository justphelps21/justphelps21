#include "Node.h"
#include "Iterator.h"

Iterator::Iterator(Node* start)
{
	current = start;
}

const int& Iterator::operator*() const 
{
	return current->data;
}

int& Iterator::operator*() 
{
	return current->data;
}

Iterator& Iterator::operator++() 
{
	current = current->next;
	return *this;
}

bool Iterator::operator!=(const Iterator& other) const 
{
	return (current != other.current);
}

bool Iterator::is_item() const 
{
	return (current != nullptr);
}