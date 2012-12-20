#include "StdAfx.h"
#include "PngImage.h"
#include <initguid.h>
#include <imgguids.h>
#include <wingdi.h>
CPngImage::CPngImage(void)
{
	m_pImagingFactory = NULL;
	m_pImage = NULL;
	m_pImgDataBuf = NULL;
}

CPngImage::~CPngImage(void)
{
}
// 初始化IImage COM组件
void CPngImage::InitIImage()
{
	// 初始化COM环境
	if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		AfxMessageBox(_T("CoInitializeEx Error!"));
		return;
	}
	if (FAILED(CoCreateInstance(CLSID_ImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IImagingFactory, (void **)&m_pImagingFactory)))
	{
		AfxMessageBox(_T("CoCreateInstance Error!"));
		ReleaseIImage();
		return;
	}
}
// 释放IImage COM组件
void CPngImage::ReleaseIImage()
{
	// 释放IImage接口对象
	if (m_pImage)
	{
		m_pImage->Release();
	}
	// 释放IImagingFactory接口对象
	if (m_pImagingFactory)
	{
		m_pImage->Release();
	}
	if (m_pImgDataBuf != NULL)  
	{
		delete[] m_pImgDataBuf;  
		m_pImgDataBuf = NULL;  
	} 
	// 释放程序占用的COM资源
	CoUninitialize();
}
// 从文件中载入图片
void CPngImage::LoadPicture(CString strPicName)
{
	CString strPicPath = PicFolderName + strPicName; // 图像文件的路径
	if (FAILED(m_pImagingFactory->CreateImageFromFile(strPicPath, &m_pImage)))
	{
		AfxMessageBox(strPicPath + _T(" Load Error!"));
	}
}
/** 从资源中载入图片*/
BOOL CPngImage::LoadPicture(LPCWSTR lpName, LPCWSTR lpType)  
{  
	// 在资源中寻找
	HRSRC	hr;
	DWORD	dwsize;
	HGLOBAL	hg;
	LPSTR	lp;
	HMODULE hModule_Current = GetModuleHandle(NULL);
	hr = FindResource(hModule_Current, lpName, lpType);
	dwsize = SizeofResource(GetModuleHandle(NULL), hr);
	hg = ::LoadResource(GetModuleHandle(NULL), hr);
	lp = (LPSTR)::LockResource(hg);
	// 从缓冲区创建图片
	if(FAILED(m_pImagingFactory->CreateImageFromBuffer(lp, dwsize, DISPOSAL_NONE, &m_pImage)))
	{
		return FALSE;
	}
	return TRUE;
}
// 将图片复制到内存DC
void CPngImage::GetDstDcFromPic(CDC* pSrcDC, CDC* pDstDC, CBitmap* pBitmap)
{
	ImageInfo oImageInfo;
	m_pImage->GetImageInfo(&oImageInfo);
	//创建一个内存DC,用来存储图片数据
	pBitmap->CreateCompatibleBitmap(pSrcDC, oImageInfo.Width,oImageInfo.Height);
	pDstDC->CreateCompatibleDC(pSrcDC);
	pDstDC->SelectObject(pBitmap);
	//将图片数据存储到内存DC中
	m_pImage->Draw(pDstDC->m_hDC ,CRect(0, 0, oImageInfo.Width, oImageInfo.Height), NULL);
	if (m_pImage)
	{
		m_pImage->Release();
		m_pImage = NULL;
	}
}
// 将位图选入内存设备
void CPngImage::OnDcBitBlt(CDC* pDstDC, CDC* pSrcDC, CRect rect, bool bTransparent)
{
	if (bTransparent)
	{
		// 		::AlphaBlend(pDstDC->m_hDC,
		// 			rect.left, 
		// 			rect.top, 
		// 			rect.Width(), 
		// 			rect.Height(), 
		// 			pSrcDC->m_hDC, 
		// 			0, 
		// 			0, 
		// 			rect.Width(), 
		// 			rect.Height(), 
		// 			m_blendfun);
	}
	else
	{
		pDstDC->BitBlt(rect.left,	// 目标位图的X起始坐标
			rect.top,			// 目标位图的y起始坐标
			rect.Width(),			// 显示图像的宽度
			rect.Height(),			// 显示图像的高度
			pSrcDC, 
			0,			// 从源位图的X坐标开始显示图片
			0,			// 从源位图的y坐标开始显示图片
			SRCCOPY);	// 显示方式
	}
}

