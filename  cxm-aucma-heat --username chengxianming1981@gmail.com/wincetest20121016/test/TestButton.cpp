// TestButton.cpp : 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "TestButton.h"


// CTestButton

IMPLEMENT_DYNAMIC(CTestButton, CButton)

CTestButton::CTestButton()
{

}

CTestButton::~CTestButton()
{
}


BEGIN_MESSAGE_MAP(CTestButton, CButton)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// CTestButton 消息处理程序



void CTestButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CTestButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

	// TODO:  添加您的代码以绘制指定项
	m_testIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(m_testIcon, TRUE);
}
