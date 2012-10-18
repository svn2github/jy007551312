// Aucma_HeaterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Aucma_Heater.h"
#include "Aucma_HeaterDlg.h"
#include "Parameter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAucma_HeaterDlg 对话框

CAucma_HeaterDlg::CAucma_HeaterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAucma_HeaterDlg::IDD, pParent)
	, m_bHeatFast(false)
	, m_bWinter(false)
	, m_bHelper(false)
	, m_bWashHand(false)
	, m_iFastHeatState(NormalHeat)
	, m_bNight(false)
	, m_bTempInsulation(false)
	, m_bTempHeat(false)
	, m_iTempState(NoTempShow)
	, m_bPower(false)
	, m_uiHeatCount(0)
	, m_iSetTemp(0)
	, m_iCurrTemp(0)
	, m_bSetTemp(false)
	, m_bSetTime(false)
	, m_CurrTime(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAucma_HeaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HEATFAST, m_ctrlHeatFast);
	DDX_Control(pDX, IDC_STATIC_HEATFAST, m_staticHeatFast);
	DDX_Control(pDX, IDC_WINTER, m_ctrlWinter);
	DDX_Control(pDX, IDC_STATIC_WINTER, m_staticWinter);
	DDX_Control(pDX, IDC_HELPER, m_ctrlHelper);
	DDX_Control(pDX, IDC_STATIC_HELPER, m_staticHelper);
	DDX_Control(pDX, IDC_WASHHAND, m_ctrlWashHand);
	DDX_Control(pDX, IDC_STATIC_WASHHAND, m_staticWashHand);
	DDX_Control(pDX, IDC_NIGHT, m_ctrlNightMode);
	DDX_Control(pDX, IDC_STATIC_NIGHT, m_staticNightMode);
	DDX_Control(pDX, IDC_TEMP, m_ctrlTemp);
	DDX_Control(pDX, IDC_STATIC_TEMP_INSULATION, m_staticTempInsulation);
	DDX_Control(pDX, IDC_STATIC_TEMP_HEAT, m_staticTempHeat);
	DDX_Control(pDX, IDC_POWER, m_ctrlPower);
	DDX_Control(pDX, IDC_STATIC_TEMP, m_staticTempLabel);
	DDX_Control(pDX, IDC_TEMP_HIGH, m_ctrlTempHigh);
	DDX_Control(pDX, IDC_TEMP_LOW, m_ctrlTempLow);
	DDX_Control(pDX, IDC_HOUR_HIGH, m_ctrlHourHigh);
	DDX_Control(pDX, IDC_HOUR_LOW, m_ctrlHourLow);
	DDX_Control(pDX, IDC_TIME_LABEL, m_ctrlTimeLabel);
	DDX_Control(pDX, IDC_MIN_HIGH, m_ctrlMinHigh);
	DDX_Control(pDX, IDC_MIN_LOW, m_ctrlMinLow);
}

