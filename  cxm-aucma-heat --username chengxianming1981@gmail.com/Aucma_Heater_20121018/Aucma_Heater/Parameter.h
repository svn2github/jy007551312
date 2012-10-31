#ifndef _Parameter_h
#define _Parameter_h

/** ����Ի��򱳾���ɫ*/
#define DialogBkColor		(RGB(255, 255, 255))
/** Ĭ��������ɫ*/
#define DefaultTextColor	(RGB(132, 128, 144))
/** ѡ��������ɫ*/
#define SelectTextColor		(RGB(255, 0, 0))
/** ����¶�״̬��ʱ�����*/
#define ShowTempStateTimerEvent	1
/** ����¶�״̬��ʱ���*/
#define ShowTempStateTimeSet	1000
/** ���ϵͳʱ�䶨ʱ�����*/
#define ShowTimeTimerEvent		2
/** ���ϵͳʱ�䶨ʱ���*/
#define ShowTimeTimeSet			10000
/** �������Ӻͼ��ٶ�ʱ�����*/
#define ContinuousOptTimerEvent		3
/** �������Ӻͼ��ٶ�ʱ���*/
#define ContinuousOptTimeSet		100
/** ������˸��ʱ�����*/
#define TwinkleTimerEvent			4
/** ������˸��ʱ���*/
#define TwinkleTimeSet				500
/** ���ӻ���ٲ���ʱ��ʱ�ر���˸��ʱ��ʱ����*/
#define TwinkleTimerSleepTimes		3
/** ��˸��������*/
#define TwinkleMaxTimes				20
/** ������Ӻͼ��ٴﵽʱ������������ж���������*/
#define ContinuousOptTimes			6
/** ��������״̬ö��*/
enum {NormalHeat, FastHeat, WinterHeat};
/** �¶���ʾ״̬*/
enum {NoTempShow, InsulationState, HeatTempState};
/** ͼƬ���ڵ��ļ���*/
#define PicFolderName				_T("\\Storage Card\\Folder2\\")
/** �����ı��������ƫ����1*/
#define TextOutMovePos1				8
/** �����ı��������ƫ����2*/
#define TextOutMovePos2				4
/** Ĭ�������¶�*/
#define DefaultSetTemp				30
/** Ĭ��pngͼƬ͸��������*/
#define DefaultPNGTransparent		128
/** �����¶�����ֵ*/
#define SetTempMaxLimit				80
/** �����¶�����ֵ*/
#define SetTempMinLimit				30
/** ���ڽ���������Ϣ*/
#define WM_RECV_UART_DATA	WM_USER + 100
/************************************************************************/
/*                ����ͨѶ������                                        */
/************************************************************************/
/** ֡����*/
#define UartFrameLength				7
/** ֡ͷ1*/
#define UartFrameHead1				0x51
/** ֡ͷ2*/
#define UartFrameHead2				0x85
/** �������ն˴���*/
#define ClientNo					0x00
/** ���� LCD����*/
#define CMD_IHMT_CTRL				0x60
/** ��λ������*/
#define CMD_IHMT_RST				0x61
/** ʵ�ʻ����¶�*/
#define	CMD_DOWN_ET					0x70
/** ʵ�������¶�*/
#define	CMD_DOWN_IT					0x71
/** �¶ȱ���*/
#define	CMD_DOWN_AM					0x72
/** ���������¶�*/
#define CMD_UP_IT					0x83
/** ���±����¶�����*/
#define CMD_UP_HAM					0x84
/** ���±����¶�����*/
#define CMD_UP_LAM					0x85
/** ֡β*/
#define UartFrameTail				0xED

/** �ر� LCD����*/
#define CMD_IHMT_OFF				0x00
/** �� LCD����*/
#define CMD_IHMT_ON					0x01
/** ���±���*/
#define CMD_DOWN_HAM				0x00
/** ���±���*/
#define CMD_DOWN_LAM				0x01
/** ���±�������*/
#define CMD_DOWN_HAMC				0x05
/** ���±�������*/
#define CMD_DOWN_LAMC				0x06
#endif