// Aucma_HeaterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Aucma_Heater.h"
#include "Aucma_HeaterDlg.h"
#include "Parameter.h"
#include <initguid.h>
#include <imgguids.h>
#include <wingdi.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAucma_HeaterDlg 对话框

CAucma_HeaterDlg::CAucma_HeaterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAucma_HeaterDlg::IDD, pParent)
	, m_bHelper(false)
	, m_bHelperOld(true)
	, m_bWashHand(false)
	, m_bWashHandOld(true)
	, m_iFastHeatState(NormalHeat)
	, m_iFastHeatStateOld(WinterHeat)
	, m_bNight(false)
	, m_bNightOld(true)
	, m_iTempState(NoTempShow)
	, m_iTempStateOld(HeatTempState)
	, m_bTempHeat(false)
	, m_bPower(false)
	, m_bPowerOld(true)
	, m_uiHeatCount(0)
	, m_iSetTemp(88)
	, m_iSetTempOld(0)
	, m_iCurrTemp(0)
	, m_bSetTemp(false)
	, m_bSetTempOld(true)
	, m_bSetTime(false)
	, m_bSetTimeOld(true)
	, m_CurrTime(0)
	, m_CurrTimeOld(1)
	, m_bAdd(false)
	, m_bAddOld(true)
	, m_bReduce(false)
	, m_bReduceOld(true)
	, m_bTempLabel(false)
	, m_bTempLabelOld(true)
	, m_bTimeLabel(false)
	, m_bTimeLabelOld(true)
	, m_uiContinuousCount(0)
	, m_bAddOpt(false)
	, m_pImagingFactory(NULL)
	, m_pImage(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_rectHeatFastPic = CRect(20, 8, 84, 72);
	m_rectHeatFastText = CRect(20, 72, 84, 86);
	m_rectWinterPic = CRect(88, 40, 120, 72);
	m_rectWinterText = CRect(88, 72, 120, 86);
	m_rectHelperPic = CRect(20, 94, 84, 158);
	m_rectHelperText = CRect(20, 158, 84, 172);
	m_rectWashHandPic = CRect(20, 180, 84, 244);
	m_rectWashHandText = CRect(20, 244, 84, 258);
	m_rectNightModePic = CRect(390, 8, 454, 72);
	m_rectNightModeText = CRect(390, 72, 454, 86);
	m_rectTempPic = CRect(406, 94, 438, 158);
	m_rectTempInsulationText = CRect(390, 158, 422, 172);
	m_rectTempHeatText = CRect(422, 158, 454, 172);
	m_rectPowerPic = CRect(390, 187, 454, 251);
	m_rectTempHighPic = CRect(140, 15, 236, 159);
	m_rectTempLowPic = CRect(238, 15, 334, 159);
	m_rectTemp = CRect(140, 15, 334, 159);
	m_rectTempLabelText = CRect(336, 15, 356, 35);
	m_rectAdd = CRect(202, 161, 234, 193);
	m_rectReduce = CRect(240, 161, 272, 193);
	m_rectHourHighPic = CRect(162, 197, 194, 261);
	m_rectHourLowPic = CRect(195, 197, 227, 261);
	m_rectTimeLabelPic = CRect(227, 197, 247, 261);
	m_rectMinHighPic = CRect(247, 197, 279, 261);
	m_rectMinLowPic = CRect(280, 197, 312, 261);
	m_rectTime = CRect(162, 197, 312, 261);
}

void CAucma_HeaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAucma_HeaterDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAucma_HeaterDlg 消息处理程序