BEGIN_MESSAGE_MAP(CAucma_HeaterDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_HEATFAST, &CAucma_HeaterDlg::OnStnClickedHeatfast)
	ON_STN_CLICKED(IDC_HELPER, &CAucma_HeaterDlg::OnStnClickedHelper)
	ON_STN_CLICKED(IDC_WASHHAND, &CAucma_HeaterDlg::OnStnClickedWashhand)
	ON_WM_DESTROY()
	ON_STN_CLICKED(IDC_NIGHT, &CAucma_HeaterDlg::OnStnClickedNight)
	ON_STN_CLICKED(IDC_POWER, &CAucma_HeaterDlg::OnStnClickedPower)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_TEMP_HIGH, &CAucma_HeaterDlg::OnStnClickedTempHigh)
	ON_STN_CLICKED(IDC_TEMP_LOW, &CAucma_HeaterDlg::OnStnClickedTempLow)
	ON_BN_CLICKED(IDC_BTN_ADD, &CAucma_HeaterDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_REDUCE, &CAucma_HeaterDlg::OnBnClickedBtnReduce)
	ON_STN_CLICKED(IDC_HOUR_HIGH, &CAucma_HeaterDlg::OnStnClickedHourHigh)
	ON_STN_CLICKED(IDC_HOUR_LOW, &CAucma_HeaterDlg::OnStnClickedHourLow)
	ON_STN_CLICKED(IDC_TIME_LABEL, &CAucma_HeaterDlg::OnStnClickedTimeLabel)
	ON_STN_CLICKED(IDC_MIN_HIGH, &CAucma_HeaterDlg::OnStnClickedMinHigh)
	ON_STN_CLICKED(IDC_MIN_LOW, &CAucma_HeaterDlg::OnStnClickedMinLow)
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
	// 载入图标到图片句柄
	m_hbmpHeatFastOn = LoadBitMap(MAKEINTRESOURCE(IDB_HEATFAST_ON));
	m_hbmpHeatFastOff = LoadBitMap(MAKEINTRESOURCE(IDB_HEATFAST_OFF));
	m_hbmpWinterOn = LoadBitMap(MAKEINTRESOURCE(IDB_WINTER_ON));
	m_hbmpWinterOff = LoadBitMap(MAKEINTRESOURCE(IDB_WINTER_OFF));
	m_hbmpHelperOn = LoadBitMap(MAKEINTRESOURCE(IDB_HELPER_ON));
	m_hbmpHelperOff = LoadBitMap(MAKEINTRESOURCE(IDB_HELPER_OFF));
	m_hbmpWashHandOn = LoadBitMap(MAKEINTRESOURCE(IDB_WASHHAND_ON));
	m_hbmpWashHandOff = LoadBitMap(MAKEINTRESOURCE(IDB_WASHHAND_OFF));
	m_hbmpNightModeOn = LoadBitMap(MAKEINTRESOURCE(IDB_NIGHT_ON));
	m_hbmpNightModeOff = LoadBitMap(MAKEINTRESOURCE(IDB_NIGHT_OFF));
	m_hbmpTempOff = LoadBitMap(MAKEINTRESOURCE(IDB_TEMP_OFF));
	m_hbmpTempInsulation = LoadBitMap(MAKEINTRESOURCE(IDB_TEMP_INSULATION));
	m_hbmpTempHeat1 = LoadBitMap(MAKEINTRESOURCE(IDB_TEMP_HEAT_1));
	m_hbmpTempHeat2 = LoadBitMap(MAKEINTRESOURCE(IDB_TEMP_HEAT_2));
	m_hbmpTempHeat3 = LoadBitMap(MAKEINTRESOURCE(IDB_TEMP_HEAT_3));
	m_hbmpPowerOn = LoadBitMap(MAKEINTRESOURCE(IDB_POWER_ON));
	m_hbmpPowerOff = LoadBitMap(MAKEINTRESOURCE(IDB_POWER_OFF));
	for (int i=0; i<10; i++)
	{
		m_hbmpTempShow[i] = LoadBitMap(MAKEINTRESOURCE(IDB_TEMP_0 + i));
		m_hbmpTempSet[i] = LoadBitMap(MAKEINTRESOURCE(IDB_TEMP_LIGHT_0 + i));
		m_hbmpTimeShow[i] = LoadBitMap(MAKEINTRESOURCE(IDB_TIME_0 + i));
		m_hbmpTimeSet[i] = LoadBitMap(MAKEINTRESOURCE(IDB_TIME_LIGHT_0 + i));
	}
	// 创建背景刷子
	m_brushBk.CreateSolidBrush(DialogBkColor);
	// 对话框最大化显示
	ShowWindow(SW_SHOWMAXIMIZED);
	m_ctrlHeatFast.MoveWindow(40, 10, 48, 48);
	m_staticHeatFast.MoveWindow(40, 58, 48, 14);
	m_ctrlWinter.MoveWindow(92, 34, 24, 24);

	LOGFONT   logFont;
	CFont* pFont = NULL;
