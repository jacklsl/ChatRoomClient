
// ChatRoomClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoomClient.h"
#include "ChatRoomClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CChatRoomClientDlg 对话框



CChatRoomClientDlg::CChatRoomClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatRoomClientDlg::IDD, pParent)
	, m_recv(_T(""))
	, m_send(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatRoomClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RECV_EDIT, m_recv);
	DDX_Text(pDX, IDC_SEND_EDIT, m_send);
}

BEGIN_MESSAGE_MAP(CChatRoomClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CChatRoomClientDlg::OnClickedConnectBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CChatRoomClientDlg::OnClickedCancelBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CChatRoomClientDlg::OnClickedSendBtn)
END_MESSAGE_MAP()


// CChatRoomClientDlg 消息处理程序

BOOL CChatRoomClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_socketConnect.Create();//创建连接socket
	m_socketConnect.SetParent(this);//把当前对话框类的指针设置给对象

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatRoomClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatRoomClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatRoomClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatRoomClientDlg::OnConnect()//连接成功后，自动调用
{
	UpdateData();//更新数据到变量
	m_recv += CString("Connenct Succeed!\r\n");//
	UpdateData(FALSE);//更新显示
}
void CChatRoomClientDlg::OnClickedConnectBtn()//连接服务器按钮响应函数
{
	// TODO:  在此添加控件通知处理程序代码
	char *ipIP = "127.0.0.1";//服务器地址
	m_socketConnect.Connect(ipIP, 10000);//连接服务器
}


void CChatRoomClientDlg::OnClickedCancelBtn()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CChatRoomClientDlg::OnClickedSendBtn()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();//更新数据到变量
	int nSendLen = m_socketConnect.Send((void *)m_send.GetBuffer(0),m_send.GetLength());//获取发送数据的长度
	if (nSendLen > 0)
	{
		AfxMessageBox("发送成功!");
	}
	else
	{
		AfxMessageBox("发送失败");
	}

}

void  CChatRoomClientDlg::OnReceive()//接收函数
{
	BYTE byBuf[1024] = { 0 };//接收缓冲区
	int nRecvLen = 0;//存储接收数据的长度
	nRecvLen = m_socketConnect.Receive(byBuf, sizeof(byBuf));//获取接收数据的长度
	CString tmp;//临时变量
	if (nRecvLen > 0)
	{
		UpdateData();//更新数据到变量
		tmp.Format("%s\r\n", byBuf);//格式化字符串
		m_recv += tmp;
		UpdateData(FALSE);//更新显示

	}
	else
	{
		AfxMessageBox("数据有问题! ");//错误提示
	}
}

void CChatRoomClientDlg::OnClose()
{
	m_socketConnect.Close();//关闭连接
}