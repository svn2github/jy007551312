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
// ��ʼ��IImage COM���
void CPngImage::InitIImage()
{
	// ��ʼ��COM����
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
// �ͷ�IImage COM���
void CPngImage::ReleaseIImage()
{
	// �ͷ�IImage�ӿڶ���
	if (m_pImage)
	{
		m_pImage->Release();
	}
	// �ͷ�IImagingFactory�ӿڶ���
	if (m_pImagingFactory)
	{
		m_pImage->Release();
	}
	if (m_pImgDataBuf != NULL)  
	{
		delete[] m_pImgDataBuf;  
		m_pImgDataBuf = NULL;  
	} 
	// �ͷų���ռ�õ�COM��Դ
	CoUninitialize();
}
// ���ļ�������ͼƬ
void CPngImage::LoadPicture(CString strPicName)
{
	CString strPicPath = PicFolderName + strPicName; // ͼ���ļ���·��
	if (FAILED(m_pImagingFactory->CreateImageFromFile(strPicPath, &m_pImage)))
	{
		AfxMessageBox(strPicPath + _T(" Load Error!"));
	}
}
/** ����Դ������ͼƬ*/
BOOL CPngImage::LoadPicture(LPCWSTR lpName, LPCWSTR lpType)  
{  
	// ����Դ��Ѱ��
	HRSRC	hr;
	DWORD	dwsize;
	HGLOBAL	hg;
	LPSTR	lp;
	HMODULE hModule_Current = GetModuleHandle(NULL);
	hr = FindResource(hModule_Current, lpName, lpType);
	dwsize = SizeofResource(GetModuleHandle(NULL), hr);
	hg = ::LoadResource(GetModuleHandle(NULL), hr);
	lp = (LPSTR)::LockResource(hg);
	// �ӻ���������ͼƬ
	if(FAILED(m_pImagingFactory->CreateImageFromBuffer(lp, dwsize, DISPOSAL_NONE, &m_pImage)))
	{
		return FALSE;
	}
	return TRUE;
}
// ��ͼƬ���Ƶ��ڴ�DC
void CPngImage::GetDstDcFromPic(CDC* pSrcDC, CDC* pDstDC, CBitmap* pBitmap)
{
	ImageInfo oImageInfo;
	m_pImage->GetImageInfo(&oImageInfo);
	//����һ���ڴ�DC,�����洢ͼƬ����
	pBitmap->CreateCompatibleBitmap(pSrcDC, oImageInfo.Width,oImageInfo.Height);
	pDstDC->CreateCompatibleDC(pSrcDC);
	pDstDC->SelectObject(pBitmap);
	//��ͼƬ���ݴ洢���ڴ�DC��
	m_pImage->Draw(pDstDC->m_hDC ,CRect(0, 0, oImageInfo.Width, oImageInfo.Height), NULL);
	if (m_pImage)
	{
		m_pImage->Release();
		m_pImage = NULL;
	}
}
// ��λͼѡ���ڴ��豸
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
		pDstDC->BitBlt(rect.left,	// Ŀ��λͼ��X��ʼ����
			rect.top,			// Ŀ��λͼ��y��ʼ����
			rect.Width(),			// ��ʾͼ��Ŀ��
			rect.Height(),			// ��ʾͼ��ĸ߶�
			pSrcDC, 
			0,			// ��Դλͼ��X���꿪ʼ��ʾͼƬ
			0,			// ��Դλͼ��y���꿪ʼ��ʾͼƬ
			SRCCOPY);	// ��ʾ��ʽ
	}
}

void CPngImage::DrawAlpha(CDC* pDstDC, CDC* pSrcDC, CRect dstRect, bool bDeleteImage)
{
	// ��ȡͼ����Ϣʧ��,Ŀ���ͼ��ΪNULL
	if (m_pImage==NULL)
	{
		return;
	}
	// ��ȡԭʼ����
	GetImgDateBuf();
	// ����Ŀ����������С���ڴ�DC
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
	// ��������DC��Ŀ����������ڴ�DC
	::StretchBlt(pDstDC->m_hDC, 0, 0, dstRect.Width(), dstRect.Height(), pSrcDC->m_hDC, dstRect.left, dstRect.top, dstRect.Width(), dstRect.Height(), SRCCOPY);
	// ����ʹ��ͼƬ�ϵ�Դ�����С
	CRect srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = dstRect.Width();
	srcRect.bottom = dstRect.Height();
	// ����Alpha�������
	BYTE btAlphaSRC = 0;
	int iSrcPos = 0;
	int iDstPos = 0;
	for(int i=0; i<dstRect.Height(); i++)
	{
		for(int j=0;  j<dstRect.Width(); j++)
		{
			// ����Դ��Ŀ���������õ�ALPHAֵ
			iSrcPos = (i*srcRect.Width() + srcRect.left + j) * 4;
			iDstPos = (i*dstRect.Width() + j) * 4;
			btAlphaSRC = m_pImgDataBuf[iSrcPos+3];
			// ����Ŀ������ֵ��ALPHA���result = ALPHA * srcPixel + ( 1 - ALPHA ) * destPixel
			pbtPixels[iDstPos] = ((255-btAlphaSRC)*pbtPixels[iDstPos] + btAlphaSRC*m_pImgDataBuf[iSrcPos])/255;
			pbtPixels[iDstPos+1] = ((255-btAlphaSRC)*pbtPixels[iDstPos+1] + btAlphaSRC*m_pImgDataBuf[iSrcPos+1])/255;
			pbtPixels[iDstPos+2] = ((255-btAlphaSRC)*pbtPixels[iDstPos+2] + btAlphaSRC*m_pImgDataBuf[iSrcPos+2])/255;
		}
	}
// 	// ���ALPHA����ڴ�DC������Ŀ��DC
// 	BitBlt(hdc, dstRect->left, dstRect->top, nDstWidth, nDstHeight, hDIBDC, 0, 0, SRCCOPY);
// 	// �ͷ���ʱ�ڴ�DC
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
// ȡ��ͼƬԭʼ����
void CPngImage::GetImgDateBuf()
{
	// ������Ч��
	if (m_pImage==NULL || m_pImagingFactory==NULL)
	{
		return;
	}
	ImageInfo oImageInfo;
	m_pImage->GetImageInfo(&oImageInfo);
	// ȡ��ͼƬԭʼ����
	CRect rect(0, 0, oImageInfo.Width, oImageInfo.Height);
	BitmapData bitmapData;
	bitmapData.Width = oImageInfo.Width;
	bitmapData.Height = oImageInfo.Height;
	bitmapData.PixelFormat = oImageInfo.PixelFormat;
	IBitmapImage *pBitmapImage = NULL;
	m_pImagingFactory->CreateBitmapFromImage(m_pImage, oImageInfo.Width, oImageInfo.Height, PIXFMT_32BPP_ARGB, InterpolationHintDefault, &pBitmapImage);
	pBitmapImage->LockBits(&rect, ImageLockModeRead, PIXFMT_32BPP_ARGB, &bitmapData);
	// �ͷž�����
	if (m_pImgDataBuf != NULL)
	{
		delete[] m_pImgDataBuf;
		m_pImgDataBuf = NULL;
	}
	// �����¿ռ�
	m_pImgDataBuf = new unsigned char[oImageInfo.Width * oImageInfo.Height * 4];
	memcpy(m_pImgDataBuf, bitmapData.Scan0, oImageInfo.Width * oImageInfo.Height * 4);
	pBitmapImage->UnlockBits(&bitmapData);
	pBitmapImage->Release(); 
}  