BOOL CAucma_HeaterDlg::OnInitDialog()
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
// 	CDC hmemdc, memDC1;
// 	::AlphaBlend(hmemdc.m_hDC,0,0,260,60,memDC1.m_hDC,0,0,260,60,bindfun);
	RunIImage();
	// 创建背景刷子
	m_brushBk.CreateSolidBrush(DialogBkColor);
	CFont* pfont = NULL;
	LOGFONT logFont;
	LONG lfHeight = 0;
	pfont = GetDC()->GetCurrentFont();
	memset(&logFont, 0, sizeof(LOGFONT));
	pfont->GetLogFont(&logFont);
	lfHeight = logFont.lfHeight;
	VERIFY(m_FontDefault.CreateFontIndirect(&logFont));
	logFont.lfHeight = lfHeight * 6 / 7;
	VERIFY(m_FontWinter.CreateFontIndirect(&logFont));
	logFont.lfHeight = lfHeight * 3 / 2;
	VERIFY(m_FontTemp.CreateFontIndirect(&logFont));
	// 对话框最大化显示
	//	ShowWindow(SW_SHOWMAXIMIZED);
	int iFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int iFullHeight = GetSystemMetrics(SM_CYSCREEN);
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, iFullWidth, iFullHeight, SWP_NOOWNERZORDER|SWP_SHOWWINDOW);
	m_CurrTime = CTime::GetCurrentTime();
	SetTimer(ShowTimeTimerEvent, ShowTimeTimeSet, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CAucma_HeaterDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_AUCMA_HEATER_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_AUCMA_HEATER_DIALOG));
	}
}
#endif
// 运行IImage COM组件
void CAucma_HeaterDlg::RunIImage()
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
	// 载入图标到图片句柄
	LoadPicFromFile(_T("速热引擎_1.png"));
	GetMemDcFromPic(&m_dcHeatFastOff, &m_bmpHeatFastOff);
	LoadPicFromFile(_T("速热引擎_2.png"));
	GetMemDcFromPic(&m_dcHeatFastOn, &m_bmpHeatFastOn);
	LoadPicFromFile(_T("冬天_1.png"));
	GetMemDcFromPic(&m_dcWinterOff, &m_bmpWinterOff);
	LoadPicFromFile(_T("冬天_2.png"));
	GetMemDcFromPic(&m_dcWinterOn, &m_bmpWinterOn);
	LoadPicFromFile(_T("智能助手_1.png"));
	GetMemDcFromPic(&m_dcHelperOff, &m_bmpHelperOff);
	LoadPicFromFile(_T("智能助手_2.png"));
	GetMemDcFromPic(&m_dcHelperOn, &m_bmpHelperOn);
	LoadPicFromFile(_T("洗手加热_1.png"));
	GetMemDcFromPic(&m_dcWashHandOff, &m_bmpWashHandOff);
	LoadPicFromFile(_T("洗手加热_2.png"));
	GetMemDcFromPic(&m_dcWashHandOn, &m_bmpWashHandOn);
	LoadPicFromFile(_T("夜电模式_1.png"));
	GetMemDcFromPic(&m_dcNightModeOff, &m_bmpNightModeOff);
	LoadPicFromFile(_T("夜电模式_2.png"));
	GetMemDcFromPic(&m_dcNightModeOn, &m_bmpNightModeOn);
	LoadPicFromFile(_T("保温_加热.png"));
	GetMemDcFromPic(&m_dcTempOff, &m_bmpTempOff);
	LoadPicFromFile(_T("保温.png"));
	GetMemDcFromPic(&m_dcTempInsulation, &m_bmpTempInsulation);
	LoadPicFromFile(_T("加热_1.png"));
	GetMemDcFromPic(&m_dcTempHeat1, &m_bmpTempHeat1);
	LoadPicFromFile(_T("加热_2.png"));
	GetMemDcFromPic(&m_dcTempHeat2, &m_bmpTempHeat2);
	LoadPicFromFile(_T("加热_3.png"));
	GetMemDcFromPic(&m_dcTempHeat3, &m_bmpTempHeat3);
	LoadPicFromFile(_T("电源_1.png"));
	GetMemDcFromPic(&m_dcPowerOff, &m_bmpPowerOff);
	LoadPicFromFile(_T("电源_2.png"));
	GetMemDcFromPic(&m_dcPowerOn, &m_bmpPowerOn);
	LoadPicFromFile(_T("增加.png"));
	GetMemDcFromPic(&m_dcAdd, &m_bmpAdd);
	LoadPicFromFile(_T("减少.png"));
	GetMemDcFromPic(&m_dcReduce, &m_bmpReduce);
	LoadPicFromFile(_T("时间标志.png"));
	GetMemDcFromPic(&m_dcTimeLabel, &m_bmpTimeLabel);
	CString str = _T("");
	for (int i=0; i<10; i++)
	{
		str.Format(_T("温度1_%d.png"), i);
		LoadPicFromFile(str);
		GetMemDcFromPic(&m_dcTempShow[i], &m_bmpTempShow[i]);
		str.Format(_T("温度2_%d.png"), i);
		LoadPicFromFile(str);
		GetMemDcFromPic(&m_dcTempSet[i], &m_bmpTempSet[i]);
		str.Format(_T("时间1_%d.png"), i);
		LoadPicFromFile(str);
		GetMemDcFromPic(&m_dcTimeShow[i], &m_bmpTimeShow[i]);
		str.Format(_T("时间2_%d.png"), i);
		LoadPicFromFile(str);
		GetMemDcFromPic(&m_dcTimeSet[i], &m_bmpTimeSet[i]);
	}
	ReleaseIImage();
}
// 释放IImage COM组件
void CAucma_HeaterDlg::ReleaseIImage()
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
	// 释放程序占用的COM资源
	CoUninitialize();
}
// 从文件中载入图片
void CAucma_HeaterDlg::LoadPicFromFile(CString strPicName)
{
	CString strPicPath = PicFolderName + strPicName; // 图像文件的路径
	if (FAILED(m_pImagingFactory->CreateImageFromFile(strPicPath, &m_pImage)))
	{
		AfxMessageBox(strPicPath + _T("Load Error!"));
		PostMessage(WM_DESTROY);
	}
}
// 将图片复制到内存DC
void CAucma_HeaterDlg::GetMemDcFromPic(CDC* pDC, CBitmap* pBitmap, bool bTransparent)
{
	ImageInfo oImageInfo;
	m_pImage->GetImageInfo(&oImageInfo);
	//创建一个内存DC,用来存储图片数据
	pBitmap->CreateCompatibleBitmap(GetDC(), oImageInfo.Width,oImageInfo.Height);
	pDC->CreateCompatibleDC(GetDC());
	pDC->SelectObject(pBitmap);
	//将图片数据存储到内存DC中
	m_pImage->Draw(pDC->m_hDC ,CRect(0, 0, oImageInfo.Width, oImageInfo.Height), NULL);
}
HBRUSH CAucma_HeaterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brushBk;
}

