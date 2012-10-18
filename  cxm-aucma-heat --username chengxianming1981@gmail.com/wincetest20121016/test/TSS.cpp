// TSS.cpp : 实现文件
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



// CTSS 消息处理程序



void CTSS::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
// 	HBITMAP hbmp = (HBITMAP) ::LoadImage (
// 		AfxGetResourceHandle (),
// 		MAKEINTRESOURCE(IDB_BITMAP1),
// 		IMAGE_BITMAP,
// 		0, 0, 0);
// 	dc.SelectObject(hbmp);
 
// 	CBitmap BmpBack;                                       // 定义位图变量
// 	BmpBack.LoadBitmap(IDB_BITMAP1);         // 直接加载资源里面的位图 40*20
// 	CDC memDC;                                              // 定义内存设备
// 	memDC.CreateCompatibleDC(&dc);           
// 	CBitmap* pOldbmp = memDC.SelectObject(&BmpBack);              // 把位图选入内存设备
// 	dc.BitBlt(1,                 // 显示位图的X起始坐标
// 		1,                // 显示位图的y起始坐标
// 		32,               // 显示图像的X坐标
// 		32,               // 显示图像的y坐标
// 		&memDC, 
// 		0,               // 从位图的X坐标开始显示图片
// 		0,               // 从位图的y坐标开始显示图片
// 		SRCCOPY);// 显示方式 
// 	memDC.SelectObject(pOldbmp);
// 	pOldbmp->DeleteObject();
// 	memDC.DeleteDC();

//	SetBitmap(hbmp);
}
