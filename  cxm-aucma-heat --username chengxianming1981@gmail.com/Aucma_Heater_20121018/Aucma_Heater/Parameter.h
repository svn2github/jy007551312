#ifndef _Parameter_h
#define _Parameter_h

/** �汳��ɫ*/
#define TempTextColor				(RGB(255, 255, 255))
/** Ĭ��������ɫ*/
#define DefaultTextColor			(RGB(132, 128, 144))
/** ѡ��������ɫ*/
#define SelectTextColor				(RGB(255, 0, 0))
/** ����¶�״̬��ʱ�����*/
#define ShowTempStateTimerEvent		1
/** ����¶�״̬��ʱ���*/
#define ShowTempStateTimeSet		1000
/** ���ϵͳʱ�䶨ʱ�����*/
#define ShowTimeTimerEvent			2
/** ���ϵͳʱ�䶨ʱ���*/
#define ShowTimeTimeSet				60000
/** �������Ӻͼ��ٶ�ʱ�����*/
#define ContinuousOptTimerEvent		3
/** �������Ӻͼ��ٶ�ʱ���*/
#define ContinuousOptTimeSet		100
/** ������˸��ʱ�����*/
#define TwinkleTimerEvent			4
/** ������˸��ʱ���*/
#define TwinkleTimeSet				500
/** ��������ʱ�����*/
#define BuzzerTimerEvent			5
/** ������һ�β�������ʱ��*/
#define BuzzerOptTime				175
/** ��������������ʱ��*/
#define BuzzerWarningTime			4925
/** ϴ�ּ���ȷ�϶�ʱ�����*/
#define WashHandTimerEvent			6
/** ϴ�ּ���ȷ�϶�ʱ��ʱ��*/
#define WashHandTimeSet				3000
/** ҹ��ģʽȷ�϶�ʱ�����*/
#define NightModeTimerEvent			7
/** ҹ��ģʽȷ�϶�ʱ��ʱ��*/
#define NightModeTimeSet			3000
/** ����������˸��ʱ�����*/
#define HelperTwinkleTimerEvent		8
/** ����������˸��ʱ��ʱ��*/
#define HelperTwinkleTimeSet		500
/** ����������˸��ʱ�����*/
#define HeatFastTwinkleTimerEvent	9
/** ����������˸��ʱ��ʱ��*/
#define HeatFastTwinkleTimeSet		500
/** ��˸��������*/
#define TwinkleMaxTimes				6
/** ������Ӻͼ��ٴﵽʱ������������ж���������*/
#define ContinuousOptTimes			6
/** ��������״̬ö��*/
enum {NormalHeat, SummerHeat, WinterHeat};
/** �¶���ʾ״̬*/
enum {NoTempShow, InsulationState, HeatTempState};
/** ͼƬ���ڵ��ļ���*/
//#define PicFolderName					_T("\\Storage Card\\Folder2\\")
#define PicFolderName					_T("\\Program Files\\Folder2\\")
/** ����ע���������*/
#define RegKeyNameHeater				_T("Aucma\\Heater")
/** ����ע�����ͨ�����¶������Ӽ���*/
#define RegSubKeyNameNHST				_T("��ͨ�����¶�")
/** ����ע����ļ������¶������Ӽ���*/
#define RegSubKeyNameSHST				_T("�ļ������¶�")
/** ����ע����������¶������Ӽ���*/
#define RegSubKeyNameWHST				_T("���������¶�")
/** ����ע������ģʽ�Ӽ���*/
#define RegSubKeyNameHeatMode			_T("����ģʽ")
/** ����ע���ϴ��ģʽ�Ӽ���*/
#define RegSubKeyNameWashMode			_T("ϴ��ģʽ")
/** ����ע���ҹ��ģʽ�Ӽ���*/
#define RegSubKeyNameNightMode			_T("ҹ��ģʽ")
/** ����ע�������ģʽ�Ӽ���*/
#define RegSubKeyNameHelperMode			_T("����ģʽ")
/** ����ע����Դ�����Ӽ���*/
#define RegSubKeyNamePower				_T("��Դ����")
/** ����ע�������������˸�Ӽ���*/
#define RegSubKeyNameHelperTwinkle		_T("����������˸")
/** ����ע�������������˸�Ӽ���*/
#define RegSubKeyNameHeatFastTwinkle	_T("����������˸")
// @@@��������
/** ����ע������ʹ�ô��������Ӽ���*/
#define RegSubKeyNameLimit				_T("��������")
/** ������ô�������*/
#define SoftUseLimitNum					20
/** �����ı��������ƫ����1*/
#define TextOutMovePos1					8
/** �����ı��������ƫ����2*/
#define TextOutMovePos2					4
/** ��ͨ����Ĭ�������¶�*/
#define DefaultNormalTemp				80
/** ��������Ĭ�������¶�*/
#define DefaultWinterTemp				80
/** �ļ�����Ĭ�������¶�*/
#define DefaultSummerTemp				50
/** Ĭ������ʵ���¶�*/
#define DefaultInTempActual				48
/** Ĭ��pngͼƬ͸��������*/
#define DefaultPNGTransparent			128
/** �����¶�����ֵ*/
#define SetTempMaxLimit					80
/** �����¶�����ֵ*/
#define SetTempMinLimit					30
/** ���ڽ���������Ϣ*/
#define WM_RECV_UART_DATA				WM_USER + 100
/** Ĭ�Ϸ�����Ƶ�ʣ���Ϊ1��Ƶ��Ϊ2Hz*/
#define DefaultBuzzFrq					2
/** ǿ�ƽ����߳�ʱ��*/
#define TerminalThreadTime				4000
/************************************************************************/
/*                ����ͨѶ������                                        */
/************************************************************************/
/** ֡����*/
#define UartFrameLength					7
/** ֡ͷ1*/
#define UartFrameHead1					0x51
/** ֡ͷ2*/
#define UartFrameHead2					0x85
/** �������ն˴���*/
#define ClientNo						0x00
// /** ���� LCD����*/
// #define CMD_IHMT_CTRL				0x60
// /** ��λ������*/
// #define CMD_IHMT_RST					0x61
/** ��������ִ��*/
#define CMD_DOWN_HP						0x69
/** ʵ�ʻ����¶�*/
#define	CMD_DOWN_ET						0x70
/** ʵ�������¶�*/
#define	CMD_DOWN_IT						0x71
/** ��������*/
#define	CMD_DOWN_WT						0x72
/** ���������¶�*/
#define CMD_DOWN_QT						0x73

