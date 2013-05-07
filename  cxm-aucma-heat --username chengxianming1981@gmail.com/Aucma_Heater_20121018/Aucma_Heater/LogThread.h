#pragma once
#include "Log.h"
class CLogThread
{
public:
	CLogThread(void);
	~CLogThread(void);
public:
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecLogOutPutThread;
	/** �߳̾��*/
	HANDLE m_hThread;
	/** �̺߳�*/
	DWORD m_dwThreadID;
	/**�Ƿ���״̬*/
	bool m_bWork;
	/** �Ƿ�ر��߳�*/
	bool m_bClose;
	/** �߳̽����¼�*/
	HANDLE m_hThreadClose;
	/** �����־ָ��*/
	CLog* m_pLog;
public:
	// ��ʼ����־����߳�
	void OnInitLogOutPutThread(CLog* pLog);
	// �ر���־����߳�
	void OnCloseLogOutPutThread(void);
};
