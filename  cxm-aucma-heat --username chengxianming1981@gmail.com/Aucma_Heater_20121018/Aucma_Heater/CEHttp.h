#pragma once
#include <afxinet.h>
typedef CString(CALLBACK* ONHTTPREQUEST)(void* pFatherPtr /** ������ָ��*/);
typedef void(CALLBACK* ONHTTPRESPONSE)(void* pFatherPtr, CString strResponse);
class CCEHttp
{
public:
	CCEHttp(void);
	~CCEHttp(void);
private:
	// ���߳̾��
	HANDLE m_hReadThread;
	// ���߳��˳��¼����
	HANDLE m_hCloseEvent;
	// ���߳�ID��ʶ
	DWORD m_dwReadThreadID;
	// ���ڶ��̺߳���
	static DWORD WINAPI ThreadProc(LPVOID lparam);
	HINTERNET m_hOpen;
	HINTERNET m_hConnect;
	HINTERNET m_hRequest;
public:
	// Http����ص�����ָ��
	ONHTTPREQUEST m_oHttpRequest;
	// Http��Ӧ�ص�����ָ��
	ONHTTPRESPONSE m_oHttpResponse;
	// ����ָ��
	void* m_pFatherPtr;
public:
	// ��ʼ��
	void OnInit(void* pFatherPtr);
	// ���ӷ�����
	bool ConnectServer(void);
	// �ر�
	void OnClose(void);
	// ����HTTP����
	bool SendHttpRequest(CString strRequest);
};
