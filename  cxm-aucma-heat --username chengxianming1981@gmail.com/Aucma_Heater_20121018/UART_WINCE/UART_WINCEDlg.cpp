// UART_WINCEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UART_WINCE.h"
#include "UART_WINCEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CUART_WINCEDlg 对话框

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


// CUART_WINCEDlg 消息处理程序

BOOL CUART_WINCEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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
	// TODO: 在此添加控件通知处理程序代码
	if (m_oCEUart.GetComOpened())
	{
		m_oCEUart.ClosePort();
	}
	m_oCEUart.m_OnUartRead = OnUartRead;
	if (m_oCEUart.OpenPort(this, 1, 4800, NOPARITY, 8, 1))
	{
		AfxMessageBox(_T("串口打开成功！"));
	}
	else
	{
		AfxMessageBox(_T("串口打开失败！"));
	}
}

void CUART_WINCEDlg::OnBnClickedButtonCloseport()
{
	// TODO: 在此添加控件通知处理程序代码
	m_oCEUart.ClosePort();
}

void CUART_WINCEDlg::OnBnClickedButtonSenddata()
{
	// TODO: 在此添加控件通知处理程序代码
	BYTE buf[10];
	// @@@@@发送数据
	m_oCEUart.WriteSyncPort(buf, 10);
}

// 串口接收数据回调函数
void CALLBACK CUART_WINCEDlg::OnUartRead(void* pFatherPtr, BYTE* pbuf, DWORD dwbufLen)
{
	BYTE* pRecBuf = NULL;
	// 得到父对象指针
	CUART_WINCEDlg* pThis = (CUART_WINCEDlg*)pFatherPtr;
	pRecBuf = new BYTE[dwbufLen];
	CopyMemory(pRecBuf, pbuf, dwbufLen);
	pThis->PostMessage(WM_RECV_UART_DATA, WPARAM(pRecBuf), dwbufLen);
}
// 串口接收数据处理
LRESULT CUART_WINCEDlg::OnRecvUartData(WPARAM wParam, LPARAM lParam)
{
	// 串口接收到的BUF
	CHAR* pBuf = (CHAR*)wParam;
	// 串口接收到的Buf长度
	DWORD dwBufLen = lParam;
	//@@@@ 数据处理
	
	delete[] pBuf;
	pBuf = NULL;
	return 0;
}