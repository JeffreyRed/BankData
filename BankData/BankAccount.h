#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;

class BankAccount
{
private:
	int bankAccount;
	int balance;
public:
	BankAccount(int account, int total);
	BankAccount();
	virtual ~BankAccount();
	int GetBankAccout() const { return bankAccount; };
	int GetBalance() { return balance; };
	void Deposit(int value) { balance = balance + value; };
	void Withdraw(int value) { balance = balance - value; };
};

