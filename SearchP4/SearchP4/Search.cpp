#include <iostream>
#include <random>
#include "Search.h"

using namespace std;

bool Search::SequentialSearch(int target)
{
	for (int i = 0; i < size; i++)
	{
		if (data[i] == target)
		{
			return true;
		}
	}

	return false;
}

bool Search::IterativeBinarySearch(int target)
{
	int lowIndex = 0;
	int highIndex = size - 1;
	

	while (lowIndex <= highIndex)
	{
		int midIndex = (lowIndex + highIndex) / 2;
		if (target == data[midIndex])
		{
			return true;
		}
		if (data[midIndex] < target)
		{
			lowIndex = midIndex + 1;
		}

		else if (data[midIndex] > target)
		{
			highIndex = midIndex - 1;
		}
	}

	return false;
	
}


bool Search::RecursiveBinarySearch(int target)
{
	return RecursiveBinarySearchHelper(0, (size - 1), target);
}

bool Search::RecursiveBinarySearchHelper(int lowIndex, int highIndex, int target) const
{
	RecursionCounter rcTmp;	// used for unit testing DO NOT REMOVE
   // add more code here...
	int midIndex = (lowIndex + highIndex) / 2;
	if (target == data[midIndex])
	{
		return true;
	}

	if (lowIndex > highIndex)
		return false;

	if (data[midIndex] < target)
	{
		lowIndex = midIndex + 1;
		return RecursiveBinarySearchHelper(lowIndex, highIndex, target);
	}

	else if (data[midIndex] > target)
	{
		highIndex = midIndex - 1;
		return RecursiveBinarySearchHelper(lowIndex, highIndex, target);
	}

}


Search::Search(int size)
{
	data = new int[size];
	this->size = size;
}

Search::~Search()
{
	delete[] data;
}

void Search::InitSortedArray()
{
	cout << "Creating a sorted array of "<< size << endl;
	srand(0);
	data[0] = rand() % 5;
	for (int i = 1; i < size; i++)
	{
		data[i] = data[i - 1] + rand() % 10;
	}
	cout << "Finished creating array" << endl;
}

int * Search::GetDataArray()
{
	return data;
}
