// UART_WINCEDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UART_WINCE.h"
#include "UART_WINCEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CUART_WINCEDlg �Ի���

CUART_WINCEDlg::CUART_WINCEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUART_WINCEDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUART_WINCEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUART_WINCEDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPENPORT, &CUART_WINCEDlg::OnBnClickedButtonOpenport)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEPORT, &CUART_WINCEDlg::OnBnClickedButtonCloseport)
	ON_BN_CLICKED(IDC_BUTTON_SENDDATA, &CUART_WINCEDlg::OnBnClickedButtonSenddata)
	ON_MESSAGE(WM_RECV_UART_DATA, &CUART_WINCEDlg::OnRecvUartData)
END_MESSAGE_MAP()


// CUART_WINCEDlg ��Ϣ�������

BOOL CUART_WINCEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CUART_WINCEDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_UART_WINCE_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_UART_WINCE_DIALOG));
	}
}
#endif


void CUART_WINCEDlg::OnBnClickedButtonOpenport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_oCEUart.GetComOpened())
	{
		m_oCEUart.ClosePort();
	}
	m_oCEUart.m_OnUartRead = OnUartRead;
	if (m_oCEUart.OpenPort(this, 1, 4800, NOPARITY, 8, 1))
	{
		AfxMessageBox(_T("���ڴ򿪳ɹ���"));
	}
	else
	{
		AfxMessageBox(_T("���ڴ�ʧ�ܣ�"));
	}
}

void CUART_WINCEDlg::OnBnClickedButtonCloseport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oCEUart.ClosePort();
}

void CUART_WINCEDlg::OnBnClickedButtonSenddata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BYTE buf[10];
	// @@@@@��������
	m_oCEUart.WriteSyncPort(buf, 10);
}

// ���ڽ������ݻص�����
void CALLBACK CUART_WINCEDlg::OnUartRead(void* pFatherPtr, BYTE* pbuf, DWORD dwbufLen)
{
	BYTE* pRecBuf = NULL;
	// �õ�������ָ��
	CUART_WINCEDlg* pThis = (CUART_WINCEDlg*)pFatherPtr;
	pRecBuf = new BYTE[dwbufLen];
	CopyMemory(pRecBuf, pbuf, dwbufLen);
	pThis->PostMessage(WM_RECV_UART_DATA, WPARAM(pRecBuf), dwbufLen);
}
// ���ڽ������ݴ���
LRESULT CUART_WINCEDlg::OnRecvUartData(WPARAM wParam, LPARAM lParam)
{
	// ���ڽ��յ���BUF
	CHAR* pBuf = (CHAR*)wParam;
	// ���ڽ��յ���Buf����
	DWORD dwBufLen = lParam;
	//@@@@ ���ݴ���
	
	delete[] pBuf;
	pBuf = NULL;
	return 0;
}