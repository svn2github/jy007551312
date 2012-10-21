// UART_WINCEDlg.h : ͷ�ļ�
//
#include "CEUart.h"
#pragma once
#define WM_RECV_UART_DATA	WM_USER + 100
// CUART_WINCEDlg �Ի���
class CUART_WINCEDlg : public CDialog
{
// ����
public:
	CUART_WINCEDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UART_WINCE_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;
public:
	CCEUart m_oCEUart;
	// ���ڽ������ݻص�����
	static void CALLBACK OnUartRead(void* pFatherPtr, BYTE* pbuf, DWORD dwbufLen);
	// ���ɵ���Ϣӳ�亯��
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
