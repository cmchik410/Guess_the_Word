
// Guess_the_WordDlg.h : header file
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <locale>
#include <codecvt>
#include <sstream>
#include <algorithm>
#include <utility>


// CGuesstheWordDlg dialog
class CGuesstheWordDlg : public CDialogEx
{
private:
	std::string answer, optionA, optionB, optionC = "";
	LPCTSTR userName = NULL;
	CString rankName = NULL;
	std::vector<std::string> dict {}, choices {};
	int scores = 5;
	int trial = 0;
	bool gameActive = false;
	std::vector<std::string> used {};

	CFont* font1 = nullptr;
	CStatic* textBox1 = nullptr, * textBox2 = nullptr,
		* textBox3 = nullptr, * textBox4 = nullptr,
		* textBox5 = nullptr, * textBox6 = nullptr,
		* textBox7 = nullptr, * textBox8 = nullptr,
		* textBox9 = nullptr;
	CStatic* editBox1 = nullptr;

// Construction
public:
	CGuesstheWordDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GUESS_THE_WORD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void initializer();
	void updateTop10();
	void genPicture(int, std::string);
	void generator(bool);
	int genChoices();
	int getPicID(std::string);
	bool not_repeated(std::vector<std::string>, const std::string);
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonA();
	afx_msg void OnBnClickedButtonB();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedStaticText6();
};