void CAucma_HeaterDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	m_brushBk.DeleteObject();
	m_FontDefault.DeleteObject();
	m_FontWinter.DeleteObject();
	m_FontTemp.DeleteObject();

	m_dcHeatFastOn.DeleteDC();
	m_bmpHeatFastOn.DeleteObject();
	m_dcHeatFastOff.DeleteDC();
	m_bmpHeatFastOff.DeleteObject();
	m_dcWinterOn.DeleteDC();
	m_bmpWinterOn.DeleteObject();
	m_dcWinterOff.DeleteDC();
	m_bmpWinterOff.DeleteObject();
	m_dcHelperOn.DeleteDC();
	m_bmpHelperOn.DeleteObject();
	m_dcHelperOff.DeleteDC();
	m_bmpHelperOff.DeleteObject();
	m_dcWashHandOn.DeleteDC();
	m_bmpWashHandOn.DeleteObject();
	m_dcWashHandOff.DeleteDC();
	m_bmpWashHandOff.DeleteObject();
	m_dcNightModeOn.DeleteDC();
	m_bmpNightModeOn.DeleteObject();
	m_dcNightModeOff.DeleteDC();
	m_bmpNightModeOff.DeleteObject();
	m_dcTempOff.DeleteDC();
	m_bmpTempOff.DeleteObject();
	m_dcTempInsulation.DeleteDC();
	m_bmpTempInsulation.DeleteObject();
	m_dcTempHeat1.DeleteDC();
	m_bmpTempHeat1.DeleteObject();
	m_dcTempHeat2.DeleteDC();
	m_bmpTempHeat2.DeleteObject();
	m_dcTempHeat3.DeleteDC();
	m_bmpTempHeat3.DeleteObject();
	m_dcPowerOn.DeleteDC();
	m_bmpPowerOn.DeleteObject();
	m_dcPowerOff.DeleteDC();
	m_bmpPowerOff.DeleteObject();
	for (int i=0; i<10; i++)
	{
		m_bmpTempShow[i].DeleteObject();
		m_dcTempShow[i].DeleteDC();
		m_bmpTimeSet[i].DeleteObject();
		m_dcTempSet[i].DeleteDC();
		m_bmpTimeShow[i].DeleteObject();
		m_dcTimeShow[i].DeleteDC();
		m_bmpTimeSet[i].DeleteObject();
		m_dcTimeSet[i].DeleteDC();
	}
	m_bmpAdd.DeleteObject();
	m_dcAdd.DeleteDC();
	m_bmpReduce.DeleteObject();
	m_dcReduce.DeleteDC();
	m_bmpTimeLabel.DeleteObject();
	m_dcTimeLabel.DeleteDC();
}

void CAucma_HeaterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonDown(nFlags, point);
}

