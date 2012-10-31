#pragma once
#include <imaging.h>
#include "Parameter.h"
class CPngImage
{
public:
	CPngImage(void);
	~CPngImage(void);
private:
	// Image�����ӿڶ���
	IImagingFactory* m_pImagingFactory;
	// Image�ӿڶ���
	IImage* m_pImage;
	// Image���ݻ���
	unsigned char* m_pImgDataBuf;
public:
	/** ��ʼ��IImage COM���*/
	void InitIImage();
	/** �ͷ�IImage COM���*/
	void ReleaseIImage();
	/** ���ļ�������ͼƬ*/
	void LoadPicFromFile(CString strPicName);
	/** ����Դ������ͼƬ*/
	BOOL LoadFromResource(LPCWSTR lpName, LPCWSTR lpType);
	/** ��ͼƬ���Ƶ��ڴ�DC*/
	void GetDstDcFromPic(CDC* pSrcDC, CDC* pDstDC, CBitmap* pBitmap);
	/** ��λͼѡ���ڴ��豸*/
	void OnDcBitBlt(CDC* pDstDC, CDC* pSrcDC, CRect rect, bool bTransparent = false);
	/** ����ͼ����һ���ֵ�ָ���Ĳ��֣�֧��alpha��ϣ�*/
	void DrawAlpha(CDC* pDstDC, CDC* pSrcDC, CRect dstRect);
	/** ȡ��ͼƬԭʼ����*/
	void GetImgDateBuf();
};
