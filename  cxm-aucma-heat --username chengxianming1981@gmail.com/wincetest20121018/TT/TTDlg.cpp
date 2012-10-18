// TTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TT.h"
#include "TTDlg.h"
#include <wingdi.h>
//#pragma   comment(lib, "msimg32.lib") 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTTDlg �Ի���

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


// CTTDlg ��Ϣ�������

BOOL CTTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	BLENDFUNCTION bindfun;    
	//����AlphaBind�����һ������  
	bindfun.BlendOp=AC_SRC_OVER;  
	bindfun.BlendFlags=0;  
	bindfun.SourceConstantAlpha=255;  
	bindfun.AlphaFormat=AC_SRC_ALPHA;    
	//��������Ϊ�����,����ʵ����ο���ش���  
	//HDC hmemdc=CreateMemDC(); //�����ڴ��ͼ�豸���  
	//CPng png;  
	//png.Load("1.png");//����pngͼƬ  

	//�ڽ�ColorBitsת��ΪDCǰ���Ƚ�ÿ�����ؽ������������  

	//R=BYTE(MulDiv(R,A,255));  
	//G=BYTE(MulDiv(G,A,255));  
	//B=BYTE(MulDiv(B,A,255));  
	CDC hmemdc, memDC1;
	::AlphaBlend(hmemdc.m_hDC,0,0,260,60,memDC1.m_hDC,0,0,260,60,bindfun);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

