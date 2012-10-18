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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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
	m_bmpHeatFastOn.LoadBitmap(IDB_HEATFAST_ON);
	m_bmpHeatFastOff.LoadBitmap(IDB_HEATFAST_OFF);
	m_bmpWinterOn.LoadBitmap(IDB_WINTER_ON);
	m_bmpWinterOff.LoadBitmap(IDB_WINTER_OFF);
	m_bmpHelperOn.LoadBitmap(IDB_HELPER_ON);
	m_bmpHelperOff.LoadBitmap(IDB_HELPER_OFF);
	m_bmpWashHandOn.LoadBitmap(IDB_WASHHAND_ON);
	m_bmpWashHandOff.LoadBitmap(IDB_WASHHAND_OFF);
	m_bmpNightModeOn.LoadBitmap(IDB_NIGHT_ON);
	m_bmpNightModeOff.LoadBitmap(IDB_NIGHT_OFF);
	m_bmpTempOff.LoadBitmap(IDB_TEMP_OFF);
	m_bmpTempInsulation.LoadBitmap(IDB_TEMP_INSULATION);
	m_bmpTempHeat1.LoadBitmap(IDB_TEMP_HEAT_1);
	m_bmpTempHeat2.LoadBitmap(IDB_TEMP_HEAT_2);
	m_bmpTempHeat3.LoadBitmap(IDB_TEMP_HEAT_3);
	m_bmpPowerOn.LoadBitmap(IDB_POWER_ON);
	m_bmpPowerOff.LoadBitmap(IDB_POWER_OFF);
	for (int i=0; i<10; i++)
	{
		m_bmpTempShow[i].LoadBitmap(IDB_TEMP_0 + i);
		m_bmpTempSet[i].LoadBitmap(IDB_TEMP_LIGHT_0 + i);
		m_bmpTimeShow[i].LoadBitmap(IDB_TIME_0 + i);
		m_bmpTimeSet[i].LoadBitmap(IDB_TIME_LIGHT_0 + i);
	}
	m_bmpAdd.LoadBitmap(IDB_ADD);
	m_bmpReduce.LoadBitmap(IDB_REDUCE);
	m_bmpTimeLabel.LoadBitmap(IDB_TIME_LABEL);
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
	
	CRect rect;
	GetClientRect(rect);
	m_rectHeatFastPic = OnSetRect(40, 10, 48, 48);
	m_rectHeatFastText = OnSetRect(40, 58, 48, 14);
	m_rectWinterPic = OnSetRect(92, 34, 24, 24);
	m_rectWinterText = OnSetRect(92, 58, 24, 12);
	m_rectHelperPic = OnSetRect(40, 82, 48, 48);
	m_rectHelperText = OnSetRect(40, 130, 48, 14);
	m_rectWashHandPic = OnSetRect(40, 154, 48, 48);
	m_rectWashHandText = OnSetRect(40, 202, 48, 14);
	m_rectNightModePic = OnSetRect(390, 10, 48, 48);
	m_rectNightModeText = OnSetRect(390, 58, 48, 14);
	m_rectTempPic = OnSetRect(402, 82, 24, 48);
	m_rectTempInsulationText = OnSetRect(384, 130, 24, 14);
	m_rectTempHeatText = OnSetRect(420, 130, 24, 14);
	m_rectPowerPic = OnSetRect(390, 160, 48, 48);
	m_rectTempHighPic = OnSetRect(179, 10, 72, 108);
	m_rectTempLowPic = OnSetRect(255, 10, 72, 108);
	m_rectTemp = OnSetRect(179, 10, 148, 108);
	m_rectTempLabelText = OnSetRect(327, 10, 20, 20);
	m_rectAdd = OnSetRect(227, 122, 24, 24);
	m_rectReduce = OnSetRect(255, 122, 24, 24);
	m_rectTimeLabelPic = OnSetRect(245, 154, 16, 48);
	m_rectHourHighPic = OnSetRect(179, 154, 32, 48);
	m_rectHourLowPic = OnSetRect(213, 154, 32, 48);
	m_rectMinHighPic = OnSetRect(261, 154, 32, 48);
	m_rectMinLowPic = OnSetRect(295, 154, 32, 48);
	m_rectTime = OnSetRect(179, 154, 148, 48);
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

