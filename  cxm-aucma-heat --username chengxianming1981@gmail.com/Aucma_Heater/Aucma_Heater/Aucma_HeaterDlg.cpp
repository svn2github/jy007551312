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
	, m_iSetTemp(1)
	, m_iCurrTemp(0)
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
	// 创建背景刷子
	m_brushBk.CreateSolidBrush(DialogBkColor);
	// 对话框最大化显示
	ShowWindow(SW_SHOWMAXIMIZED);
	m_ctrlHeatFast.MoveWindow(40, 10, 48, 48);
	m_staticHeatFast.MoveWindow(40, 58, 48, 14);
	m_ctrlWinter.MoveWindow(92, 34, 24, 24);
	m_FontWinter.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
	 	DEFAULT_PITCH&FF_SWISS, _T("MS Sans Serif"));
	m_staticWinter.SetFont(&m_FontWinter);
	m_FontTemp.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
		DEFAULT_PITCH&FF_SWISS, _T("MS Sans Serif"));
	m_staticTempLabel.SetFont(&m_FontTemp);
	m_staticTempLabel.Invalidate();
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
	OnPictureShow();
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
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_HEATFAST)
	{
		SetTextHighLighted(pDC, m_bHeatFast);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_WINTER)
	{
		SetTextHighLighted(pDC, m_bWinter);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_HELPER)
	{
		SetTextHighLighted(pDC, m_bHelper);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_WASHHAND)
	{
		SetTextHighLighted(pDC, m_bWashHand);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_NIGHT)
	{
		SetTextHighLighted(pDC, m_bNight);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEMP_INSULATION)
	{
		SetTextHighLighted(pDC, m_bTempInsulation);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEMP_HEAT)
	{
		SetTextHighLighted(pDC, m_bTempHeat);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEMP)
	{
		pDC->SetTextColor(DefaultTextColor);
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
		m_ctrlHeatFast.SetBitmap(m_hbmpHeatFastOff);
		m_ctrlWinter.SetBitmap(m_hbmpWinterOff);
	}
	else if (m_iFastHeatState == FastHeat)
	{
		m_bHeatFast = true;
		m_bWinter = false;
		m_ctrlHeatFast.SetBitmap(m_hbmpHeatFastOn);
		m_ctrlWinter.SetBitmap(m_hbmpWinterOff);
	}
	else if (m_iFastHeatState == WinterHeat)
	{
		m_bHeatFast = true;
		m_bWinter = true;
		m_ctrlHeatFast.SetBitmap(m_hbmpHeatFastOn);
		m_ctrlWinter.SetBitmap(m_hbmpWinterOn);
	}
	m_staticHeatFast.Invalidate();
	m_staticWinter.Invalidate();
	if (m_bHelper == true)
	{
		m_ctrlHelper.SetBitmap(m_hbmpHelperOn);
	}
	else
	{
		m_ctrlHelper.SetBitmap(m_hbmpHelperOff);
	}
	m_staticHelper.Invalidate();
	if (m_bWashHand == true)
	{
		m_ctrlWashHand.SetBitmap(m_hbmpWashHandOn);
	}
	else
	{
		m_ctrlWashHand.SetBitmap(m_hbmpWashHandOff);
	}
	m_staticWashHand.Invalidate();
	if (m_bNight == true)
	{
		m_ctrlNightMode.SetBitmap(m_hbmpNightModeOn);
	}
	else
	{
		m_ctrlNightMode.SetBitmap(m_hbmpNightModeOff);
	}
	m_staticNightMode.Invalidate();
	if (m_iTempState == NoTempShow)
	{
		m_bTempInsulation = false;
		m_bTempHeat = false;
		m_ctrlTemp.SetBitmap(m_hbmpTempOff);
		m_staticTempInsulation.Invalidate();
		m_staticTempHeat.Invalidate();
	}
	if (m_bPower == true)
	{
		m_ctrlPower.SetBitmap(m_hbmpPowerOn);
	}
	else
	{
		m_ctrlPower.SetBitmap(m_hbmpPowerOff);
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
		m_bPower = false;
	}
	else
	{
		KillTimer(ShowTempStateTimerEvent);
		SetTimer(ShowTempStateTimerEvent, ShowTempStateTimeSet, NULL);
		m_bPower = true;
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
				m_ctrlTemp.SetBitmap(m_hbmpTempInsulation);
				m_staticTempInsulation.Invalidate();
				m_staticTempHeat.Invalidate();
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
				m_staticTempInsulation.Invalidate();
				m_staticTempHeat.Invalidate();
			}
		}
		if (m_iTempState == HeatTempState)
		{
			if (m_uiHeatCount == 0)
			{
				m_ctrlTemp.SetBitmap(m_hbmpTempHeat1);
				m_uiHeatCount = 1;
			}
			else if (m_uiHeatCount == 1)
			{
				m_ctrlTemp.SetBitmap(m_hbmpTempHeat2);
				m_uiHeatCount = 2;
			}
			else if (m_uiHeatCount == 2)
			{
				m_ctrlTemp.SetBitmap(m_hbmpTempHeat3);
				m_uiHeatCount = 0;
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

// 得到当前温度
int CAucma_HeaterDlg::GetCurrTemp(void)
{
	return 0;
}
