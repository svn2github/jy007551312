#pragma once
#include "Parameter.h"
#include <list>
using std::list;
class CLog
{
public:
	CLog(void);
	~CLog(void);
public:
	/** ��־�����Դͬ������*/
	CRITICAL_SECTION m_oSecLogFile;
	/** ��־����ļ�ָ��*/
	FILE* m_pFile;
	/** ��־����ṹ*/
	list<CString> m_oLogOutputList;
	/** ��־���·��*/
	CString m_SaveLogFilePath;
	/** ��־�ļ����*/
	unsigned int m_uiLogFileNb;
	/** ��־�ļ��洢��Ϣ��������*/
	unsigned int m_uiLogInfoCount;
public:
	// ��ʼ��
	void OnInitLogOutPut(void);
	// ����־����ļ�
	int OpenLogOutPutFile(void);
	// ���뵽��־�������
	void AddMsgToLogOutPutList(CString strLog);
	// ��־���д���ļ�
	void LogOutPutWriteInFile(FILE* pFile, CString str, bool bFlush = true);
	// д����־����ļ�
	void WriteLogOutPutListToFile(void);
	// �ر���־����ļ�
	void CloseLogOutPutFile(void);
	// �ر���־����ṹ��
	void OnCloseLogOutPut(void);
};