// 设置绘图坐标区域
CRect CAucma_HeaterDlg::OnSetRect(int x, int y, int iWidth, int iHeight)
{
	CRect rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + iWidth;
	rect.bottom = y + iHeight;
	return rect;
}
HBRUSH CAucma_HeaterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何属性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_brushBk;
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
		m_iSetTemp = 88;
		m_iCurrTemp = 0;
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
void CAucma_HeaterDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	m_brushBk.DeleteObject();
	m_FontDefault.DeleteObject();
	m_FontWinter.DeleteObject();
	m_FontTemp.DeleteObject();
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
		m_iSetTemp++;
		if (m_iSetTemp == 100)
		{
			m_iSetTemp = 0;
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
		if (m_iSetTemp != 0)
		{
			m_iSetTemp--;
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
// 将位图选入内存设备
void CAucma_HeaterDlg::OnDcBitBlt(CDC* pDC, CDC* pmemDC, CRect rect, CBitmap* pBitmap)
{
	CBitmap* pOldbmp = NULL;
	pOldbmp = pmemDC->SelectObject(pBitmap);
	pDC->BitBlt(rect.left,	// 目标位图的X起始坐标
		rect.top,			// 目标位图的y起始坐标
		rect.Width(),			// 显示图像的宽度
		rect.Height(),			// 显示图像的高度
		pmemDC, 
		0,			// 从源位图的X坐标开始显示图片
		0,			// 从源位图的y坐标开始显示图片
		SRCCOPY);	// 显示方式
	pmemDC->SelectObject(pOldbmp);
	pOldbmp->DeleteObject();
}
void CAucma_HeaterDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	// 定义内存设备
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	if (m_iFastHeatStateOld != m_iFastHeatState)
	{
		if (m_iFastHeatState == NormalHeat)
		{
			OnDcBitBlt(&dc, &memDC, m_rectHeatFastPic, &m_bmpHeatFastOff);
			OnDcBitBlt(&dc, &memDC, m_rectWinterPic, &m_bmpWinterOff);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectHeatFastText.left, m_rectHeatFastText.top, ETO_OPAQUE, NULL, _T("速热引擎"), NULL);
			dc.ExtTextOut(m_rectWinterText.left, m_rectWinterText.top, ETO_OPAQUE, NULL, _T("冬天"), NULL);
		}
		else if (m_iFastHeatState == FastHeat)
		{
			OnDcBitBlt(&dc, &memDC, m_rectHeatFastPic, &m_bmpHeatFastOn);
			OnDcBitBlt(&dc, &memDC, m_rectWinterPic, &m_bmpWinterOff);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectHeatFastText.left, m_rectHeatFastText.top, ETO_OPAQUE, NULL, _T("速热引擎"), NULL);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectWinterText.left, m_rectWinterText.top, ETO_OPAQUE, NULL, _T("冬天"), NULL);
		}
		else if (m_iFastHeatState == WinterHeat)
		{
			OnDcBitBlt(&dc, &memDC, m_rectHeatFastPic, &m_bmpHeatFastOn);
			OnDcBitBlt(&dc, &memDC, m_rectWinterPic, &m_bmpWinterOn);
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
			OnDcBitBlt(&dc, &memDC, m_rectHelperPic, &m_bmpHelperOn);
			dc.SetTextColor(SelectTextColor);
		}
		else
		{
			OnDcBitBlt(&dc, &memDC, m_rectHelperPic, &m_bmpHelperOff);
			dc.SetTextColor(DefaultTextColor);
		}
		dc.ExtTextOut(m_rectHelperText.left, m_rectHelperText.top, ETO_OPAQUE, NULL, _T("智能助手"), NULL);
		m_bHelperOld = m_bHelper;
	}
	if (m_bWashHandOld != m_bWashHand)
	{
		if (m_bWashHand == true)
		{
			OnDcBitBlt(&dc, &memDC, m_rectWashHandPic, &m_bmpWashHandOn);
			dc.SetTextColor(SelectTextColor);
		}
		else
		{
			OnDcBitBlt(&dc, &memDC, m_rectWashHandPic, &m_bmpWashHandOff);
			dc.SetTextColor(DefaultTextColor);
		}
		dc.ExtTextOut(m_rectWashHandText.left, m_rectWashHandText.top, ETO_OPAQUE, NULL, _T("洗手加热"), NULL);
		m_bWashHandOld = m_bWashHand;
	}
	if (m_bNightOld != m_bNight)
	{
		if (m_bNight == true)
		{
			OnDcBitBlt(&dc, &memDC, m_rectNightModePic, &m_bmpNightModeOn);
			dc.SetTextColor(SelectTextColor);
		}
		else
		{
			OnDcBitBlt(&dc, &memDC, m_rectNightModePic, &m_bmpNightModeOff);
			dc.SetTextColor(DefaultTextColor);
		}
		dc.ExtTextOut(m_rectNightModeText.left, m_rectNightModeText.top, ETO_OPAQUE, NULL, _T("夜电模式"), NULL);
		m_bNightOld = m_bNight;
	}
	if (m_bPowerOld != m_bPower)
	{
		if (m_bPower == true)
		{
			OnDcBitBlt(&dc, &memDC, m_rectPowerPic, &m_bmpPowerOn);
		}
		else
		{
			OnDcBitBlt(&dc, &memDC, m_rectPowerPic, &m_bmpPowerOff);
		}
		m_bPowerOld = m_bPower;
	}
	if (m_bAddOld != m_bAdd)
	{
		OnDcBitBlt(&dc, &memDC, m_rectAdd, &m_bmpAdd);
		m_bAddOld = m_bAdd;
	}
	if (m_bReduceOld != m_bReduce)
	{
		OnDcBitBlt(&dc, &memDC, m_rectReduce, &m_bmpReduce);
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
			OnDcBitBlt(&dc, &memDC, m_rectTempHighPic, &m_bmpTempSet[m_iSetTemp / 10]);
			OnDcBitBlt(&dc, &memDC, m_rectTempLowPic, &m_bmpTempSet[m_iSetTemp % 10]);
		}
		else
		{
			OnDcBitBlt(&dc, &memDC, m_rectTempHighPic, &m_bmpTempShow[m_iSetTemp / 10]);
			OnDcBitBlt(&dc, &memDC, m_rectTempLowPic, &m_bmpTempShow[m_iSetTemp % 10]);
		}
		m_iSetTempOld = m_iSetTemp;
		m_bSetTempOld = m_bSetTemp;
	}
	if ((m_CurrTimeOld != m_CurrTime) || (m_bSetTimeOld != m_bSetTime))
	{
		if (m_bSetTime == true)
		{
			OnDcBitBlt(&dc, &memDC, m_rectHourHighPic, &m_bmpTimeSet[m_CurrTime.GetHour() / 10]);
			OnDcBitBlt(&dc, &memDC, m_rectHourLowPic, &m_bmpTimeSet[m_CurrTime.GetHour() % 10]);
			OnDcBitBlt(&dc, &memDC, m_rectMinHighPic, &m_bmpTimeSet[m_CurrTime.GetMinute() / 10]);
			OnDcBitBlt(&dc, &memDC, m_rectMinLowPic, &m_bmpTimeSet[m_CurrTime.GetMinute() % 10]);
		}
		else
		{
			OnDcBitBlt(&dc, &memDC, m_rectHourHighPic, &m_bmpTimeShow[m_CurrTime.GetHour() / 10]);
			OnDcBitBlt(&dc, &memDC, m_rectHourLowPic, &m_bmpTimeShow[m_CurrTime.GetHour() % 10]);
			OnDcBitBlt(&dc, &memDC, m_rectMinHighPic, &m_bmpTimeShow[m_CurrTime.GetMinute() / 10]);
			OnDcBitBlt(&dc, &memDC, m_rectMinLowPic, &m_bmpTimeShow[m_CurrTime.GetMinute() % 10]);
		}
		m_CurrTimeOld = m_CurrTime;
		m_bSetTimeOld = m_bSetTime;
	}
	if (m_bTimeLabelOld != m_bTimeLabel)
	{
		OnDcBitBlt(&dc, &memDC, m_rectTimeLabelPic, &m_bmpTimeLabel);
		m_bTimeLabelOld = m_bTimeLabel;
	}
	if ((m_iTempStateOld != m_iTempState) || (m_bTempHeat == true))
	{
		if (m_iTempState == NoTempShow)
		{
			OnDcBitBlt(&dc, &memDC, m_rectTempPic, &m_bmpTempOff);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectTempInsulationText.left, m_rectTempInsulationText.top, ETO_OPAQUE, NULL, _T("保温"), NULL);
			dc.ExtTextOut(m_rectTempHeatText.left, m_rectTempHeatText.top, ETO_OPAQUE, NULL, _T("加热"), NULL);
		}
		else if (m_iTempState == InsulationState)
		{
			OnDcBitBlt(&dc, &memDC, m_rectTempPic, &m_bmpTempInsulation);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectTempInsulationText.left, m_rectTempInsulationText.top, ETO_OPAQUE, NULL, _T("保温"), NULL);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectTempHeatText.left, m_rectTempHeatText.top, ETO_OPAQUE, NULL, _T("加热"), NULL);
		}
		else if (m_iTempState == HeatTempState)
		{
			if (m_uiHeatCount == 0)
			{
				OnDcBitBlt(&dc, &memDC, m_rectTempPic, &m_bmpTempHeat1);
			}
			else if (m_uiHeatCount == 1)
			{
				OnDcBitBlt(&dc, &memDC, m_rectTempPic, &m_bmpTempHeat2);
			}
			else if (m_uiHeatCount == 2)
			{
				OnDcBitBlt(&dc, &memDC, m_rectTempPic, &m_bmpTempHeat3);
			}
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectTempInsulationText.left, m_rectTempInsulationText.top, ETO_OPAQUE, NULL, _T("保温"), NULL);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectTempHeatText.left, m_rectTempHeatText.top, ETO_OPAQUE, NULL, _T("加热"), NULL);
		}
		m_iTempStateOld = m_iTempState;
	}
	memDC.DeleteDC();
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