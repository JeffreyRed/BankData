#include "../BankData/Person.h"
#include <string>

using std::to_string;
using std::vector;
using std::string;

Person::Person(string name1, vector<vector<string>> trans, int account, int total)
	: BankAccount(account, total)
{
	name = name1;
	transactions = trans;
}
Person::Person()
{

}
Person::~Person() {}
bool Person::operator==(Person const& tmp)
{
	return this->GetBankAccout() == tmp.GetBankAccout();
}

int ConvertToInteger(string text) {
	int n = std::stoi(text);//Convert String to Int
	return n;
}

void Person::Deposit(int value, string date) 
{
	this->SetBalance(this->GetBalance() + value);
	vector<string> temp{ date, this->name,to_string(this->GetBankAccout()), to_string(value), to_string(this->GetBalance()) };
	this->AddTransaction(temp);
}

void Person::Withdraw(int value, string date)
{
	this->SetBalance(this->GetBalance() - value);
	vector<string> temp{ date, this->name,to_string(this->GetBankAccout()), to_string(value), to_string(this->GetBalance()) };
	this->AddTransaction(temp);
}


