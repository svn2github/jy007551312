// Aucma_Heater.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CAucma_HeaterApp:
// �йش����ʵ�֣������ Aucma_Heater.cpp
//

class CAucma_HeaterApp : public CWinApp
{
public:
	CAucma_HeaterApp();
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAucma_HeaterApp theApp;