
// ChatRoomClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoomClient.h"
#include "ChatRoomClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CChatRoomClientDlg �Ի���



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


// CChatRoomClientDlg ��Ϣ�������

BOOL CChatRoomClientDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_socketConnect.Create();//��������socket
	m_socketConnect.SetParent(this);//�ѵ�ǰ�Ի������ָ�����ø�����

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatRoomClientDlg::OnPaint()
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
HCURSOR CChatRoomClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatRoomClientDlg::OnConnect()//���ӳɹ����Զ�����
{
	UpdateData();//�������ݵ�����
	m_recv += CString("Connenct Succeed!\r\n");//
	UpdateData(FALSE);//������ʾ
}
void CChatRoomClientDlg::OnClickedConnectBtn()//���ӷ�������ť��Ӧ����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	char *ipIP = "127.0.0.1";//��������ַ
	m_socketConnect.Connect(ipIP, 10000);//���ӷ�����
}


void CChatRoomClientDlg::OnClickedCancelBtn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void CChatRoomClientDlg::OnClickedSendBtn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();//�������ݵ�����
	int nSendLen = m_socketConnect.Send((void *)m_send.GetBuffer(0),m_send.GetLength());//��ȡ�������ݵĳ���
	if (nSendLen > 0)
	{
		AfxMessageBox("���ͳɹ�!");
	}
	else
	{
		AfxMessageBox("����ʧ��");
	}

}

void  CChatRoomClientDlg::OnReceive()//���պ���
{
	BYTE byBuf[1024] = { 0 };//���ջ�����
	int nRecvLen = 0;//�洢�������ݵĳ���
	nRecvLen = m_socketConnect.Receive(byBuf, sizeof(byBuf));//��ȡ�������ݵĳ���
	CString tmp;//��ʱ����
	if (nRecvLen > 0)
	{
		UpdateData();//�������ݵ�����
		tmp.Format("%s\r\n", byBuf);//��ʽ���ַ���
		m_recv += tmp;
		UpdateData(FALSE);//������ʾ

	}
	else
	{
		AfxMessageBox("����������! ");//������ʾ
	}
}

void CChatRoomClientDlg::OnClose()
{
	m_socketConnect.Close();//�ر�����
}