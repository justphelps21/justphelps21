/********************************************************************************************
**	Project: Dynamic Sequence
**  Programmer: Justin Phelps
**  Course:		cs2420
**	Section:	003
**	Assignment: 1
**	Date:		August 20, 2018
**
**	I certify that I wrote all code in this project except that which was
**	provided by the instructor.
**
***********************************************************************************************/

/* Milestones
Copy files over from zybooks - DONE
Implement Transaction.cpp - DONE
Implement DynamicArray.cpp - DONE MAYBE NOT
Implement DebitCard.cpp
Move back over to zybooks
*/
#include <iostream>
#include <fstream>
#include <string>

#include "DebitCard.h"
using namespace std;

// the format for the data file is:
// <cmd> data
//
// the recognized commands and their corresponding data are:
// b xxxx.xx	- sets the "Origianl Balance" to the amount xxxx.xx
// d xxxx.xx	- deposits $xxxx.xx into the debit card account
// p ID# date yyyy.yy description - post a "pending" transaction of "ID#" number on "date" with the ammount of yyyy.yy with the "description"
// c ID#		- clear transaction ID#

// used for the static members of Observer (testing)
//ADD BACK IN LATER
//int Observer::numConstructions = 0;
//int Observer::numDestructions = 0;

int main()
{
	// specify the input data file
	char dataFileName[] = "data.txt";

	// I've got the file name, now try to open the file for reading
	ifstream fileData;
	fileData.open(dataFileName, fstream::in);
	if (fileData.good() == false)
	{
		cout << "ERROR: can't open data file: " << dataFileName << endl;

		// wait for the user to press enter to quit
		cout << endl << "Press the [Enter] key to quit...";
		getchar();
		return -1;
	}

	// I've got the data file open.
	// so create the DebitCard
	DebitCard debitCard;

	// read and use the data
	while (fileData.eof() == false)
	{
		char command[256];
		fileData >> command;

		// attempt to perform the specified command
		switch (command[0])
		{
		case 'b':	// sets the balance of the account
		{
			double newAccountBalance = 0.0;
			fileData >> newAccountBalance;
			debitCard.Deposit(newAccountBalance);
			break;
		}


		case 'd':	// deposits funds into the account
		{
			double deposit;
			fileData >> deposit;
			debitCard.Deposit(deposit);
			break;
		}

		case 'p':	// post a pending transaction
		{
			unsigned int idNumber;
			char  date[50];
			string description;

			double amount;
			fileData >> idNumber;
			fileData >> date;
			fileData >> amount;
			getline(fileData, description);

			debitCard.PostTransaction(idNumber, date, description, amount);
			break;
		}

		case 'c':	// the specified transaction has been cleared
		{
			unsigned int transactionID;

			fileData >> transactionID;
			debitCard.ClearTransaction(transactionID);
			break;
		}

		default:
			break;
		}
	}

	fileData.close();

	debitCard.DisplayActivity();

}