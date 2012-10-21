// UART_WINCEDlg.h : 头文件
//
#include "CEUart.h"
#pragma once
#define WM_RECV_UART_DATA	WM_USER + 100
// CUART_WINCEDlg 对话框
class CUART_WINCEDlg : public CDialog
{
// 构造
public:
	CUART_WINCEDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UART_WINCE_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
public:
	CCEUart m_oCEUart;
	// 串口接收数据回调函数
	static void CALLBACK OnUartRead(void* pFatherPtr, BYTE* pbuf, DWORD dwbufLen);
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenport();
	afx_msg void OnBnClickedButtonCloseport();
	afx_msg void OnBnClickedButtonSenddata();
	afx_msg LRESULT OnRecvUartData(WPARAM wParam, LPARAM lParam);
};
