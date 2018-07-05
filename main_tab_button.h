#ifndef MAIN_TAB_BUTTON_H_
#define MAIN_TAB_BUTTON_H_

#include <sobject/Sobject.hpp>


class MainTabButton :
	public SImageButton
{
	SOUI_CLASS_NAME(MainTabButton, L"mainTabBtn")
public:
	MainTabButton();
	~MainTabButton();
protected:
	void OnPaint(IRenderTarget *pRT);
	HRESULT OnAttrCheck(const SStringW& strValue, BOOL bLoading);
	virtual void OnStateChanging(DWORD dwOldState, DWORD dwNewState);
	SWindow * GetSelectedSiblingInGroup();
	CSize GetDesiredSize(IRenderTarget *pRT, LPCRECT pRcContainer);
	CSize GetIconSize();

	SOUI_ATTRS_BEGIN()
		ATTR_SKIN(L"icon", m_pIconSkin, FALSE)
		ATTR_CUSTOM(L"selected", OnAttrCheck)
		ATTR_INT(L"sepSize", m_nSepSize, TRUE)    //FREE_DRAWÊ±ÎÞÐ§
	SOUI_ATTRS_END()

	SOUI_MSG_MAP_BEGIN()
		MSG_WM_PAINT_EX(OnPaint)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_SETFOCUS_EX(OnSetFocus)
	SOUI_MSG_MAP_END()
protected:
	void OnSetFocus(SWND wndOld);
	void OnLButtonUp(UINT nFlags, CPoint pt);
protected:
	ISkinObj	*m_pIconSkin;
	int			 m_nSepSize;
	CPoint		 m_ptPushOffet;
};

#endif

