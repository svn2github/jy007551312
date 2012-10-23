// Aucma_HeaterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Aucma_Heater.h"
#include "Aucma_HeaterDlg.h"
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
	, m_iInTempSet(DefaultSetTemp)
	, m_iInTempSetOld(0)
	, m_iInTempActual(0)
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
	, m_iEnvTempActual(0)
	, m_iHighWarnTemp(0)
	, m_iLowWarnTemp(0)
	, m_uiUartRcvCount(0)
	, m_byCheck(0)
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
	ON_MESSAGE(WM_RECV_UART_DATA, &CAucma_HeaterDlg::OnRecvUartData)
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
	m_oCEUart.m_OnUartRead = OnUartRead;
	if (m_oCEUart.OpenPort(this, 1, 4800, NOPARITY, 8, ONESTOPBIT))
	{
		TRACE(_T("串口打开成功！"));
		// @@@@测试数据发送
// 		OnWriteUartData(CMD_IHMT_CTRL, CMD_IHMT_OFF);
// 		OnWriteUartData(CMD_IHMT_CTRL, CMD_IHMT_ON);
// 		OnWriteUartData(CMD_IHMT_RST, 0);
// 		OnWriteUartData(CMD_DOWN_ET, -99 + 127);
// 		OnWriteUartData(CMD_DOWN_ET, 0 + 127);
// 		OnWriteUartData(CMD_DOWN_ET, 99 + 127);
// 		OnWriteUartData(CMD_DOWN_IT, -99 + 127);
// 		OnWriteUartData(CMD_DOWN_IT, 0 + 127);
// 		OnWriteUartData(CMD_DOWN_IT, 99 + 127);
// 		OnWriteUartData(CMD_DOWN_AM, CMD_DOWN_HAM);
// 		OnWriteUartData(CMD_DOWN_AM, CMD_DOWN_LAM);
// 		OnWriteUartData(CMD_DOWN_AM, CMD_DOWN_HAMC);
// 		OnWriteUartData(CMD_DOWN_AM, CMD_DOWN_LAMC);
// 		OnWriteUartData(CMD_UP_IT, -99 + 127);
// 		OnWriteUartData(CMD_UP_IT, 0 + 127);
// 		OnWriteUartData(CMD_UP_IT, 99 + 127);
// 		OnWriteUartData(CMD_UP_HAM, -99 + 127);
// 		OnWriteUartData(CMD_UP_HAM, 0 + 127);
// 		OnWriteUartData(CMD_UP_HAM, 99 + 127);
// 		OnWriteUartData(CMD_UP_LAM, -99 + 127);
// 		OnWriteUartData(CMD_UP_LAM, 0 + 127);
// 		OnWriteUartData(CMD_UP_LAM, 99 + 127);
	}
	else
	{
		TRACE(_T("串口打开失败！"));
	}
	// BlendOp字段指明了源混合操作，但只支持AC_SRC_OVER，即根据源alpha值把源图像叠加到目标图像上  
	m_blendfun.BlendOp = AC_SRC_OVER;
	// BlendFlags必须是0，也是为以后的应用保留的
	m_blendfun.BlendFlags = 0;
	// 0到255间的值，这里0表示完全透明，255表示完全不透明
	m_blendfun.SourceConstantAlpha = DefaultPNGTransparent;
	// AlphaFormat有两个选择：0表示常量alpha值，AC_SRC_ALPHA表示每个像素有各自的alpha通道。
	/** 如果AlphaFormat字段为0,源位图中的所有像素使用同样的常量alpha值，即SourceConstantAlpha
	字段中的值，该值实际上是0和255，而不是0和1。这里0表示完全透明，255表示完全不透明。目标
	像素以255-SourceConstantAlpha值作为alpha值。*/
	/** 如果AlphaFormat字段的值是AC_SRC_ALPHA，源设备表面的每个像素必须有各自的alpha通道。
	即，必须是32-bpp的物理设备上下文，或是选中了32-bpp DDB和DIB段的内存设备上下文。
	这些情况下，每个源像素有4个8位通道：红、绿、蓝和alpha。每个像素的alpha通道和
	SourceConstantAlpha字段一起用于把源和目标混合起来。实际用于计算的运算式如下：
	Tmp.Red = Src.Red * SourceConstantAlpha / 255;
	Tmp.Green = Src.Green * SourceConstantAlpha / 255;
	Tmp.Blue = Src.Blue * SourceConstantAlpha / 255;
	Tmp.Alpha = Src.Alpha * SourceConstantAlpha / 255;
	Beta = 255 – Tmp.alpha;
	Dst.Red = Tmp.Red + Round((Beta * Dst.Red )/255);
	Dst.Green = Tmp.Green + Round((Beta * Dst.Green)/255);
	Dst.Blue = Tmp.Blue + Round((Beta * Dst.Blue )/255);
	Dst.Alpha = Tmp.Alpha + Round((Beta * Dst.Alpha)/255);*/
	// 有两个值 0表示常量alpha值，AC_SRC_ALPHA表示每个像素有各自的alpha通道
	m_blendfun.AlphaFormat = AC_SRC_ALPHA;
	// 对话框最大化显示
