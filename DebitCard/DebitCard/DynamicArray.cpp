#include "DynamicArray.h"

DynamicArray::DynamicArray()
{
	capacity = INITIAL_CAPACITY;
	transactions = new Transaction[capacity];
	used = 0;
}

DynamicArray::~DynamicArray()
{
	delete[] transactions;
}



void DynamicArray::push_back(const Transaction & newTransaction)
{
	if (used >= capacity)
	{
		Realloc();
	}
	transactions[used++] = newTransaction;
}

int DynamicArray::size() const
{
	return used;
}

int DynamicArray::currentCapacity() const
{
	return capacity;
}

Transaction & DynamicArray::at(int index)
{
	return transactions[index];
}

void DynamicArray::Realloc()
{
	capacity *= 2;
	Transaction *tmp = new Transaction[capacity];
	for (int i = 0; i < used; i++)
	{
		tmp[i] = transactions[i];
	}
	delete[] transactions;
	transactions = tmp;
}
