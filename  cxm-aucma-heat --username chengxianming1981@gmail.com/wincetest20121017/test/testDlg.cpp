// testDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h" 
#include <initguid.h>
#include <imgguids.h>

// #include <wingdi.h>
// #pragma   comment(lib, "msimg32.lib") 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CtestDlg �Ի���


CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtestDlg::IDD, pParent)
	, m_bImage(false)
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


// CtestDlg ��Ϣ�������

BOOL CtestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
// 	int   cx   =   GetSystemMetrics(   SM_CXSCREEN   ); 
// 	int   cy   =   GetSystemMetrics(   SM_CYSCREEN   );
// 	int   nTitleHeight     =   GetSystemMetrics(SM_CYCAPTION);//������ 
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
	m_brush.CreateSolidBrush(RGB(255,   0,   0));   //   ����һ��ɫˢ��
	CFont* pfont;
	LOGFONT   logFont;
	pfont = GetDC()->GetCurrentFont();
	memset(&logFont, 0, sizeof(LOGFONT));
	pfont->GetLogFont(&logFont);
	logFont.lfHeight = logFont.lfHeight * 3;
	VERIFY(m_FontWinter.CreateFontIndirect(&logFont));
	logFont.lfHeight = logFont.lfHeight / 3;
	VERIFY(m_FontSummer.CreateFontIndirect(&logFont));


	CoInitializeEx(NULL ,COINIT_MULTITHREADED);

	if(FAILED(CoCreateInstance(CLSID_ImagingFactory,NULL,CLSCTX_INPROC_SERVER,IID_IImagingFactory ,(void **) &m_pImageFactory)))
	{
		MessageBox(_T("CoCreateInstance Error"));

	}
	ImageInfo oImageInfo;
	if(!SUCCEEDED(m_pImageFactory->CreateImageFromFile(_T("\\Storage Card\\��Դ_1.png"),&m_pImage)))
	{
		MessageBox(_T("CreateImageFromFile Error"));
	}
	m_pImage->GetImageInfo(&oImageInfo);
	//����һ���ڴ�DC,�����洢ͼƬ����
	bmp.CreateCompatibleBitmap(GetDC(), oImageInfo.Width,oImageInfo.Height);
	memdc.CreateCompatibleDC(GetDC());
	memdc.SelectObject(&bmp);
	//��ͼƬ���ݴ洢���ڴ�DC��
	m_pImage->Draw(memdc.m_hDC ,CRect(0,0,oImageInfo.Width,oImageInfo.Height) ,NULL);

	if(!SUCCEEDED(m_pImageFactory->CreateImageFromFile(_T("\\Storage Card\\��Դ_2.png"),&m_pImage)))
	{
		MessageBox(_T("CreateImageFromFile Error"));
	}
	m_pImage->GetImageInfo(&oImageInfo);
	//����һ���ڴ�DC,�����洢ͼƬ����
	bmp2.CreateCompatibleBitmap(GetDC(), oImageInfo.Width,oImageInfo.Height);
	hmemdc.CreateCompatibleDC(GetDC());
	hmemdc.SelectObject(&bmp2);
	//��ͼƬ���ݴ洢���ڴ�DC��
	m_pImage->Draw(hmemdc.m_hDC ,CRect(0,0,oImageInfo.Width,oImageInfo.Height) ,NULL);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return m_brush;
//	return hbr;
}

void CtestDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CBitmap BmpBack1, BmpBack;                                       // ����λͼ����
	BmpBack.LoadBitmap(IDB_BITMAP1);         // ֱ�Ӽ�����Դ�����λͼ 40*20
	BmpBack1.LoadBitmap(IDB_BITMAP2);
	CDC memDC1;                                              // �����ڴ��豸
	memDC1.CreateCompatibleDC(&dc);
	CBitmap* pOldbmp = memDC1.SelectObject(&BmpBack);              // ��λͼѡ���ڴ��豸
	dc.BitBlt(0,                 // Ŀ��λͼ��X��ʼ����
		0,                // Ŀ��λͼ��y��ʼ����
		32,               // ��ʾͼ��Ŀ��
		32,               // ��ʾͼ��ĸ߶�
		&memDC1, 
		0,               // ��Դλͼ��X���꿪ʼ��ʾͼƬ
		0,               // ��Դλͼ��y���꿪ʼ��ʾͼƬ
		SRCCOPY);// ��ʾ��ʽ 
	memDC1.SelectObject(pOldbmp);
	pOldbmp->DeleteObject();
	pOldbmp = memDC1.SelectObject(&BmpBack1);
	dc.BitBlt(40,                 // ��ʾλͼ��X��ʼ����
		40,                // ��ʾλͼ��y��ʼ����
		48,               // ��ʾͼ���X����
		48,               // ��ʾͼ���y����
		&memDC1, 
		0,               // ��λͼ��X���꿪ʼ��ʾͼƬ
		0,               // ��λͼ��y���꿪ʼ��ʾͼƬ
		SRCCOPY);// ��ʾ��ʽ 
	memDC1.SelectObject(pOldbmp);
	pOldbmp->DeleteObject();
	memDC1.DeleteDC();
	dc.SelectObject(&m_FontWinter);
	dc.SetTextColor(0xff0000);
	dc.ExtTextOut(90, 90, ETO_OPAQUE, NULL, _T("TEXT"), NULL);
	dc.SelectObject(&m_FontSummer);
	dc.SetTextColor(0xff00);
	dc.ExtTextOut(120, 120, ETO_OPAQUE, NULL, _T("TEXT"), NULL);
	
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
 
//	AlphaBlend(hmemdc.m_hDC,0,0,260,60,memDC1.m_hDC,0,0,260,60,bindfun);
//	pImage->Draw(dc.m_hDC ,CRect(180,120,244,184) ,NULL);
	dc.BitBlt(180,                 // ��ʾλͼ��X��ʼ����
		120,                // ��ʾλͼ��y��ʼ����
		64,               // ��ʾͼ���X����
		64,               // ��ʾͼ���y����
		&memdc, 
		0,               // ��λͼ��X���꿪ʼ��ʾͼƬ
		0,               // ��λͼ��y���꿪ʼ��ʾͼƬ
		SRCCOPY);// ��ʾ��ʽ 
	dc.BitBlt(244,                 // ��ʾλͼ��X��ʼ����
		120,                // ��ʾλͼ��y��ʼ����
		64,               // ��ʾͼ���X����
		64,               // ��ʾͼ���y����
		&hmemdc, 
		0,               // ��λͼ��X���꿪ʼ��ʾͼƬ
		0,               // ��λͼ��y���꿪ʼ��ʾͼƬ
		SRCCOPY);// ��ʾ��ʽ 
}

void CtestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bImage = !m_bImage;
	InvalidateRect(CRect(180,120,228,168), false);
	CDialog::OnLButtonDown(nFlags, point);
}

void CtestDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	m_brush.DeleteObject();
	m_FontSummer.DeleteObject();
	m_FontWinter.DeleteObject();
	CoUninitialize();
}
