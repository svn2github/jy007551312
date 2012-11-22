// Aucma_HeaterDlg.h : ͷ�ļ�
//
#pragma once
#include "..\UART_WINCE\CEUart.h"
#include "Parameter.h"
#include "PngImage.h"
// CAucma_HeaterDlg �Ի���
class CAucma_HeaterDlg : public CDialog
{
// ����
public:
	CAucma_HeaterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUCMA_HEATER_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
private:
// 	// ����ˢ��
// 	CBrush m_brushBk;
	// ϵͳĬ������
	CFont m_FontDefault;
	// ��������
	CFont m_FontWinter;
	// �¶�����
	CFont m_FontTemp;
	// ��������ͼƬ��ͼ����
	CRect m_rectHeatFastPic;
	// ���������ı���ͼ����
	CRect m_rectHeatFastText;
	// ����ͼƬ��ͼ����
	CRect m_rectWinterPic;
	// �����ı���ͼ����
	CRect m_rectWinterText;
	// ��������ͼƬ��ͼ����
	CRect m_rectHelperPic;
	// ���������ı���ͼ����
	CRect m_rectHelperText;
	// ϴ�ּ���ͼƬ��ͼ����
	CRect m_rectWashHandPic;
	// ϴ�ּ����ı���ͼ����
	CRect m_rectWashHandText;
	// ҹ��ģʽͼƬ��ͼ����
	CRect m_rectNightModePic;
	// ҹ��ģʽ�ı���ͼ����
	CRect m_rectNightModeText;
	// �¶�ͼƬ��ͼ����
	CRect m_rectTempPic;
	// �����ı���ͼ����
	CRect m_rectTempInsulationText;
	// �����ı���ͼ����
	CRect m_rectTempHeatText;
	// ��ԴͼƬ��ͼ����
	CRect m_rectPowerPic;
	// �¶ȵ�λ�ı���ͼ����
	CRect m_rectTempLabelText;
	// �¶ȸ�λ��ʾͼƬ��ͼ����
	CRect m_rectTempHighPic;
	// �¶ȵ�λ��ʾͼƬ��ͼ����
	CRect m_rectTempLowPic;
	// Сʱ��λͼƬ��ͼ����
	CRect m_rectHourHighPic;
	// Сʱ��λͼƬ��ͼ����
	CRect m_rectHourLowPic;
	// ʱ���־ͼƬ��ͼ����
	CRect m_rectTimeLabelPic;
	// ���Ӹ�λͼƬ��ͼ����
	CRect m_rectMinHighPic;
	// ���ӵ�λͼƬ��ͼ����
	CRect m_rectMinLowPic;
	// "����"ͼƬ��ͼ����
	CRect m_rectAdd;
	// "����"ͼƬ��ͼ����
	CRect m_rectReduce;
	// �¶�����Χ
	CRect m_rectTemp;
	// ʱ������Χ
	CRect m_rectTime;
	// ������Χ
	CRect m_rectBK;
	// ���������ͼ����
	CDC m_dcHeatFastOn;
	// ��������ر�ͼ����
	CDC m_dcHeatFastOff;
	// �����ͼ����
	CDC m_dcWinterOn;
	// ����ر�ͼ����
	CDC m_dcWinterOff;
	// �������ִ�ͼ����
	CDC m_dcHelperOn;
	// �������ֹر�ͼ����
	CDC m_dcHelperOff;
	// ϴ�ּ��ȴ�ͼ����
	CDC m_dcWashHandOn;
	// ϴ�ּ��ȹر�ͼ����
	CDC m_dcWashHandOff;
	// ҹ��ģʽ��ͼ����
	CDC m_dcNightModeOn;
	// ҹ��ģʽ�ر�ͼ����
	CDC m_dcNightModeOff;
	// �¶���ʾ�ر�ͼ����
	CDC m_dcTempOff;
	// �¶ȱ���ͼ����
	CDC m_dcTempInsulation;
	// �¶ȼ���ͼ����1
	CDC m_dcTempHeat1;
	// �¶ȼ���ͼ����2
	CDC m_dcTempHeat2;
	// �¶ȼ���ͼ����3
	CDC m_dcTempHeat3;
	// ��Դ��ͼ����
	CDC m_dcPowerOn;
	// ��Դ�ر�ͼ����
	CDC m_dcPowerOff;
	// �¶���ʾͼ����
	CDC m_dcTempHighShow[10];
	// �¶���ʾͼ����
	CDC m_dcTempLowShow[10];
	// �¶�����ͼ����
	CDC m_dcTempHighSet[10];
	// �¶���ʾͼ����
	CDC m_dcTempLowSet[10];
	// ʱ����ʾͼ����
	CDC m_dcHourHighShow[10];
	// ʱ����ʾͼ����
	CDC m_dcHourLowShow[10];
	// ʱ����ʾͼ����
	CDC m_dcMinHighShow[10];
	// ʱ����ʾͼ����
	CDC m_dcMinLowShow[10];
	// ʱ������ͼ����
	CDC m_dcHourHighSet[10];
	// ʱ������ͼ����
	CDC m_dcHourLowSet[10];
	// ʱ������ͼ����
	CDC m_dcMinHighSet[10];
	// ʱ������ͼ����
	CDC m_dcMinLowSet[10];
	// ��ť"����"ͼ�갴��
	CDC m_dcAdd;
	// ��ť"����"ͼ�갴��
	CDC m_dcReduce;
	// ʱ���־ͼ����
	CDC m_dcTimeLabel;
	// ����ͼ����
	CDC m_dcBK;
// 	// ���������ͼ����
// 	CBitmap m_bmpHeatFastOn;
// 	// ��������ر�ͼ����
// 	CBitmap m_bmpHeatFastOff;
// 	// �����ͼ����
// 	CBitmap m_bmpWinterOn;
// 	// ����ر�ͼ����
// 	CBitmap m_bmpWinterOff;
// 	// �������ִ�ͼ����
// 	CBitmap m_bmpHelperOn;
// 	// �������ֹر�ͼ����
// 	CBitmap m_bmpHelperOff;
// 	// ϴ�ּ��ȴ�ͼ����
// 	CBitmap m_bmpWashHandOn;
// 	// ϴ�ּ��ȹر�ͼ����
// 	CBitmap m_bmpWashHandOff;
// 	// ҹ��ģʽ��ͼ����
// 	CBitmap m_bmpNightModeOn;
// 	// ҹ��ģʽ�ر�ͼ����
// 	CBitmap m_bmpNightModeOff;
// 	// �¶���ʾ�ر�ͼ����
// 	CBitmap m_bmpTempOff;
// 	// �¶ȱ���ͼ����
// 	CBitmap m_bmpTempInsulation;
// 	// �¶ȼ���ͼ����1
// 	CBitmap m_bmpTempHeat1;
// 	// �¶ȼ���ͼ����2
// 	CBitmap m_bmpTempHeat2;
// 	// �¶ȼ���ͼ����3
// 	CBitmap m_bmpTempHeat3;
// 	// ��Դ��ͼ����
// 	CBitmap m_bmpPowerOn;
// 	// ��Դ�ر�ͼ����
// 	CBitmap m_bmpPowerOff;
// 	// �¶���ʾͼ����
// 	CBitmap m_bmpTempShow[10];
// 	// �¶�����ͼ����
// 	CBitmap m_bmpTempSet[10];
// 	// ʱ����ʾͼ����
// 	CBitmap m_bmpTimeShow[10];
// 	// ʱ������ͼ����
// 	CBitmap m_bmpTimeSet[10];
// 	// ��ť"����"ͼ�갴��
// 	CBitmap m_bmpAdd;
// 	// ��ť"����"ͼ�갴��
// 	CBitmap m_bmpReduce;
// 	// ʱ���־ͼ����
// 	CBitmap m_bmpTimeLabel;
	// ����
	CBitmap m_bmpBK;
	// �������ֱ�־λ
	bool m_bHelper;
	bool m_bHelperOld;
	// ϴ�ּ��ȱ�־λ
	bool m_bWashHand;
	bool m_bWashHandOld;
	// ҹ��ģʽ��־λ
	bool m_bNight;
	bool m_bNightOld;
	// ��Դ���ر�־λ
	bool m_bPower;
	bool m_bPowerOld;
	// ��������״̬
	int m_iFastHeatState;
	int m_iFastHeatStateOld;
	// �¶���ʾ״̬
	int m_iTempState;
	int m_iTempStateOld;
	// �¶ȼ�����ʾ
	bool m_bTempHeat;
	// �¶ȵ�λ
	bool m_bTempLabel;
	bool m_bTempLabelOld;
	// ������ʾ״̬����
	unsigned int m_uiHeatCount;
	// �¶����ñ�־λ
	bool m_bSetTemp;
	bool m_bSetTempOld;
	// ʱ�����ñ�־λ
	bool m_bSetTime;
	bool m_bSetTimeOld;
	// ��ǰʱ��
	CTime m_CurrTime;
	CTime m_CurrTimeOld;
	// ʱ���־λ
	bool m_bTimeLabel;
	bool m_bTimeLabelOld;
	// "���ٰ�����־λ"
	bool m_bAdd;
	bool m_bAddOld;
	// "���Ӱ�����־λ"
	bool m_bReduce;
	bool m_bReduceOld;
	/** �ж���������ʱ�����*/
	unsigned int m_uiContinuousCount;
	/** ���Ӳ�����־λ*/
	bool m_bAddOpt;
	/** ���ٲ�����־λ*/
	bool m_bReduceOpt;
// 	// ����AlphaBlend����
// 	BLENDFUNCTION m_blendfun;
	// ����ͨѶ���Ա
	CCEUart m_oCEUart;
	// ���������¶�
	int m_iInTempSet;
	int m_iInTempSetOld;
	// ʵ�ʵ������¶�
	int m_iInTempActual;
	// ʵ�ʵĻ����¶�
	int m_iEnvTempActual;
// 	// ���ø��±����¶�
// 	int m_iHighWarnTemp;
// 	// ���õ��±����¶�
// 	int m_iLowWarnTemp;
	// ���ڽ������ݴ������
	unsigned int m_uiUartRcvCount;
	// У��λ
	BYTE m_byCheck;
	// ���ڽ������ݴ�������
	BYTE m_ucRcvBuf[UartFrameLength];
	// ��˸��������
	unsigned int m_uiTwinkleCount;
	// ��˸��־λ
	bool m_bTwinkle;
//	// ��˸���ߴ���
//	unsigned int m_uiTwinkleSleepTimes;
	// png�������Ա
	CPngImage m_oPngImage;
	// ������PWM
	HANDLE m_hPWM;
public:
	// ������������������ѡ������
	bool OnPointInRect(CRect rect, CPoint point);
	// �����¶�
	void OnSetTemp(void);
	// ����ʱ��
	void OnSetTime(void);
	// �����������
	void OnClickedHeatfast();
	// �����������
	void OnClickedHelper();
	// ���ϴ�ּ���
	void OnClickedWashhand();
	// ���ҹ��ģʽ
	void OnClickedNight();
	// ������ص�Դ
	void OnClickedPower();
	// ������Ӱ���
	void OnClickedAdd();
	// ������ٰ���
	void OnClickedReduce();
	// ���ڽ������ݻص�����
	static void CALLBACK OnUartRead(void* pFatherPtr, BYTE* pbuf, DWORD dwbufLen);
	// �򴮿ڷ�������
	void OnWriteUartData(BYTE ucCmd, BYTE ucData);
	// �������ڽ�������֡
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
	// ��ʼ���������
	void OnInit(void);
public:
	// ����ͼƬ
	void LoadPicture(void);
	// ��������
	void LoadFont(void);
	// ���ô�������
	void SetWindowFullScreen(void);
	// ����������
	void StartBuzzer(int iPwmValue = DefaultBuzzFrq);
	// �رշ�����
	void StopBuzzer(void);
};
