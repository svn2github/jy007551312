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
/** 点击增加和减少达到时间次数，用于判定连续操作*/
#define ContinuousOptTimes			10
/** 速热引擎状态枚举*/
enum {NormalHeat, FastHeat, WinterHeat};
/** 温度显示状态*/
enum {NoTempShow, InsulationState, HeatTempState};
/** 图片所在的文件夹*/
#define PicFolderName				_T("\\Storage Card\\")
#endif