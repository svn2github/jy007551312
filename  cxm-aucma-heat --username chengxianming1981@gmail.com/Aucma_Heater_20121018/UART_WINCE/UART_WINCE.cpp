// UART_WINCE.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "UART_WINCE.h"
#include "UART_WINCEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUART_WINCEApp

BEGIN_MESSAGE_MAP(CUART_WINCEApp, CWinApp)
END_MESSAGE_MAP()


// CUART_WINCEApp ����
CUART_WINCEApp::CUART_WINCEApp()
	: CWinApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CUART_WINCEApp ����
CUART_WINCEApp theApp;

// CUART_WINCEApp ��ʼ��

BOOL CUART_WINCEApp::InitInstance()
{

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CUART_WINCEDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
