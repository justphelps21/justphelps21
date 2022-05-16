#include "Transaction.h"

Transaction::Transaction(int transactionID, std::string date, std::string description, double amount)
{
	idNumber = transactionID;
	this->date = date;
	this->description = description;
	this->amount = amount;
	this->cleared = false;
}
