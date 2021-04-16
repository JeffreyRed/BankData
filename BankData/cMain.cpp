#include "cMain.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Person.h"
#include <windows.h>
#include <ctime>
#include <wx/datectrl.h>
#include <wx/msgdlg.h>
#include "wx/textctrl.h"


using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::wstring;
using std::stoi;
using std::map;
using std::to_string;
using std::to_wstring;

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(01, OnButtonClicked)
	EVT_BUTTON(02, DepositClicked)
	EVT_BUTTON(03, WithdrawClicked)
	EVT_BUTTON(04, GetStatement)
	EVT_CLOSE(OnClose)
wxEND_EVENT_TABLE()


vector<Person> users;
wstring fileNameAccount = L"accounts.txt";
wstring fileNameTrans = L"transactions.txt";
map<int, int> allAccounts;
map<int, string> userAccounts;

int ConvertToInteger(wstring text) {
	int n = std::stoi(text);//Convert String to Int
	return n;
}

vector<vector<string>> importAccounts(std::wstring fileName2) {
	std::wstring texttemp = fileName2;
	vector<vector<string>> data_file;
	ifstream MyFile(texttemp);
	if (MyFile.fail())
		return data_file;
	//MyFile.open(fileName);
	string temp;
	vector<string> temp2;
	int columns = 0;
	while (MyFile >> temp) {
		columns = 0;
		while (temp != "") {
			temp2.push_back(temp.substr(0, temp.find(",")));
			temp.erase(0, temp.find(",") + 1);
			columns++;
		}
		data_file.push_back(temp2);
		temp2.clear();
	}
	MyFile.close();

	return data_file;
}

void ImportData() {
	vector<vector<string>> data = importAccounts(fileNameAccount);

	if (data.empty())
		return;
	for (vector<string> tmp : data) {
		allAccounts[stoi(tmp[0])] = stoi(tmp[2]);
		userAccounts[stoi(tmp[0])] = tmp[1];
	}
}

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Bank", wxPoint(30, 30), wxSize(600, 600))
{
	
	m_label1 = new wxStaticText(this, wxID_ANY, "Bank Account", wxPoint(10, 10), wxSize(150, 20));
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 35), wxSize(100, 25), wxFILTER_NUMERIC);
	m_btn1 = new wxButton(this, 01, "Sing in", wxPoint(10, 65), wxSize(100, 25));

	m_label2 = new wxStaticText(this, wxID_ANY, "Amount", wxPoint(10, 90), wxSize(150, 20));
	m_txt2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 120), wxSize(100, 25));
	m_btn2 = new wxButton(this, 02, "Deposit", wxPoint(10, 155), wxSize(100, 25));
	m_btn3 = new wxButton(this, 03, "Withdraw", wxPoint(10, 185), wxSize(100, 25));
	
	m_label3 = new wxStaticText(this, wxID_ANY, "Get Statement", wxPoint(180, 10), wxSize(150, 20));
	m_date1 = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxPoint(180, 35), wxSize(150, 20));
	m_date2 = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxPoint(340, 35), wxSize(150, 20));
	m_btn4 = new wxButton(this, 04, "Get Statement", wxPoint(180, 65), wxSize(150, 20));
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(180, 90), wxSize(300, 300));

	m_btn2->Enable(false);
	m_btn3->Enable(false);
	m_btn4->Enable(false);

	ImportData();
	
}

cMain::~cMain() 
{
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	if (m_txt1->IsEmpty()) {
		wxMessageBox(wxT("Please write your bank account"));
		return;
	}
	wstring userAccount = m_txt1->GetValue().ToStdWstring();
	if (allAccounts.find(ConvertToInteger(userAccount)) != allAccounts.end()) {

		string name = userAccounts[ConvertToInteger(userAccount)];
		vector<vector<string>> data = importAccounts(userAccount+ L".txt");
		int account = ConvertToInteger(userAccount);
		int total = allAccounts[ConvertToInteger(userAccount)];
		Person tmp(name, data, account, total);

		if (find(users.begin(), users.end(), tmp) == users.end())
		{
			users.push_back(tmp);
		}
		else { return; }
		wxMessageBox(wxT("Welcome, Now you can make a Deposit/Withdraw or Get Statement"));
	}
	else {
		wxMessageBox(wxT("Your account does not exists"));
		return;
	}

	m_btn2->Enable(true);
	m_btn3->Enable(true);
	m_btn4->Enable(true);
	evt.Skip();
}
wstring ConvertstringTowstring(string text) {
	std::string str = text;
	std::wstring str2(str.length(), L' '); // Make room for characters

	// Copy string to wstring.
	std::copy(str.begin(), str.end(), str2.begin());
	return str2;
}
string ConvertwstringTostring(wstring text)
{
	//std::wstring wide(text);
	std::string str(text.begin(), text.end());
	return str;
}

wstring GetDate() 
{
	wstring date;
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	date = to_wstring(now->tm_year + 1900) + L'/' + to_wstring(now->tm_mon + 1) + L'/' + to_wstring(now->tm_mday);
	return date;
}

