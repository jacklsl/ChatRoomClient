
// ChatRoomClientDlg.h : 头文件
//

#pragma once
#include "MySocket.h"

// CChatRoomClientDlg 对话框
class CChatRoomClientDlg : public CDialogEx
{
// 构造
public:
	void OnConnect();
	void OnClose();
	void OnReceive();
	CChatRoomClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHATROOMCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
