#pragma once


// CTSS

class CTSS : public CStatic
{
	DECLARE_DYNAMIC(CTSS)

public:
	CTSS();
	virtual ~CTSS();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


