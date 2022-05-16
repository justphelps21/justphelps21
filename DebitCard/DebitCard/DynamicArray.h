#ifndef __DynamicArray__
#define __DynamicArray__

#include "Transaction.h"

class DynamicArray
{
public:
	DynamicArray();
	~DynamicArray();

	void push_back(const Transaction &newTransaction); // adds newTransaction to the end of the dynamic array
	int size() const;	// returns the number of Transactions currently stored in the dynamic array
	int currentCapacity() const; // returns the current capacity of the array
	Transaction& at(int index); // returns a reference to the Transaction stored at the specified index

private:
	Transaction * transactions;	// pointer to the actual array
	int capacity;	// capacity of the array in its current state
	int used;		// number of entries already used in the array

	void Realloc();	// make the current array bigger when the current array is full and push_back() is called

	static const int INITIAL_CAPACITY = 2; // used in the constructor to set the initial size of the array
};

#endif
