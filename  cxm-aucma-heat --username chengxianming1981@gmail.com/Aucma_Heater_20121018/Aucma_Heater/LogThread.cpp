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
// �̵߳ȴ�����
void WaitLogOutPutThread(CLogThread* pLogThread)
{
	ASSERT(pLogThread != NULL);
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(50);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pLogThread->m_oSecLogOutPutThread);
		bClose = pLogThread->m_bClose;
		LeaveCriticalSection(&pLogThread->m_oSecLogOutPutThread);
		// �ж��Ƿ���Դ��������
		if(bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(iWaitCount == 5)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
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
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pLogThread->m_hThreadClose);
	LeaveCriticalSection(&pLogThread->m_oSecLogOutPutThread);
	return 1;
}
// ��ʼ����־����߳�
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
	// �����¼�����
	m_hThreadClose = CreateEvent(false, false, NULL, NULL);
	// �����¼�����Ϊ���ź�״̬
	ResetEvent(m_hThreadClose);
	// �����߳�
	m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunLogOutPutThread,
		this, 
		0, 
		&m_dwThreadID);
	LeaveCriticalSection(&m_oSecLogOutPutThread);
	m_pLog->AddMsgToLogOutPutList(_T("��־����̴߳����ɹ�"));
}
// �ر���־����߳�
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
	m_pLog->AddMsgToLogOutPutList(_T("��־����̳߳ɹ��ر�"));
}