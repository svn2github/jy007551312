// Aucma_HeaterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Aucma_Heater.h"
#include "Aucma_HeaterDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAucma_HeaterDlg 对话框

CAucma_HeaterDlg::CAucma_HeaterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAucma_HeaterDlg::IDD, pParent)
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
	m_rectBK = CRect(0, 0, 480, 272);
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
//	ON_WM_CTLCOLOR()
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
	OnInit();
	SetTimer(ShowTimeTimerEvent, ShowTimeTimeSet, NULL);
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
		AfxMessageBox(_T("串口打开失败！"));
	}
	m_hPWM = CreateFile(_T("PWM1:"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if ( m_hPWM == INVALID_HANDLE_VALUE )
	{
		AfxMessageBox(_T("Open PWM Failed!\n"));
	}
// 	// BlendOp字段指明了源混合操作，但只支持AC_SRC_OVER，即根据源alpha值把源图像叠加到目标图像上  
// 	m_blendfun.BlendOp = AC_SRC_OVER;
// 	// BlendFlags必须是0，也是为以后的应用保留的
// 	m_blendfun.BlendFlags = 0;
// 	// 0到255间的值，这里0表示完全透明，255表示完全不透明
// 	m_blendfun.SourceConstantAlpha = DefaultPNGTransparent;
// 	// AlphaFormat有两个选择：0表示常量alpha值，AC_SRC_ALPHA表示每个像素有各自的alpha通道。
// 	/** 如果AlphaFormat字段为0,源位图中的所有像素使用同样的常量alpha值，即SourceConstantAlpha
// 	字段中的值，该值实际上是0和255，而不是0和1。这里0表示完全透明，255表示完全不透明。目标
// 	像素以255-SourceConstantAlpha值作为alpha值。*/
// 	/** 如果AlphaFormat字段的值是AC_SRC_ALPHA，源设备表面的每个像素必须有各自的alpha通道。
// 	即，必须是32-bpp的物理设备上下文，或是选中了32-bpp DDB和DIB段的内存设备上下文。
// 	这些情况下，每个源像素有4个8位通道：红、绿、蓝和alpha。每个像素的alpha通道和
// 	SourceConstantAlpha字段一起用于把源和目标混合起来。实际用于计算的运算式如下：
// 	Tmp.Red = Src.Red * SourceConstantAlpha / 255;
// 	Tmp.Green = Src.Green * SourceConstantAlpha / 255;
// 	Tmp.Blue = Src.Blue * SourceConstantAlpha / 255;
// 	Tmp.Alpha = Src.Alpha * SourceConstantAlpha / 255;
// 	Beta = 255 – Tmp.alpha;
// 	Dst.Red = Tmp.Red + Round((Beta * Dst.Red )/255);
// 	Dst.Green = Tmp.Green + Round((Beta * Dst.Green)/255);
// 	Dst.Blue = Tmp.Blue + Round((Beta * Dst.Blue )/255);
// 	Dst.Alpha = Tmp.Alpha + Round((Beta * Dst.Alpha)/255);*/
// 	// 有两个值 0表示常量alpha值，AC_SRC_ALPHA表示每个像素有各自的alpha通道
// 	m_blendfun.AlphaFormat = 0;
//	// 对话框最大化显示
//	ShowWindow(SW_SHOWMAXIMIZED);
//	// 创建背景刷子
//	m_brushBk.CreateSolidBrush(DialogBkColor);
	SetWindowFullScreen();
	LoadFont();
	LoadPicture();
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
// HBRUSH CAucma_HeaterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
// {
// //	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
// 
// 	// TODO:  在此更改 DC 的任何属性
// 
// 	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
// 	return m_brushBk;
// }

// 设置窗口满屏
void CAucma_HeaterDlg::SetWindowFullScreen(void)
{
	int iFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int iFullHeight = GetSystemMetrics(SM_CYSCREEN);
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, iFullWidth, 
		iFullHeight, SWP_NOOWNERZORDER|SWP_SHOWWINDOW);
}
// 载入字体
void CAucma_HeaterDlg::LoadFont(void)
{
	CFont* pfont = NULL;
	CDC* pDC = this->GetDC();
	LOGFONT logFont;
	LONG lfHeight = 0;
	pfont = pDC->GetCurrentFont();
	memset(&logFont, 0, sizeof(LOGFONT));
	pfont->GetLogFont(&logFont);
	lfHeight = logFont.lfHeight;
	VERIFY(m_FontDefault.CreateFontIndirect(&logFont));
	logFont.lfHeight = lfHeight * 6 / 7;
	VERIFY(m_FontWinter.CreateFontIndirect(&logFont));
	logFont.lfHeight = lfHeight * 3 / 2;
	VERIFY(m_FontTemp.CreateFontIndirect(&logFont));
	pDC->DeleteDC();
}
// 载入图片
void CAucma_HeaterDlg::LoadPicture(void)
{
	// 初始化IImage
	m_oPngImage.InitIImage();
	// 从文件中载入图标到图片句柄
	CDC* pDC = this->GetDC();
	m_oPngImage.LoadPicFromFile(_T("背景.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_BK), _T("PNG"));
	m_oPngImage.GetDstDcFromPic(pDC, &m_dcBK, &m_bmpBK);
	m_oPngImage.LoadPicFromFile(_T("速热引擎_1.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_HEATFAST_OFF), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcHeatFastOff, &m_bmpHeatFastOff);
	m_oPngImage.DrawAlpha(&m_dcHeatFastOff, &m_dcBK, m_rectHeatFastPic);
	m_oPngImage.LoadPicFromFile(_T("速热引擎_2.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_HEATFAST_ON), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcHeatFastOn, &m_bmpHeatFastOn);
	m_oPngImage.DrawAlpha(&m_dcHeatFastOn, &m_dcBK, m_rectHeatFastPic);
	m_oPngImage.LoadPicFromFile(_T("冬天_1.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_WINTER_OFF), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcWinterOff, &m_bmpWinterOff);
	m_oPngImage.DrawAlpha(&m_dcWinterOff, &m_dcBK, m_rectWinterPic);
	m_oPngImage.LoadPicFromFile(_T("冬天_2.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_WINTER_OFF), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcWinterOn, &m_bmpWinterOn);
	m_oPngImage.DrawAlpha(&m_dcWinterOn, &m_dcBK, m_rectWinterPic);
	m_oPngImage.LoadPicFromFile(_T("智能助手_1.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_HELPER_OFF), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcHelperOff, &m_bmpHelperOff);
	m_oPngImage.DrawAlpha(&m_dcHelperOff, &m_dcBK, m_rectHelperPic);
	m_oPngImage.LoadPicFromFile(_T("智能助手_2.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_HELPER_ON), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcHelperOn, &m_bmpHelperOn);
	m_oPngImage.DrawAlpha(&m_dcHelperOn, &m_dcBK, m_rectHelperPic);
	m_oPngImage.LoadPicFromFile(_T("洗手加热_1.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_WASHHAND_OFF), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcWashHandOff, &m_bmpWashHandOff);
	m_oPngImage.DrawAlpha(&m_dcWashHandOff, &m_dcBK, m_rectWashHandPic);
	m_oPngImage.LoadPicFromFile(_T("洗手加热_2.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_WASHHAND_ON), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcWashHandOn, &m_bmpWashHandOn);
	m_oPngImage.DrawAlpha(&m_dcWashHandOn, &m_dcBK, m_rectWashHandPic);
	m_oPngImage.LoadPicFromFile(_T("夜电模式_1.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_NIGHTMODE_OFF), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcNightModeOff, &m_bmpNightModeOff);
	m_oPngImage.DrawAlpha(&m_dcNightModeOff, &m_dcBK, m_rectNightModePic);
	m_oPngImage.LoadPicFromFile(_T("夜电模式_2.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_NIGHTMODE_ON), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcNightModeOn, &m_bmpNightModeOn);
	m_oPngImage.DrawAlpha(&m_dcNightModeOn, &m_dcBK, m_rectNightModePic);
	m_oPngImage.LoadPicFromFile(_T("保温_加热.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_OFF), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcTempOff, &m_bmpTempOff);
	m_oPngImage.DrawAlpha(&m_dcTempOff, &m_dcBK, m_rectTempPic);
	m_oPngImage.LoadPicFromFile(_T("保温.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_ON), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcTempInsulation, &m_bmpTempInsulation);
	m_oPngImage.DrawAlpha(&m_dcTempInsulation, &m_dcBK, m_rectTempPic);
	m_oPngImage.LoadPicFromFile(_T("加热_1.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_HEAT1), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcTempHeat1, &m_bmpTempHeat1);
	m_oPngImage.DrawAlpha(&m_dcTempHeat1, &m_dcBK, m_rectTempPic);
	m_oPngImage.LoadPicFromFile(_T("加热_2.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_HEAT2), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcTempHeat2, &m_bmpTempHeat2);
	m_oPngImage.DrawAlpha(&m_dcTempHeat2, &m_dcBK, m_rectTempPic);
	m_oPngImage.LoadPicFromFile(_T("加热_3.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_HEAT3), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcTempHeat3, &m_bmpTempHeat3);
	m_oPngImage.DrawAlpha(&m_dcTempHeat3, &m_dcBK, m_rectTempPic);
	m_oPngImage.LoadPicFromFile(_T("电源_1.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_POWER_OFF), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcPowerOff, &m_bmpPowerOff);
	m_oPngImage.DrawAlpha(&m_dcPowerOff, &m_dcBK, m_rectPowerPic);
	m_oPngImage.LoadPicFromFile(_T("电源_2.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_POWER_ON), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcPowerOn, &m_bmpPowerOn);
	m_oPngImage.DrawAlpha(&m_dcPowerOn, &m_dcBK, m_rectPowerPic);
	m_oPngImage.LoadPicFromFile(_T("增加.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_ADD), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcAdd, &m_bmpAdd);
	m_oPngImage.DrawAlpha(&m_dcAdd, &m_dcBK, m_rectAdd);
	m_oPngImage.LoadPicFromFile(_T("减少.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_REDUCE), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcReduce, &m_bmpReduce);
	m_oPngImage.DrawAlpha(&m_dcReduce, &m_dcBK, m_rectReduce);
	m_oPngImage.LoadPicFromFile(_T("时间标志.png"));
	//	m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_TIMELABEL), _T("PNG"));
	//	m_oPngImage.GetDstDcFromPic(pDC, &m_dcTimeLabel, &m_bmpTimeLabel);
	m_oPngImage.DrawAlpha(&m_dcTimeLabel, &m_dcBK, m_rectTimeLabelPic);
	CString str = _T("");
	for (int i=0; i<10; i++)
	{
		str.Format(_T("温度1_%d.png"), i);
		m_oPngImage.LoadPicFromFile(str);
		//		m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_TEMP0 + i), _T("PNG"));
		//		m_oPngImage.GetDstDcFromPic(pDC, &m_dcTempShow[i], &m_bmpTempShow[i]);
		m_oPngImage.DrawAlpha(&m_dcTempHighShow[i], &m_dcBK, m_rectTempHighPic, false);
		m_oPngImage.DrawAlpha(&m_dcTempLowShow[i], &m_dcBK, m_rectTempLowPic);
		str.Format(_T("温度2_%d.png"), i);
		m_oPngImage.LoadPicFromFile(str);
		//		m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_TEMP_LIGHT0 + i), _T("PNG"));
		//		m_oPngImage.GetDstDcFromPic(pDC, &m_dcTempSet[i], &m_bmpTempSet[i]);
		m_oPngImage.DrawAlpha(&m_dcTempHighSet[i], &m_dcBK, m_rectTempHighPic, false);
		m_oPngImage.DrawAlpha(&m_dcTempLowSet[i], &m_dcBK, m_rectTempLowPic);
		str.Format(_T("时间1_%d.png"), i);
		m_oPngImage.LoadPicFromFile(str);
		//		m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_TIME0 + i), _T("PNG"));
		//		m_oPngImage.GetDstDcFromPic(pDC, &m_dcTimeShow[i], &m_bmpTimeShow[i]);
		m_oPngImage.DrawAlpha(&m_dcHourHighShow[i], &m_dcBK, m_rectHourHighPic, false);
		m_oPngImage.DrawAlpha(&m_dcHourLowShow[i], &m_dcBK, m_rectHourLowPic, false);
		m_oPngImage.DrawAlpha(&m_dcMinHighShow[i], &m_dcBK, m_rectMinHighPic, false);
		m_oPngImage.DrawAlpha(&m_dcMinLowShow[i], &m_dcBK, m_rectMinLowPic);
		str.Format(_T("时间2_%d.png"), i);
		m_oPngImage.LoadPicFromFile(str);
		//		m_oPngImage.LoadFromResource(MAKEINTRESOURCE(IDB_TIME_LIGHT0 + i), _T("PNG"));
		//		m_oPngImage.GetDstDcFromPic(pDC, &m_dcTimeSet[i], &m_bmpTimeSet[i]);
		m_oPngImage.DrawAlpha(&m_dcHourHighSet[i], &m_dcBK, m_rectHourHighPic, false);
		m_oPngImage.DrawAlpha(&m_dcHourLowSet[i], &m_dcBK, m_rectHourLowPic, false);
		m_oPngImage.DrawAlpha(&m_dcMinHighSet[i], &m_dcBK, m_rectMinHighPic, false);
		m_oPngImage.DrawAlpha(&m_dcMinLowSet[i], &m_dcBK, m_rectMinLowPic);
	}
	pDC->DeleteDC();
}
void CAucma_HeaterDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
//	m_brushBk.DeleteObject();
	m_FontDefault.DeleteObject();
	m_FontWinter.DeleteObject();
	m_FontTemp.DeleteObject();

	m_dcHeatFastOn.DeleteDC();
//	m_bmpHeatFastOn.DeleteObject();
	m_dcHeatFastOff.DeleteDC();
//	m_bmpHeatFastOff.DeleteObject();
	m_dcWinterOn.DeleteDC();
//	m_bmpWinterOn.DeleteObject();
	m_dcWinterOff.DeleteDC();
//	m_bmpWinterOff.DeleteObject();
	m_dcHelperOn.DeleteDC();
//	m_bmpHelperOn.DeleteObject();
	m_dcHelperOff.DeleteDC();
//	m_bmpHelperOff.DeleteObject();
	m_dcWashHandOn.DeleteDC();
//	m_bmpWashHandOn.DeleteObject();
	m_dcWashHandOff.DeleteDC();
//	m_bmpWashHandOff.DeleteObject();
	m_dcNightModeOn.DeleteDC();
//	m_bmpNightModeOn.DeleteObject();
	m_dcNightModeOff.DeleteDC();
//	m_bmpNightModeOff.DeleteObject();
	m_dcTempOff.DeleteDC();
//	m_bmpTempOff.DeleteObject();
	m_dcTempInsulation.DeleteDC();
//	m_bmpTempInsulation.DeleteObject();
	m_dcTempHeat1.DeleteDC();
//	m_bmpTempHeat1.DeleteObject();
	m_dcTempHeat2.DeleteDC();
//	m_bmpTempHeat2.DeleteObject();
	m_dcTempHeat3.DeleteDC();
//	m_bmpTempHeat3.DeleteObject();
	m_dcPowerOn.DeleteDC();
//	m_bmpPowerOn.DeleteObject();
	m_dcPowerOff.DeleteDC();
//	m_bmpPowerOff.DeleteObject();
	for (int i=0; i<10; i++)
	{
//		m_bmpTempShow[i].DeleteObject();
		m_dcTempHighShow[i].DeleteDC();
		m_dcTempLowShow[i].DeleteDC();
//		m_bmpTimeSet[i].DeleteObject();
		m_dcTempHighSet[i].DeleteDC();
		m_dcTempLowSet[i].DeleteDC();
//		m_bmpTimeShow[i].DeleteObject();
		m_dcHourHighShow[i].DeleteDC();
		m_dcHourLowShow[i].DeleteDC();
		m_dcMinHighShow[i].DeleteDC();
		m_dcMinLowShow[i].DeleteDC();
//		m_bmpTimeSet[i].DeleteObject();
		m_dcHourHighSet[i].DeleteDC();
		m_dcHourLowSet[i].DeleteDC();
		m_dcMinHighSet[i].DeleteDC();
		m_dcMinLowSet[i].DeleteDC();
	}
//	m_bmpAdd.DeleteObject();
	m_dcAdd.DeleteDC();
//	m_bmpReduce.DeleteObject();
	m_dcReduce.DeleteDC();
//	m_bmpTimeLabel.DeleteObject();
	m_dcTimeLabel.DeleteDC();
	m_bmpBK.DeleteObject();
	m_dcBK.DeleteDC();
	m_oCEUart.ClosePort();
	m_oPngImage.ReleaseIImage();
}
void CAucma_HeaterDlg::OnClickedHeatfast()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPower == false)
	{
		return;
	}
	if (m_iFastHeatState == NormalHeat)
	{
		m_iFastHeatState = FastHeat;
		InvalidateRect(m_rectHeatFastPic, FALSE);
		InvalidateRect(m_rectHeatFastText, FALSE);
		// 夏季智能开启
		OnWriteUartData(CMD_UP_SO, CMD_WORD_SO);
		// 冬季智能关闭
		OnWriteUartData(CMD_UP_WO, CMD_WORD_WC);
	}
	else if (m_iFastHeatState == FastHeat)
	{
		m_iFastHeatState = WinterHeat;
		InvalidateRect(m_rectWinterPic, FALSE);
		InvalidateRect(m_rectWinterText, FALSE);
		// 夏季智能关闭
		OnWriteUartData(CMD_UP_SO, CMD_WORD_SC);
		// 冬季智能开启
		OnWriteUartData(CMD_UP_WO, CMD_WORD_WO);
	}
	else if (m_iFastHeatState == WinterHeat)
	{
		m_iFastHeatState = NormalHeat;
		InvalidateRect(m_rectHeatFastPic, FALSE);
		InvalidateRect(m_rectHeatFastText, FALSE);
		InvalidateRect(m_rectWinterPic, FALSE);
		InvalidateRect(m_rectWinterText, FALSE);
		// 夏季智能关闭
		OnWriteUartData(CMD_UP_SO, CMD_WORD_SC);
		// 冬季智能关闭
		OnWriteUartData(CMD_UP_WO, CMD_WORD_WC);
	}
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
	if (m_bHelper == true)
	{
		// 智能助手开启
		OnWriteUartData(CMD_UP_HP, CMD_WORD_HO);
	}
	else
	{
		// 智能助手关闭
		OnWriteUartData(CMD_UP_HP, CMD_WORD_HC);
	}
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
	if (m_bWashHand == true)
	{
		// 洗手加热开启
		OnWriteUartData(CMD_UP_WH, CMD_WORD_WHO);
	}
	else
	{
		// 洗手加热关闭
		OnWriteUartData(CMD_UP_WH, CMD_WORD_WHC);
	}
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
	if (m_bNight == true)
	{
		// 夜电运行方式开启
		OnWriteUartData(CMD_UP_NO, CMD_WORD_NO);
	}
	else
	{
		// 夜电运行方式关闭
		OnWriteUartData(CMD_UP_NO, CMD_WORD_NC);
	}
}

void CAucma_HeaterDlg::OnClickedPower()
{
	// TODO: 在此添加控件通知处理程序代码
	StartBuzzer();
	SetTimer(BuzzerTimerEvent, 300, NULL);
	if (m_bPower == true)
	{
		OnInit();
		Invalidate(FALSE);
		// 夏季智能关闭
		OnWriteUartData(CMD_UP_SO, CMD_WORD_SC);
		// 冬季智能关闭
		OnWriteUartData(CMD_UP_WO, CMD_WORD_WC);
		// 智能助手关闭
		OnWriteUartData(CMD_UP_HP, CMD_WORD_HC);
		// 洗手加热关闭
		OnWriteUartData(CMD_UP_WH, CMD_WORD_WHC);
		// 夜电运行方式关闭
		OnWriteUartData(CMD_UP_NO, CMD_WORD_NC);
	}
	else
	{
		m_bPower = true;
		SetTimer(ShowTempStateTimerEvent, ShowTempStateTimeSet, NULL);
		InvalidateRect(m_rectPowerPic, FALSE);
	}
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
	KillTimer(TwinkleTimerEvent);
	if (m_uiContinuousCount == 0)
	{
		KillTimer(ContinuousOptTimerEvent);
		SetTimer(ContinuousOptTimerEvent, ContinuousOptTimeSet, NULL);
		m_bAddOpt = true;
		if (m_bTwinkle == false)
		{
			m_bTwinkle = true;
			if (m_bSetTemp == true)
			{
				InvalidateRect(m_rectTempHighPic, FALSE);
				InvalidateRect(m_rectTempLowPic, FALSE);
			}
			else if (m_bSetTime == true)
			{
				InvalidateRect(m_rectHourHighPic, FALSE);
				InvalidateRect(m_rectHourLowPic, FALSE);
				InvalidateRect(m_rectMinHighPic, FALSE);
				InvalidateRect(m_rectMinLowPic, FALSE);
			}
		}
	}
	if (m_bSetTemp == true)
	{
		if (m_iInTempSet < SetTempMaxLimit)
		{
			m_iInTempSet++;
			if ((m_iInTempSet / 10) != (m_iInTempSetOld / 10))
			{
				InvalidateRect(m_rectTempHighPic, FALSE);
			}
			if ((m_iInTempSet % 10) != (m_iInTempSetOld % 10))
			{
				InvalidateRect(m_rectTempLowPic, FALSE);
			}
		}
	}
	else if (m_bSetTime == true)
	{
		KillTimer(ShowTimeTimerEvent);
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
		if ((m_CurrTime.GetHour() / 10) != (m_CurrTimeOld.GetHour() / 10))
		{
			InvalidateRect(m_rectHourHighPic, FALSE);
		}
		if ((m_CurrTime.GetHour() % 10) != (m_CurrTimeOld.GetHour() % 10))
		{
			InvalidateRect(m_rectHourLowPic, FALSE);
		}
		if ((m_CurrTime.GetMinute() / 10) != (m_CurrTimeOld.GetMinute() / 10))
		{
			InvalidateRect(m_rectMinHighPic, FALSE);
		}
		if ((m_CurrTime.GetMinute() % 10) != (m_CurrTimeOld.GetMinute() % 10))
		{
			InvalidateRect(m_rectMinLowPic, FALSE);
		}
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
	KillTimer(TwinkleTimerEvent);
	if (m_uiContinuousCount == 0)
	{
		KillTimer(ContinuousOptTimerEvent);
		SetTimer(ContinuousOptTimerEvent, ContinuousOptTimeSet, NULL);
		m_bReduceOpt = true;
		if (m_bTwinkle == false)
		{
			m_bTwinkle = true;
			if (m_bSetTemp == true)
			{
				InvalidateRect(m_rectTempHighPic, FALSE);
				InvalidateRect(m_rectTempLowPic, FALSE);
			}
			else if (m_bSetTime == true)
			{
				InvalidateRect(m_rectHourHighPic, FALSE);
				InvalidateRect(m_rectHourLowPic, FALSE);
				InvalidateRect(m_rectMinHighPic, FALSE);
				InvalidateRect(m_rectMinLowPic, FALSE);
			}
		}
	}
	if (m_bSetTemp == true)
	{
		if (m_iInTempSet > SetTempMinLimit)
		{
			m_iInTempSet--;
		}
		if ((m_iInTempSet / 10) != (m_iInTempSetOld / 10))
		{
			InvalidateRect(m_rectTempHighPic, FALSE);
		}
		if ((m_iInTempSet % 10) != (m_iInTempSetOld % 10))
		{
			InvalidateRect(m_rectTempLowPic, FALSE);
		}
	}
	else if (m_bSetTime == true)
	{
		KillTimer(ShowTimeTimerEvent);
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
		if ((m_CurrTime.GetHour() / 10) != (m_CurrTimeOld.GetHour() / 10))
		{
			InvalidateRect(m_rectHourHighPic, FALSE);
		}
		if ((m_CurrTime.GetHour() % 10) != (m_CurrTimeOld.GetHour() % 10))
		{
			InvalidateRect(m_rectHourLowPic, FALSE);
		}
		if ((m_CurrTime.GetMinute() / 10) != (m_CurrTimeOld.GetMinute() / 10))
		{
			InvalidateRect(m_rectMinHighPic, FALSE);
		}
		if ((m_CurrTime.GetMinute() % 10) != (m_CurrTimeOld.GetMinute() % 10))
		{
			InvalidateRect(m_rectMinLowPic, FALSE);
		}
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
	if (m_bSetTemp == true)
	{
		m_uiTwinkleCount = 0;
		SetTimer(TwinkleTimerEvent, TwinkleTimeSet, NULL);
	}
	else
	{
		KillTimer(TwinkleTimerEvent);
		// 设置箱内温度
		OnWriteUartData(CMD_UP_IT, m_iInTempSet + 127);
	}
	InvalidateRect(m_rectTempHighPic, FALSE);
	InvalidateRect(m_rectTempLowPic, FALSE);
}

// 设置时间
void CAucma_HeaterDlg::OnSetTime(void)
{
	if ((m_bPower == false) || (m_bSetTemp == true))
	{
		return;
	}
	m_bSetTime = !m_bSetTime;
	if (m_bSetTime == true)
	{
		m_uiTwinkleCount = 0;
		SetTimer(TwinkleTimerEvent, TwinkleTimeSet, NULL);
	}
	else
	{
		KillTimer(TwinkleTimerEvent);
	}
	InvalidateRect(m_rectHourHighPic, FALSE);
	InvalidateRect(m_rectHourLowPic, FALSE);
	InvalidateRect(m_rectMinHighPic, FALSE);
	InvalidateRect(m_rectMinLowPic, FALSE);
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
	if ((m_bAddOpt == true) || (m_bReduceOpt == true))
	{
		m_uiTwinkleCount = 0;
		SetTimer(TwinkleTimerEvent, TwinkleTimeSet, NULL);
		SetTimer(ShowTimeTimerEvent, ShowTimeTimeSet, NULL);
	}
	m_bAddOpt = false;
	m_bReduceOpt = false;
	CDialog::OnLButtonUp(nFlags, point);
}
void CAucma_HeaterDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	m_oPngImage.OnDcBitBlt(&dc, &m_dcBK, m_rectBK);
	dc.SetBkMode(TRANSPARENT);
	if (m_iFastHeatStateOld != m_iFastHeatState)
	{
		if (m_iFastHeatState == NormalHeat)
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcHeatFastOff, m_rectHeatFastPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcWinterOff, m_rectWinterPic);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectHeatFastText.left + TextOutMovePos1, m_rectHeatFastText.top, ETO_OPAQUE, NULL, _T("速热引擎"), NULL);
			dc.SelectObject(&m_FontWinter);
			dc.ExtTextOut(m_rectWinterText.left + TextOutMovePos2, m_rectWinterText.top, ETO_OPAQUE, NULL, _T("冬天"), NULL);
			dc.SelectObject(&m_FontDefault);
		}
		else if (m_iFastHeatState == FastHeat)
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcHeatFastOn, m_rectHeatFastPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcWinterOff, m_rectWinterPic);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectHeatFastText.left + TextOutMovePos1, m_rectHeatFastText.top, ETO_OPAQUE, NULL, _T("速热引擎"), NULL);
			dc.SetTextColor(DefaultTextColor);
			dc.SelectObject(&m_FontWinter);
			dc.ExtTextOut(m_rectWinterText.left + TextOutMovePos2, m_rectWinterText.top, ETO_OPAQUE, NULL, _T("冬天"), NULL);
			dc.SelectObject(&m_FontDefault);
		}
		else if (m_iFastHeatState == WinterHeat)
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcHeatFastOn, m_rectHeatFastPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcWinterOn, m_rectWinterPic);
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
			m_oPngImage.OnDcBitBlt(&dc, &m_dcHelperOn, m_rectHelperPic);
			dc.SetTextColor(SelectTextColor);
		}
		else
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcHelperOff, m_rectHelperPic);
			dc.SetTextColor(DefaultTextColor);
		}
		dc.ExtTextOut(m_rectHelperText.left + TextOutMovePos1, m_rectHelperText.top, ETO_OPAQUE, NULL, _T("智能助手"), NULL);
		m_bHelperOld = m_bHelper;
	}
	if (m_bWashHandOld != m_bWashHand)
	{
		if (m_bWashHand == true)
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcWashHandOn, m_rectWashHandPic);
			dc.SetTextColor(SelectTextColor);
		}
		else
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcWashHandOff, m_rectWashHandPic);
			dc.SetTextColor(DefaultTextColor);
		}
		dc.ExtTextOut(m_rectWashHandText.left + TextOutMovePos1, m_rectWashHandText.top, ETO_OPAQUE, NULL, _T("洗手加热"), NULL);
		m_bWashHandOld = m_bWashHand;
	}
	if (m_bNightOld != m_bNight)
	{
		if (m_bNight == true)
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcNightModeOn, m_rectNightModePic);
			dc.SetTextColor(SelectTextColor);
		}
		else
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcNightModeOff, m_rectNightModePic);
			dc.SetTextColor(DefaultTextColor);
		}
		dc.ExtTextOut(m_rectNightModeText.left + TextOutMovePos1, m_rectNightModeText.top, ETO_OPAQUE, NULL, _T("夜电模式"), NULL);
		m_bNightOld = m_bNight;
	}
	if (m_bPowerOld != m_bPower)
	{
		if (m_bPower == true)
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcPowerOn, m_rectPowerPic);
		}
		else
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcPowerOff, m_rectPowerPic);
		}
		m_bPowerOld = m_bPower;
	}
	if (m_bAddOld != m_bAdd)
	{
		m_oPngImage.OnDcBitBlt(&dc, &m_dcAdd, m_rectAdd);
		m_bAddOld = m_bAdd;
	}
	if (m_bReduceOld != m_bReduce)
	{
		m_oPngImage.OnDcBitBlt(&dc, &m_dcReduce, m_rectReduce);
		m_bReduceOld = m_bReduce;
	}
	if (m_bTempLabelOld != m_bTempLabel)
	{
		dc.SetTextColor(TempTextColor);
		dc.SelectObject(&m_FontTemp);
		dc.ExtTextOut(m_rectTempLabelText.left, m_rectTempLabelText.top, ETO_OPAQUE, NULL, _T("℃"), NULL);
		dc.SetTextColor(DefaultTextColor);
		dc.SelectObject(&m_FontDefault);
		m_bTempLabelOld = m_bTempLabel;
	}
	if ((m_iInTempSetOld != m_iInTempSet) || (m_bSetTempOld != m_bSetTemp) || ((m_bTwinkle == true) && (m_bSetTemp == true)))
	{
		if (m_bSetTemp == true)
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcTempHighSet[m_iInTempSet / 10], m_rectTempHighPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcTempLowSet[m_iInTempSet % 10], m_rectTempLowPic);
		}
		else
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcTempHighShow[m_iInTempActual / 10], m_rectTempHighPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcTempLowShow[m_iInTempActual % 10], m_rectTempLowPic);
		}
		m_iInTempSetOld = m_iInTempSet;
		m_bSetTempOld = m_bSetTemp;
	}
	if ((m_CurrTimeOld != m_CurrTime) || (m_bSetTimeOld != m_bSetTime) || ((m_bTwinkle == true) && (m_bSetTime == true)))
	{
		if (m_bSetTime == true)
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcHourHighSet[m_CurrTime.GetHour() / 10], m_rectHourHighPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcHourLowSet[m_CurrTime.GetHour() % 10], m_rectHourLowPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcMinHighSet[m_CurrTime.GetMinute() / 10], m_rectMinHighPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcMinLowSet[m_CurrTime.GetMinute() % 10], m_rectMinLowPic);
		}
		else
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcHourHighShow[m_CurrTime.GetHour() / 10], m_rectHourHighPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcHourLowShow[m_CurrTime.GetHour() % 10], m_rectHourLowPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcMinHighShow[m_CurrTime.GetMinute() / 10], m_rectMinHighPic);
			m_oPngImage.OnDcBitBlt(&dc, &m_dcMinLowShow[m_CurrTime.GetMinute() % 10], m_rectMinLowPic);
		}
		m_CurrTimeOld = m_CurrTime;
		m_bSetTimeOld = m_bSetTime;
	}
	if (m_bTimeLabelOld != m_bTimeLabel)
	{
		m_oPngImage.OnDcBitBlt(&dc, &m_dcTimeLabel, m_rectTimeLabelPic);
		m_bTimeLabelOld = m_bTimeLabel;
	}
	if ((m_iTempStateOld != m_iTempState) || (m_bTempHeat == true))
	{
		if (m_iTempState == NoTempShow)
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcTempOff, m_rectTempPic);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectTempInsulationText.left, m_rectTempInsulationText.top, ETO_OPAQUE, NULL, _T("保温"), NULL);
			dc.ExtTextOut(m_rectTempHeatText.left, m_rectTempHeatText.top, ETO_OPAQUE, NULL, _T("加热"), NULL);
		}
		else if (m_iTempState == InsulationState)
		{
			m_oPngImage.OnDcBitBlt(&dc, &m_dcTempInsulation, m_rectTempPic);
			dc.SetTextColor(SelectTextColor);
			dc.ExtTextOut(m_rectTempInsulationText.left, m_rectTempInsulationText.top, ETO_OPAQUE, NULL, _T("保温"), NULL);
			dc.SetTextColor(DefaultTextColor);
			dc.ExtTextOut(m_rectTempHeatText.left, m_rectTempHeatText.top, ETO_OPAQUE, NULL, _T("加热"), NULL);
		}
		else if (m_iTempState == HeatTempState)
		{
			if (m_uiHeatCount == 0)
			{
				m_oPngImage.OnDcBitBlt(&dc, &m_dcTempHeat1, m_rectTempPic);
			}
			else if (m_uiHeatCount == 1)
			{
				m_oPngImage.OnDcBitBlt(&dc, &m_dcTempHeat2, m_rectTempPic);
			}
			else if (m_uiHeatCount == 2)
			{
				m_oPngImage.OnDcBitBlt(&dc, &m_dcTempHeat3, m_rectTempPic);
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
		if ((m_CurrTime.GetHour() / 10) != (m_CurrTimeOld.GetHour() / 10))
		{
			InvalidateRect(m_rectHourHighPic, FALSE);
		}
		if ((m_CurrTime.GetHour() % 10) != (m_CurrTimeOld.GetHour() % 10))
		{
			InvalidateRect(m_rectHourLowPic, FALSE);
		}
		if ((m_CurrTime.GetMinute() / 10) != (m_CurrTimeOld.GetMinute() / 10))
		{
			InvalidateRect(m_rectMinHighPic, FALSE);
		}
		if ((m_CurrTime.GetMinute() % 10) != (m_CurrTimeOld.GetMinute() % 10))
		{
			InvalidateRect(m_rectMinLowPic, FALSE);
		}
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
			else if (m_bReduceOpt == true)
			{
				OnClickedReduce();
			}
		}
	}
	else if (nIDEvent == TwinkleTimerEvent)
	{
		m_uiTwinkleCount++;
		if (m_uiTwinkleCount >= TwinkleMaxTimes)
		{
			if (m_bSetTemp == true)
			{
				OnSetTemp();
			}
			else if (m_bSetTime == true)
			{
				OnSetTime();
			}
		}
		else
		{
			if (m_uiTwinkleCount % 2 == 0)
			{
				m_bTwinkle = true;
			}
			else
			{
				m_bTwinkle = false;
			}
			if (m_bSetTemp == true)
			{
				InvalidateRect(m_rectTempHighPic, FALSE);
				InvalidateRect(m_rectTempLowPic, FALSE);
			}
			else if (m_bSetTime == true)
			{
				InvalidateRect(m_rectHourHighPic, FALSE);
				InvalidateRect(m_rectHourLowPic, FALSE);
				InvalidateRect(m_rectMinHighPic, FALSE);
				InvalidateRect(m_rectMinLowPic, FALSE);
			}
		}
	}
	else if (nIDEvent == BuzzerTimerEvent)
	{
		StopBuzzer();
		KillTimer(BuzzerTimerEvent);
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
// 	case CMD_IHMT_CTRL:
// 		if (byData == CMD_IHMT_OFF)
// 		{
// 			TRACE(_T("关闭 LCD背光\n"));
// 		}
// 		else if (byData == CMD_IHMT_ON)
// 		{
// 			TRACE(_T("打开 LCD背光\n"));
// 		}
// 		break;
// 	case CMD_IHMT_RST:
// 		TRACE(_T("复位触摸屏\n"));
// 		break;
	case CMD_DOWN_ET:
		m_iEnvTempActual = (unsigned int)byData - 127;
		AfxMessageBox(_T("实际环境温度 %d \n"), m_iEnvTempActual);
		break;
	case CMD_DOWN_IT:
		m_iInTempActual = (unsigned int)byData - 127;
		AfxMessageBox(_T("实际箱内温度 %d \n"), m_iInTempActual);
		break;
	case CMD_DOWN_WT:
		if (byData == CMD_WORD_WT_NWE)
		{
			AfxMessageBox(_T("干烧/缺水报警\n"));
		}
		else if (byData == CMD_WORD_WT_SE)
		{
			AfxMessageBox(_T("传感器故障报警\n"));
		}
		else if (byData == CMD_WORD_WT_LE)
		{
			AfxMessageBox(_T("漏电故障报警\n"));
		}
		else if (byData == CMD_WORD_WT_WHE)
		{
			AfxMessageBox(_T("水温超高故障报警\n"));
		}
		else if (byData == CMD_WORD_WT_LCE)
		{
			AfxMessageBox(_T("漏电线圈故障报警\n"));
		}
		else if (byData == CMD_WORD_WT_NWEC)
		{
			AfxMessageBox(_T("干烧/缺水报警消除\n"));
		}
		else if (byData == CMD_WORD_WT_SEC)
		{
			AfxMessageBox(_T("传感器故障报警消除\n"));
		}
		else if (byData == CMD_WORD_WT_LEC)
		{
			AfxMessageBox(_T("漏电故障报警消除\n"));
		}
		else if (byData == CMD_WORD_WT_WHEC)
		{
			AfxMessageBox(_T("水温超高故障报警消除\n"));
		}
		else if (byData == CMD_WORD_WT_LCEC)
		{
			AfxMessageBox(_T("漏电线圈故障报警消除\n"));
		}
		break;
	case CMD_DOWN_QT:
		OnWriteUartData(CMD_UP_IT, m_iInTempSet + 127);
		break;
	default:
		break;
	}
	// @@@调试用
//	m_oCEUart.WriteSyncPort(m_ucRcvBuf, UartFrameLength);
}
// 初始化界面参数
void CAucma_HeaterDlg::OnInit(void)
{
	m_iFastHeatState = NormalHeat;
	m_iFastHeatStateOld = WinterHeat;
	m_bHelper = false;
	m_bHelperOld = true;
	m_bWashHand = false;
	m_bWashHandOld = true;
	m_bNight = false;
	m_bNightOld = true;
	m_iTempState = NoTempShow;
	m_iTempStateOld = HeatTempState;
	m_bSetTemp = false;
	m_bSetTempOld = true;
	m_bSetTime = false;
	m_bSetTimeOld = true;
	m_bPower = false;
	m_bPowerOld = true;
	m_uiHeatCount = 0;
	m_iInTempSet = DefaultSetTemp;
	m_iInTempSetOld = 0;
	m_iInTempActual = 48;
	m_bTempHeat = false;
	m_CurrTime = CTime::GetCurrentTime();
	m_CurrTimeOld = 1;
	m_bAdd = false;
	m_bAddOld = true;
	m_bReduce = false;
	m_bReduceOld = true;
	m_bTempLabel = false;
	m_bTempLabelOld = true;
	m_bTimeLabel = false;
	m_bTimeLabelOld = true;
	m_uiContinuousCount = 0;
	m_bAddOpt = false;
	m_bReduceOpt = false;
	m_iEnvTempActual = 0;
// 	m_iHighWarnTemp = 0;
// 	m_iLowWarnTemp = 0;
	m_uiUartRcvCount = 0;
	m_byCheck = 0;
	m_uiTwinkleCount = 0;
	m_bTwinkle = false;
//	m_uiTwinkleSleepTimes = 0;
	KillTimer(ShowTempStateTimerEvent);
	KillTimer(ContinuousOptTimerEvent);
	KillTimer(TwinkleTimerEvent);
}
// 开启蜂鸣器
void CAucma_HeaterDlg::StartBuzzer(int iPwmValue)
{
	DeviceIoControl(m_hPWM, 2, &iPwmValue, sizeof(iPwmValue), NULL, NULL, NULL, NULL);
}

// 关闭蜂鸣器
void CAucma_HeaterDlg::StopBuzzer(void)
{
	DeviceIoControl(m_hPWM, 1, NULL, NULL, NULL, NULL, NULL, NULL);
}
