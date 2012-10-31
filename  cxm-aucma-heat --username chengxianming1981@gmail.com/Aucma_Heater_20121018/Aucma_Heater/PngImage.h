#pragma once
#include <imaging.h>
#include "Parameter.h"
class CPngImage
{
public:
	CPngImage(void);
	~CPngImage(void);
private:
	// Image工厂接口对象
	IImagingFactory* m_pImagingFactory;
	// Image接口对象
	IImage* m_pImage;
	// Image数据缓冲
	unsigned char* m_pImgDataBuf;
public:
	/** 初始化IImage COM组件*/
	void InitIImage();
	/** 释放IImage COM组件*/
	void ReleaseIImage();
	/** 从文件中载入图片*/
	void LoadPicFromFile(CString strPicName);
	/** 从资源中载入图片*/
	BOOL LoadFromResource(LPCWSTR lpName, LPCWSTR lpType);
	/** 将图片复制到内存DC*/
	void GetDstDcFromPic(CDC* pSrcDC, CDC* pDstDC, CBitmap* pBitmap);
	/** 将位图选入内存设备*/
	void OnDcBitBlt(CDC* pDstDC, CDC* pSrcDC, CRect rect, bool bTransparent = false);
	/** 绘制图像上一部分到指定的部分（支持alpha混合）*/
	void DrawAlpha(CDC* pDstDC, CDC* pSrcDC, CRect dstRect);
	/** 取得图片原始数据*/
	void GetImgDateBuf();
};
