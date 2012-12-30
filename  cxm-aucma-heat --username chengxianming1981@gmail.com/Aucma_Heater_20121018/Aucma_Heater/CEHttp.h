#pragma once
#include <afxinet.h>
typedef CString(CALLBACK* ONHTTPREQUEST)(void* pFatherPtr /** 父对象指针*/);
typedef void(CALLBACK* ONHTTPRESPONSE)(void* pFatherPtr, CString strResponse);
class CCEHttp
{
public:
	CCEHttp(void);
	~CCEHttp(void);
private:
	// 读线程句柄
	HANDLE m_hReadThread;
	// 读线程退出事件句柄
	HANDLE m_hCloseEvent;
	// 读线程ID标识
	DWORD m_dwReadThreadID;
	// 串口读线程函数
	static DWORD WINAPI ThreadProc(LPVOID lparam);
	HINTERNET m_hOpen;
	HINTERNET m_hConnect;
	HINTERNET m_hRequest;
public:
	// Http请求回调函数指针
	ONHTTPREQUEST m_oHttpRequest;
	// Http响应回调函数指针
	ONHTTPRESPONSE m_oHttpResponse;
	// 父类指针
	void* m_pFatherPtr;
public:
	// 初始化
	void OnInit(void* pFatherPtr);
	// 连接服务器
	bool ConnectServer(void);
	// 关闭
	void OnClose(void);
	// 发送HTTP请求
	bool SendHttpRequest(CString strRequest);
};
