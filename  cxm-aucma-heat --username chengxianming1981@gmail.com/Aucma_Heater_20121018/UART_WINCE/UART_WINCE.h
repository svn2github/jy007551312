// UART_WINCE.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CUART_WINCEApp:
// �йش����ʵ�֣������ UART_WINCE.cpp
//

class CUART_WINCEApp : public CWinApp
{
public:
	CUART_WINCEApp();
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUART_WINCEApp theApp;
