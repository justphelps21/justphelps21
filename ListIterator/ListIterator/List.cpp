#include <iostream>
#include "Node.h"
#include "Iterator.h"
#include "List.h"

using namespace std;

List::List()
{
	head = nullptr;
	numElements = 0;
}

List::~List() 
{
	while (head != nullptr) {
		Node* temp = head;
		head = head->next;
		delete temp;
		numElements--;
	}
}

Iterator List::begin() const 
{
	return Iterator(head);
}

Iterator List::end() const 
{
	return Iterator(nullptr);
}

void List::push_front(const int& item) 
{
	head = new Node(head, item);
	numElements++;
}

void List::push_back(const int& item) 
{
	Node* newNode = new Node(nullptr, item);

	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* cursor = head;
		while (cursor->next != nullptr)
			cursor = cursor->next;

		cursor->next = newNode;
	}

	numElements++;
}

void List::remove(const int& item) 
{
	Node* previous = nullptr;
	Node* cursor = head;

	while (cursor != nullptr) {
		if (cursor->data == item && previous == nullptr) {
			Node* temp = cursor;
			cursor = cursor->next;
			head = cursor;

			delete temp;
			numElements--;
		}
		else if (cursor->data == item) {
			previous->next = cursor->next;
			delete cursor;
			cursor = previous->next;
			numElements--;
		}
		else {
			previous = cursor;
			cursor = cursor->next;
		}
	}
}

int List::size() const 
{
	return numElements;
}

void List::PrintList() const 
{
	for (const Node* cursor = head; cursor != nullptr; cursor = cursor->next)
		cout << cursor->data << ' ';
	cout << endl;
}