// testDlg.h : 头文件
//
#include "TestButton.h"
#include "TSS.h"
#pragma once
#include "afxwin.h"
#include <imaging.h>



// CtestDlg 对话框
class CtestDlg : public CDialog
{
// 构造
public:
	CtestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	CTestButton m_testBut;
	HICON icon2;
	CBrush   m_brush;
	CFont m_FontWinter;
	CFont m_FontSummer;
public:
	IImage *m_pImage;
	bool m_bImage;
	CDC memdc;
	CDC hmemdc;
	IImagingFactory *m_pImageFactory;
	CBitmap bmp;
	CBitmap bmp2;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};
