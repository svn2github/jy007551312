#pragma once
#include "Log.h"
class CLogThread
{
public:
	CLogThread(void);
	~CLogThread(void);
public:
	/** 资源同步对象*/
	CRITICAL_SECTION m_oSecLogOutPutThread;
	/** 线程句柄*/
	HANDLE m_hThread;
	/** 线程号*/
	DWORD m_dwThreadID;
	/**是否工作状态*/
	bool m_bWork;
	/** 是否关闭线程*/
	bool m_bClose;
	/** 线程结束事件*/
	HANDLE m_hThreadClose;
	/** 输出日志指针*/
	CLog* m_pLog;
public:
	// 初始化日志输出线程
	void OnInitLogOutPutThread(CLog* pLog);
	// 关闭日志输出线程
	void OnCloseLogOutPutThread(void);
};
