
// ChatRoomClientDlg.h : ͷ�ļ�
//

#pragma once
#include "MySocket.h"

// CChatRoomClientDlg �Ի���
class CChatRoomClientDlg : public CDialogEx
{
// ����
public:
	void OnConnect();
	void OnClose();
	void OnReceive();
	CChatRoomClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATROOMCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_recv;
	CString m_send;
private:
	CMySocket m_socketConnect;
public:
	afx_msg void OnClickedConnectBtn();
	afx_msg void OnClickedCancelBtn();
	afx_msg void OnClickedSendBtn();
};
