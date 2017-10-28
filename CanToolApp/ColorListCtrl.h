#pragma once


// CColorListCtrl

class CColorListCtrl : public CListCtrl
{

public:
	CColorListCtrl();
	virtual ~CColorListCtrl();
	void SetColor(int ,int,COLORREF);
	void SetSubItemFont(LOGFONT font, COLORREF color, long lsize);
	int m_iRow;
	int m_iCol;
	COLORREF m_Color;
	COLORREF m_TextColor;
	CFont *m_Font;
	long m_TextSize;
protected:
	DECLARE_MESSAGE_MAP()

	virtual void PreSubclassWindow();
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};