// 	m_FontWinter.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,
// 		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
// 	 	DEFAULT_PITCH&FF_SWISS, _T("MS Sans Serif"));
	pFont = m_staticWinter.GetFont();
	memset(&logFont, 0, sizeof(LOGFONT));
	pFont->GetLogFont(&logFont);
	logFont.lfHeight = logFont.lfHeight * 6 / 7;
	VERIFY(m_FontWinter.CreateFontIndirect(&logFont));
	m_staticWinter.SetFont(&m_FontWinter);
	m_staticWinter.MoveWindow(92, 58, 24, 12);
	m_ctrlHelper.MoveWindow(40, 82, 48, 48);
	m_staticHelper.MoveWindow(40, 130, 48, 14);
	m_ctrlWashHand.MoveWindow(40, 154, 48, 48);
	m_staticWashHand.MoveWindow(40, 202, 48, 14);
	m_ctrlNightMode.MoveWindow(390, 10, 48, 48);
	m_staticNightMode.MoveWindow(390, 58, 48, 14);
	m_ctrlTemp.MoveWindow(402, 82, 24, 48);
	m_staticTempInsulation.MoveWindow(384, 130, 24, 14);
	m_staticTempHeat.MoveWindow(420, 130, 24, 14);
	m_ctrlPower.MoveWindow(390, 160, 48, 48);
 	m_ctrlTempHigh.MoveWindow(179, 10, 72, 108);
 	m_ctrlTempLow.MoveWindow(255, 10, 72, 108);
// 	m_FontTemp.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,
// 		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
// 		DEFAULT_PITCH&FF_SWISS, _T("MS Sans Serif"));
	pFont = m_staticTempLabel.GetFont();
	memset(&logFont, 0, sizeof(LOGFONT));
	pFont->GetLogFont(&logFont);
	logFont.lfHeight = logFont.lfHeight * 3 / 2;
	VERIFY(m_FontTemp.CreateFontIndirect(&logFont));

	m_staticTempLabel.SetFont(&m_FontTemp);
	m_staticTempLabel.MoveWindow(327, 10, 20, 20);
	m_staticTempLabel.Invalidate(FALSE);
	m_bmpBtnAdd.LoadBitmaps(IDB_ADD,IDB_ADD,0,0);
	m_bmpBtnAdd.SubclassDlgItem(IDC_BTN_ADD,this);
	m_bmpBtnAdd.SizeToContent();
	m_bmpBtnAdd.MoveWindow(227, 122, 24, 24);
	m_bmpBtnReduce.LoadBitmaps(IDB_REDUCE,IDB_REDUCE,0,0);
	m_bmpBtnReduce.SubclassDlgItem(IDC_BTN_REDUCE,this);
	m_bmpBtnReduce.SizeToContent();
	m_bmpBtnReduce.MoveWindow(255, 122, 24, 24);
	m_ctrlTimeLabel.MoveWindow(245, 154, 16, 48);
	m_ctrlHourHigh.MoveWindow(179, 154, 32, 48);
	m_ctrlHourLow.MoveWindow(213, 154, 32, 48);
	m_ctrlMinHigh.MoveWindow(261, 154, 32, 48);
	m_ctrlMinLow.MoveWindow(295, 154, 32, 48);
	m_CurrTime = CTime::GetCurrentTime();
	OnShowTime(m_CurrTime, false);
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


