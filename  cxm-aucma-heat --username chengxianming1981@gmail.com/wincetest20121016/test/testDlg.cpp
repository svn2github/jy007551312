// testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CtestDlg 对话框

CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CtestDlg 消息处理程序

BOOL CtestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
// 	int   cx   =   GetSystemMetrics(   SM_CXSCREEN   ); 
// 	int   cy   =   GetSystemMetrics(   SM_CYSCREEN   );
// 	int   nTitleHeight     =   GetSystemMetrics(SM_CYCAPTION);//工具栏 
	ShowWindow(SW_SHOWMAXIMIZED);

// 	myButton.LoadBitmaps(IDB_BITMAP1,IDB_BITMAP2,0,0);
// 	myButton.SubclassDlgItem(IDC_BUTTON1,this);
// 	myButton.SizeToContent();
	HBITMAP hbmp2 = (HBITMAP) ::LoadImage (
		AfxGetResourceHandle (),
		MAKEINTRESOURCE(IDI_ICON2),
		IMAGE_ICON,
		32, 32, 0);
	HICON hic = AfxGetApp()->LoadIcon(IDI_ICON2);
	GetDlgItem(IDC_STATIC_3)->SetIcon(hic, FALSE);
	GetDlgItem(IDC_STATIC_3)->Invalidate();
	m_brush.CreateSolidBrush(RGB(255,   255,   255));   //   生成一绿色刷子
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CtestDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_TEST_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_TEST_DIALOG));
	}
}
#endif



HBRUSH CtestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brush;
}

void CtestDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CBitmap BmpBack1, BmpBack;                                       // 定义位图变量
	BmpBack.LoadBitmap(IDB_BITMAP1);         // 直接加载资源里面的位图 40*20
	BmpBack1.LoadBitmap(IDB_BITMAP2);
	CDC memDC1;                                              // 定义内存设备
	memDC1.CreateCompatibleDC(&dc);
	CBitmap* pOldbmp = memDC1.SelectObject(&BmpBack);              // 把位图选入内存设备
	dc.BitBlt(0,                 // 目标位图的X起始坐标
		0,                // 目标位图的y起始坐标
		32,               // 显示图像的宽度
		32,               // 显示图像的高度
		&memDC1, 
		0,               // 从源位图的X坐标开始显示图片
		0,               // 从源位图的y坐标开始显示图片
		SRCCOPY);// 显示方式 
	memDC1.SelectObject(pOldbmp);
	pOldbmp->DeleteObject();
	pOldbmp = memDC1.SelectObject(&BmpBack1);
	dc.BitBlt(40,                 // 显示位图的X起始坐标
		40,                // 显示位图的y起始坐标
		48,               // 显示图像的X坐标
		48,               // 显示图像的y坐标
		&memDC1, 
		0,               // 从位图的X坐标开始显示图片
		0,               // 从位图的y坐标开始显示图片
		SRCCOPY);// 显示方式 
	memDC1.SelectObject(pOldbmp);
	pOldbmp->DeleteObject();
	memDC1.DeleteDC();
	CFont* pfont;
	CFont m_FontWinter;
	LOGFONT   logFont;
	pfont = dc.GetCurrentFont();
	memset(&logFont, 0, sizeof(LOGFONT));
	pfont->GetLogFont(&logFont);
	logFont.lfHeight = logFont.lfHeight * 3;
	VERIFY(m_FontWinter.CreateFontIndirect(&logFont));
	dc.SelectObject(&m_FontWinter);
	dc.SetTextColor(0xff0000);
	dc.ExtTextOut(90, 90, ETO_OPAQUE, NULL, _T("TEXT"), NULL);
}

void CtestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonDown(nFlags, point);
}

void CtestDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	m_brush.DeleteObject();
}
