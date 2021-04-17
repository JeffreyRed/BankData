#include "pch.h"
#include "CppUnitTest.h"
#include "../BankData/BankAccount.h"
#include "../BankData/Person.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

using std::vector;
using std::string;
using std::map;
using std::ifstream;
using std::ofstream;
using std::wstring;
using std::stoi;
using std::to_string;
using std::to_wstring;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{

	TEST_CLASS(UnitTest1)
	{

	public:
		
		TEST_METHOD(TestName)
		{
			string name = "Jeffrey";
			int account = 19890512;
			int total = 4000;
			int deposit = 300;
			vector<string> temp;
			temp.push_back("2021/4/16");
			temp.push_back(name);
			temp.push_back(to_string(account));
			temp.push_back(to_string(deposit));
			temp.push_back(to_string(total));
			vector<vector<string>> data;
			data.push_back(temp);
			Person jeff(name, data, account, total);
			Assert::AreEqual(name, jeff.GetName());
		}
		TEST_METHOD(TestTotal)
		{
			string name = "Jeffrey";
			int account = 19890512;
			int total = 4000;
			int deposit = 300;
			vector<string> temp;
			temp.push_back("2021/4/16");
			temp.push_back(name);
			temp.push_back(to_string(account));
			temp.push_back(to_string(deposit));
			temp.push_back(to_string(total));
			vector<vector<string>> data;
			data.push_back(temp);
			Person jeff(name, data, account, total);
			Assert::AreNotEqual(1243, jeff.GetBalance());
		}
		TEST_METHOD(TestDeposit)
		{
			string name = "Jeffrey";
			int account = 19890512;
			int total = 4000;
			int deposit = 300;
			vector<string> temp;
			temp.push_back("2021/4/16");
			temp.push_back(name);
			temp.push_back(to_string(account));
			temp.push_back(to_string(deposit));
			temp.push_back(to_string(total));
			vector<vector<string>> data;
			data.push_back(temp);
			Person jeff(name, data, account, total);
			jeff.Deposit(200);
			Assert::AreNotEqual(total, jeff.GetBalance());
		}
	};
}
