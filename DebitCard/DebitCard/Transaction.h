#ifndef __Transaction__
#define __Transaction__

#include <string>
//ADD BACK IN LATER
//#include "Observer.h"

class Transaction
{
public:
	Transaction() = default;
	Transaction(int transactionID, std::string date, std::string description, double amount);

	int idNumber;		// unique identification number of the transaction
	std::string date;	// date of the transaction i.e. "08/17/2018"
	std::string description;	// where was the transaction made
	double amount;		// amount of transaction
	bool cleared;		// has the transaction been "cleared"

	// for unit testing purposes only
	//ADD BACK IN LATER
	//Observer tmp;
};

#endif