//	ShowWindow(SW_SHOWMAXIMIZED);
	int iFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int iFullHeight = GetSystemMetrics(SM_CYSCREEN);
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, iFullWidth, iFullHeight, SWP_NOOWNERZORDER|SWP_SHOWWINDOW);
	m_CurrTime = CTime::GetCurrentTime();
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
	SetTimer(ShowTimeTimerEvent, ShowTimeTimeSet, NULL);
	RunIImage();
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
	// 从文件中载入图标到图片句柄
//	LoadPicFromFile(_T("速热引擎_1.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_HEATFAST_OFF), _T("PNG"));
	GetDstDcFromPic(&m_dcHeatFastOff, &m_bmpHeatFastOff);
//	LoadPicFromFile(_T("速热引擎_2.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_HEATFAST_ON), _T("PNG"));
	GetDstDcFromPic(&m_dcHeatFastOn, &m_bmpHeatFastOn);
//	LoadPicFromFile(_T("冬天_1.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_WINTER_OFF), _T("PNG"));
	GetDstDcFromPic(&m_dcWinterOff, &m_bmpWinterOff);
//	LoadPicFromFile(_T("冬天_2.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_WINTER_OFF), _T("PNG"));
	GetDstDcFromPic(&m_dcWinterOn, &m_bmpWinterOn);
//	LoadPicFromFile(_T("智能助手_1.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_HELPER_OFF), _T("PNG"));
	GetDstDcFromPic(&m_dcHelperOff, &m_bmpHelperOff);
//	LoadPicFromFile(_T("智能助手_2.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_HELPER_ON), _T("PNG"));
	GetDstDcFromPic(&m_dcHelperOn, &m_bmpHelperOn);
//	LoadPicFromFile(_T("洗手加热_1.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_WASHHAND_OFF), _T("PNG"));
	GetDstDcFromPic(&m_dcWashHandOff, &m_bmpWashHandOff);
//	LoadPicFromFile(_T("洗手加热_2.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_WASHHAND_ON), _T("PNG"));
	GetDstDcFromPic(&m_dcWashHandOn, &m_bmpWashHandOn);
//	LoadPicFromFile(_T("夜电模式_1.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_NIGHTMODE_OFF), _T("PNG"));
	GetDstDcFromPic(&m_dcNightModeOff, &m_bmpNightModeOff);
//	LoadPicFromFile(_T("夜电模式_2.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_NIGHTMODE_ON), _T("PNG"));
	GetDstDcFromPic(&m_dcNightModeOn, &m_bmpNightModeOn);
//	LoadPicFromFile(_T("保温_加热.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_OFF), _T("PNG"));
	GetDstDcFromPic(&m_dcTempOff, &m_bmpTempOff);
//	LoadPicFromFile(_T("保温.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_ON), _T("PNG"));
	GetDstDcFromPic(&m_dcTempInsulation, &m_bmpTempInsulation);
//	LoadPicFromFile(_T("加热_1.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_HEAT1), _T("PNG"));
	GetDstDcFromPic(&m_dcTempHeat1, &m_bmpTempHeat1);
//	LoadPicFromFile(_T("加热_2.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_HEAT2), _T("PNG"));
	GetDstDcFromPic(&m_dcTempHeat2, &m_bmpTempHeat2);
//	LoadPicFromFile(_T("加热_3.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_HEAT3), _T("PNG"));
	GetDstDcFromPic(&m_dcTempHeat3, &m_bmpTempHeat3);
//	LoadPicFromFile(_T("电源_1.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_POWER_OFF), _T("PNG"));
	GetDstDcFromPic(&m_dcPowerOff, &m_bmpPowerOff);
