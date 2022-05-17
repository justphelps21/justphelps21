#ifndef __NODE__
#define __NODE__
#include "Observer.h"

class Node {
public:
	Node(Node* next, int data);
	int data;
	Node* next;
};

#endif