HBRUSH CAucma_HeaterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何属性
	if (nCtlColor != CTLCOLOR_STATIC)
	{
		return m_brushBk;
	}
	int Id = pWnd->GetDlgCtrlID();
	if (Id == IDC_STATIC_HEATFAST)
	{
		SetTextHighLighted(pDC, m_bHeatFast);
	}
	else if (Id == IDC_STATIC_WINTER)
	{
		SetTextHighLighted(pDC, m_bWinter);
	}
	else if (Id == IDC_STATIC_HELPER)
	{
		SetTextHighLighted(pDC, m_bHelper);
	}
	else if (Id == IDC_STATIC_WASHHAND)
	{
		SetTextHighLighted(pDC, m_bWashHand);
	}
	else if (Id == IDC_STATIC_NIGHT)
	{
		SetTextHighLighted(pDC, m_bNight);
	}
	else if (Id == IDC_STATIC_TEMP_INSULATION)
	{
		SetTextHighLighted(pDC, m_bTempInsulation);
	}
	else if (Id == IDC_STATIC_TEMP_HEAT)
	{
		SetTextHighLighted(pDC, m_bTempHeat);
	}
	else if (Id == IDC_STATIC_TEMP)
	{
		SetTextHighLighted(pDC, false);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brushBk;
}

// 图片和文字显示函数
void CAucma_HeaterDlg::OnPictureShow()
{
	if (m_iFastHeatState == NormalHeat)
	{
		m_bHeatFast = false;
		m_bWinter = false;
		OnSelectBitMap(&m_ctrlHeatFast, m_hbmpHeatFastOff);
		OnSelectBitMap(&m_ctrlWinter, m_hbmpWinterOff);
	}
	else if (m_iFastHeatState == FastHeat)
	{
		m_bHeatFast = true;
		m_bWinter = false;
		OnSelectBitMap(&m_ctrlHeatFast, m_hbmpHeatFastOn);
		OnSelectBitMap(&m_ctrlWinter, m_hbmpWinterOff);
	}
	else if (m_iFastHeatState == WinterHeat)
	{
		m_bHeatFast = true;
		m_bWinter = true;
		OnSelectBitMap(&m_ctrlHeatFast, m_hbmpHeatFastOn);
		OnSelectBitMap(&m_ctrlWinter, m_hbmpWinterOn);
	}
	m_staticHeatFast.Invalidate(FALSE);
	m_staticWinter.Invalidate(FALSE);
	if (m_bHelper == true)
	{
		OnSelectBitMap(&m_ctrlHelper, m_hbmpHelperOn);
	}
	else
	{
		OnSelectBitMap(&m_ctrlHelper, m_hbmpHelperOff);
	}
	m_staticHelper.Invalidate(FALSE);
	if (m_bWashHand == true)
	{
		OnSelectBitMap(&m_ctrlWashHand, m_hbmpWashHandOn);
	}
	else
	{
		OnSelectBitMap(&m_ctrlWashHand, m_hbmpWashHandOff);
	}
	m_staticWashHand.Invalidate(FALSE);
	if (m_bNight == true)
	{
		OnSelectBitMap(&m_ctrlNightMode, m_hbmpNightModeOn);
	}
	else
	{
		OnSelectBitMap(&m_ctrlNightMode, m_hbmpNightModeOff);
	}
	m_staticNightMode.Invalidate(FALSE);
	if (m_iTempState == NoTempShow)
	{
		m_bTempInsulation = false;
		m_bTempHeat = false;
		OnSelectBitMap(&m_ctrlTemp, m_hbmpTempOff);
		m_staticTempInsulation.Invalidate(FALSE);
		m_staticTempHeat.Invalidate(FALSE);
	}
	if (m_bPower == true)
	{
		OnSelectBitMap(&m_ctrlPower, m_hbmpPowerOn);
	}
	else
	{
		OnSelectBitMap(&m_ctrlPower, m_hbmpPowerOff);
	}
}

void CAucma_HeaterDlg::OnStnClickedHeatfast()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
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
	OnPictureShow();
}

void CAucma_HeaterDlg::OnStnClickedHelper()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	m_bHelper = !m_bHelper;
	OnPictureShow();
}

void CAucma_HeaterDlg::OnStnClickedWashhand()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	m_bWashHand = !m_bWashHand;
	OnPictureShow();
}

void CAucma_HeaterDlg::OnStnClickedNight()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	m_bNight = !m_bNight;
	OnPictureShow();
}

