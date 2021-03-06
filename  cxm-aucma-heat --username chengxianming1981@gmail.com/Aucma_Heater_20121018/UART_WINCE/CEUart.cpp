#include "StdAfx.h"
#include "CEUart.h"

CCEUart::CCEUart(void)
: m_bOpened(false)
, m_pFatherPtr(NULL)
, m_dwReadThreadID(0)
{
	m_hComm = INVALID_HANDLE_VALUE;
	m_hReadThread = INVALID_HANDLE_VALUE;
	m_hReadCloseEvent = INVALID_HANDLE_VALUE;
}

CCEUart::~CCEUart(void)
{
	if (m_bOpened)
	{
		// 关闭串口
		ClosePort();
	}
}

// 串口读线程函数
DWORD CCEUart::ReadThreadProc(LPVOID lparam)
{
	CCEUart* pCEUart = (CCEUart*)lparam;
	DWORD dwEvtMask = 0;
	// 读取数据缓冲区
	BYTE* readBuf = NULL;
	// 实际读取字节数
	DWORD dwActualReadLen = 0;
	// 想要读取的字节数
	DWORD dwWillReadLen = 0;
	// 串口错误数
	DWORD dwUartErrors = 0;
	// 串口状态
	COMSTAT cmstate;

	// 检查串口是否打开
	ASSERT(pCEUart->m_hComm != INVALID_HANDLE_VALUE);
	// 清空串口接收和发送缓冲区
	PurgeComm(pCEUart->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);
	// 设置端口检测事件
	SetCommMask(pCEUart->m_hComm, EV_RXCHAR | EV_CTS | EV_DSR);
	while (TRUE)
	{
		if (WaitCommEvent(pCEUart->m_hComm, &dwEvtMask, 0))
		{
			SetCommMask(pCEUart->m_hComm, EV_RXCHAR | EV_CTS | EV_DSR);
			// 串口接收到字符
			if (dwEvtMask & EV_RXCHAR)
			{
				ClearCommError(pCEUart->m_hComm, &dwUartErrors, &cmstate);
				dwWillReadLen = cmstate.cbInQue;
				if (dwWillReadLen < 0)
				{
					continue;
				}
				// 创建接收缓冲区
				readBuf = new BYTE[dwWillReadLen];
				ZeroMemory(readBuf, dwWillReadLen);
				// 读取串口数据
				ReadFile(pCEUart->m_hComm, readBuf, dwWillReadLen,
					&dwActualReadLen, 0);
				if (dwActualReadLen > 0)
				{
					// 触发回调函数
					if (pCEUart->m_OnUartRead)
					{
						pCEUart->m_OnUartRead(pCEUart->m_pFatherPtr,
							readBuf, dwActualReadLen);
					}
				}
				delete[] readBuf;
				readBuf = NULL;
			}
		}
		if (WaitForSingleObject(pCEUart->m_hReadCloseEvent, 100) == WAIT_OBJECT_0)
		{
			break;
		}
	}
	return 0;
}

// 关闭读线程
void CCEUart::CloseReadThread(void)
{
	SetEvent(m_hReadCloseEvent);
	// 设置所有事件无效
	SetCommMask(m_hComm, 0);
	// 清空所有要读的数据
	PurgeComm(m_hComm, PURGE_RXCLEAR);
	// 如果读线程没有退出则强制退出
	if (WaitForSingleObject(m_hReadThread, 2000) == WAIT_TIMEOUT)
	{
		TerminateThread(m_hReadThread, 0);
	}
	m_hReadThread = NULL;
}

