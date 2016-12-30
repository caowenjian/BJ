
// TestCaseDlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestCaseDlg.h"
#include "TestCaseDlgDlg.h"
#include "afxdialogex.h"
#include "../utility/APISrcCoding.h"
#include "../utility/APIDateTime.h"
#include "../utility/APIDirectoryFile.h"
#include "../network/APINetwork.h"
#include "../network/HttpClient.h"
#include "../network/HttpRequestInfo.h"
#include "../network/HttpResponseInfo.h"
#include "../utility/APIOther.h"
#include "../utility/IModuleSubjectBase.h"
#include "../utility/IEventManager.h"
#include "../utility/IThreadManager.h"
#include "../utility/Exception.h"
/*#include "../utilityLibrary/ISocketManager.h"*/
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������Con
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestCaseDlgDlg �Ի���



CTestCaseDlgDlg::CTestCaseDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestCaseDlgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCaseDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestCaseDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestCaseDlgDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestCaseDlgDlg ��Ϣ�������
UINT64 g_1, g_2;

BOOL CTestCaseDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	utility::GetThreadManagerInstance().Startup();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//BOOL T = utility::GetEventManagerInstance().Startup();
// 	g_1 = utility::GetEventManagerInstance().AsynFireUIEventWithTimerLambda(
// 		[=](){
// 		//Sleep(5000);
// 		int i = 0;
// 		i++;
// 	}, 5);
// 	g_2 = utility::GetEventManagerInstance().AsynFireUIEventWithTimerLambda(
// 		[=](){
// 		//Sleep(5000);
// 		int i = 0;
// 		i++;
// 	}, 5);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestCaseDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestCaseDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestCaseDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


class CFather
{
public:

	CFather()
	{
		int* i = (int*)(*(int**)this);
		this->ADD();
	}
	virtual INT32 ADD(){ return 10; }
};

class CChild : public CFather
{
public:
	CChild()
	{
		int* i = (int*)(*(int**)this);
		this->ADD();
	}
	

	virtual INT32 ADD(){ return 20; }
};

