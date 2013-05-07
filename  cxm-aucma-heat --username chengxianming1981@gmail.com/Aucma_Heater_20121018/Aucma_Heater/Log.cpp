#include "StdAfx.h"
#include "Log.h"
#include <string>
using std::string;
CLog::CLog(void)
{
	InitializeCriticalSection(&m_oSecLogFile);
}

CLog::~CLog(void)
{
	DeleteCriticalSection(&m_oSecLogFile);
}
// ��ʼ��
void CLog::OnInitLogOutPut(void)
{
	if (OutPutSelect == 1)
	{
		return;
	}
	EnterCriticalSection(&m_oSecLogFile);
	// ��־�ļ�ָ��Ϊ��
	m_pFile = NULL;
	// �����־�������
	m_oLogOutputList.clear();
	// ��־�ļ�����趨
	m_uiLogFileNb = 0;
	// ��־�ļ��洢��Ϣ��������
	m_uiLogInfoCount = 0;
	// ����־����ļ�
	OpenLogOutPutFile();
	LeaveCriticalSection(&m_oSecLogFile);
}
// ����־����ļ�
int CLog::OpenLogOutPutFile(void)
{
	if (OutPutSelect == 1)
	{
		return -1;
	}
	CString strPath = _T("");
	CString str = _T("");
	errno_t err;
//	unsigned char fh[2];
	// ��������������־�ļ���
	EnterCriticalSection(&m_oSecLogFile);
	m_uiLogFileNb++;
	strPath.Format(_T("\\%d.log"), m_uiLogFileNb);
	strPath = m_SaveLogFilePath + strPath;
	m_uiLogInfoCount = 0;
	err = _tfopen_s(&m_pFile, (const TCHAR*)strPath.GetBuffer(), _T("wt+"));
	strPath.ReleaseBuffer();
// 	fh[0] = 0xff;
// 	fh[1] = 0xfe;
// 	fwrite(fh, sizeof(unsigned char), sizeof(fh), m_pFile);
	LeaveCriticalSection(&m_oSecLogFile);
	return err;
}
// ���뵽��־�������
void CLog::AddMsgToLogOutPutList(CString strLog)
{
	if (OutPutSelect == 1)
	{
		return;
	}
	CString strTime = _T("");
	CString strOutPut = _T("");
	SYSTEMTIME  sysTime;
	GetLocalTime(&sysTime);
	strTime.Format(_T("%04d��%02d��%02d�� %02d:%02d:%02d\t"), sysTime.wYear,
		sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, 
		sysTime.wSecond);
	strOutPut += strTime;
	strOutPut += strLog;
	strOutPut += _T("\r\n");
	EnterCriticalSection(&m_oSecLogFile);
	m_oLogOutputList.push_back(strOutPut);
	LeaveCriticalSection(&m_oSecLogFile);
}
// ��־���д���ļ�
void CLog::LogOutPutWriteInFile(FILE* pFile, CString str, bool bFlush)
{
	if (pFile == NULL)
	{
		return;
	}
	string strConv = (CStringA)str;
	size_t strSize = strConv.length();
	fwrite(strConv.c_str(), sizeof(char), strSize, pFile);
	if (bFlush == true)
	{
		fflush(pFile);
	}
}
// д����־����ļ�
void CLog::WriteLogOutPutListToFile(void)
{
	if ((OutPutSelect == 1) || (m_pFile == NULL))
	{
		return;
	}
	list<CString>::iterator iter;
	CString str = _T("");
	bool bOpenNewFile = false;
	EnterCriticalSection(&m_oSecLogFile);
	while(m_oLogOutputList.empty() == false)
	{
		iter = m_oLogOutputList.begin();
		str += *iter;
		m_oLogOutputList.pop_front();
		m_uiLogInfoCount++;
	}
	LogOutPutWriteInFile(m_pFile, str);
	if (m_uiLogInfoCount > OutPutLogFileInfoNumLimit)
	{
		fclose(m_pFile);
		bOpenNewFile = true;
	}
	if (bOpenNewFile == true)
	{
		OpenLogOutPutFile();
	}
	LeaveCriticalSection(&m_oSecLogFile);
}
// �ر���־����ļ�
void CLog::CloseLogOutPutFile(void)
{
	if ((OutPutSelect == 1) || (m_pFile == NULL))
	{
		return;
	}
	EnterCriticalSection(&m_oSecLogFile);
	WriteLogOutPutListToFile();
	fclose(m_pFile);
	LeaveCriticalSection(&m_oSecLogFile);
}


// �ر���־����ṹ��
void CLog::OnCloseLogOutPut(void)
{
	EnterCriticalSection(&m_oSecLogFile);
	// �ر���־����ļ�
	CloseLogOutPutFile();
	// �����־�������
	m_oLogOutputList.clear();
	LeaveCriticalSection(&m_oSecLogFile);
}