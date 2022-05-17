#ifndef __SEARCH__
#define __SEARCH__
#include "RecursionCounter.h"

class Search
{
public:
	// add your code here  
	Search(int size);
	~Search();
	void InitSortedArray();
	int *GetDataArray();
	bool SequentialSearch(int target);
	bool IterativeBinarySearch(int target);
	bool RecursiveBinarySearch(int target);
	int size;
	int* data;
	

private:
	
	bool RecursiveBinarySearchHelper(int lowIndex, int highIndex, int target) const;
	 //add your code here
	
	
};


#endif