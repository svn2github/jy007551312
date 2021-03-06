// Aucma_HeaterDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

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
	// 背景刷子
	CBrush m_brushBk;
	// 系统默认字体
	CFont m_FontDefault;
	// 冬天字体
	CFont m_FontWinter;
	// 温度字体
	CFont m_FontTemp;
public:
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
	// 速热引擎打开图标句柄
	CBitmap m_bmpHeatFastOn;
	// 速热引擎关闭图标句柄
	CBitmap m_bmpHeatFastOff;
	// 冬天打开图标句柄
	CBitmap m_bmpWinterOn;
	// 冬天关闭图标句柄
	CBitmap m_bmpWinterOff;
	// 智能助手打开图标句柄
	CBitmap m_bmpHelperOn;
	// 智能助手关闭图标句柄
	CBitmap m_bmpHelperOff;
	// 洗手加热打开图标句柄
	CBitmap m_bmpWashHandOn;
	// 洗手加热关闭图标句柄
	CBitmap m_bmpWashHandOff;
	// 夜间模式打开图标句柄
	CBitmap m_bmpNightModeOn;
	// 夜间模式关闭图标句柄
	CBitmap m_bmpNightModeOff;
	// 温度显示关闭图标句柄
	CBitmap m_bmpTempOff;
	// 温度保温图标句柄
	CBitmap m_bmpTempInsulation;
	// 温度加热图标句柄1
	CBitmap m_bmpTempHeat1;
	// 温度加热图标句柄2
	CBitmap m_bmpTempHeat2;
	// 温度加热图标句柄3
	CBitmap m_bmpTempHeat3;
	// 电源打开图标句柄
	CBitmap m_bmpPowerOn;
	// 电源关闭图标句柄
	CBitmap m_bmpPowerOff;
	// 温度显示图标句柄
	CBitmap m_bmpTempShow[10];
	// 温度设置图标句柄
	CBitmap m_bmpTempSet[10];
	// 时间显示图标句柄
	CBitmap m_bmpTimeShow[10];
	// 时间设置图标句柄
	CBitmap m_bmpTimeSet[10];
	// 按钮"增加"图标按键
	CBitmap m_bmpAdd;
	// 按钮"减少"图标按键
	CBitmap m_bmpReduce;
	// 时间标志图标句柄
	CBitmap m_bmpTimeLabel;
	// 智能助手标志位
	bool m_bHelper;
	bool m_bHelperOld;
	// 洗手加热标志位
	bool m_bWashHand;
	bool m_bWashHandOld;
	// 夜电模式标志位
	bool m_bNight;
	bool m_bNightOld;
	// 电源开关标志位
	bool m_bPower;
	bool m_bPowerOld;
	// 速热引擎状态
	int m_iFastHeatState;
	int m_iFastHeatStateOld;
	// 速热引擎状态枚举
	enum FastHeatState: int{NormalHeat, FastHeat, WinterHeat};
	// 温度显示状态
	int m_iTempState;
	int m_iTempStateOld;
	// 温度加热显示
	bool m_bTempHeat;
	// 温度显示状态
	enum TempShowState: int{NoTempShow, InsulationState, HeatTempState};
	// 温度单位
	bool m_bTempLabel;
	bool m_bTempLabelOld;
	// 加热显示状态计数
	unsigned int m_uiHeatCount;
	// 设置温度
	int m_iSetTemp;
	int m_iSetTempOld;
	// 当前温度
	int m_iCurrTemp;
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
public:
	// 设置绘图坐标区域
	CRect OnSetRect(int x, int y, int iWidth, int iHeight);
	// 得到当前温度
	int GetCurrTemp(void);
	// 设置温度
	void OnSetTemp(void);
	// 设置时间
	void OnSetTime(void);
	// 将位图选入内存设备
	void OnDcBitBlt(CDC* pDC, CDC* pmemDC, CRect rect, CBitmap* pBitmap);
	// 鼠标左键单击坐标在所选区域内
	bool OnPointInRect(CRect rect, CPoint point);
	void OnClickedHeatfast();
	void OnClickedHelper();
	void OnClickedWashhand();
	void OnClickedNight();
	void OnClickedPower();
	void OnClickedAdd();
	void OnClickedReduce();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
