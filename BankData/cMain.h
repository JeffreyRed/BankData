#pragma once
#include "wx/wx.h"
//#include "wx/frame.h"
#include <wx/stattext.h>
#include <wx/datectrl.h>
#include "wx/textctrl.h"
#include <wx/dateevt.h>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	wxButton* m_btn1 = nullptr;
	wxButton* m_btn2 = nullptr;
	wxButton* m_btn3 = nullptr;
	wxButton* m_btn4 = nullptr;

	wxTextCtrl* m_txt1 = nullptr;
	wxTextCtrl* m_txt2 = nullptr;

	wxStaticText* m_label1 = nullptr;
	wxStaticText* m_label2 = nullptr;
	wxStaticText* m_label3 = nullptr;

	wxDatePickerCtrl* m_date1 = nullptr;
	wxDatePickerCtrl* m_date2 = nullptr;

	wxListBox* m_list1 = nullptr;

	void OnButtonClicked(wxCommandEvent& evt);
	void DepositClicked(wxCommandEvent& evt);
	void WithdrawClicked(wxCommandEvent& evt);
	void OnClose(wxCloseEvent& event);
	void GetStatement(wxCommandEvent& evt);
	void DateChangeDate1(wxDateEvent& event);
	void DateChangeDate2(wxDateEvent& event);

	wxDECLARE_EVENT_TABLE();
};