void CAucma_HeaterDlg::OnStnClickedPower()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == true)
	{
		m_iFastHeatState = NormalHeat;
		m_bHelper = false;
		m_bWashHand = false;
		m_bNight = false;
		KillTimer(ShowTempStateTimerEvent);
		m_iTempState = NoTempShow;
		m_bSetTemp = false;
		m_bSetTime = false;
		OnShowTemp(88, m_bSetTemp);
		OnShowTime(m_CurrTime, m_bSetTime);
		m_bPower = false;
	}
	else
	{
		KillTimer(ShowTempStateTimerEvent);
		SetTimer(ShowTempStateTimerEvent, ShowTempStateTimeSet, NULL);
		m_bPower = true;
		OnShowTemp(m_iSetTemp, false);
	}
	OnPictureShow();
}
void CAucma_HeaterDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	m_brushBk.DeleteObject();
	m_FontWinter.DeleteObject();
	m_FontTemp.DeleteObject();
}

// 载入图片到图片句柄
HBITMAP CAucma_HeaterDlg::LoadBitMap(LPCTSTR lpszName)
{
	return (HBITMAP) ::LoadImage (AfxGetResourceHandle(), lpszName, IMAGE_BITMAP, 0, 0, 0);
}

// 设置文本高亮显示
void CAucma_HeaterDlg::SetTextHighLighted(CDC* pDC, bool bHighLight)
{
	if (bHighLight == true)
	{
		pDC->SetTextColor(SelectTextColor);
	}
	else
	{
		pDC->SetTextColor(DefaultTextColor);
	}
}

void CAucma_HeaterDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == ShowTempStateTimerEvent)
	{
		m_iCurrTemp = GetCurrTemp();
		if (m_iCurrTemp >= m_iSetTemp)
		{
			// 保温
			if (m_iTempState != InsulationState)
			{
				m_iTempState = InsulationState;
				m_bTempInsulation = true;
				m_bTempHeat = false;
				OnSelectBitMap(&m_ctrlTemp, m_hbmpTempInsulation);
				m_staticTempInsulation.Invalidate(FALSE);
				m_staticTempHeat.Invalidate(FALSE);
			}
		}
		else
		{
			// 加热
			if (m_iTempState != HeatTempState)
			{
				m_iTempState = HeatTempState;
				m_bTempInsulation = false;
				m_bTempHeat = true;
				m_uiHeatCount = 0;
				m_staticTempInsulation.Invalidate(FALSE);
				m_staticTempHeat.Invalidate(FALSE);
			}
		}
		if (m_iTempState == HeatTempState)
		{
			if (m_uiHeatCount == 0)
			{
				OnSelectBitMap(&m_ctrlTemp, m_hbmpTempHeat1);
				m_uiHeatCount = 1;
			}
			else if (m_uiHeatCount == 1)
			{
				OnSelectBitMap(&m_ctrlTemp, m_hbmpTempHeat2);
				m_uiHeatCount = 2;
			}
			else if (m_uiHeatCount == 2)
			{
				OnSelectBitMap(&m_ctrlTemp, m_hbmpTempHeat3);
				m_uiHeatCount = 0;
			}
		}
	}
	else if (nIDEvent == ShowTimeTimerEvent)
	{
		m_CurrTime = CTime::GetCurrentTime();
		OnShowTime(m_CurrTime, m_bSetTime);
	}
	CDialog::OnTimer(nIDEvent);
}

// 得到当前温度
int CAucma_HeaterDlg::GetCurrTemp(void)
{
	return 20;
}

// 显示温度
void CAucma_HeaterDlg::OnShowTemp(unsigned int uiTemp, bool bLight)
{
	unsigned int uiHigh = 0;
	unsigned int uiLow = 0;
	uiHigh = uiTemp / 10;
	uiLow = uiTemp % 10;
	if (bLight == false)
	{
		OnSelectBitMap(&m_ctrlTempHigh, m_hbmpTempShow[uiHigh]);
		OnSelectBitMap(&m_ctrlTempLow, m_hbmpTempShow[uiLow]);
	}
	else
	{
		OnSelectBitMap(&m_ctrlTempHigh, m_hbmpTempSet[uiHigh]);
		OnSelectBitMap(&m_ctrlTempLow, m_hbmpTempSet[uiLow]);
	}
}