// 打开串口
BOOL CCEUart::OpenPort(void* pFatherPtr, UINT uiPortNo, UINT uiBaud, UINT uiParity, UINT uiDatabits, UINT uiStopbits)
{
	DCB commParam;
	TCHAR szPortName[16];
	ASSERT(pFatherPtr != NULL);
	m_pFatherPtr = pFatherPtr;
	// 串口已经打开
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	// 设置串口名，此处需注意一定要有“:”
	wsprintf(szPortName, _T("COM%d:"), uiPortNo);
	// 打开串口
	m_hComm = CreateFile(
		szPortName,
		GENERIC_READ | GENERIC_WRITE, // 允许读写
		0,
		NULL,
		OPEN_EXISTING, // 打开而不是创建
		0,
		NULL
		);
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	// 得到打开串口的当前属性参数，修改后再重新设置串口
	if (!GetCommState(m_hComm, &commParam))
	{
		// 关闭串口
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
		return FALSE;
	}
	// 设置串口参数
	commParam.BaudRate = uiBaud;			// 设置波特率
	commParam.fBinary = TRUE;				// 设置二进制模式，此处必须设置为TRUE
	commParam.fParity = TRUE;				// 支持奇偶校验
	commParam.ByteSize = uiDatabits;		// 数据位，范围4-8
	commParam.Parity = uiParity;			// 校验模式
	commParam.StopBits = uiStopbits;		// 停止位

	commParam.fOutxCtsFlow = FALSE;			// No CTS output flow control
	commParam.fOutxDsrFlow = FALSE;			// No DSR output flow control
	commParam.fDtrControl = DTR_CONTROL_ENABLE;
	// DTR flow control type
	commParam.fDsrSensitivity = FALSE;		// DSR Sensitivity
	commParam.fTXContinueOnXoff = TRUE;		// XOFF continues TX
	commParam.fOutX = FALSE;				// No XON/XOFF out flow control
	commParam.fInX = FALSE;					// No XON/XOFF in flow control
	commParam.fErrorChar = FALSE;			// Disable error replacement
	commParam.fNull = FALSE;				// Disable null stripping
	commParam.fRtsControl = RTS_CONTROL_ENABLE;
	// RTS flow control
	commParam.fAbortOnError = FALSE;		// 当串口发生错误时并不终止串口读写

	if (!SetCommState(m_hComm, &commParam))
	{
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
		return FALSE;
	}

	// 设置串口读写时间
	COMMTIMEOUTS CommTimeOuts;
	GetCommTimeouts(m_hComm, &CommTimeOuts);
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 10;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	if (!SetCommTimeouts(m_hComm, &CommTimeOuts))
	{
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
		return FALSE;
	}
	// 指定端口监测事件集
	SetCommMask(m_hComm, EV_RXCHAR);
	// 设置串口设备缓冲区
	SetupComm(m_hComm, 512, 512);
	// 清空接收和发送缓冲区
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);
	CString strEvent;
	strEvent.Format(_T("Com_CloseEvent%d"), uiPortNo);
	m_hReadCloseEvent = CreateEvent(NULL, TRUE, FALSE, strEvent);

	// 创建串口读数据接收线程
	m_hReadThread = CreateThread(NULL, 0, ReadThreadProc, this, 0, &m_dwReadThreadID);
	m_bOpened = TRUE;
	return TRUE;
}

// 关闭串口
void CCEUart::ClosePort(void)
{
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		return;
	}
	// 关闭读线程
	CloseReadThread();
	// 关闭串口
	CloseHandle(m_hComm);
	m_hComm = INVALID_HANDLE_VALUE;
	// 关闭事件
	CloseHandle(m_hReadCloseEvent);
	m_bOpened = FALSE;
}

// 往串口写入数据
BOOL CCEUart::WriteSyncPort(const BYTE* pbuf, DWORD dwbufLen)
{
	DWORD dwNumBytesWritten = 0;
	DWORD dwNumHaveWritten = 0;
	int iRetryCount = 0;
	if (m_bOpened == false)
	{
		return FALSE;
	}
	ASSERT(m_hComm != INVALID_HANDLE_VALUE);
	do 
	{
		if (WriteFile(m_hComm, // 串口句柄
				pbuf + dwNumHaveWritten,
				dwbufLen - dwNumHaveWritten,
				&dwNumBytesWritten,
				NULL))
		{
			dwNumHaveWritten += dwNumBytesWritten;
			if (dwNumHaveWritten == dwbufLen)
			{
				break;
			}
			iRetryCount++;
			if (iRetryCount >= 3)
			{
				return FALSE;
			}
			Sleep(10);
		}
		else
		{
			return FALSE;
		}
	} while (TRUE);
	return TRUE;
}

// 设置串口读取、写入超时
BOOL CCEUart::SetUartTimeouts(COMMTIMEOUTS CommTimeOuts)
{
	ASSERT(m_hComm != INVALID_HANDLE_VALUE);
	return SetCommTimeouts(m_hComm, &CommTimeOuts);
}

// 得到串口是否打开
BOOL CCEUart::GetComOpened(void)
{
	return m_bOpened;
}
