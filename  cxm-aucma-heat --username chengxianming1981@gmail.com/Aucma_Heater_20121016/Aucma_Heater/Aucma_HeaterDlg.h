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
	// ��������
	CFont m_FontWinter;
	// �¶�����
	CFont m_FontTemp;
public:
	// ��������ͼƬ���Ʊ���
	CStatic m_ctrlHeatFast;
	// ���������ı����Ʊ���
	CStatic m_staticHeatFast;
	// ����ͼƬ���Ʊ���
	CStatic m_ctrlWinter;
	// �����ı����Ʊ���
	CStatic m_staticWinter;
	// ��������ͼƬ���Ʊ���
	CStatic m_ctrlHelper;
	// ���������ı����Ʊ���
	CStatic m_staticHelper;
	// ϴ�ּ���ͼƬ���Ʊ���
	CStatic m_ctrlWashHand;
	// ϴ�ּ����ı����Ʊ���
	CStatic m_staticWashHand;
	// ҹ��ģʽͼƬ���Ʊ���
	CStatic m_ctrlNightMode;
	// ҹ��ģʽ�ı����Ʊ���
	CStatic m_staticNightMode;
	// �¶�ͼƬ���Ʊ���
	CStatic m_ctrlTemp;
	// �����ı����Ʊ���
	CStatic m_staticTempInsulation;
	// �����ı����Ʊ���
	CStatic m_staticTempHeat;
	// ��ԴͼƬ���Ʊ���
	CStatic m_ctrlPower;
	// �¶ȵ�λ�ı����Ʊ���
	CStatic m_staticTempLabel;
	// �¶ȸ�λ��ʾͼƬ���Ʊ���
	CStatic m_ctrlTempHigh;
	// �¶ȵ�λ��ʾͼƬ���Ʊ���
	CStatic m_ctrlTempLow;
	// Сʱ��λͼƬ���Ʊ���
	CStatic m_ctrlHourHigh;
	// Сʱ��λͼƬ���Ʊ���
	CStatic m_ctrlHourLow;
	// ʱ���־ͼƬ���Ʊ���
	CStatic m_ctrlTimeLabel;
	// ���Ӹ�λͼƬ���Ʊ���
	CStatic m_ctrlMinHigh;
	// ���ӵ�λͼƬ���Ʊ���
	CStatic m_ctrlMinLow;
	// ���������ͼ����
	HBITMAP m_hbmpHeatFastOn;
	// ��������ر�ͼ����
	HBITMAP m_hbmpHeatFastOff;
	// �����ͼ����
	HBITMAP m_hbmpWinterOn;
	// ����ر�ͼ����
	HBITMAP m_hbmpWinterOff;
	// �������ִ�ͼ����
	HBITMAP m_hbmpHelperOn;
	// �������ֹر�ͼ����
	HBITMAP m_hbmpHelperOff;
	// ϴ�ּ��ȴ�ͼ����
	HBITMAP m_hbmpWashHandOn;
	// ϴ�ּ��ȹر�ͼ����
	HBITMAP m_hbmpWashHandOff;
	// ҹ��ģʽ��ͼ����
	HBITMAP m_hbmpNightModeOn;
	// ҹ��ģʽ�ر�ͼ����
	HBITMAP m_hbmpNightModeOff;
	// �¶���ʾ�ر�ͼ����
	HBITMAP m_hbmpTempOff;
	// �¶ȱ���ͼ����
	HBITMAP m_hbmpTempInsulation;
	// �¶ȼ���ͼ����1
	HBITMAP m_hbmpTempHeat1;
	// �¶ȼ���ͼ����2
	HBITMAP m_hbmpTempHeat2;
	// �¶ȼ���ͼ����3
	HBITMAP m_hbmpTempHeat3;
	// ��Դ��ͼ����
	HBITMAP m_hbmpPowerOn;
	// ��Դ�ر�ͼ����
	HBITMAP m_hbmpPowerOff;
	// �¶���ʾͼ����
	HBITMAP m_hbmpTempShow[10];
	// �¶�����ͼ����
	HBITMAP m_hbmpTempSet[10];
	// ʱ����ʾͼ����
	HBITMAP m_hbmpTimeShow[10];
	// ʱ������ͼ����
	HBITMAP m_hbmpTimeSet[10];
	// ��ť"����"ͼ�갴��
	CBitmapButton m_bmpBtnAdd;
	// ��ť"����"ͼ�갴��
	CBitmapButton m_bmpBtnReduce;
	// ���������־λ
	bool m_bHeatFast;
	// �����־λ
	bool m_bWinter;
	// �������ֱ�־λ
	bool m_bHelper;
	// ϴ�ּ��ȱ�־λ
	bool m_bWashHand;
	// ҹ��ģʽ��־λ
	bool m_bNight;
	// �¶ȱ��±�־λ
	bool m_bTempInsulation;
	// �¶ȼ��ȱ�־λ
	bool m_bTempHeat;
	// ��Դ���ر�־λ
	bool m_bPower;
	// ��������״̬
	int m_iFastHeatState;
	// ��������״̬ö��
	enum FastHeatState: int{NormalHeat, FastHeat, WinterHeat};
	// �¶���ʾ״̬
	int m_iTempState;
	// �¶���ʾ״̬
	enum TempShowState: int{NoTempShow, InsulationState, HeatTempState};
	// ������ʾ״̬����
	unsigned int m_uiHeatCount;
	// �����¶�
	int m_iSetTemp;
	// ��ǰ�¶�
	int m_iCurrTemp;
	// �¶����ñ�־λ
	bool m_bSetTemp;
	// ʱ�����ñ�־λ
	bool m_bSetTime;
	// ��ǰʱ��
	CTime m_CurrTime;
public:
	// ͼƬ��������ʾ����
	void OnPictureShow();
	// ����ͼƬ��ͼƬ���
	HBITMAP LoadBitMap(LPCTSTR lpszName);
	// �����ı�������ʾ
	void SetTextHighLighted(CDC* pDC, bool bHighLight);
	// �õ���ǰ�¶�
	int GetCurrTemp(void);
	// ��ʾ�¶�
	void OnShowTemp(unsigned int uiTemp, bool bLight);
	// ��̬�ؼ�ѡ��ͼƬ
	void OnSelectBitMap(CStatic* pStatic, HBITMAP hBitMap);
	// ��ʾ��ǰʱ��
	void OnShowTime(CTime time, bool bLight);
	// �����¶�
	void OnSetTemp(void);
	// ����ʱ��
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
