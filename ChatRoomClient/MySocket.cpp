// MySocket.cpp : ʵ���ļ�             
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


// CMySocket ��Ա����
void CMySocket::SetParent(CDialog *pDlg)//����ChatRoomClientDlg���ָ��
{
	m_pDlg = (CChatRoomClientDlg*)pDlg;
	
}


void CMySocket::OnConnect(int nErrorCode)//�����¼�������
{
	((CChatRoomClientDlg*)m_pDlg)->OnConnect();//����ChatRoomClientDlg���е�OnConnect����
}

void CMySocket::OnReceive(int nErrorCode)//�����¼�������
{
	((CChatRoomClientDlg*)m_pDlg)->OnReceive();//����ChatRoomClientDlg���е�OnReceive����
}

void CMySocket::OnClose(int nErrorCode)//�ر��¼�������
{
	((CChatRoomClientDlg*)m_pDlg)->OnClose();//����ChatRoomClientDlg���е�OnClose����
}