//	LoadPicFromFile(_T("电源_2.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_POWER_ON), _T("PNG"));
	GetDstDcFromPic(&m_dcPowerOn, &m_bmpPowerOn);
//	LoadPicFromFile(_T("增加.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_ADD), _T("PNG"));
	GetDstDcFromPic(&m_dcAdd, &m_bmpAdd);
//	LoadPicFromFile(_T("减少.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_REDUCE), _T("PNG"));
	GetDstDcFromPic(&m_dcReduce, &m_bmpReduce);
//	LoadPicFromFile(_T("时间标志.png"));
	LoadFromResource(MAKEINTRESOURCE(IDB_TIMELABEL), _T("PNG"));
	GetDstDcFromPic(&m_dcTimeLabel, &m_bmpTimeLabel);
	CString str = _T("");
	for (int i=0; i<10; i++)
	{
//		str.Format(_T("温度1_%d.png"), i);
//		LoadPicFromFile(str);
		LoadFromResource(MAKEINTRESOURCE(IDB_TEMP0 + i), _T("PNG"));
		GetDstDcFromPic(&m_dcTempShow[i], &m_bmpTempShow[i]);
// 		str.Format(_T("温度2_%d.png"), i);
// 		LoadPicFromFile(str);
		LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_LIGHT0 + i), _T("PNG"));
		GetDstDcFromPic(&m_dcTempSet[i], &m_bmpTempSet[i]);
// 		str.Format(_T("时间1_%d.png"), i);
// 		LoadPicFromFile(str);
		LoadFromResource(MAKEINTRESOURCE(IDB_TIME0 + i), _T("PNG"));
		GetDstDcFromPic(&m_dcTimeShow[i], &m_bmpTimeShow[i]);
// 		str.Format(_T("时间2_%d.png"), i);
// 		LoadPicFromFile(str);
		LoadFromResource(MAKEINTRESOURCE(IDB_TIME_LIGHT0 + i), _T("PNG"));
		GetDstDcFromPic(&m_dcTimeSet[i], &m_bmpTimeSet[i]);
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
		AfxMessageBox(strPicPath + _T(" Load Error!"));
		PostMessage(WM_DESTROY);
	}
}
/** 从资源中载入图片*/
BOOL CAucma_HeaterDlg::LoadFromResource(LPCWSTR lpName, LPCWSTR lpType)  
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
	HRESULT hrt = NULL;
	if(FAILED(hrt = m_pImagingFactory->CreateImageFromBuffer(lp, dwsize, DISPOSAL_NONE, &m_pImage)))
	{
		::DeleteObject(hr);
		return FALSE;
	}
	::DeleteObject(hr);
	return TRUE;
}  

// 将图片复制到内存DC
void CAucma_HeaterDlg::GetDstDcFromPic(CDC* pDstDC, CBitmap* pBitmap)
{
	ImageInfo oImageInfo;
	m_pImage->GetImageInfo(&oImageInfo);
	//创建一个内存DC,用来存储图片数据
	pBitmap->CreateCompatibleBitmap(GetDC(), oImageInfo.Width,oImageInfo.Height);
	pDstDC->CreateCompatibleDC(GetDC());
	pDstDC->SelectObject(pBitmap);
	//将图片数据存储到内存DC中
	m_pImage->Draw(pDstDC->m_hDC ,CRect(0, 0, oImageInfo.Width, oImageInfo.Height), NULL);
	if (m_pImage)
	{
		m_pImage->Release();
		m_pImage = NULL;
	}
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
	m_oCEUart.ClosePort();
}
void CAucma_HeaterDlg::OnClickedHeatfast()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	CRect rect;
	if (m_iFastHeatState == NormalHeat)
	{
		m_iFastHeatState = FastHeat;
	}
	else if (m_iFastHeatState == FastHeat)
	{
		m_iFastHeatState = WinterHeat;
	}
	else if (m_iFastHeatState == WinterHeat)
	{
		m_iFastHeatState = NormalHeat;
	}
	InvalidateRect(m_rectHeatFastPic, FALSE);
	InvalidateRect(m_rectHeatFastText, FALSE);
	InvalidateRect(m_rectWinterPic, FALSE);
	InvalidateRect(m_rectWinterText, FALSE);
}

void CAucma_HeaterDlg::OnClickedHelper()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	m_bHelper = !m_bHelper;
	InvalidateRect(m_rectHelperPic, FALSE);
	InvalidateRect(m_rectHelperText, FALSE);
}