/** ʱ��Сʱ��*/
#define CMD_UP_HOUR						0x60
/** ʱ�������*/
#define CMD_UP_WEEK						0x61
/** ������������*/
#define CMD_UP_WO						0x80
/** �ļ���������*/
#define CMD_UP_SO						0x81
/** ��������*/
#define CMD_UP_HP						0x82
/** ���������¶�*/
#define CMD_UP_IT						0x83
/** ҹ������*/
#define CMD_UP_NO						0x84
/** ϴ�ּ���*/
#define CMD_UP_WH						0x85
/** ���ص�Դ*/
#define CMD_UP_PW						0x86
// /** ���±����¶�����*/
// #define CMD_UP_HAM					0x84
// /** ���±����¶�����*/
// #define CMD_UP_LAM					0x85
/** ֡β*/
#define UartFrameTail					0xED

// /** �ر� LCD����*/
// #define CMD_IHMT_OFF					0x00
// /** �� LCD����*/
// #define CMD_IHMT_ON					0x01
/** ����/ȱˮ����*/
#define CMD_WORD_WT_NWE					0x00
/** ���������ϱ���*/
#define CMD_WORD_WT_SE					0x01
/** ©����ϱ���*/
#define CMD_WORD_WT_LE					0x02
/** ˮ�³��߹��ϱ���*/
#define CMD_WORD_WT_WHE					0x03
/** ©����Ȧ���ϱ���*/
#define CMD_WORD_WT_LCE					0x04
/** ����/ȱˮ��������*/
#define CMD_WORD_WT_NWEC				0x05
/** ���������ϱ�������*/
#define CMD_WORD_WT_SEC					0x06
/** ©����ϱ�������*/
#define CMD_WORD_WT_LEC					0x07
/** ˮ�³��߹��ϱ�������*/
#define CMD_WORD_WT_WHEC				0x08
/** ©����Ȧ���ϱ�������*/
#define CMD_WORD_WT_LCEC				0x09
/** ˮ������*/
#define CMD_WORD_WT_WE					0x0a
/** ˮ������*/
#define CMD_WORD_WT_WL					0x0b
/** �������ܿ���*/
#define CMD_WORD_WO						0x01
/** �ļ����ܿ���*/
#define CMD_WORD_SO						0x01
/** �������ֹر�*/
#define CMD_WORD_HC						0x00
/** �������ֿ���*/
#define CMD_WORD_HO						0x01
/** ҹ�����з�ʽ�ر�*/
#define CMD_WORD_NC						0x00
/** ҹ�����з�ʽ����*/
#define CMD_WORD_NO						0x01
/** ϴ�ּ��ȹر�*/
#define CMD_WORD_WHC					0x00
/** ϴ�ּ��ȿ���*/
#define CMD_WORD_WHO					0x01
/** �������״̬*/
#define CMD_WORD_PC						0x00
/** ��ͨ����ģʽ*/
#define CMD_WORD_PO						0x01
/************************************************************************/
/*					HTTPͨѶ                                            */
/************************************************************************/
/** ��������ַ��Ϣ*/
#define ServerURL	_T("http://mail.shgymy.com:9898/reshuiqiSrv/renshuiqisrv")
/** HTTP��ʱʱ��*/
#define HttpTimeout						1000
/** HTTP�����߳�����ʱ��*/
#define HttpThreadSleepTime				3000
/** HTTP*/
#define HttpContentType	_T("Content-Type: application/x-www-form-urlencoded")
/** HTTP��Ϣ�����¶�*/
#define WM_HTTP_SETTEMP					WM_USER + 101
/** HTTP��Ϣ����ʱ��*/
#define WM_HTTP_SETTIME					WM_USER + 102
/** HTTP��Ϣ��������*/
#define WM_HTTP_HEATFAST				WM_USER + 103
/** HTTP��Ϣ��������*/
#define WM_HTTP_HELPER					WM_USER + 104
/** HTTP��Ϣϴ�ּ���*/
#define WM_HTTP_WASHHAND				WM_USER + 105
/** HTTP��Ϣҹ��ģʽ*/
#define WM_HTTP_NIGHTMODE				WM_USER + 106
/** HTTP��Ϣ��Դ����*/
#define WM_HTTP_POWER					WM_USER + 107
#endif