#include "StdAfx.h"
#include "CEHttp.h"
#include "Parameter.h"
CCEHttp::CCEHttp(void)
{
	m_pFatherPtr = NULL;
	m_oHttpRequest = NULL;
	m_oHttpResponse = NULL;
}

CCEHttp::~CCEHttp(void)
{
}

// 初始化
void CCEHttp::OnInit(void* pFatherPtr)
{
	ASSERT(pFatherPtr != NULL);
	m_pFatherPtr = pFatherPtr;
	m_hCloseEvent = CreateEvent(NULL, TRUE, FALSE, _T("Http_CloseEvent"));
	m_hReadThread = CreateThread(NULL, 0, ThreadProc, this, 0, &m_dwReadThreadID);
}
DWORD CCEHttp::ThreadProc(LPVOID lparam)
{
	CCEHttp* pCEHttp = (CCEHttp*)lparam;
	bool bConnect = false;
	CString strRequest = _T("");
	while (TRUE)
	{
		if (bConnect == false)
		{
			bConnect = pCEHttp->ConnectServer();
		}
		else
		{
			if (pCEHttp->m_oHttpRequest)
			{
				strRequest = pCEHttp->m_oHttpRequest(pCEHttp->m_pFatherPtr);
				bConnect = pCEHttp->SendHttpRequest(strRequest);
			}
		}
		if (WaitForSingleObject(pCEHttp->m_hCloseEvent, HttpThreadSleepTime) == WAIT_OBJECT_0)
		{
			break;
		}
	}
	return 0;
}
// 连接服务器
bool CCEHttp::ConnectServer(void)
{
	DWORD dwServiceType = 0;
	CString strServer = _T("");
	CString strObject = _T("");
	INTERNET_PORT nPort = 0;

	if (!AfxParseURL(ServerURL, dwServiceType, strServer, strObject, nPort) || 
		dwServiceType != AFX_INET_SERVICE_HTTPS && dwServiceType != AFX_INET_SERVICE_HTTP)
	{
		return false;
	}
	/*m_hOpen = InternetOpen(_T(""), INTERNET_OPEN_TYPE_DIRECT, NULL, 0, 0);*/
	if (!(m_hOpen = InternetOpen(AfxGetAppName(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, 0, 0)))
	{
		return false;
	}
	if (!(m_hConnect = InternetConnect(m_hOpen, strServer, nPort, NULL, NULL, dwServiceType, 0, 0)))
	{
		InternetCloseHandle(m_hOpen);
		return false;
	}
	LPTSTR AcceptTypes[2] = {_T("*/*"), NULL};
	DWORD dwFlags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE;
	// Open an HTTP request handle.
	if (!(m_hRequest = HttpOpenRequest (m_hConnect, _T("POST"), strObject, HTTP_VERSION, NULL, (LPCTSTR*)AcceptTypes,
		dwFlags, 0)))
	{
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		return false;
	}
	DWORD dwHttpTimeout = HttpTimeout;
	if(!InternetSetOption(m_hRequest, INTERNET_OPTION_CONNECT_TIMEOUT, &dwHttpTimeout, sizeof(DWORD)))
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		return false;
	}
	if(!InternetSetOption(m_hRequest, INTERNET_OPTION_SEND_TIMEOUT, &dwHttpTimeout, sizeof(DWORD)))
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		return false;
	}
	if(!InternetSetOption(m_hRequest, INTERNET_OPTION_RECEIVE_TIMEOUT, &dwHttpTimeout, sizeof(DWORD)))
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);;
		return false;
	}
	return true;
}

// 关闭
void CCEHttp::OnClose(void)
{
	SetEvent(m_hCloseEvent);
	// 如果读线程没有退出则强制退出
	if (WaitForSingleObject(m_hReadThread, TerminalThreadTime) == WAIT_TIMEOUT)
	{
		TerminateThread(m_hReadThread, 0);
	}
	m_hReadThread = NULL;
	InternetCloseHandle(m_hRequest);
	InternetCloseHandle(m_hConnect);
	InternetCloseHandle(m_hOpen);
}

// 发送HTTP请求
bool CCEHttp::SendHttpRequest(CString strRequest)
{
	CString strHeaders = HttpContentType;
	int len = WideCharToMultiByte(CP_ACP, 0, strRequest, strRequest.GetLength(), NULL, 0, NULL, NULL);
	//为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小,以字节为单位
	char* pszData = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, strRequest, strRequest.GetLength() + 1, pszData,len + 1, NULL, NULL);
	if(HttpSendRequest(m_hRequest, strHeaders, strHeaders.GetLength(), pszData, strRequest.GetLength())
		== FALSE)
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		delete[] pszData;
		return false;  
	}
	delete[] pszData;
	DWORD dwSize;
	HttpQueryInfo(m_hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, NULL, &dwSize, NULL);
	TCHAR* lpHeaders = new TCHAR [dwSize];
	if (!HttpQueryInfo (m_hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, (LPVOID) lpHeaders, 
		&dwSize, NULL))
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		delete[] lpHeaders;
		return false;
	}
	TCHAR szHttpStatus[4] = {0};
	memcpy(szHttpStatus, lpHeaders + _tcslen(_T("HTTP/1.1 ")), 3 * sizeof(TCHAR));
	delete[] lpHeaders;
	int dwHttpStatus = 0;
	dwHttpStatus = _ttoi(szHttpStatus);
	if (dwHttpStatus != 200)
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		return false;
	}
	char cResponse[4096];
	if(!InternetReadFile (m_hRequest, (LPVOID)(cResponse), 4096, &dwSize))
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen); 
		return false; 
	}
	if(dwSize == 0)
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		return false;  
	}
	CString strResponse(cResponse);
	if (m_oHttpResponse)
	{
		m_oHttpResponse(m_pFatherPtr, strResponse);
	}
	return true;
}
