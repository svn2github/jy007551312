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
	// 冬天字体
	CFont m_FontWinter;
	// 温度字体
	CFont m_FontTemp;
public:
	// 速热引擎图片控制变量
	CStatic m_ctrlHeatFast;
	// 速热引擎文本控制变量
	CStatic m_staticHeatFast;
	// 冬天图片控制变量
	CStatic m_ctrlWinter;
	// 冬天文本控制变量
	CStatic m_staticWinter;
	// 智能助手图片控制变量
	CStatic m_ctrlHelper;
	// 智能助手文本控制变量
	CStatic m_staticHelper;
	// 洗手加热图片控制变量
	CStatic m_ctrlWashHand;
	// 洗手加热文本控制变量
	CStatic m_staticWashHand;
	// 夜电模式图片控制变量
	CStatic m_ctrlNightMode;
	// 夜电模式文本控制变量
	CStatic m_staticNightMode;
	// 温度图片控制变量
	CStatic m_ctrlTemp;
	// 保温文本控制变量
	CStatic m_staticTempInsulation;
	// 加热文本控制变量
	CStatic m_staticTempHeat;
	// 电源图片控制变量
	CStatic m_ctrlPower;
	// 温度单位文本控制变量
	CStatic m_staticTempLabel;
	// 温度高位显示图片控制变量
	CStatic m_ctrlTempHigh;
	// 温度低位显示图片控制变量
	CStatic m_ctrlTempLow;
	// 小时高位图片控制变量
	CStatic m_ctrlHourHigh;
	// 小时低位图片控制变量
	CStatic m_ctrlHourLow;
	// 时间标志图片控制变量
	CStatic m_ctrlTimeLabel;
	// 分钟高位图片控制变量
	CStatic m_ctrlMinHigh;
	// 分钟低位图片控制变量
	CStatic m_ctrlMinLow;
	// 速热引擎打开图标句柄
	HBITMAP m_hbmpHeatFastOn;
	// 速热引擎关闭图标句柄
	HBITMAP m_hbmpHeatFastOff;
	// 冬天打开图标句柄
	HBITMAP m_hbmpWinterOn;
	// 冬天关闭图标句柄
	HBITMAP m_hbmpWinterOff;
	// 智能助手打开图标句柄
	HBITMAP m_hbmpHelperOn;
	// 智能助手关闭图标句柄
	HBITMAP m_hbmpHelperOff;
	// 洗手加热打开图标句柄
	HBITMAP m_hbmpWashHandOn;
	// 洗手加热关闭图标句柄
	HBITMAP m_hbmpWashHandOff;
	// 夜间模式打开图标句柄
	HBITMAP m_hbmpNightModeOn;
	// 夜间模式关闭图标句柄
	HBITMAP m_hbmpNightModeOff;
	// 温度显示关闭图标句柄
	HBITMAP m_hbmpTempOff;
	// 温度保温图标句柄
	HBITMAP m_hbmpTempInsulation;
	// 温度加热图标句柄1
	HBITMAP m_hbmpTempHeat1;
	// 温度加热图标句柄2
	HBITMAP m_hbmpTempHeat2;
	// 温度加热图标句柄3
	HBITMAP m_hbmpTempHeat3;
	// 电源打开图标句柄
	HBITMAP m_hbmpPowerOn;
	// 电源关闭图标句柄
	HBITMAP m_hbmpPowerOff;
	// 温度显示图标句柄
	HBITMAP m_hbmpTempShow[10];
	// 温度设置图标句柄
	HBITMAP m_hbmpTempSet[10];
	// 时间显示图标句柄
	HBITMAP m_hbmpTimeShow[10];
	// 时间设置图标句柄
	HBITMAP m_hbmpTimeSet[10];
	// 按钮"增加"图标按键
	CBitmapButton m_bmpBtnAdd;
	// 按钮"减少"图标按键
	CBitmapButton m_bmpBtnReduce;
	// 速热引擎标志位
	bool m_bHeatFast;
	// 冬天标志位
	bool m_bWinter;
	// 智能助手标志位
	bool m_bHelper;
	// 洗手加热标志位
	bool m_bWashHand;
	// 夜电模式标志位
	bool m_bNight;
	// 温度保温标志位
	bool m_bTempInsulation;
	// 温度加热标志位
	bool m_bTempHeat;
	// 电源开关标志位
	bool m_bPower;
	// 速热引擎状态
	int m_iFastHeatState;
	// 速热引擎状态枚举
	enum FastHeatState: int{NormalHeat, FastHeat, WinterHeat};
	// 温度显示状态
	int m_iTempState;
	// 温度显示状态
	enum TempShowState: int{NoTempShow, InsulationState, HeatTempState};
	// 加热显示状态计数
	unsigned int m_uiHeatCount;
	// 设置温度
	int m_iSetTemp;
	// 当前温度
	int m_iCurrTemp;
	// 温度设置标志位
	bool m_bSetTemp;
	// 时间设置标志位
	bool m_bSetTime;
	// 当前时间
	CTime m_CurrTime;
public:
	// 图片和文字显示函数
	void OnPictureShow();
	// 载入图片到图片句柄
	HBITMAP LoadBitMap(LPCTSTR lpszName);
	// 设置文本高亮显示
	void SetTextHighLighted(CDC* pDC, bool bHighLight);
	// 得到当前温度
	int GetCurrTemp(void);
	// 显示温度
	void OnShowTemp(unsigned int uiTemp, bool bLight);
	// 静态控件选择图片
	void OnSelectBitMap(CStatic* pStatic, HBITMAP hBitMap);
	// 显示当前时间
	void OnShowTime(CTime time, bool bLight);
	// 设置温度
	void OnSetTemp(void);
	// 设置时间
	void OnSetTime(void);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedHeatfast();
	afx_msg void OnStnClickedHelper();
	afx_msg void OnStnClickedWashhand();
	afx_msg void OnDestroy();
	afx_msg void OnStnClickedNight();
	afx_msg void OnStnClickedPower();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedTempHigh();
	afx_msg void OnStnClickedTempLow();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnReduce();
	afx_msg void OnStnClickedHourHigh();
	afx_msg void OnStnClickedHourLow();
	afx_msg void OnStnClickedTimeLabel();
	afx_msg void OnStnClickedMinHigh();
	afx_msg void OnStnClickedMinLow();
};
