#include "StdAfx.h"
#include "LogThread.h"

CLogThread::CLogThread(void)
{
	InitializeCriticalSection(&m_oSecLogOutPutThread);
}

CLogThread::~CLogThread(void)
{
	DeleteCriticalSection(&m_oSecLogOutPutThread);
}
// 线程等待函数
void WaitLogOutPutThread(CLogThread* pLogThread)
{
	ASSERT(pLogThread != NULL);
	// 初始化等待次数为0
	int iWaitCount = 0;
	bool bClose = false;
	// 循环
	while(true)
	{	// 休眠50毫秒
		Sleep(50);
		// 等待次数加1
		iWaitCount++;
		EnterCriticalSection(&pLogThread->m_oSecLogOutPutThread);
		bClose = pLogThread->m_bClose;
		LeaveCriticalSection(&pLogThread->m_oSecLogOutPutThread);
		// 判断是否可以处理的条件
		if(bClose == true)
		{
			// 返回
			return;
		}
		// 判断等待次数是否大于等于最多等待次数
		if(iWaitCount == 5)
		{
			// 返回
			return;
		}		
	}
}
// 线程函数
DWORD WINAPI RunLogOutPutThread(CLogThread* pLogThread)
{
	ASSERT(pLogThread != NULL);
	bool bClose = false;
	bool bWork = false;
	while(true)
	{
		EnterCriticalSection(&pLogThread->m_oSecLogOutPutThread);
		bClose = pLogThread->m_bClose;
		bWork = pLogThread->m_bWork;
		LeaveCriticalSection(&pLogThread->m_oSecLogOutPutThread);
		if (bClose == true)
		{
			break;
		}
		if (bWork == true)
		{
			pLogThread->m_pLog->WriteLogOutPutListToFile();
		}
		EnterCriticalSection(&pLogThread->m_oSecLogOutPutThread);
		bClose = pLogThread->m_bClose;
		LeaveCriticalSection(&pLogThread->m_oSecLogOutPutThread);
		if (bClose == true)
		{
			break;
		}
		WaitLogOutPutThread(pLogThread);
	}
	EnterCriticalSection(&pLogThread->m_oSecLogOutPutThread);
	// 设置事件对象为有信号状态,释放等待线程后将事件置为无信号
	SetEvent(pLogThread->m_hThreadClose);
	LeaveCriticalSection(&pLogThread->m_oSecLogOutPutThread);
	return 1;
}
// 初始化日志输出线程
void CLogThread::OnInitLogOutPutThread(CLog* pLog)
{
	ASSERT(pLog != NULL);
	EnterCriticalSection(&m_oSecLogOutPutThread);
	m_pLog = pLog;
	m_bClose = false;
	m_bWork = true;
	m_dwThreadID = 0;
	m_hThread = INVALID_HANDLE_VALUE;
	m_hThreadClose = INVALID_HANDLE_VALUE;
	// 创建事件对象
	m_hThreadClose = CreateEvent(false, false, NULL, NULL);
	// 设置事件对象为无信号状态
	ResetEvent(m_hThreadClose);
	// 创建线程
	m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunLogOutPutThread,
		this, 
		0, 
		&m_dwThreadID);
	LeaveCriticalSection(&m_oSecLogOutPutThread);
	m_pLog->AddMsgToLogOutPutList(_T("日志输出线程创建成功"));
}
// 关闭日志输出线程
void CLogThread::OnCloseLogOutPutThread(void)
{
	EnterCriticalSection(&m_oSecLogOutPutThread);
	int iResult = WaitForSingleObject(m_hThreadClose, 500);
	CloseHandle(m_hThreadClose);
	m_hThreadClose = INVALID_HANDLE_VALUE;
	if (iResult != WAIT_OBJECT_0)
	{
		TerminateThread(m_hThread, 0);
	}
	else
	{
		CloseHandle(m_hThread);
		m_hThread = INVALID_HANDLE_VALUE;
	}
	LeaveCriticalSection(&m_oSecLogOutPutThread);
	m_pLog->AddMsgToLogOutPutList(_T("日志输出线程成功关闭"));
}