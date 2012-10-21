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
		// �رմ���
		ClosePort();
	}
}

// ���ڶ��̺߳���
DWORD CCEUart::ReadThreadProc(LPVOID lparam)
{
	CCEUart* pCEUart = (CCEUart*)lparam;
	DWORD dwEvtMask = 0;
	// ��ȡ���ݻ�����
	BYTE* readBuf = NULL;
	// ʵ�ʶ�ȡ�ֽ���
	DWORD dwActualReadLen = 0;
	// ��Ҫ��ȡ���ֽ���
	DWORD dwWillReadLen = 0;
	// ���ڴ�����
	DWORD dwUartErrors = 0;
	// ����״̬
	COMSTAT cmstate;

	// ��鴮���Ƿ��
	ASSERT(pCEUart->m_hComm != INVALID_HANDLE_VALUE);
	// ��մ��ڽ��պͷ��ͻ�����
	PurgeComm(pCEUart->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);
	// ���ö˿ڼ���¼�
	SetCommMask(pCEUart->m_hComm, EV_RXCHAR | EV_CTS | EV_DSR);
	while (TRUE)
	{
		if (WaitCommEvent(pCEUart->m_hComm, &dwEvtMask, 0))
		{
			SetCommMask(pCEUart->m_hComm, EV_RXCHAR | EV_CTS | EV_DSR);
			// ���ڽ��յ��ַ�
			if (dwEvtMask & EV_RXCHAR)
			{
				ClearCommError(pCEUart->m_hComm, &dwUartErrors, &cmstate);
				dwWillReadLen = cmstate.cbInQue;
				if (dwWillReadLen < 0)
				{
					continue;
				}
				// �������ջ�����
				readBuf = new BYTE[dwWillReadLen];
				ZeroMemory(readBuf, dwWillReadLen);
				// ��ȡ��������
				ReadFile(pCEUart->m_hComm, readBuf, dwWillReadLen,
					&dwActualReadLen, 0);
				if (dwActualReadLen > 0)
				{
					// �����ص�����
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

// �رն��߳�
void CCEUart::CloseReadThread(void)
{
	SetEvent(m_hReadCloseEvent);
	// ���������¼���Ч
	SetCommMask(m_hComm, 0);
	// �������Ҫ��������
	PurgeComm(m_hComm, PURGE_RXCLEAR);
	// ������߳�û���˳���ǿ���˳�
	if (WaitForSingleObject(m_hReadThread, 2000) == WAIT_TIMEOUT)
	{
		TerminateThread(m_hReadThread, 0);
	}
	m_hReadThread = NULL;
}

// �򿪴���
BOOL CCEUart::OpenPort(void* pFatherPtr, UINT uiPortNo, UINT uiBaud, UINT uiParity, UINT uiDatabits, UINT uiStopbits)
{
	DCB commParam;
	TCHAR szPortName[16];
	ASSERT(pFatherPtr != NULL);
	m_pFatherPtr = pFatherPtr;
	// �����Ѿ���
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	// ���ô�����
	wsprintf(szPortName, _T("COM%d"), uiPortNo);
	// �򿪴���
	m_hComm = CreateFile(
		szPortName,
		GENERIC_READ | GENERIC_WRITE, // �����д
		0,
		NULL,
		OPEN_EXISTING, // �򿪶����Ǵ���
		0,
		NULL
		);
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	// �õ��򿪴��ڵĵ�ǰ���Բ������޸ĺ����������ô���
	if (!GetCommState(m_hComm, &commParam))
	{
		// �رմ���
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
		return FALSE;
	}
	// ���ô��ڲ���
	commParam.BaudRate = uiBaud;			// ���ò�����
	commParam.fBinary = TRUE;				// ���ö�����ģʽ���˴���������ΪTRUE
	commParam.fParity = TRUE;				// ֧����żУ��
	commParam.ByteSize = uiDatabits;		// ����λ����Χ4-8
	commParam.Parity = uiParity;			// У��ģʽ
	commParam.StopBits = uiStopbits;		// ֹͣλ

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
	commParam.fAbortOnError = FALSE;		// �����ڷ�������ʱ������ֹ���ڶ�д

	if (!SetCommState(m_hComm, &commParam))
	{
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
		return FALSE;
	}
	// ���ô��ڶ�дʱ��
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
	// ָ���˿ڼ���¼���
	SetCommMask(m_hComm, EV_RXCHAR);
	// ���ô����豸������
	SetupComm(m_hComm, 512, 512);
	// ��ս��պͷ��ͻ�����
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);
	CString strEvent;
	strEvent.Format(_T("Com_ReadCloseEvent%d"), uiPortNo);
	m_hReadCloseEvent = CreateEvent(NULL, TRUE, FALSE, strEvent);

	// �������ڶ����ݽ����߳�
	m_hReadThread = CreateThread(NULL, 0, ReadThreadProc, this, 0, &m_dwReadThreadID);
	m_bOpened = TRUE;
	return TRUE;
}

// �رմ���
void CCEUart::ClosePort(void)
{
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		return;
	}
	// �رն��߳�
	CloseReadThread();
	// �رմ���
	CloseHandle(m_hComm);
	m_hComm = INVALID_HANDLE_VALUE;
	// �ر��¼�
	CloseHandle(m_hReadCloseEvent);
	m_bOpened = FALSE;
}

// ������д������
BOOL CCEUart::WriteSyncPort(const BYTE* pbuf, DWORD dwbufLen)
{
	DWORD dwNumBytesWritten = 0;
	DWORD dwNumHaveWritten = 0;
	int iRetryCount = 0;
	ASSERT(m_hComm != INVALID_HANDLE_VALUE);
	do 
	{
		if (WriteFile(m_hComm, // ���ھ��
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

// ���ô��ڶ�ȡ��д�볬ʱ
BOOL CCEUart::SetUartTimeouts(COMMTIMEOUTS CommTimeOuts)
{
	ASSERT(m_hComm != INVALID_HANDLE_VALUE);
	return SetCommTimeouts(m_hComm, &CommTimeOuts);
}

// �õ������Ƿ��
BOOL CCEUart::GetComOpened(void)
{
	return m_bOpened;
}
