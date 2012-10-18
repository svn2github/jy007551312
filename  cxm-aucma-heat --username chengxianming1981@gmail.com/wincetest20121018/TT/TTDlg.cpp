// TTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TT.h"
#include "TTDlg.h"
#include <wingdi.h>
//#pragma   comment(lib, "msimg32.lib") 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTTDlg 对话框

CTTDlg::CTTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTTDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTTDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CTTDlg 消息处理程序

BOOL CTTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	BLENDFUNCTION bindfun;    
	//设置AlphaBind的最后一个参数  
	bindfun.BlendOp=AC_SRC_OVER;  
	bindfun.BlendFlags=0;  
	bindfun.SourceConstantAlpha=255;  
	bindfun.AlphaFormat=AC_SRC_ALPHA;    
	//以下三行为虚代码,具体实现请参考相关代码  
	//HDC hmemdc=CreateMemDC(); //创建内存绘图设备句柄  
	//CPng png;  
	//png.Load("1.png");//加载png图片  

	//在将ColorBits转换为DC前，先将每个像素进行下面的运算  

	//R=BYTE(MulDiv(R,A,255));  
	//G=BYTE(MulDiv(G,A,255));  
	//B=BYTE(MulDiv(B,A,255));  
	CDC hmemdc, memDC1;
	::AlphaBlend(hmemdc.m_hDC,0,0,260,60,memDC1.m_hDC,0,0,260,60,bindfun);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CTTDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_TT_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_TT_DIALOG));
	}
}
#endif