INT32 Fun()
{
	return 20;
}
const TCHAR * StringError(DWORD ulErrorNumber)
{
	int iStringLength;
	__declspec(thread) static TCHAR szErrorString[1024];//�����Ϣ�ַ������ֲ߳̾��ڴ�
	__declspec(thread) static HMODULE hNetmsgModule = NULL;
	__declspec(thread) static HMODULE hWininetModule = NULL;

// 	if ((ulErrorNumber >= NERR_BASE) && (ulErrorNumber <= MAX_NERR))//�����lmerr.h��netmsg.dllģ������Ĵ�����
// 	{
// 		if (hNetmsgModule == NULL)
// 		{
// 			hNetmsgModule = LoadLibraryEx(TEXT("netmsg.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE);
// 
// 			if (hNetmsgModule == NULL)
// 			{
// 				return NULL;
// 			}
// 		}
// 
// 		iStringLength = FormatMessage(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS, hNetmsgModule, ulErrorNumber, 0, szErrorString, sizeof(szErrorString), NULL);
//  	}
// 	else if ((ulErrorNumber >= INTERNET_ERROR_BASE) && (ulErrorNumber <= INTERNET_ERROR_LAST))//�����wininet.h��wininet.dllģ������Ĵ�����
// 	{
 		if (hWininetModule == NULL)
 		{
			hWininetModule = LoadLibraryEx(TEXT("wininet.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE);

			if (hWininetModule == NULL)
			{
				return NULL;
			}
		}

		iStringLength = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, ulErrorNumber, 0, szErrorString, sizeof(szErrorString), NULL);
// 	}
// 	else//���������ϵͳ�Ĵ�����
// 		iStringLength = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, ulErrorNumber, 0, szErrorString, sizeof(szErrorString), NULL);
// 
		if (iStringLength > 0)//����ɹ���ȡ��������Ϣ�ַ�����ȥ���ַ���ĩβ�ġ�\r\n��
		{
			if (szErrorString[iStringLength - 2] == '\r')
			{
				if (szErrorString[iStringLength - 1] == '\n')
				{
					iStringLength -= 2;
				}
				else
				{
					iStringLength--;
				}

				szErrorString[iStringLength] = '\0';
			}

			return szErrorString;
		}
		else
		{
			return NULL;
 	}
 }
#include <map>
utility::IModuleSubjectBase* g_pImp = NULL;
class CMyText
{
public:
	CMyText()
	{
		g_pImp = new utility::IModuleSubjectBase();
		g_pImp->AddObserver(this, BIND_CALLBACK_2(CMyText::CallFUN));
	}
public:
	VOID CallFUN(std::string strKeyID, MKO_TUPLE_PARAM tParam)
	{
		if (strKeyID == "123")
		{
			int i = 0;
			i++;
		}
		return;
	}
};

int* g_n = NULL;

VOID Fun1()
{
	MSG msg;

	while (GetMessage(&msg, 0, 0, 0))

	{

		if (msg.message == WM_TIMER)

		{

			MessageBox(NULL, L"Hi", L"Worker Thread", MB_OK);

		}

		DispatchMessage(&msg);

	}
 	g_n = new int;
// 	utility::GetEventManagerInstance().Startup();
// 	while (1)
// 	{
// 
// 	}
}

class CA
{
public:
	int a;
};
void CTestCaseDlgDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


	
/*
	BOOL ba = utility::IsIncludeChinese("a�й�a");
 	std::wstring ss = _T("a�й�");
	int xx = ss.length();
 	std::string str = utility::WStringToString(ss,CP_ACP);

 	CString sss = utility::StringToCString(str,CP_ACP);

	utility::InitException();

	

	std::map<int,int> mm;
	mm[10] = 5;
	mm[11] = 6;
	mm[12] = 4;
	mm[13] = 7;
	mm.erase(100);*/
// 	CString ssAP = utility::GetAppPath();
// 	CString strsize = utility::ByteSizeToString(1234000000);
	CChild *cc = new CChild;
	int i = 0;
	i = network::InitWinSocket();
// 	sockaddr_in in;
// 	network::GetAddrStruct("dispatch.e-faxin.com", 8080, &in);
// 
// 
// 	SOCKET m_socket = socket(AF_INET, SOCK_STREAM, 0);
// 	BOOL nodelay = 0;
// 	int nL = 4;
// 	nL = getsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&nodelay, &nL);
// 	
// 	int ret = false;
// 	while (!ret)
// 	{
// 		sockaddr_in serv_addr;
// 		network::GetAddrStruct("127.0.0.1", 8080, &serv_addr);
// 		network::SetSocketReuse(m_socket, TRUE);
// 		ret = ::bind(m_socket, (sockaddr*)&serv_addr, sizeof(serv_addr));
// 		SOCKET m_socket1 = socket(AF_INET, SOCK_STREAM, 0);
// 		network::SetSocketReuse(m_socket1, TRUE);
// 		ret = ::bind(m_socket1, (sockaddr*)&serv_addr, sizeof(serv_addr));
// 	}
// 	std::map<std::string, int> map1;
// 	map1["123"] = 5;
// 	map1["1234"] = 6;
// 	map1.erase("123");
// 	map1.erase("123");
// 	//SOCKET s1 = network::Listen("127.0.0.1", 8081);
// 	SOCKET s1 = network::Connect("121.201.36.78", 8080);
// 	//SOCKET s1 = network::Connect("192.168.1.31", 5858);
// 	CString ssurl = _T("http://121.201.36.78:8080/msg_server");
// 	CString strHost;
// 	UINT16 strPort;
// 	CString strObject;
// 	network::URLParse(ssurl, strHost, strPort, strObject);
// 	CString s = utility::GetLastErrorString();
// 	utility::GetThreadManagerInstance().StartOperationWithLambda(
// 		[=](){
// 		int i = 0;
// 		i++;
// 	});
// 	CMyText *p = new CMyText();
// 	utility::IModuleSubjectBase* pImp = new utility::IModuleSubjectBase();
// 	std::string ss = "123";
// 	g_pImp->AsynNotifyObserver("123", ss);
// 	utility::GetEventManagerInstance().KillTimerLambda(g_1);
// 	int g = 0;
// 	CString strURL = _T("http://dispatch.e-faxin.com:8080/msg_server");
// 	strURL = _T("http://121.201.36.78:8080/msg_server");
// 	//strURL = _T("http://121.201.36.80:29090///fabao-file/file/upload");
// 	network::CHttpRequestInfo requestInfo(strURL, network::E_HTTP_REQUEST_METHOD_GET);
// 	network::CHttpResponseInfo responseInfo;
// 	network::CHttpClient client;
// 	client.SendRequestInfo(&requestInfo, &responseInfo);
	DWORD dwThreadID = 0;
	HANDLE h = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Fun1, NULL, 0, &dwThreadID);
	Sleep(3000);
	BOOL b =::PostThreadMessage(dwThreadID, WM_TIMER, 0, 0);
	CString s = utility::GetLastErrorString();
// 	WaitForSingleObject(h, INFINITE);
// 
// 	delete g_n;
// 
// 	utility::CLock lock;
// 	for (int i = 0; i < 100; i++)
// 	{
// 		utility::CAutoLock autoLock(&lock);
// 		int g = 0;
// 
// 	}
// 	return;
}


LRESULT CTestCaseDlgDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  �ڴ����ר�ô����/����û���
	switch (message)
	{
	case WM_TIMER:
	{
		int i = 0;
		int g = 0;
		break;
	}
	default:
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}
