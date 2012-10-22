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
/** ������Ӻͼ��ٴﵽʱ������������ж���������*/
#define ContinuousOptTimes			10
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
#define DefaultSetTemp				88
/** Ĭ��pngͼƬ͸��������*/
#define DefaultPNGTransparent		255
/** �����¶�����ֵ*/
#define SetTempLimit				100
/** ���ڽ���������Ϣ*/
#define WM_RECV_UART_DATA	WM_USER + 100
#endif