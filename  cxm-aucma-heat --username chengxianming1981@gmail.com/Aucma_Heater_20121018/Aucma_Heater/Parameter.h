#ifndef _Parameter_h
#define _Parameter_h

/** ℃背景色*/
#define TempTextColor				(RGB(255, 255, 255))
/** 默认文字颜色*/
#define DefaultTextColor			(RGB(132, 128, 144))
/** 选中文字颜色*/
#define SelectTextColor				(RGB(255, 0, 0))
/** 监控温度状态定时器序号*/
#define ShowTempStateTimerEvent		1
/** 监控温度状态定时间隔*/
#define ShowTempStateTimeSet		1000
/** 监控系统时间定时器序号*/
#define ShowTimeTimerEvent			2
/** 监控系统时间定时间隔*/
#define ShowTimeTimeSet				60000
/** 连续增加和减少定时器序号*/
#define ContinuousOptTimerEvent		3
/** 连续增加和减少定时间隔*/
#define ContinuousOptTimeSet		100
/** 设置闪烁定时器序号*/
#define TwinkleTimerEvent			4
/** 设置闪烁定时间隔*/
#define TwinkleTimeSet				500
/** 蜂鸣器定时器序号*/
#define BuzzerTimerEvent			5
/** 蜂鸣器一次操作鸣响时间*/
#define BuzzerOptTime				175
/** 蜂鸣器报警鸣响时间*/
#define BuzzerWarningTime			4925
/** 洗手加热确认定时器序号*/
#define WashHandTimerEvent			6
/** 洗手加热确认定时器时间*/
#define WashHandTimeSet				3000
/** 夜电模式确认定时器序号*/
#define NightModeTimerEvent			7
/** 夜电模式确认定时器时间*/
#define NightModeTimeSet			3000
/** 智能助手闪烁定时器序号*/
#define HelperTwinkleTimerEvent		8
/** 智能助手闪烁定时器时间*/
#define HelperTwinkleTimeSet		500
/** 速热引擎闪烁定时器序号*/
#define HeatFastTwinkleTimerEvent	9
/** 速热引擎闪烁定时器时间*/
#define HeatFastTwinkleTimeSet		500
/** 闪烁次数上限*/
#define TwinkleMaxTimes				6
/** 点击增加和减少达到时间次数，用于判定连续操作*/
#define ContinuousOptTimes			6
/** 速热引擎状态枚举*/
enum {NormalHeat, SummerHeat, WinterHeat};
/** 温度显示状态*/
enum {NoTempShow, InsulationState, HeatTempState};
/** 图片所在的文件夹*/
//#define PicFolderName					_T("\\Storage Card\\Folder2\\")
#define PicFolderName					_T("\\Program Files\\Folder2\\")
/** 定义注册表主键名*/
#define RegKeyNameHeater				_T("Aucma\\Heater")
/** 定义注册表普通加热温度设置子键名*/
#define RegSubKeyNameNHST				_T("普通设置温度")
/** 定义注册表夏季加热温度设置子键名*/
#define RegSubKeyNameSHST				_T("夏季设置温度")
/** 定义注册表冬季加热温度设置子键名*/
#define RegSubKeyNameWHST				_T("冬季设置温度")
/** 定义注册表加热模式子键名*/
#define RegSubKeyNameHeatMode			_T("加热模式")
/** 定义注册表洗手模式子键名*/
#define RegSubKeyNameWashMode			_T("洗手模式")
/** 定义注册表夜间模式子键名*/
#define RegSubKeyNameNightMode			_T("夜间模式")
/** 定义注册表助手模式子键名*/
#define RegSubKeyNameHelperMode			_T("助手模式")
/** 定义注册表电源开关子键名*/
#define RegSubKeyNamePower				_T("电源开关")
/** 定义注册表智能助手闪烁子键名*/
#define RegSubKeyNameHelperTwinkle		_T("智能助手闪烁")
/** 定义注册表速热引擎闪烁子键名*/
#define RegSubKeyNameHeatFastTwinkle	_T("速热引擎闪烁")
// @@@加入限制
/** 定义注册表软件使用次数限制子键名*/
#define RegSubKeyNameLimit				_T("次数限制")
/** 软件试用次数限制*/
#define SoftUseLimitNum					20
/** 定义文本输出坐标偏移量1*/
#define TextOutMovePos1					8
/** 定义文本输出坐标偏移量2*/
#define TextOutMovePos2					4
/** 普通加热默认设置温度*/
#define DefaultNormalTemp				80
/** 冬季加热默认设置温度*/
#define DefaultWinterTemp				80
/** 夏季加热默认设置温度*/
#define DefaultSummerTemp				50
/** 默认箱内实际温度*/
#define DefaultInTempActual				48
/** 默认png图片透明度设置*/
#define DefaultPNGTransparent			128
/** 设置温度上限值*/
#define SetTempMaxLimit					80
/** 设置温度上限值*/
#define SetTempMinLimit					30
/** 串口接收数据消息*/
#define WM_RECV_UART_DATA				WM_USER + 100
/** 默认蜂鸣器频率，设为1则频率为2Hz*/
#define DefaultBuzzFrq					2
/** 强制结束线程时间*/
#define TerminalThreadTime				4000
/************************************************************************/
/*                串口通讯命令字                                        */
/************************************************************************/
/** 帧长度*/
#define UartFrameLength					7
/** 帧头1*/
#define UartFrameHead1					0x51
/** 帧头2*/
#define UartFrameHead2					0x85
/** 触摸屏终端代码*/
#define ClientNo						0x00
// /** 控制 LCD背光*/
// #define CMD_IHMT_CTRL				0x60
// /** 复位触摸屏*/
// #define CMD_IHMT_RST					0x61
/** 智能助手执行*/
#define CMD_DOWN_HP						0x69
/** 实际环境温度*/
#define	CMD_DOWN_ET						0x70
/** 实际箱内温度*/
#define	CMD_DOWN_IT						0x71
/** 报警类型*/
#define	CMD_DOWN_WT						0x72
/** 请求箱内温度*/
#define CMD_DOWN_QT						0x73

