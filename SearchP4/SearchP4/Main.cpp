/********************************************************************************************
**	Project: Search Project
**  Programmer: Justin Phelps
**  Course:		cs2420
**	Section:	001
**	Assignment: 4
**	Date:		Sept 17, 2019
**
**	I certify that I wrote all code in this project except that which was
**	provided by the instructor.
**
***********************************************************************************************/

#include <iostream>
#include <random>
#include "Search.h"
#include "RecursionCounter.h"
#include "Timer.h"

using namespace std;

// used for Recursion Unit Testing. DO NOT REMOVE
int RecursionCounter::currentDepth = 0;
int RecursionCounter::maxDepth = 0;

// add code here
int main()
{
	const int ARRAYSIZE = 1000000;
	Timer ti;
	Search s1(ARRAYSIZE);
	s1.InitSortedArray();

	cout << "Searching for number at start of array" << endl;
	ti.Start();
	s1.SequentialSearch(s1.data[0]);
	ti.End();
	cout << "Sequential Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;

	ti.Start();
	s1.IterativeBinarySearch(s1.data[0]);
	ti.End();
	cout << "Iterative Binary Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;

	ti.Start();
	s1.RecursiveBinarySearch(s1.data[0]);
	ti.End();
	cout << "Recursive Binary Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;

	cout << "Searching for number at middle of array" << endl;
	ti.Start();
	s1.SequentialSearch(s1.data[ARRAYSIZE / 2]);
	ti.End();
	cout << "Sequential Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;

	ti.Start();
	s1.IterativeBinarySearch(s1.data[ARRAYSIZE / 2]);
	ti.End();
	cout << "Iterative Binary Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;

	ti.Start();
	s1.RecursiveBinarySearch(s1.data[ARRAYSIZE / 2]);
	ti.End();
	cout << "Recursive Binary Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;


	cout << "Searching for number at end of array" << endl;
	ti.Start();
	s1.SequentialSearch(s1.data[ARRAYSIZE - 1]);
	ti.End();
	cout << "Sequential Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;

	ti.Start();
	s1.IterativeBinarySearch(s1.data[ARRAYSIZE - 1]);
	ti.End();
	cout << "Iterative Binary Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;

	ti.Start();
	s1.RecursiveBinarySearch(s1.data[ARRAYSIZE - 1]);
	ti.End();
	cout << "Recursive Binary Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;


	cout << "Searching for number not in array" << endl;
	ti.Start();
	s1.SequentialSearch(-1);
	ti.End();
	cout << "Sequential Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;

	ti.Start();
	s1.IterativeBinarySearch(-1);
	ti.End();
	cout << "Iterative Binary Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;

	ti.Start();
	s1.RecursiveBinarySearch(-1);
	ti.End();
	cout << "Recursive Binary Search returned in " << ti.DurationInNanoSeconds() << "ns" << endl;



	return 0;
}