void CAucma_HeaterDlg::OnClickedWashhand()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	m_bWashHand = !m_bWashHand;
	InvalidateRect(m_rectWashHandPic, FALSE);
	InvalidateRect(m_rectWashHandText, FALSE);
}

void CAucma_HeaterDlg::OnClickedNight()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	m_bNight = !m_bNight;
	InvalidateRect(m_rectNightModePic, FALSE);
	InvalidateRect(m_rectNightModeText, FALSE);
}

void CAucma_HeaterDlg::OnClickedPower()
{
	// TODO: 在此添加控件通知处理程序代码
	BYTE buf[10];
	for (int i= 0;i<10; i++)
	{
		buf[i] = 0x33;
	}
	if (m_bPower == true)
	{
		KillTimer(ShowTempStateTimerEvent);
		m_iFastHeatState = NormalHeat;
		m_bHelper = false;
		m_bWashHand = false;
		m_bNight = false;
		m_iTempState = NoTempShow;
		m_bSetTemp = false;
		m_bSetTime = false;
		m_bPower = false;
		m_uiHeatCount = 0;
		m_iInTempSet = DefaultSetTemp;
		m_iInTempActual = 0;
		m_bTempHeat = false;
		Invalidate(FALSE);
	}
	else
	{
		KillTimer(ShowTempStateTimerEvent);
		SetTimer(ShowTempStateTimerEvent, ShowTempStateTimeSet, NULL);
		m_bPower = true;
		InvalidateRect(m_rectPowerPic, FALSE);
	}
}
// 得到当前温度
int CAucma_HeaterDlg::GetCurrTemp(void)
{
	return 87;
}
void CAucma_HeaterDlg::OnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	SYSTEMTIME sysTime;
	CTimeSpan time(60);
	if (m_uiContinuousCount == 0)
	{
		KillTimer(ContinuousOptTimerEvent);
		SetTimer(ContinuousOptTimerEvent, ContinuousOptTimeSet, NULL);
		m_bAddOpt = true;
	}
	if (m_bSetTemp == true)
	{
		m_iInTempSet++;
		if (m_iInTempSet == SetTempLimit)
		{
			m_iInTempSet = 0;
		}
		InvalidateRect(m_rectTemp, FALSE);
	}
	else if (m_bSetTime == true)
	{
		memset(&sysTime, 0 ,sizeof(SYSTEMTIME));
		m_CurrTime += time;
		sysTime.wYear = (WORD)m_CurrTime.GetYear();
		sysTime.wMonth = (WORD)m_CurrTime.GetMonth();
		sysTime.wDay = (WORD)m_CurrTime.GetDay();
		sysTime.wDayOfWeek = (WORD)m_CurrTime.GetDayOfWeek();
		sysTime.wHour = (WORD)m_CurrTime.GetHour();
		sysTime.wMinute = (WORD)m_CurrTime.GetMinute();
		sysTime.wSecond = (WORD)m_CurrTime.GetSecond();
		::SetLocalTime(&sysTime);
		InvalidateRect(m_rectTime, FALSE);
	}
}

void CAucma_HeaterDlg::OnClickedReduce()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	SYSTEMTIME sysTime;
	CTimeSpan time(-60);
	if (m_uiContinuousCount == 0)
	{
		KillTimer(ContinuousOptTimerEvent);
		SetTimer(ContinuousOptTimerEvent, ContinuousOptTimeSet, NULL);
		m_bAddOpt = false;
	}
	if (m_bSetTemp == true)
	{
		if (m_iInTempSet != 0)
		{
			m_iInTempSet--;
		}
		InvalidateRect(m_rectTemp, FALSE);
	}
	else if (m_bSetTime == true)
	{
		memset(&sysTime, 0 ,sizeof(SYSTEMTIME));
		m_CurrTime += time;
		sysTime.wYear = (WORD)m_CurrTime.GetYear();
		sysTime.wMonth = (WORD)m_CurrTime.GetMonth();
		sysTime.wDay = (WORD)m_CurrTime.GetDay();
		sysTime.wDayOfWeek = (WORD)m_CurrTime.GetDayOfWeek();
		sysTime.wHour = (WORD)m_CurrTime.GetHour();
		sysTime.wMinute = (WORD)m_CurrTime.GetMinute();
		sysTime.wSecond = (WORD)m_CurrTime.GetSecond();
		::SetLocalTime(&sysTime);
		InvalidateRect(m_rectTime, FALSE);
	}
}
// 设置温度
void CAucma_HeaterDlg::OnSetTemp(void)
{
	if ((m_bPower == false) || (m_bSetTime == true))
	{
		return;
	}
	m_bSetTemp = !m_bSetTemp;
	InvalidateRect(m_rectTemp, FALSE);
}

