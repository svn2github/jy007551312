// TSS.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test.h"
#include "TSS.h"


// CTSS

IMPLEMENT_DYNAMIC(CTSS, CStatic)

CTSS::CTSS()
{

}

CTSS::~CTSS()
{
}


BEGIN_MESSAGE_MAP(CTSS, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CTSS ��Ϣ�������



void CTSS::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
// 	HBITMAP hbmp = (HBITMAP) ::LoadImage (
// 		AfxGetResourceHandle (),
// 		MAKEINTRESOURCE(IDB_BITMAP1),
// 		IMAGE_BITMAP,
// 		0, 0, 0);
// 	dc.SelectObject(hbmp);
 
// 	CBitmap BmpBack;                                       // ����λͼ����
// 	BmpBack.LoadBitmap(IDB_BITMAP1);         // ֱ�Ӽ�����Դ�����λͼ 40*20
// 	CDC memDC;                                              // �����ڴ��豸
// 	memDC.CreateCompatibleDC(&dc);           
// 	CBitmap* pOldbmp = memDC.SelectObject(&BmpBack);              // ��λͼѡ���ڴ��豸
// 	dc.BitBlt(1,                 // ��ʾλͼ��X��ʼ����
// 		1,                // ��ʾλͼ��y��ʼ����
// 		32,               // ��ʾͼ���X����
// 		32,               // ��ʾͼ���y����
// 		&memDC, 
// 		0,               // ��λͼ��X���꿪ʼ��ʾͼƬ
// 		0,               // ��λͼ��y���꿪ʼ��ʾͼƬ
// 		SRCCOPY);// ��ʾ��ʽ 
// 	memDC.SelectObject(pOldbmp);
// 	pOldbmp->DeleteObject();
// 	memDC.DeleteDC();

//	SetBitmap(hbmp);
}