void RecordTransaction(wstring fileName, wstring value, int total)
{
	ofstream file(fileName + L".txt", std::ios::app);
	if (file.fail())
		return;
	wstring tmp = ConvertstringTowstring(userAccounts[ConvertToInteger(fileName)]);
	wstring lineToSave = GetDate() + L"," + tmp + L"," + fileName + L"," + value + L"," + std::to_wstring(total) + L",\n";
	file << lineToSave;
	file.close();
}

void cMain::DepositClicked(wxCommandEvent& evt) 
{
	if (m_txt2->IsEmpty() || ConvertToInteger(m_txt2->GetValue().ToStdWstring()) <= 0) {
		wxMessageBox(wxT("Please the deposit should be higher than 0"));
		return;
	}
	wstring userAccount = m_txt1->GetValue().ToStdWstring();
	wstring value = m_txt2->GetValue().ToStdWstring();
	int balance = 0;
	for (int i = 0; i < users.size(); i++) {
		if (users[i].GetBankAccout() == ConvertToInteger(userAccount)) {
			users[i].Deposit(ConvertToInteger(value));
			wxMessageBox(wxT("New Balance: " + std::to_string(users[i].GetBalance())));
			balance = users[i].GetBalance();
			allAccounts[ConvertToInteger(userAccount)] = balance;
			vector<string> temp{ ConvertwstringTostring(GetDate()), users[i].GetName(),ConvertwstringTostring(userAccount),
				ConvertwstringTostring(value), to_string(balance) };
			users[i].AddTransaction(temp);
			RecordTransaction(userAccount, value, balance);
			m_txt2->Clear();
			return;
		}
	}
	
}

void cMain::WithdrawClicked(wxCommandEvent& evt)
{
	if (m_txt2->IsEmpty() || (ConvertToInteger(m_txt2->GetValue().ToStdWstring()) <= 0))
	{
		wxMessageBox(wxT("Please the deposit should be higher than 0"));
		return;
	}
	else if (ConvertToInteger(m_txt2->GetValue().ToStdWstring()) >= allAccounts[ConvertToInteger(m_txt1->GetValue().ToStdWstring())])
	{
		int tmp = allAccounts[ConvertToInteger(m_txt1->GetValue().ToStdWstring())];
		string tmpString = "The withdraw amount should not be higher than yout total balance : $" + to_string(tmp);
		wxMessageBox(tmpString);
		return;
	}
	wstring userAccount = m_txt1->GetValue().ToStdWstring();
	wstring value = m_txt2->GetValue().ToStdWstring();
	int balance = 0;
	for (int i = 0; i < users.size(); i++) {
		if (users[i].GetBankAccout() == ConvertToInteger(userAccount)) {
			users[i].Withdraw(ConvertToInteger(value));
			wxMessageBox(wxT("New Balance: " + std::to_string(users[i].GetBalance())));
			balance = users[i].GetBalance();
			allAccounts[ConvertToInteger(userAccount)] = balance;
			vector<string> temp{ ConvertwstringTostring(GetDate()), users[i].GetName(),ConvertwstringTostring(userAccount),
				ConvertwstringTostring(value), to_string(balance) };
			users[i].AddTransaction(temp);
			RecordTransaction(userAccount, (L"-"+value), balance);
			m_txt2->Clear();
			return;
		}
	}
	
}

void SaveAccountBallance() 
{
	ofstream myFile(fileNameAccount);
	if (myFile.fail())
		return;
	for (auto const& pair : allAccounts) {
		myFile << pair.first << ","<< userAccounts[pair.first] << "," << pair.second << ",\n";
	}
	myFile.close();
}

void SaveUsersTransactions(wstring filename) 
{
	for (int i = 0; i < users.size(); i++)
	{
		ofstream myFile(filename);
		if (myFile.fail())
			return;
		vector<vector<string>> trans = users[i].GetTransactions();
		string tempText = "";
		for (auto data : trans) 
		{
			for (string text : data) {
				tempText = text + ",";
			}
			myFile << tempText << "\n";
		}
		myFile.close();
	}
}

void cMain::OnClose(wxCloseEvent& event)
{
	if (event.CanVeto())
	{
		if (wxMessageBox("Do you want to close the Application",
			"Please confirm", wxICON_QUESTION | wxYES_NO) == wxYES)
		{
			SaveAccountBallance();
			//SaveUsersTransactions(m_txt1->GetValue().ToStdWstring()+L".txt");
		}
		else {
			event.Veto();
			return;		
		}
	}
	Destroy();  // you may also do:  event.Skip();
				// since the default event handler does call Destroy(), too
}

void cMain::GetStatement(wxCommandEvent& evt) {
	wstring userAccount = m_txt1->GetValue().ToStdWstring();
	for (int i = 0; i < users.size(); i++) {
		if (users[i].GetBankAccout() == ConvertToInteger(userAccount)) {
			m_list1->Clear();

			m_list1->Append("date          || amount || balance");
			/*	14 / 01 / 2012 || -500.00 || 2500.00
				13 / 01 / 2012 || 2000.00 || 3000.00
				10 / 01 / 2012 || 1000.00 || 1000.00*/

			vector<vector<string>> trans = users[i].GetTransactions();
			if (trans.empty())
				return;
			string tempText = "";
			for (int i=(trans.size()-1);i>=0;i--)
			{
				auto vect = trans[i];
				tempText = vect[0] + " || " + vect[3] + "      || " + vect[4];
				m_list1->Append(tempText);
			}
			return;
		}
	}
}