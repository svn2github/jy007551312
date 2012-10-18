#pragma once


// CTestButton

class CTestButton : public CButton
{
	DECLARE_DYNAMIC(CTestButton)

public:
	CTestButton();
	virtual ~CTestButton();
	HICON m_testIcon;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