// 设置时间
void CAucma_HeaterDlg::OnSetTime(void)
{
	if ((m_bPower == false) || (m_bSetTemp == true))
	{
		return;
	}
	m_bSetTime = !m_bSetTime;
	InvalidateRect(m_rectTime, FALSE);
}
// 鼠标左键单击坐标在所选区域内
bool CAucma_HeaterDlg::OnPointInRect(CRect rect, CPoint point)
{
	if ((rect.left <= point.x) && (rect.right >= point.x)
		&& (rect.top <= point.y) && (rect.bottom >= point.y))
	{
		return true;
	}
	return false;
}
void CAucma_HeaterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 判断点击速热引擎
	if ((true == OnPointInRect(m_rectHeatFastPic, point))
		|| (true == OnPointInRect(m_rectHeatFastText, point)))
	{
		OnClickedHeatfast();
	}
	else if ((true == OnPointInRect(m_rectHelperPic, point))
		|| (true == OnPointInRect(m_rectHelperText, point)))
	{
		OnClickedHelper();
	}
	else if ((true == OnPointInRect(m_rectWashHandPic, point))
		|| (true == OnPointInRect(m_rectWashHandText, point)))
	{
		OnClickedWashhand();
	}
	else if ((true == OnPointInRect(m_rectNightModePic, point))
		|| (true == OnPointInRect(m_rectNightModeText, point)))
	{
		OnClickedNight();
	}
	else if (true == OnPointInRect(m_rectPowerPic, point))
	{
		OnClickedPower();
	}
	else if (true == OnPointInRect(m_rectTemp, point))
	{
		OnSetTemp();
	}
	else if (true == OnPointInRect(m_rectTime, point))
	{
		OnSetTime();
	}
	else if (true == OnPointInRect(m_rectAdd, point))
	{
		OnClickedAdd();
	}
	else if (true == OnPointInRect(m_rectReduce, point))
	{
		OnClickedReduce();
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CAucma_HeaterDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(ContinuousOptTimerEvent);
	m_uiContinuousCount = 0;
	CDialog::OnLButtonUp(nFlags, point);
}
// 将位图选入内存设备
void CAucma_HeaterDlg::OnDcBitBlt(CDC* pDstDC, CDC* pSrcDC, CRect rect, bool bTransparent)
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
			dc.ExtTextOut(m_rectHeatFastText.left + TextOutMovePos1, m_rectHeatFastText.top, ETO_OPAQUE, NULL, _T("速热引擎"), NULL);
			dc.SelectObject(&m_FontWinter);
			dc.ExtTextOut(m_rectWinterText.left + TextOutMovePos2, m_rectWinterText.top, ETO_OPAQUE, NULL, _T("冬天"), NULL);
			dc.SelectObject(&m_FontDefault);
		}
		else if (m_iFastHeatState == FastHeat)
		{
			OnDcBitBlt(&dc, &m_dcHeatFastOn, m_rectHeatFastPic);
			OnDcBitBlt(&dc, &m_dcWinterOff, m_rectWinterPic);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectHeatFastText.left + TextOutMovePos1, m_rectHeatFastText.top, ETO_OPAQUE, NULL, _T("速热引擎"), NULL);
			dc.SetTextColor(DefaultTextColor);
			dc.SelectObject(&m_FontWinter);
			dc.ExtTextOut(m_rectWinterText.left + TextOutMovePos2, m_rectWinterText.top, ETO_OPAQUE, NULL, _T("冬天"), NULL);
			dc.SelectObject(&m_FontDefault);
		}
		else if (m_iFastHeatState == WinterHeat)
		{
			OnDcBitBlt(&dc, &m_dcHeatFastOn, m_rectHeatFastPic);
			OnDcBitBlt(&dc, &m_dcWinterOn, m_rectWinterPic);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectHeatFastText.left + TextOutMovePos1, m_rectHeatFastText.top, ETO_OPAQUE, NULL, _T("速热引擎"), NULL);
			dc.SelectObject(&m_FontWinter);
			dc.ExtTextOut(m_rectWinterText.left + TextOutMovePos2, m_rectWinterText.top, ETO_OPAQUE, NULL, _T("冬天"), NULL);
			dc.SelectObject(&m_FontDefault);
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
		dc.ExtTextOut(m_rectHelperText.left + TextOutMovePos1, m_rectHelperText.top, ETO_OPAQUE, NULL, _T("智能助手"), NULL);
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
		dc.ExtTextOut(m_rectWashHandText.left + TextOutMovePos1, m_rectWashHandText.top, ETO_OPAQUE, NULL, _T("洗手加热"), NULL);
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
		dc.ExtTextOut(m_rectNightModeText.left + TextOutMovePos1, m_rectNightModeText.top, ETO_OPAQUE, NULL, _T("夜电模式"), NULL);
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
		dc.SelectObject(&m_FontTemp);
		dc.ExtTextOut(m_rectTempLabelText.left, m_rectTempLabelText.top, ETO_OPAQUE, NULL, _T("℃"), NULL);
		dc.SelectObject(&m_FontDefault);
		m_bTempLabelOld = m_bTempLabel;
	}
	if ((m_iInTempSetOld != m_iInTempSet) || (m_bSetTempOld != m_bSetTemp))
	{
		if (m_bSetTemp == true)
		{
			OnDcBitBlt(&dc, &m_dcTempSet[m_iInTempSet / 10], m_rectTempHighPic);
			OnDcBitBlt(&dc, &m_dcTempSet[m_iInTempSet % 10], m_rectTempLowPic);
		}
		else
		{
			OnDcBitBlt(&dc, &m_dcTempShow[m_iInTempSet / 10], m_rectTempHighPic);
			OnDcBitBlt(&dc, &m_dcTempShow[m_iInTempSet % 10], m_rectTempLowPic);
		}
		m_iInTempSetOld = m_iInTempSet;
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
	if (nIDEvent == ShowTempStateTimerEvent)
	{
		m_iInTempActual = GetCurrTemp();
		if (m_iInTempActual >= m_iInTempSet)
		{
			// 保温
			if (m_iTempState != InsulationState)
			{
				m_iTempState = InsulationState;
				InvalidateRect(m_rectTempPic, FALSE);
				InvalidateRect(m_rectTempInsulationText, FALSE);
				InvalidateRect(m_rectTempHeatText, FALSE);
			}
			m_bTempHeat = false;
		}
		else
		{
			// 加热
			if (m_iTempState != HeatTempState)
			{
				m_iTempState = HeatTempState;
				m_uiHeatCount = 0;
				InvalidateRect(m_rectTempInsulationText, FALSE);
				InvalidateRect(m_rectTempHeatText, FALSE);
			}
		}
		if (m_iTempState == HeatTempState)
		{
			if (m_uiHeatCount == 0)
			{
				m_uiHeatCount = 1;
			}
			else if (m_uiHeatCount == 1)
			{
				m_uiHeatCount = 2;
			}
			else if (m_uiHeatCount == 2)
			{
				m_uiHeatCount = 0;
			}
			m_bTempHeat = true;
			InvalidateRect(m_rectTempPic, FALSE);
		}
	}
	else if (nIDEvent == ShowTimeTimerEvent)
	{
		m_CurrTime = CTime::GetCurrentTime();
		InvalidateRect(m_rectTime, FALSE);
	}
	else if (nIDEvent == ContinuousOptTimerEvent)
	{
		m_uiContinuousCount++;
		if (m_uiContinuousCount > ContinuousOptTimes)
		{
			if (m_bAddOpt == true)
			{
				OnClickedAdd();
			}
			else
			{
				OnClickedReduce();
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}
// 串口接收数据回调函数
void CALLBACK CAucma_HeaterDlg::OnUartRead(void* pFatherPtr, BYTE* pbuf, DWORD dwbufLen)
{
	BYTE* pRecBuf = NULL;
	// 得到父对象指针
	CAucma_HeaterDlg* pThis = (CAucma_HeaterDlg*)pFatherPtr;
	pRecBuf = new BYTE[dwbufLen];
	CopyMemory(pRecBuf, pbuf, dwbufLen);
	pThis->PostMessage(WM_RECV_UART_DATA, WPARAM(pRecBuf), dwbufLen);
}
// 串口接收数据处理
LRESULT CAucma_HeaterDlg::OnRecvUartData(WPARAM wParam, LPARAM lParam)
{
	// 串口接收到的BUF
	BYTE* pBuf = (BYTE*)wParam;
	// 串口接收到的Buf长度
	DWORD dwBufLen = lParam;
	//数据处理
	for (unsigned int i=0; i<dwBufLen; i++)
	{
		switch(m_uiUartRcvCount)
		{
		case 0:
			if (pBuf[i] == UartFrameHead1)
			{
				m_ucRcvBuf[0] = pBuf[i];
				m_uiUartRcvCount++;
			}
			else
			{
				m_uiUartRcvCount = 0;
			}
			break;
		case 1:
			if (pBuf[i] == UartFrameHead2)
			{
				m_ucRcvBuf[1] = pBuf[i];
				m_uiUartRcvCount++;
			}
			else
			{
				m_uiUartRcvCount = 0;
			}
			break;
		case 2:
			m_ucRcvBuf[2] = pBuf[i];
			m_byCheck = pBuf[i];
			m_uiUartRcvCount++;
			break;
		case 3:
			m_ucRcvBuf[3] = pBuf[i];
			m_byCheck ^= pBuf[i];
			m_uiUartRcvCount++;
			break;
		case 4:
			m_ucRcvBuf[4] = pBuf[i];
			m_byCheck ^= pBuf[i];
			m_uiUartRcvCount++;
			break;
		case 5:
			if (pBuf[i] == m_byCheck)
			{
				m_ucRcvBuf[5] = pBuf[i];
				m_uiUartRcvCount++;
			}
			else
			{
				m_uiUartRcvCount = 0;
			}
			break;
		case 6:
			if (pBuf[i] == UartFrameTail)
			{
				m_ucRcvBuf[6] = pBuf[i];
				// 解析帧
				PhraseUartFrame();
				memset(m_ucRcvBuf, 0, sizeof(m_ucRcvBuf));
			}
			m_uiUartRcvCount = 0;
			break;
		default:
			m_uiUartRcvCount = 0;
			break;
		}
	}
	delete[] pBuf;
	pBuf = NULL;
	return 0;
}
// 向串口发送数据
void CAucma_HeaterDlg::OnWriteUartData(BYTE ucCmd, BYTE ucData)
{
	BYTE buf[UartFrameLength];
	buf[0] = UartFrameHead1;
	buf[1] = UartFrameHead2;
	buf[2] = ClientNo;
	buf[3] = ucCmd;
	buf[4] = ucData;
	buf[5] = buf[2] ^ buf[3] ^ buf[4];
	buf[6] = UartFrameTail;
	m_oCEUart.WriteSyncPort(buf, UartFrameLength);
}

// 解析串口接收数据帧
void CAucma_HeaterDlg::PhraseUartFrame()
{
	BYTE byCmd = m_ucRcvBuf[3];
	BYTE byData = m_ucRcvBuf[4];
	switch(byCmd)
	{
	case CMD_IHMT_CTRL:
		if (byData == CMD_IHMT_OFF)
		{
			TRACE(_T("关闭 LCD背光\n"));
		}
		else if (byData == CMD_IHMT_ON)
		{
			TRACE(_T("打开 LCD背光\n"));
		}
		break;
	case CMD_IHMT_RST:
		TRACE(_T("复位触摸屏\n"));
		break;
	case CMD_DOWN_ET:
		m_iEnvTempActual = (unsigned int)byData - 127;
		TRACE(_T("实际环境温度 %d \n"), m_iEnvTempActual);
		break;
	case CMD_DOWN_IT:
		m_iInTempActual = (unsigned int)byData - 127;
		TRACE(_T("实际箱内温度 %d \n"), m_iInTempActual);
		break;
	case CMD_DOWN_AM:
		if (byData == CMD_DOWN_HAM)
		{
			TRACE(_T("高温报警\n"));
		}
		else if (byData == CMD_DOWN_LAM)
		{
			TRACE(_T("低温报警\n"));
		}
		else if (byData == CMD_DOWN_HAMC)
		{
			TRACE(_T("高温报警消除\n"));
		}
		else if (byData == CMD_DOWN_LAMC)
		{
			TRACE(_T("低温报警消除\n"));
		}
		break;
	default:
		break;
	}
	// @@@调试用
//	m_oCEUart.WriteSyncPort(m_ucRcvBuf, UartFrameLength);
}