#include "StdAfx.h"
#include "CEHttp.h"
#include <afxinet.h>
CCEHttp::CCEHttp(void)
{
}

CCEHttp::~CCEHttp(void)
{
}

// 初始化
void CCEHttp::OnInit(void)
{
}

// 连接服务器
bool CCEHttp::ConnectServer(void)
{
//	https://accounts.google.com/ServiceLogin?hl=zh-CN&continue=http://www.google.com.hk&username=chengxianming1981&password=jy00755131@/
//	http://mail.shgymy.com:9898/reshuiqiSrv/renshuiqisrv?id=0&time=2012-12-18%2018:18:18&errorcode=0&statecode=123456
	CString pstrURL = _T("http://mail.shgymy.com:9898/reshuiqiSrv/renshuiqisrv");
	DWORD dwServiceType;
	CString strServer;
	CString strObject;
	INTERNET_PORT nPort;

	if (!AfxParseURL(pstrURL, dwServiceType, strServer, strObject, nPort) || 
		dwServiceType != AFX_INET_SERVICE_HTTPS && dwServiceType != AFX_INET_SERVICE_HTTP)
	{
		return false;
	}
	HINTERNET m_hOpen; 
	HINTERNET m_hConnect;
	HINTERNET m_hRequest;  
	m_hOpen = InternetOpen(_T(""), INTERNET_OPEN_TYPE_DIRECT, NULL, 0, 0);
	if (!m_hOpen)
	{
		return false;
	}

	if (!(m_hConnect = InternetConnect(m_hOpen, strServer, nPort, NULL, NULL, dwServiceType, 0, 0)))
	{
		int iERROR = GetLastError();
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

	DWORD dwHttpTimeout = 10000;
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
	CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded");
	CString strFormData = _T("id=0&time=2012-12-18%2018:18:18&errorcode=0&statecode=123456");

	int len = WideCharToMultiByte(CP_ACP, 0, strFormData, strFormData.GetLength(), NULL, 0, NULL, NULL);
	//为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小,以字节为单位
	char* pszData = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, strFormData, strFormData.GetLength() + 1, pszData,len + 1, NULL, NULL);

	if(HttpSendRequest(m_hRequest, strHeaders, strHeaders.GetLength(), pszData, strFormData.GetLength())
		== FALSE)
	{
		int iError = GetLastError();
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		return false;  
	}

	DWORD dwSize;
	HttpQueryInfo(m_hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, NULL, &dwSize, NULL);

	TCHAR* lpHeaders = new TCHAR [dwSize];
	if (!HttpQueryInfo (m_hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, (LPVOID) lpHeaders, &dwSize, NULL))
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		delete[] lpHeaders;
		return false;
	}

	// MessageBox(NULL, lpHeaders, _T("HttpQueryInfo"),  0);

	TCHAR szHttpStatus[4] = {0};
	memcpy(szHttpStatus, lpHeaders + wcslen(_T("HTTP/1.1 ")), 3*sizeof(TCHAR));
	int dwHttpStatus = 0;
	dwHttpStatus = _wtoi(szHttpStatus);
	if ((dwHttpStatus<200)||(dwHttpStatus>300))
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		delete[] lpHeaders;
		return false;
	}
	char cResponse[4096];
	if(!InternetReadFile (m_hRequest, (LPVOID)(cResponse),4096, &dwSize))
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		delete[] lpHeaders; 

		return false; 
	}
	if(dwSize == 0)
	{
		InternetCloseHandle(m_hRequest);
		InternetCloseHandle(m_hConnect);
		InternetCloseHandle(m_hOpen);
		delete[] lpHeaders; 
		return false;  
	}


// 	HttpQueryInfo(m_hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, NULL, &dwSize,NULL);
// 	if (!HttpQueryInfo (m_hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, 
// 		(LPVOID) lpHeaders, &dwSize, NULL))
// 	{
// 		InternetCloseHandle(m_hRequest);
// 		InternetCloseHandle(m_hConnect);
// 		InternetCloseHandle(m_hOpen);
// 		delete[] lpHeaders; 
// 		return false;
// 	}
// 
// 	memcpy(szHttpStatus,lpHeaders+wcslen(_T("HTTP/1.1 ")),3*sizeof(TCHAR));
// 	dwHttpStatus = _wtoi(szHttpStatus);
// 	if ((dwHttpStatus<200)||(dwHttpStatus>300))
// 	{
// 		InternetCloseHandle(m_hRequest);
// 		InternetCloseHandle(m_hConnect);
// 		InternetCloseHandle(m_hOpen);
// 		delete[] lpHeaders;
// 		return false;
// 	}
	delete[] lpHeaders; 
	InternetCloseHandle(m_hRequest);
	InternetCloseHandle(m_hConnect);
	InternetCloseHandle(m_hOpen);

	return true;
}
