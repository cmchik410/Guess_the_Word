
// Guess_the_Word.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "Guess_the_Word.h"
#include "Guess_the_WordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGuesstheWordApp

BEGIN_MESSAGE_MAP(CGuesstheWordApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGuesstheWordApp construction

CGuesstheWordApp::CGuesstheWordApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CGuesstheWordApp object

CGuesstheWordApp theApp;


// CGuesstheWordApp initialization

BOOL CGuesstheWordApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CGuesstheWordDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

// Self-Implemented Function
void CGuesstheWordDlg::initializer()
{
	answer = optionA = optionB = optionC = "";
	userName = L"";
	rankName = L"";
	choices.clear();
	used.clear();
	scores = 5;
	trial = 0;
	gameActive = false;

	font1 = new CFont();
	font1->CreatePointFont(150, _T("Arial"), NULL);

	textBox1 = (CStatic*)GetDlgItem(IDC_STATIC_TEXT1);
	textBox1->SetFont(font1);
	textBox1->SetWindowTextW(L"Name: ");

	textBox2 = (CStatic*)GetDlgItem(IDC_STATIC_TEXT2);
	textBox2->SetFont(font1);
	textBox2->SetWindowTextW(L"Scores: ");

	textBox3 = (CStatic*)GetDlgItem(IDC_STATIC_TEXT3);
	textBox3->SetFont(font1);
	textBox3->SetWindowTextW(L"Enter Name:");

	textBox4 = (CStatic*)GetDlgItem(IDC_STATIC_TEXT4);
	textBox4->SetFont(font1);
	textBox4->SetWindowTextW(L"");

	textBox5 = (CStatic*)GetDlgItem(IDC_STATIC_TEXT5);
	textBox5->SetFont(font1);
	textBox5->SetWindowTextW(L"");

	textBox6 = (CStatic*)GetDlgItem(IDC_STATIC_TEXT6);
	textBox6->SetFont(font1);
	textBox6->SetWindowTextW(L"Which one is ");

	textBox7 = (CStatic*)GetDlgItem(IDC_STATIC_TEXT7);
	textBox7->SetFont(font1);
	textBox7->SetWindowTextW(L"");

	textBox8 = (CStatic*)GetDlgItem(IDC_STATIC_TEXT8);
	textBox8->SetFont(font1);
	textBox8->SetWindowTextW(L"Trail: ");

	textBox9 = (CStatic*)GetDlgItem(IDC_STATIC_TEXT9);
	textBox9->SetFont(font1);
	textBox9->SetWindowTextW(L"");

	editBox1 = (CStatic*)GetDlgItem(IDC_EDIT1);

	CStatic* picbox1 = (CStatic*)GetDlgItem(IDC_STATIC_PIC1);
	CStatic* picbox2 = (CStatic*)GetDlgItem(IDC_STATIC_PIC2);
	CStatic* picbox3 = (CStatic*)GetDlgItem(IDC_STATIC_PIC3);
	picbox1->ShowWindow(gameActive);
	picbox2->ShowWindow(gameActive);
	picbox3->ShowWindow(gameActive);
}

void CGuesstheWordDlg::updateTop10()
{
	if (rankName == L"") return;

	CString rcs = rankName;
	std::string newComer = CT2A(rcs);
	newComer = newComer + " " + std::to_string(scores);

	std::vector<std::string> rankers;
	std::vector<int> allScores;
	rankers.push_back(newComer);
	allScores.push_back(scores);

	std::ifstream oldTopList;
	oldTopList.open("result.txt");
	std::string line;
	if (oldTopList.is_open()) {
		while (getline(oldTopList, line)) {
			rankers.push_back(line);
			std::string rk;
			int sc;
			std::stringstream ss;
			ss.str(line);
			ss >> rk >> sc;
			allScores.push_back(sc);
		}
	}
	oldTopList.close();

	std::ofstream newTopList;
	newTopList.open("result.txt");

	int n = rankers.size();

	int i, key, j;
	std::string keyS;
	for (i = 1; i < n; i++)
	{
		key = allScores[i];
		keyS = rankers[i];
		j = i - 1;

		while (j >= 0 && allScores.at(j) < key)
		{
			allScores[j + 1] = allScores[j];
			rankers[j + 1] = rankers[j];
			j = j - 1;
		}
		allScores[j + 1] = key;
		rankers[j + 1] = keyS;
	}

	while (rankers.size() > 10) rankers.pop_back();

	for (auto ost : rankers) {
		newTopList << ost << '\n';
	}

	newTopList.close();
}


bool CGuesstheWordDlg::not_repeated(std::vector<std::string> strs, const std::string target)
{
	for (int i = 0; i < strs.size(); ++i) {
		if (strs.at(i) == target) return false;
	}
	return true;
}

int CGuesstheWordDlg::genChoices()
{
	choices.clear();
	int num = 0;
	while (choices.size() < 3) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> unif(0.0, 55.9);
		num = static_cast<int> (unif(gen));
		if (not_repeated(choices, dict.at(num)))
		{
			choices.push_back(dict.at(num));
		}
	}
	return num;
}


