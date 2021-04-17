#pragma once
#include "../BankData/BankAccount.h"
#include <vector>
#include <map>

using std::vector;
using std::string;
using std::map;

class Person : public BankAccount
{
private:
	string name;
	vector<vector<string>> transactions;
public:
	Person(string name1, vector<vector<string>> trans, int account, int total);
	Person();
	~Person();
	bool operator==(Person const& tmp);
	void AddTransaction(vector<string>& movement) { transactions.push_back(movement); };
	string GetName() { return name; };
	vector<vector<string>> GetTransactions() { return transactions; };
	void Deposit(int value, string date);
	void Withdraw(int value, string date);
};

