// TestButton.cpp : ʵ���ļ�
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



// CTestButton ��Ϣ�������



void CTestButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CTestButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

	// TODO:  ������Ĵ����Ի���ָ����
	m_testIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(m_testIcon, TRUE);
}