void CGuesstheWordDlg::genPicture(int itemID, std::string filename)
{
	int picID = getPicID(filename);

	CStatic* picbox = (CStatic*)GetDlgItem(itemID);
	picbox->ShowWindow(TRUE);
	CRect rect;
	picbox->GetClientRect(rect);
	CClientDC dc(picbox);
	CImage img1;
	img1.LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(picID));
	CBitmap m_bitmap;
	m_bitmap.Attach(img1.Detach());
	CDC memoryDC;
	memoryDC.CreateCompatibleDC(&dc);
	memoryDC.SelectObject(m_bitmap);
	BITMAP bmp;
	m_bitmap.GetBitmap(&bmp);
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(rect.Width() / 2 - 50, rect.Height() / 2 - 50, 100, 100, &memoryDC,
		0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	return;
}

void CGuesstheWordDlg::generator(bool active)
{
	if (!active) {
		MessageBox(L"You need to start the game!", L"Error", MB_OK);
		return;
	}

	if (scores < 0) {
		scores = 0;
		MessageBox(L"You Lose", L"Game Over", MB_OK);
		updateTop10();
		initializer();
		return;
	}

	if (used.size() == 56) {
		MessageBox(L"Completed!", L"Victor", MB_OK);
		updateTop10();
		initializer();
		return;
	}

	int num = genChoices();
	answer = choices[num % 3];

	while (!not_repeated(used, answer)) {
		num = genChoices();
		answer = choices[num % 3];
	}

	used.push_back(answer);

	optionA = choices.at(0);
	optionB = choices.at(1);
	optionC = choices.at(2);

	genPicture(IDC_STATIC_PIC1, optionA);
	genPicture(IDC_STATIC_PIC2, optionB);
	genPicture(IDC_STATIC_PIC3, optionC);

	std::string strScore = std::to_string(scores);
	std::wstring wstrScore = std::wstring(strScore.begin(), strScore.end());
	textBox5->SetWindowTextW(wstrScore.c_str());

	std::wstring wstrAnswer = std::wstring(answer.begin(), answer.end());
	textBox7->SetWindowTextW(wstrAnswer.c_str());

	std::string strTrial = std::to_string(trial);
	std::wstring wstrTrial = std::wstring(strTrial.begin(), strTrial.end());
	textBox9->SetWindowTextW(wstrTrial.c_str());
}


int CGuesstheWordDlg::getPicID(std::string filename)
{
	if (filename == "abacus") return IDB_BITMAP1;
	else if (filename == "airplane") return IDB_BITMAP2;
	else if (filename == "antenna") return IDB_BITMAP3;
	else if (filename == "apple") return IDB_BITMAP4;
	else if (filename == "badminton") return IDB_BITMAP5;
	else if (filename == "ball") return IDB_BITMAP6;
	else if (filename == "banana") return IDB_BITMAP7;
	else if (filename == "basketball") return IDB_BITMAP8;
	else if (filename == "battery") return IDB_BITMAP9;
	else if (filename == "bear") return IDB_BITMAP10;
	else if (filename == "bicycle") return IDB_BITMAP11;
	else if (filename == "bird") return IDB_BITMAP12;
	else if (filename == "bread") return IDB_BITMAP13;
	else if (filename == "butterfly") return IDB_BITMAP14;
	else if (filename == "car") return IDB_BITMAP15;
	else if (filename == "computer") return IDB_BITMAP16;
	else if (filename == "crab") return IDB_BITMAP17;
	else if (filename == "deer") return IDB_BITMAP18;
	else if (filename == "eagle") return IDB_BITMAP19;
	else if (filename == "egg") return IDB_BITMAP20;
	else if (filename == "elephant") return IDB_BITMAP21;
	else if (filename == "eraser") return IDB_BITMAP22;
	else if (filename == "fish") return IDB_BITMAP23;
	else if (filename == "football") return IDB_BITMAP24;
	else if (filename == "glass") return IDB_BITMAP25;
	else if (filename == "gun") return IDB_BITMAP26;
	else if (filename == "ham") return IDB_BITMAP27;
	else if (filename == "lemon") return IDB_BITMAP28;
	else if (filename == "microphone") return IDB_BITMAP29;
	else if (filename == "missle") return IDB_BITMAP30;
	else if (filename == "monitor") return IDB_BITMAP31;
	else if (filename == "monkey") return IDB_BITMAP32;
	else if (filename == "motorcycle") return IDB_BITMAP33;
	else if (filename == "mountain") return IDB_BITMAP34;
	else if (filename == "newspaper") return IDB_BITMAP35;
	else if (filename == "nutshell") return IDB_BITMAP36;
	else if (filename == "octagon") return IDB_BITMAP37;
	else if (filename == "octopus") return IDB_BITMAP38;
	else if (filename == "orange") return IDB_BITMAP41;
	else if (filename == "owl") return IDB_BITMAP42;
	else if (filename == "pencil") return IDB_BITMAP43;
	else if (filename == "pig") return IDB_BITMAP45;
	else if (filename == "pineapple") return IDB_BITMAP46;
	else if (filename == "plate") return IDB_BITMAP47;
	else if (filename == "policeman") return IDB_BITMAP48;
	else if (filename == "rat") return IDB_BITMAP49;
	else if (filename == "rose") return IDB_BITMAP50;
	else if (filename == "saxophone") return IDB_BITMAP51;
	else if (filename == "spacecraft") return IDB_BITMAP52;
	else if (filename == "stapler") return IDB_BITMAP53;
	else if (filename == "stopwatch") return IDB_BITMAP54;
	else if (filename == "strawberry") return IDB_BITMAP55;
	else if (filename == "television") return IDB_BITMAP56;
	else if (filename == "tortoise") return IDB_BITMAP58;
	else if (filename == "watermelon") return IDB_BITMAP60;
	else if (filename == "zebra") return IDB_BITMAP61;
}

