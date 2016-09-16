// MySocket.cpp : 实现文件             
//

#include "stdafx.h"
#include "ChatRoomClient.h"
#include "MySocket.h"
#include "ChatRoomClientDlg.h"

// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket 成员函数
void CMySocket::SetParent(CDialog *pDlg)//设置ChatRoomClientDlg类的指针
{
	m_pDlg = (CChatRoomClientDlg*)pDlg;
	
}


void CMySocket::OnConnect(int nErrorCode)//连接事件处理函数
{
	((CChatRoomClientDlg*)m_pDlg)->OnConnect();//调用ChatRoomClientDlg类中的OnConnect函数
}

void CMySocket::OnReceive(int nErrorCode)//接收事件处理函数
{
	((CChatRoomClientDlg*)m_pDlg)->OnReceive();//调用ChatRoomClientDlg类中的OnReceive函数
}

void CMySocket::OnClose(int nErrorCode)//关闭事件处理函数
{
	((CChatRoomClientDlg*)m_pDlg)->OnClose();//调用ChatRoomClientDlg类中的OnClose函数
}
