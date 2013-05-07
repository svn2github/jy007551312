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
	/** 日志输出资源同步对象*/
	CRITICAL_SECTION m_oSecLogFile;
	/** 日志输出文件指针*/
	FILE* m_pFile;
	/** 日志输出结构*/
	list<CString> m_oLogOutputList;
	/** 日志输出路径*/
	CString m_SaveLogFilePath;
	/** 日志文件序号*/
	unsigned int m_uiLogFileNb;
	/** 日志文件存储信息条数记数*/
	unsigned int m_uiLogInfoCount;
public:
	// 初始化
	void OnInitLogOutPut(void);
	// 打开日志输出文件
	int OpenLogOutPutFile(void);
	// 加入到日志输出队列
	void AddMsgToLogOutPutList(CString strLog);
	// 日志输出写入文件
	void LogOutPutWriteInFile(FILE* pFile, CString str, bool bFlush = true);
	// 写入日志输出文件
	void WriteLogOutPutListToFile(void);
	// 关闭日志输出文件
	void CloseLogOutPutFile(void);
	// 关闭日志输出结构体
	void OnCloseLogOutPut(void);
};