void CAucma_HeaterDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonUp(nFlags, point);
}
// 将位图选入内存设备
void CAucma_HeaterDlg::OnDcBitBlt(CDC* pDC, CDC* pmemDC, CRect rect)
{
	pDC->BitBlt(rect.left,	// 目标位图的X起始坐标
		rect.top,			// 目标位图的y起始坐标
		rect.Width(),			// 显示图像的宽度
		rect.Height(),			// 显示图像的高度
		pmemDC, 
		0,			// 从源位图的X坐标开始显示图片
		0,			// 从源位图的y坐标开始显示图片
		SRCCOPY);	// 显示方式
}
void CAucma_HeaterDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	if (m_iFastHeatStateOld != m_iFastHeatState)
	{
		if (m_iFastHeatState == NormalHeat)
		{
			OnDcBitBlt(&dc, &m_dcHeatFastOff, m_rectHeatFastPic);
			OnDcBitBlt(&dc, &m_dcWinterOff, m_rectWinterPic);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectHeatFastText.left, m_rectHeatFastText.top, ETO_OPAQUE, NULL, _T("速热引擎"), NULL);
			dc.ExtTextOut(m_rectWinterText.left, m_rectWinterText.top, ETO_OPAQUE, NULL, _T("冬天"), NULL);
		}
		else if (m_iFastHeatState == FastHeat)
		{
			OnDcBitBlt(&dc, &m_dcHeatFastOn, m_rectHeatFastPic);
			OnDcBitBlt(&dc, &m_dcWinterOff, m_rectWinterPic);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectHeatFastText.left, m_rectHeatFastText.top, ETO_OPAQUE, NULL, _T("速热引擎"), NULL);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectWinterText.left, m_rectWinterText.top, ETO_OPAQUE, NULL, _T("冬天"), NULL);
		}
		else if (m_iFastHeatState == WinterHeat)
		{
			OnDcBitBlt(&dc, &m_dcHeatFastOn, m_rectHeatFastPic);
			OnDcBitBlt(&dc, &m_dcWinterOn, m_rectWinterPic);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectHeatFastText.left, m_rectHeatFastText.top, ETO_OPAQUE, NULL, _T("速热引擎"), NULL);
			dc.ExtTextOut(m_rectWinterText.left, m_rectWinterText.top, ETO_OPAQUE, NULL, _T("冬天"), NULL);
		}
		m_iFastHeatStateOld = m_iFastHeatState;
	}
	if (m_bHelperOld != m_bHelper)
	{
		if (m_bHelper == true)
		{
			OnDcBitBlt(&dc, &m_dcHelperOn, m_rectHelperPic);
			dc.SetTextColor(SelectTextColor);
		}
		else
		{
			OnDcBitBlt(&dc, &m_dcHelperOff, m_rectHelperPic);
			dc.SetTextColor(DefaultTextColor);
		}
		dc.ExtTextOut(m_rectHelperText.left, m_rectHelperText.top, ETO_OPAQUE, NULL, _T("智能助手"), NULL);
		m_bHelperOld = m_bHelper;
	}
	if (m_bWashHandOld != m_bWashHand)
	{
		if (m_bWashHand == true)
		{
			OnDcBitBlt(&dc, &m_dcWashHandOn, m_rectWashHandPic);
			dc.SetTextColor(SelectTextColor);
		}
		else
		{
			OnDcBitBlt(&dc, &m_dcWashHandOff, m_rectWashHandPic);
			dc.SetTextColor(DefaultTextColor);
		}
		dc.ExtTextOut(m_rectWashHandText.left, m_rectWashHandText.top, ETO_OPAQUE, NULL, _T("洗手加热"), NULL);
		m_bWashHandOld = m_bWashHand;
	}
	if (m_bNightOld != m_bNight)
	{
		if (m_bNight == true)
		{
			OnDcBitBlt(&dc, &m_dcNightModeOn, m_rectNightModePic);
			dc.SetTextColor(SelectTextColor);
		}
		else
		{
			OnDcBitBlt(&dc, &m_dcNightModeOff, m_rectNightModePic);
			dc.SetTextColor(DefaultTextColor);
		}
		dc.ExtTextOut(m_rectNightModeText.left, m_rectNightModeText.top, ETO_OPAQUE, NULL, _T("夜电模式"), NULL);
		m_bNightOld = m_bNight;
	}
	if (m_bPowerOld != m_bPower)
	{
		if (m_bPower == true)
		{
			OnDcBitBlt(&dc, &m_dcPowerOn, m_rectPowerPic);
		}
		else
		{
			OnDcBitBlt(&dc, &m_dcPowerOff, m_rectPowerPic);
		}
		m_bPowerOld = m_bPower;
	}
	if (m_bAddOld != m_bAdd)
	{
		OnDcBitBlt(&dc, &m_dcAdd, m_rectAdd);
		m_bAddOld = m_bAdd;
	}
	if (m_bReduceOld != m_bReduce)
	{
		OnDcBitBlt(&dc, &m_dcReduce, m_rectReduce);
		m_bReduceOld = m_bReduce;
	}
	if (m_bTempLabelOld != m_bTempLabel)
	{
		dc.SetTextColor(DefaultTextColor);
		dc.ExtTextOut(m_rectTempLabelText.left, m_rectTempLabelText.top, ETO_OPAQUE, NULL, _T("℃"), NULL);
		m_bTempLabelOld = m_bTempLabel;
	}
	if ((m_iSetTempOld != m_iSetTemp) || (m_bSetTempOld != m_bSetTemp))
	{
		if (m_bSetTemp == true)
		{
			OnDcBitBlt(&dc, &m_dcTempSet[m_iSetTemp / 10], m_rectTempHighPic);
			OnDcBitBlt(&dc, &m_dcTempSet[m_iSetTemp % 10], m_rectTempLowPic);
		}
		else
		{
			OnDcBitBlt(&dc, &m_dcTempShow[m_iSetTemp / 10], m_rectTempHighPic);
			OnDcBitBlt(&dc, &m_dcTempShow[m_iSetTemp % 10], m_rectTempLowPic);
		}
		m_iSetTempOld = m_iSetTemp;
		m_bSetTempOld = m_bSetTemp;
	}
	if ((m_CurrTimeOld != m_CurrTime) || (m_bSetTimeOld != m_bSetTime))
	{
		if (m_bSetTime == true)
		{
			OnDcBitBlt(&dc, &m_dcTimeSet[m_CurrTime.GetHour() / 10], m_rectHourHighPic);
			OnDcBitBlt(&dc, &m_dcTimeSet[m_CurrTime.GetHour() % 10], m_rectHourLowPic);
			OnDcBitBlt(&dc, &m_dcTimeSet[m_CurrTime.GetMinute() / 10], m_rectMinHighPic);
			OnDcBitBlt(&dc, &m_dcTimeSet[m_CurrTime.GetMinute() % 10], m_rectMinLowPic);
		}
		else
		{
			OnDcBitBlt(&dc, &m_dcTimeShow[m_CurrTime.GetHour() / 10], m_rectHourHighPic);
			OnDcBitBlt(&dc, &m_dcTimeShow[m_CurrTime.GetHour() % 10], m_rectHourLowPic);
			OnDcBitBlt(&dc, &m_dcTimeShow[m_CurrTime.GetMinute() / 10], m_rectMinHighPic);
			OnDcBitBlt(&dc, &m_dcTimeShow[m_CurrTime.GetMinute() % 10], m_rectMinLowPic);
		}
		m_CurrTimeOld = m_CurrTime;
		m_bSetTimeOld = m_bSetTime;
	}
	if (m_bTimeLabelOld != m_bTimeLabel)
	{
		OnDcBitBlt(&dc, &m_dcTimeLabel, m_rectTimeLabelPic);
		m_bTimeLabelOld = m_bTimeLabel;
	}
	if ((m_iTempStateOld != m_iTempState) || (m_bTempHeat == true))
	{
		if (m_iTempState == NoTempShow)
		{
			OnDcBitBlt(&dc, &m_dcTempOff, m_rectTempPic);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectTempInsulationText.left, m_rectTempInsulationText.top, ETO_OPAQUE, NULL, _T("保温"), NULL);
			dc.ExtTextOut(m_rectTempHeatText.left, m_rectTempHeatText.top, ETO_OPAQUE, NULL, _T("加热"), NULL);
		}
		else if (m_iTempState == InsulationState)
		{
			OnDcBitBlt(&dc, &m_dcTempInsulation, m_rectTempPic);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectTempInsulationText.left, m_rectTempInsulationText.top, ETO_OPAQUE, NULL, _T("保温"), NULL);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectTempHeatText.left, m_rectTempHeatText.top, ETO_OPAQUE, NULL, _T("加热"), NULL);
		}
		else if (m_iTempState == HeatTempState)
		{
			if (m_uiHeatCount == 0)
			{
				OnDcBitBlt(&dc, &m_dcTempHeat1, m_rectTempPic);
			}
			else if (m_uiHeatCount == 1)
			{
				OnDcBitBlt(&dc, &m_dcTempHeat2, m_rectTempPic);
			}
			else if (m_uiHeatCount == 2)
			{
				OnDcBitBlt(&dc, &m_dcTempHeat3, m_rectTempPic);
			}
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectTempInsulationText.left, m_rectTempInsulationText.top, ETO_OPAQUE, NULL, _T("保温"), NULL);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectTempHeatText.left, m_rectTempHeatText.top, ETO_OPAQUE, NULL, _T("加热"), NULL);
		}
		m_iTempStateOld = m_iTempState;
	}
}

void CAucma_HeaterDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnTimer(nIDEvent);
}
