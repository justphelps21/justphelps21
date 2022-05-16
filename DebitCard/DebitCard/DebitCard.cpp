#include <iostream>
#include <iomanip>
#include "DebitCard.h"
using namespace std;

DebitCard::DebitCard()
{
	totalTransactions = 0;
	accountBalance = 0.0;
	totalDeposits = 0.0;
}

DebitCard::~DebitCard()
{

}

double DebitCard::Deposit(double deposit)
{
	accountBalance += deposit;
	totalDeposits += deposit;
	return accountBalance;
	
}

double DebitCard::PostTransaction(int idNumber, std::string date, std::string description, double amount)
{
	Transaction postTransaction(idNumber, date, description, amount);
	transactions.push_back(postTransaction);
	totalTransactions++;
	accountBalance -= amount;
	return accountBalance;
}

bool DebitCard::ClearTransaction(int idNumber)
{
	for (int i = 0; i < transactions.size(); i++)
	{
		if (transactions.at(i).idNumber == idNumber)
		{
			transactions.at(i).cleared = true;
			return true;
		}
	}
	return false;
}

void DebitCard::DisplayActivity()
{
	cout << fixed << setprecision(2);
	cout << "total transactions: " << totalTransactions << endl;
	cout << "total deposits: $" << totalDeposits << endl;
	cout << "account balance: $" << accountBalance << endl;
	cout << "List of cleared transactions:" << endl;
	for (int i = 0; i < transactions.size(); i++)
	{
		if (transactions.at(i).cleared == true)
		{
			cout << transactions.at(i).date << "\t$" << transactions.at(i).amount << "\t" << transactions.at(i).description << endl;

		}
	}
	cout << endl;
	cout << "List of pending transactions:" << endl;
	for (int i = 0; i < transactions.size(); i++)
	{
		if (transactions.at(i).cleared == false)
		{
			cout << transactions.at(i).date << "\t$" << transactions.at(i).amount << "\t" << transactions.at(i).description << endl;

		}
	}
}
