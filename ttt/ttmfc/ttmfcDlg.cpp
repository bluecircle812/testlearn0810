
// ttmfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ttmfc.h"
#include "ttmfcDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#include <string>
#include <sstream>
//#include <Winsock2.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
void FAR PASCAL CatchMTimer( WORD IDEvent, WORD uReserved, DWORD dwUser, DWORD dwReserved1, DWORD dwReserve2 )                 //��ý�嶨ʱ��������ʱ����ң��֡
{
	CttmfcDlg  *m_pView = (CttmfcDlg *)dwUser;
	m_pView->step();
}
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
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


// CttmfcDlg �Ի���



CttmfcDlg::CttmfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CttmfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CttmfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CttmfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CttmfcDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CttmfcDlg ��Ϣ�������

BOOL CttmfcDlg::OnInitDialog()
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
	http = new HttpConnect();
	//SetTimer( 1, 100, NULL );
	k=0;
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CttmfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CttmfcDlg::OnPaint()
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
HCURSOR CttmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CttmfcDlg::OnBnClickedButton1()
{
	//SetTimer( 1, 5000, NULL );
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 //request("127.0.0.1", "http://127.0.0.1/zdd", "");
	//HttpConnect *http = new HttpConnect();
   //http->getData("127.0.0.1", "/zadd", "id=ichsdiucbd&pw=123");
	
	//int aaaa=recsss.GetLength();
	//MessageBox(recsss);


    //http->postData("127.0.0.1", "/login","id=liukang&pw=123");




		//TIMECAPS tc;
		//if(timeGetDevCaps(&tc,sizeof(TIMECAPS)) == TIMERR_NOERROR)		//ȡ��ϵͳ�ֱ��ʵ�ȡֵ��Χ������޴����
		//{
		//	wAccuracy = min(max(tc.wPeriodMin,1),tc.wPeriodMax);
		//	//���ö�ʱ���ķֱ���
		//	timeBeginPeriod( wAccuracy );
		//}

		TimerID = timeSetEvent( 10, 1, ( LPTIMECALLBACK ) CatchMTimer, ( DWORD ) this, TIME_PERIODIC );
		
}


//����ʵ��
//int CttmfcDlg:: (char* hostname, char* api, char* parameters)
//{
//    WSADATA WsaData;
//    WSAStartup(0x0101, &WsaData);
//
//
//    //��ʼ��socket
//    struct hostent* host_addr = gethostbyname(hostname);
//    if (host_addr == NULL)
//    {
//        //cout<<"Unable to locate host"<<endl;
//        return -103;
//    }
//
//
//    sockaddr_in sin;
//    sin.sin_family = AF_INET;
//    sin.sin_port = htons((unsigned short)80);
//    sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);
//
// 
//    int sock = socket(AF_INET, SOCK_STREAM, 0);
//    if (sock == -1)
//    {
//        return -100;
//    }
//
//
//    //��������
//    if (connect(sock, (const struct sockaddr *)&sin, sizeof(sockaddr_in) ) == -1)
//    {
//        //cout<<"connect failed"<<endl;
//        return -101;
//    }
//
//
//    //��ʼ��������Ϣ
//    char send_str[2048] = {0};
//
//
//    //ͷ��Ϣ
//    strcat_s(send_str, "POST ");
//    strcat_s(send_str, api);
//    strcat_s(send_str, " HTTP/1.1\r\n");
//    strcat_s(send_str, "Host: ");
//    strcat_s(send_str, hostname);
//    strcat_s(send_str, "\r\n");
//    strcat_s(send_str, "Connection: keep-alive\r\n");
//
//
//    char content_header[100];
//    //sprintf(content_header,"Content-Length: %d\r\n", strlen(parameters));
//
//
//    strcat_s(send_str, content_header);
//    strcat_s(send_str, "Cache-Control: max-age=0\r\n");
//    strcat_s(send_str, "Origin: http://www.hao123.com\r\n");
//    strcat_s(send_str, "User-Agent: Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/15.0.849.0 Safari/535.1\r\n");
//    strcat_s(send_str, "Content-Type: application/x-www-form-urlencoded\r\n");
//    strcat_s(send_str, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n");
//    strcat_s(send_str, "Referer: http://www.hao123.com/\r\n");
//    strcat_s(send_str, "Accept-Encoding: gzip,deflate,sdch\r\n");
//    strcat_s(send_str, "Accept-Language: zh-CN,zh;q=0.8\r\n");
//
//
//    //������Ϣ
//    strcat_s(send_str, "\r\n");
//    strcat_s(send_str, parameters);
//
//
//    if (send(sock, send_str, strlen(send_str),0) == -1)
//    {
//        //cout<<"send failed"<<endl;
//        return -101;
//    }
//
//
//    //��ȡ������Ϣ
//    char recv_str[4096] = {0};
//    if (recv(sock, recv_str, sizeof(recv_str), 0) == -1)
//    {
//        //cout<<"recv failed"<<endl;
//        return -101;
//    }
//
//
//   // cout<<recv_str<<endl;
//
//
//    WSACleanup( );
//
//
//    return 0;
//}

void CttmfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//HttpConnect *http = new HttpConnect();

	std::stringstream streama;
    streama << "id=" << k << "&pw=asdfghj";
	
	http->getData("127.0.0.1", "/zadd", streama.str());
	k++;
	//int aaaa=recsss.GetLength();
	CDialogEx::OnTimer(nIDEvent);
}

void CttmfcDlg::step()
{
	std::stringstream streama;
    streama << "id=" << k << "&pw=asdfghj";
	
	http->getData("127.0.0.1", "/zadd", streama.str());
	k++;
	//int aaaa=recsss.GetLength();

}

