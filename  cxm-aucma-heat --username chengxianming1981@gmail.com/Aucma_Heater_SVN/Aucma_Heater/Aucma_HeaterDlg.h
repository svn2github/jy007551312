// Aucma_HeaterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

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
	// ����ˢ��
	CBrush m_brushBk;
	// ϵͳĬ������
	CFont m_FontDefault;
	// ��������
	CFont m_FontWinter;
	// �¶�����
	CFont m_FontTemp;
public:
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
	// ���������ͼ����
	CBitmap m_bmpHeatFastOn;
	// ��������ر�ͼ����
	CBitmap m_bmpHeatFastOff;
	// �����ͼ����
	CBitmap m_bmpWinterOn;
	// ����ر�ͼ����
	CBitmap m_bmpWinterOff;
	// �������ִ�ͼ����
	CBitmap m_bmpHelperOn;
	// �������ֹر�ͼ����
	CBitmap m_bmpHelperOff;
	// ϴ�ּ��ȴ�ͼ����
	CBitmap m_bmpWashHandOn;
	// ϴ�ּ��ȹر�ͼ����
	CBitmap m_bmpWashHandOff;
	// ҹ��ģʽ��ͼ����
	CBitmap m_bmpNightModeOn;
	// ҹ��ģʽ�ر�ͼ����
	CBitmap m_bmpNightModeOff;
	// �¶���ʾ�ر�ͼ����
	CBitmap m_bmpTempOff;
	// �¶ȱ���ͼ����
	CBitmap m_bmpTempInsulation;
	// �¶ȼ���ͼ����1
	CBitmap m_bmpTempHeat1;
	// �¶ȼ���ͼ����2
	CBitmap m_bmpTempHeat2;
	// �¶ȼ���ͼ����3
	CBitmap m_bmpTempHeat3;
	// ��Դ��ͼ����
	CBitmap m_bmpPowerOn;
	// ��Դ�ر�ͼ����
	CBitmap m_bmpPowerOff;
	// �¶���ʾͼ����
	CBitmap m_bmpTempShow[10];
	// �¶�����ͼ����
	CBitmap m_bmpTempSet[10];
	// ʱ����ʾͼ����
	CBitmap m_bmpTimeShow[10];
	// ʱ������ͼ����
	CBitmap m_bmpTimeSet[10];
	// ��ť"����"ͼ�갴��
	CBitmap m_bmpAdd;
	// ��ť"����"ͼ�갴��
	CBitmap m_bmpReduce;
	// ʱ���־ͼ����
	CBitmap m_bmpTimeLabel;
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
	// �����¶�
	int m_iSetTemp;
	int m_iSetTempOld;
	// ��ǰ�¶�
	int m_iCurrTemp;
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
public:
	// ���û�ͼ��������
	CRect OnSetRect(int x, int y, int iWidth, int iHeight);
	// �õ���ǰ�¶�
	int GetCurrTemp(void);
	// �����¶�
	void OnSetTemp(void);
	// ����ʱ��
	void OnSetTime(void);
	// ��λͼѡ���ڴ��豸
	void OnDcBitBlt(CDC* pDC, CDC* pmemDC, CRect rect, CBitmap* pBitmap);
	// ������������������ѡ������
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