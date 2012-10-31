#ifndef _Parameter_h
#define _Parameter_h

/** 定义对话框背景颜色*/
#define DialogBkColor		(RGB(255, 255, 255))
/** 默认文字颜色*/
#define DefaultTextColor	(RGB(132, 128, 144))
/** 选中文字颜色*/
#define SelectTextColor		(RGB(255, 0, 0))
/** 监控温度状态定时器序号*/
#define ShowTempStateTimerEvent	1
/** 监控温度状态定时间隔*/
#define ShowTempStateTimeSet	1000
/** 监控系统时间定时器序号*/
#define ShowTimeTimerEvent		2
/** 监控系统时间定时间隔*/
#define ShowTimeTimeSet			10000
/** 连续增加和减少定时器序号*/
#define ContinuousOptTimerEvent		3
/** 连续增加和减少定时间隔*/
#define ContinuousOptTimeSet		100
/** 设置闪烁定时器序号*/
#define TwinkleTimerEvent			4
/** 设置闪烁定时间隔*/
#define TwinkleTimeSet				500
/** 增加或减少操作时暂时关闭闪烁定时器时间间隔*/
#define TwinkleTimerSleepTimes		3
/** 闪烁次数上限*/
#define TwinkleMaxTimes				20
/** 点击增加和减少达到时间次数，用于判定连续操作*/
#define ContinuousOptTimes			6
/** 速热引擎状态枚举*/
enum {NormalHeat, FastHeat, WinterHeat};
/** 温度显示状态*/
enum {NoTempShow, InsulationState, HeatTempState};
/** 图片所在的文件夹*/
#define PicFolderName				_T("\\Storage Card\\Folder2\\")
/** 定义文本输出坐标偏移量1*/
#define TextOutMovePos1				8
/** 定义文本输出坐标偏移量2*/
#define TextOutMovePos2				4
/** 默认设置温度*/
#define DefaultSetTemp				30
/** 默认png图片透明度设置*/
#define DefaultPNGTransparent		128
/** 设置温度上限值*/
#define SetTempMaxLimit				80
/** 设置温度上限值*/
#define SetTempMinLimit				30
/** 串口接收数据消息*/
#define WM_RECV_UART_DATA	WM_USER + 100
/************************************************************************/
/*                串口通讯命令字                                        */
/************************************************************************/
/** 帧长度*/
#define UartFrameLength				7
/** 帧头1*/
#define UartFrameHead1				0x51
/** 帧头2*/
#define UartFrameHead2				0x85
/** 触摸屏终端代码*/
#define ClientNo					0x00
/** 控制 LCD背光*/
#define CMD_IHMT_CTRL				0x60
/** 复位触摸屏*/
#define CMD_IHMT_RST				0x61
/** 实际环境温度*/
#define	CMD_DOWN_ET					0x70
/** 实际箱内温度*/
#define	CMD_DOWN_IT					0x71
/** 温度报警*/
#define	CMD_DOWN_AM					0x72
/** 箱内设置温度*/
#define CMD_UP_IT					0x83
/** 高温报警温度设置*/
#define CMD_UP_HAM					0x84
/** 低温报警温度设置*/
#define CMD_UP_LAM					0x85
/** 帧尾*/
#define UartFrameTail				0xED

/** 关闭 LCD背光*/
#define CMD_IHMT_OFF				0x00
/** 打开 LCD背光*/
#define CMD_IHMT_ON					0x01
/** 高温报警*/
#define CMD_DOWN_HAM				0x00
/** 低温报警*/
#define CMD_DOWN_LAM				0x01
/** 高温报警消除*/
#define CMD_DOWN_HAMC				0x05
/** 低温报警消除*/
#define CMD_DOWN_LAMC				0x06
#endif