/** 时间小时数*/
#define CMD_UP_HOUR						0x60
/** 时间分钟数*/
#define CMD_UP_WEEK						0x61
/** 冬季智能运行*/
#define CMD_UP_WO						0x80
/** 夏季智能运行*/
#define CMD_UP_SO						0x81
/** 智能助手*/
#define CMD_UP_HP						0x82
/** 箱内设置温度*/
#define CMD_UP_IT						0x83
/** 夜电运行*/
#define CMD_UP_NO						0x84
/** 洗手加热*/
#define CMD_UP_WH						0x85
/** 开关电源*/
#define CMD_UP_PW						0x86
// /** 高温报警温度设置*/
// #define CMD_UP_HAM					0x84
// /** 低温报警温度设置*/
// #define CMD_UP_LAM					0x85
/** 帧尾*/
#define UartFrameTail					0xED

// /** 关闭 LCD背光*/
// #define CMD_IHMT_OFF					0x00
// /** 打开 LCD背光*/
// #define CMD_IHMT_ON					0x01
/** 干烧/缺水报警*/
#define CMD_WORD_WT_NWE					0x00
/** 传感器故障报警*/
#define CMD_WORD_WT_SE					0x01
/** 漏电故障报警*/
#define CMD_WORD_WT_LE					0x02
/** 水温超高故障报警*/
#define CMD_WORD_WT_WHE					0x03
/** 漏电线圈故障报警*/
#define CMD_WORD_WT_LCE					0x04
/** 干烧/缺水报警消除*/
#define CMD_WORD_WT_NWEC				0x05
/** 传感器故障报警消除*/
#define CMD_WORD_WT_SEC					0x06
/** 漏电故障报警消除*/
#define CMD_WORD_WT_LEC					0x07
/** 水温超高故障报警消除*/
#define CMD_WORD_WT_WHEC				0x08
/** 漏电线圈故障报警消除*/
#define CMD_WORD_WT_LCEC				0x09
/** 水量充足*/
#define CMD_WORD_WT_WE					0x0a
/** 水量不足*/
#define CMD_WORD_WT_WL					0x0b
/** 冬季智能开启*/
#define CMD_WORD_WO						0x01
/** 夏季智能开启*/
#define CMD_WORD_SO						0x01
/** 智能助手关闭*/
#define CMD_WORD_HC						0x00
/** 智能助手开启*/
#define CMD_WORD_HO						0x01
/** 夜电运行方式关闭*/
#define CMD_WORD_NC						0x00
/** 夜电运行方式开启*/
#define CMD_WORD_NO						0x01
/** 洗手加热关闭*/
#define CMD_WORD_WHC					0x00
/** 洗手加热开启*/
#define CMD_WORD_WHO					0x01
/** 进入待机状态*/
#define CMD_WORD_PC						0x00
/** 普通加热模式*/
#define CMD_WORD_PO						0x01
/************************************************************************/
/*					HTTP通讯                                            */
/************************************************************************/
/** 服务器网址信息*/
#define ServerURL	_T("http://mail.shgymy.com:9898/reshuiqiSrv/renshuiqisrv")
/** HTTP超时时间*/
#define HttpTimeout						1000
/** HTTP请求线程休眠时间*/
#define HttpThreadSleepTime				3000
/** HTTP*/
#define HttpContentType	_T("Content-Type: application/x-www-form-urlencoded")
/** HTTP消息设置温度*/
#define WM_HTTP_SETTEMP					WM_USER + 101
/** HTTP消息设置时间*/
#define WM_HTTP_SETTIME					WM_USER + 102
/** HTTP消息速热引擎*/
#define WM_HTTP_HEATFAST				WM_USER + 103
/** HTTP消息智能助手*/
#define WM_HTTP_HELPER					WM_USER + 104
/** HTTP消息洗手加热*/
#define WM_HTTP_WASHHAND				WM_USER + 105
/** HTTP消息夜间模式*/
#define WM_HTTP_NIGHTMODE				WM_USER + 106
/** HTTP消息电源开关*/
#define WM_HTTP_POWER					WM_USER + 107
#endif