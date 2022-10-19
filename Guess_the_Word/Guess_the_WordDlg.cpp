
// Guess_the_WordDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Guess_the_Word.h"
#include "Guess_the_WordDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGuesstheWordDlg dialog



CGuesstheWordDlg::CGuesstheWordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GUESS_THE_WORD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGuesstheWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGuesstheWordDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON_OK, &CGuesstheWordDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CGuesstheWordDlg::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_A, &CGuesstheWordDlg::OnBnClickedButtonA)
	ON_BN_CLICKED(IDC_BUTTON_B, &CGuesstheWordDlg::OnBnClickedButtonB)
	ON_BN_CLICKED(IDC_BUTTON_C, &CGuesstheWordDlg::OnBnClickedButtonC)
	ON_BN_CLICKED(IDC_BUTTON1, &CGuesstheWordDlg::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_STATIC_TEXT6, &CGuesstheWordDlg::OnStnClickedStaticText6)
END_MESSAGE_MAP()


// CGuesstheWordDlg message handlers

BOOL CGuesstheWordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	std::ifstream tempFile("list.txt");

	std::string word;

	if (tempFile.is_open())
	{
		while (tempFile >> word)
		{
			dict.push_back(word);
		}
	}
	tempFile.close();

	initializer();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGuesstheWordDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGuesstheWordDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGuesstheWordDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGuesstheWordDlg::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	if (gameActive) {
		updateTop10();
		initializer();
		return;
	}

	gameActive = true;

	CString inputName = NULL;
	editBox1->GetWindowTextW(inputName);
	editBox1->SetWindowTextW(L"");
	if (inputName == "" || inputName[0] == ' ') {
		MessageBox(L"Please enter your name before you start", L"Error", MB_OK);
		return;
	}

	rankName = inputName;
	userName = inputName;

	textBox4->SetWindowTextW(userName);

	CStatic* picbox1 = (CStatic*)GetDlgItem(IDC_STATIC_PIC1);
	CStatic* picbox2 = (CStatic*)GetDlgItem(IDC_STATIC_PIC2);
	CStatic* picbox3 = (CStatic*)GetDlgItem(IDC_STATIC_PIC3);
	picbox1->ShowWindow(gameActive);
	picbox2->ShowWindow(gameActive);
	picbox3->ShowWindow(gameActive);

	++trial;
	generator(gameActive);
}


void CGuesstheWordDlg::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	int bye = MessageBox(L"Are you going to leave?", L"Exit", MB_YESNO | MB_ICONQUESTION);

	switch (bye) {
	case IDYES:
		updateTop10();
		initializer();
		exit(0);
		break;
	case IDNO:
	default:
		break;
	}

}

void CGuesstheWordDlg::OnBnClickedButtonA()
{
	// TODO: Add your control notification handler code here
	++trial;
	scores += (answer == optionA) ? (int)answer.size() : -1;
	generator(gameActive);
}


void CGuesstheWordDlg::OnBnClickedButtonB()
{
	// TODO: Add your control notification handler code here
	++trial;
	scores += (answer == optionB) ? (int)answer.size() : -1;
	generator(gameActive);
}


void CGuesstheWordDlg::OnBnClickedButtonC()
{
	// TODO: Add your control notification handler code here
	++trial;
	scores += (answer == optionC) ? (int)answer.size() : -1;
	generator(gameActive);
}


void CGuesstheWordDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	std::ifstream topList("result.txt");
	std::string displayer = "";
	std::string r = "";
	if (topList.is_open()) {
		while (getline(topList, r)) {
			if (!r.empty()) {
				displayer += (r + '\n');
			}
		}
	}
	topList.close();

	std::wstring wdisp = std::wstring(displayer.begin(), displayer.end());

	MessageBox(wdisp.c_str(), L"Top 10");
}


void CGuesstheWordDlg::OnStnClickedStaticText6()
{
	// TODO: Add your control notification handler code here
}
