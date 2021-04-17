#include "../BankData/Person.h"

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