void CPngImage::DrawAlpha(CDC* pDstDC, CDC* pSrcDC, CRect dstRect, bool bDeleteImage)
{
	// 获取图像信息失败,目标绘图区为NULL
	if (m_pImage==NULL)
	{
		return;
	}
	// 获取原始数据
	GetImgDateBuf();
	// 创建目标绘制区域大小的内存DC
	pDstDC->CreateCompatibleDC(pSrcDC);
	BITMAPINFO hdr;
	ZeroMemory(&hdr , sizeof(BITMAPINFO));
	hdr.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	hdr.bmiHeader.biWidth = dstRect.Width();
	hdr.bmiHeader.biHeight = -dstRect.Height();
	hdr.bmiHeader.biPlanes = 1;
	hdr.bmiHeader.biBitCount = 32;
	BYTE * pbtPixels = NULL;
	HBITMAP hDIBitmap = CreateDIBSection(pDstDC->m_hDC, (BITMAPINFO *)&hdr, DIB_RGB_COLORS, (void **)&pbtPixels, NULL, 0);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(pDstDC->m_hDC, hDIBitmap);
	// 拷贝背景DC上目标绘制区域到内存DC
	::StretchBlt(pDstDC->m_hDC, 0, 0, dstRect.Width(), dstRect.Height(), pSrcDC->m_hDC, dstRect.left, dstRect.top, dstRect.Width(), dstRect.Height(), SRCCOPY);
	// 计算使用图片上的源区域大小
	CRect srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = dstRect.Width();
	srcRect.bottom = dstRect.Height();
	// 进行Alpha混合运算
	BYTE btAlphaSRC = 0;
	int iSrcPos = 0;
	int iDstPos = 0;
	for(int i=0; i<dstRect.Height(); i++)
	{
		for(int j=0;  j<dstRect.Width(); j++)
		{
			// 计算源及目标索引及该点ALPHA值
			iSrcPos = (i*srcRect.Width() + srcRect.left + j) * 4;
			iDstPos = (i*dstRect.Width() + j) * 4;
			btAlphaSRC = m_pImgDataBuf[iSrcPos+3];
			// 计算目标像素值，ALPHA混合result = ALPHA * srcPixel + ( 1 - ALPHA ) * destPixel
			pbtPixels[iDstPos] = ((255-btAlphaSRC)*pbtPixels[iDstPos] + btAlphaSRC*m_pImgDataBuf[iSrcPos])/255;
			pbtPixels[iDstPos+1] = ((255-btAlphaSRC)*pbtPixels[iDstPos+1] + btAlphaSRC*m_pImgDataBuf[iSrcPos+1])/255;
			pbtPixels[iDstPos+2] = ((255-btAlphaSRC)*pbtPixels[iDstPos+2] + btAlphaSRC*m_pImgDataBuf[iSrcPos+2])/255;
		}
	}
// 	// 混合ALPHA后的内存DC拷贝到目标DC
// 	BitBlt(hdc, dstRect->left, dstRect->top, nDstWidth, nDstHeight, hDIBDC, 0, 0, SRCCOPY);
// 	// 释放临时内存DC
// 	SelectObject(hDIBDC, hOldBmp);
// 	DeleteObject(hDIBDC);
 	DeleteObject(hDIBitmap);
	if (bDeleteImage == true)
	{
		if (m_pImage)
		{
			m_pImage->Release();
			m_pImage = NULL;
		}
	}
}
// 取得图片原始数据
void CPngImage::GetImgDateBuf()
{
	// 参数有效性
	if (m_pImage==NULL || m_pImagingFactory==NULL)
	{
		return;
	}
	ImageInfo oImageInfo;
	m_pImage->GetImageInfo(&oImageInfo);
	// 取得图片原始数据
	CRect rect(0, 0, oImageInfo.Width, oImageInfo.Height);
	BitmapData bitmapData;
	bitmapData.Width = oImageInfo.Width;
	bitmapData.Height = oImageInfo.Height;
	bitmapData.PixelFormat = oImageInfo.PixelFormat;
	IBitmapImage *pBitmapImage = NULL;
	m_pImagingFactory->CreateBitmapFromImage(m_pImage, oImageInfo.Width, oImageInfo.Height, PIXFMT_32BPP_ARGB, InterpolationHintDefault, &pBitmapImage);
	pBitmapImage->LockBits(&rect, ImageLockModeRead, PIXFMT_32BPP_ARGB, &bitmapData);
	// 释放旧数据
	if (m_pImgDataBuf != NULL)
	{
		delete[] m_pImgDataBuf;
		m_pImgDataBuf = NULL;
	}
	// 申请新空间
	m_pImgDataBuf = new unsigned char[oImageInfo.Width * oImageInfo.Height * 4];
	memcpy(m_pImgDataBuf, bitmapData.Scan0, oImageInfo.Width * oImageInfo.Height * 4);
	pBitmapImage->UnlockBits(&bitmapData);
	pBitmapImage->Release(); 
}  