// 静态控件选择图片
void CAucma_HeaterDlg::OnSelectBitMap(CStatic* pStatic, HBITMAP hBitMap)
{
	if (hBitMap != pStatic->GetBitmap())
	{
		pStatic->SetBitmap(hBitMap);
		pStatic->Invalidate(FALSE);
	}
}

void CAucma_HeaterDlg::OnStnClickedTempHigh()
{
	// TODO: 在此添加控件通知处理程序代码
	OnSetTemp();
}

void CAucma_HeaterDlg::OnStnClickedTempLow()
{
	// TODO: 在此添加控件通知处理程序代码
	OnSetTemp();
}

void CAucma_HeaterDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	SYSTEMTIME sysTime;
	CTimeSpan time(60);
	if (m_bSetTemp == true)
	{
		m_iSetTemp++;
		if (m_iSetTemp == 100)
		{
			m_iSetTemp = 0;
		}
		OnShowTemp(m_iSetTemp, true);
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
		OnShowTime(m_CurrTime, true);
	}
}

void CAucma_HeaterDlg::OnBnClickedBtnReduce()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	SYSTEMTIME sysTime;
	CTimeSpan time(-60);
	if (m_bSetTemp == true)
	{
		if (m_iSetTemp != 0)
		{
			m_iSetTemp--;
		}
		OnShowTemp(m_iSetTemp, true);
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
		OnShowTime(m_CurrTime, true);
	}
}

void CAucma_HeaterDlg::OnStnClickedHourHigh()
{
	// TODO: 在此添加控件通知处理程序代码
	OnSetTime();
}

void CAucma_HeaterDlg::OnStnClickedHourLow()
{
	// TODO: 在此添加控件通知处理程序代码
	OnSetTime();
}

void CAucma_HeaterDlg::OnStnClickedTimeLabel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnSetTime();
}

void CAucma_HeaterDlg::OnStnClickedMinHigh()
{
	// TODO: 在此添加控件通知处理程序代码
	OnSetTime();
}

void CAucma_HeaterDlg::OnStnClickedMinLow()
{
	// TODO: 在此添加控件通知处理程序代码
	OnSetTime();
}

// 显示当前时间
void CAucma_HeaterDlg::OnShowTime(CTime time, bool bLight)
{
	int iHour = time.GetHour();
	int iMin = time.GetMinute();
	if (bLight == false)
	{
		OnSelectBitMap(&m_ctrlHourHigh, m_hbmpTimeShow[iHour / 10]);
		OnSelectBitMap(&m_ctrlHourLow, m_hbmpTimeShow[iHour % 10]);
		OnSelectBitMap(&m_ctrlMinHigh, m_hbmpTimeShow[iMin / 10]);
		OnSelectBitMap(&m_ctrlMinLow, m_hbmpTimeShow[iMin % 10]);
	}
	else
	{
		OnSelectBitMap(&m_ctrlHourHigh, m_hbmpTimeSet[iHour / 10]);
		OnSelectBitMap(&m_ctrlHourLow, m_hbmpTimeSet[iHour % 10]);
		OnSelectBitMap(&m_ctrlMinHigh, m_hbmpTimeSet[iMin / 10]);
		OnSelectBitMap(&m_ctrlMinLow, m_hbmpTimeSet[iMin % 10]);
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
	OnShowTemp(m_iSetTemp, m_bSetTemp);
}

// 设置时间
void CAucma_HeaterDlg::OnSetTime(void)
{
	if ((m_bPower == false) || (m_bSetTemp == true))
	{
		return;
	}
	m_bSetTime = !m_bSetTime;
	OnShowTime(m_CurrTime, m_bSetTime);
}
