// Aucma_HeaterDlg.h : 头文件
//
#pragma once
#include "..\UART_WINCE\CEUart.h"
#include "Parameter.h"
#include "PngImage.h"
#include "CEHttp.h"
#include "Log.h"
#include "LogThread.h"
// CAucma_HeaterDlg 对话框
class CAucma_HeaterDlg : public CDialog
{
// 构造
public:
	CAucma_HeaterDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AUCMA_HEATER_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
private:
// 	// 背景刷子
// 	CBrush m_brushBk;
	// 系统默认字体
	CFont m_FontDefault;
	// 冬天字体
	CFont m_FontWinter;
	// 温度字体
	CFont m_FontTemp;
	// 速热引擎图片绘图区域
	CRect m_rectHeatFastPic;
	// 速热引擎文本绘图区域
	CRect m_rectHeatFastText;
	// 冬天图片绘图区域
	CRect m_rectWinterPic;
	// 冬天文本绘图区域
	CRect m_rectWinterText;
	// 智能助手图片绘图区域
	CRect m_rectHelperPic;
	// 智能助手文本绘图区域
	CRect m_rectHelperText;
	// 洗手加热图片绘图区域
	CRect m_rectWashHandPic;
	// 洗手加热文本绘图区域
	CRect m_rectWashHandText;
	// 夜电模式图片绘图区域
	CRect m_rectNightModePic;
	// 夜电模式文本绘图区域
	CRect m_rectNightModeText;
	// 温度图片绘图区域
	CRect m_rectTempPic;
	// 保温文本绘图区域
	CRect m_rectTempInsulationText;
	// 加热文本绘图区域
	CRect m_rectTempHeatText;
	// 电源图片绘图区域
	CRect m_rectPowerPic;
	// 温度单位文本绘图区域
	CRect m_rectTempLabelText;
	// 温度高位显示图片绘图区域
	CRect m_rectTempHighPic;
	// 温度低位显示图片绘图区域
	CRect m_rectTempLowPic;
	// 小时高位图片绘图区域
	CRect m_rectHourHighPic;
	// 小时低位图片绘图区域
	CRect m_rectHourLowPic;
	// 时间标志图片绘图区域
	CRect m_rectTimeLabelPic;
	// 分钟高位图片绘图区域
	CRect m_rectMinHighPic;
	// 分钟低位图片绘图区域
	CRect m_rectMinLowPic;
	// "增加"图片绘图区域
	CRect m_rectAdd;
	// "减少"图片绘图区域
	CRect m_rectReduce;
	// 温度区范围
	CRect m_rectTemp;
	// 时间区范围
	CRect m_rectTime;
	// 背景范围
	CRect m_rectBK;
	// 速热引擎打开图标句柄
	CDC m_dcHeatFastOn;
	// 速热引擎关闭图标句柄
	CDC m_dcHeatFastOff;
	// 冬天打开图标句柄
	CDC m_dcWinterOn;
	// 冬天关闭图标句柄
	CDC m_dcWinterOff;
	// 智能助手打开图标句柄
	CDC m_dcHelperOn;
	// 智能助手关闭图标句柄
	CDC m_dcHelperOff;
	// 洗手加热打开图标句柄
	CDC m_dcWashHandOn;
	// 洗手加热关闭图标句柄
	CDC m_dcWashHandOff;
	// 夜间模式打开图标句柄
	CDC m_dcNightModeOn;
	// 夜间模式关闭图标句柄
	CDC m_dcNightModeOff;
	// 温度显示关闭图标句柄
	CDC m_dcTempOff;
	// 温度保温图标句柄
	CDC m_dcTempInsulation;
	// 温度加热图标句柄1
	CDC m_dcTempHeat1;
	// 温度加热图标句柄2
	CDC m_dcTempHeat2;
	// 温度加热图标句柄3
	CDC m_dcTempHeat3;
	// 电源打开图标句柄
	CDC m_dcPowerOn;
	// 电源关闭图标句柄
	CDC m_dcPowerOff;
	// 温度显示图标句柄
	CDC m_dcTempHighShow[10];
	// 温度显示图标句柄
	CDC m_dcTempLowShow[10];
	// 温度设置图标句柄
	CDC m_dcTempHighSet[10];
	// 温度显示图标句柄
	CDC m_dcTempLowSet[10];
	// 时间显示图标句柄
	CDC m_dcHourHighShow[10];
	// 时间显示图标句柄
	CDC m_dcHourLowShow[10];
	// 时间显示图标句柄
	CDC m_dcMinHighShow[10];
	// 时间显示图标句柄
	CDC m_dcMinLowShow[10];
	// 时间设置图标句柄
	CDC m_dcHourHighSet[10];
	// 时间设置图标句柄
	CDC m_dcHourLowSet[10];
	// 时间设置图标句柄
	CDC m_dcMinHighSet[10];
	// 时间设置图标句柄
	CDC m_dcMinLowSet[10];
	// 按钮"增加"图标按键
	CDC m_dcAdd;
	// 按钮"减少"图标按键
	CDC m_dcReduce;
	// 时间标志图标句柄
	CDC m_dcTimeLabel;
	// 背景图标句柄
	CDC m_dcBK;
// 	// 速热引擎打开图标句柄
// 	CBitmap m_bmpHeatFastOn;
// 	// 速热引擎关闭图标句柄
// 	CBitmap m_bmpHeatFastOff;
// 	// 冬天打开图标句柄
// 	CBitmap m_bmpWinterOn;
// 	// 冬天关闭图标句柄
// 	CBitmap m_bmpWinterOff;
// 	// 智能助手打开图标句柄
// 	CBitmap m_bmpHelperOn;
// 	// 智能助手关闭图标句柄
// 	CBitmap m_bmpHelperOff;
// 	// 洗手加热打开图标句柄
// 	CBitmap m_bmpWashHandOn;
// 	// 洗手加热关闭图标句柄
// 	CBitmap m_bmpWashHandOff;
// 	// 夜间模式打开图标句柄
// 	CBitmap m_bmpNightModeOn;
// 	// 夜间模式关闭图标句柄
// 	CBitmap m_bmpNightModeOff;
// 	// 温度显示关闭图标句柄
// 	CBitmap m_bmpTempOff;
// 	// 温度保温图标句柄
// 	CBitmap m_bmpTempInsulation;
// 	// 温度加热图标句柄1
// 	CBitmap m_bmpTempHeat1;
// 	// 温度加热图标句柄2
// 	CBitmap m_bmpTempHeat2;
// 	// 温度加热图标句柄3
// 	CBitmap m_bmpTempHeat3;
// 	// 电源打开图标句柄
// 	CBitmap m_bmpPowerOn;
// 	// 电源关闭图标句柄
// 	CBitmap m_bmpPowerOff;
// 	// 温度显示图标句柄
// 	CBitmap m_bmpTempShow[10];
// 	// 温度设置图标句柄
// 	CBitmap m_bmpTempSet[10];
// 	// 时间显示图标句柄
// 	CBitmap m_bmpTimeShow[10];
// 	// 时间设置图标句柄
// 	CBitmap m_bmpTimeSet[10];
// 	// 按钮"增加"图标按键
// 	CBitmap m_bmpAdd;
// 	// 按钮"减少"图标按键
// 	CBitmap m_bmpReduce;
// 	// 时间标志图标句柄
// 	CBitmap m_bmpTimeLabel;
	// 背景
	CBitmap m_bmpBK;
	// 智能助手标志位
	bool m_bHelper;
	bool m_bHelperOld;
	// 注册表中智能助手标志位
	bool m_bHelperReg;
	// 洗手加热标志位
	bool m_bWashHand;
	bool m_bWashHandOld;
	// 注册表中洗手加热标志位
	bool m_bWashHandReg;
	// 夜电模式标志位
	bool m_bNight;
	bool m_bNightOld;
	bool m_bNightMode;
	// 注册表中夜电模式标志位
	bool m_bNightReg;
	// 电源开关标志位
	bool m_bPower;
	bool m_bPowerOld;
	// 注册表中电源开关标志位
	bool m_bPowerReg;
	// 速热引擎状态
	DWORD m_dwFastHeatState;
	DWORD m_dwFastHeatStateOld;
	// 注册表中速热引擎状态
	DWORD m_dwFastHeatStateReg;
	// 温度显示状态
	DWORD m_dwTempState;
	DWORD m_dwTempStateOld;
	// 温度加热显示
	bool m_bTempHeat;
	// 温度单位
	bool m_bTempLabel;
	bool m_bTempLabelOld;
	// 加热显示状态计数
	unsigned int m_uiHeatCount;
	// 温度设置标志位
	bool m_bSetTemp;
	bool m_bSetTempOld;
	// 时间设置标志位
	bool m_bSetTime;
	bool m_bSetTimeOld;
	// 当前时间
	CTime m_CurrTime;
	CTime m_CurrTimeOld;
	// 时间标志位
	bool m_bTimeLabel;
	bool m_bTimeLabelOld;
	// "减少按键标志位"
	bool m_bAdd;
	bool m_bAddOld;
	// "增加按键标志位"
	bool m_bReduce;
	bool m_bReduceOld;
	/** 判断连续操作时间计数*/
	unsigned int m_uiContinuousCount;
	/** 增加操作标志位*/
	bool m_bAddOpt;
	/** 减少操作标志位*/
	bool m_bReduceOpt;
// 	// 设置AlphaBlend参数
// 	BLENDFUNCTION m_blendfun;
	// 串口通讯类成员
	CCEUart m_oCEUart;
	// 箱内温度设置
	DWORD m_dwInTempSet[3];
	DWORD m_dwInTempSetOld;
	// 注册表中箱内温度设置
	DWORD m_dwInTempSetReg[3];
	// 实际的箱内温度
	int m_iInTempActual;
	int m_iInTempActualOld;
	// 实际的环境温度
	int m_iEnvTempActual;
	// 串口接收数据处理记数
	unsigned int m_uiUartRcvCount;
	// 校验位
	BYTE m_byCheck;
	// 串口接收数据处理缓冲区
	BYTE m_ucRcvBuf[UartFrameLength];
	// 闪烁次数计数
	unsigned int m_uiTwinkleCount;
	// 闪烁标志位
	bool m_bTwinkleLabel;
	// 智能助手闪烁标志位
	bool m_bTwinkleHelperLabel;
	// 智能助手图标闪烁功能开启标志位
	bool m_bTwinkleHelper;
	// 注册表中智能助手图标闪烁功能开启标志位
	bool m_bTwinkleHelperReg;
	// 速热引擎闪烁标志位
	bool m_bTwinkleHeatFastLabel;
	// 速热引擎图标闪烁功能开启标志位
	bool m_bTwinkleHeatFast;
	// 注册表中速热引擎图标闪烁功能开启标志位
	bool m_bTwinkleHeatFastReg;
	// png绘制类成员
	CPngImage m_oPngImage;
	// 蜂鸣器PWM
	HANDLE m_hPWM;
	// 设置分钟
	bool m_bSetTimeMin;
	// 软件使用次数限制
	DWORD m_dwSoftUseLimit;
	// HTTP连接类成员
	CCEHttp m_oCEHttp;
	// errorcode
	unsigned int m_uiErrorCode;
	// 使用次数超过设定次数时锁定界面
	bool m_bLock;
	// 防止快速连续点击按键造成按键响应速度跟不上
	bool m_bLBtnDownLimit;
	// 鼠标左键点击区域坐标
	CPoint m_pointLBtn;
public:
	CLog m_oLog;
	CLogThread m_oLogThread;
public:
	// 鼠标左键单击坐标在所选区域内
	bool OnPointInRect(CRect rect, CPoint point);
	// 设置温度
	void OnSetTemp(void);
	// 设置时间
	void OnSetTime(void);
	// 点击速热引擎
	void OnClickedHeatfast();
	// 点击智能助手
	void OnClickedHelper();
	// 点击洗手加热
	void OnClickedWashhand();
	// 点击夜电模式
	void OnClickedNight();
	// 点击开关电源
	void OnClickedPower();
	// 点击增加按键
	void OnClickedAdd();
	// 点击减少按键
	void OnClickedReduce();
	// 串口接收数据回调函数
	static void CALLBACK OnUartRead(void* pFatherPtr, BYTE* pbuf, DWORD dwbufLen);
	// Http请求回调函数
	static CString CALLBACK OnHttpRequest(void* pFatherPtr);
	// Http响应回调函数
	static void CALLBACK OnHttpResponse(void* pFatherPtr, CString strResponse);
	// Http单条命令处理
	LRESULT OnHttpResponseCmd(WPARAM wParam, LPARAM lParam);
	// 向串口发送数据
	void OnWriteUartData(BYTE ucCmd, BYTE ucData);
	// 解析串口接收数据帧
	void PhraseUartFrame();
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnRecvUartData(WPARAM wParam, LPARAM lParam);
private:
	// 初始化界面参数
	void OnReset(void);
public:
	// 载入图片
	void LoadPicture(void);
	// 载入字体
	void LoadFont(void);
	// 设置窗口满屏
	void SetWindowFullScreen(void);
	// 开启蜂鸣器
	void StartBuzzer(void);
	// 关闭蜂鸣器
	void StopBuzzer(void);
	// 打开串口
	void OpenComm(void);
	// 初始化蜂鸣器
	void InitBuzzer(void);
	// 操作蜂鸣器鸣响
	void OptBuzzer(void);
	// 报警蜂鸣器鸣响
	void WarningBuzzer(void);
	// 点击设置温度
	void OnClickedSetTemp(void);
	// 点击设置时间
	void OnClickedSetTime(void);
	// 增加操作
	void OnOptAdd(void);
	// 减小操作
	void OnOptReduce(void);
	// 更新加热状态
	void UpdataHeatState(void);
	// 更新当前时间
	void UpdataCurrTime(void);
	void ContinuousOpt(void);
	// 闪烁设置参数
	void TwinkleSet(void);
	// 发送洗手加热命令
	void SendWashHandCmd(void);
	// 发送夜间模式命令
	void ProNightMode(void);
	// 智能助手闪烁处理
	void TwinkleHelper(void);
	// 速热引擎闪烁处理
	void TwinkleHeatFast(void);
	// 程序初始化
	void OnInit(void);
	// 载入键值
	DWORD LoadRegKey(HKEY hKey, CString strKeyName, DWORD dwDefaultKeyValue, 
		DWORD dwOpenStyle = REG_CREATED_NEW_KEY);
	// 从注册表中载入参数
	void LoadParamFromReg(void);
	// 保存参数到注册表
	void SaveParamToReg(void);
	// 解锁函数
	void UnLockFunc(void);
	// 普通加热
	void OnHeatfastNormal(void);
	// 夏季加热
	void OnHeatfastSummer(void);
	// 冬季加热
	void OnHeatfastWinter(void);
	// 创建日志文件
	void OnInitLog(void);
	// 添加信息到日志文件
	void AddMsgToLog(CString strLog);
};
