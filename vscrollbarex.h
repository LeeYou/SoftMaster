#ifndef VSCROLLBAR_EX_H_
#define VSCROLLBAR_EX_H_



//treeview 滚动条
//实现一个只有纵向滚动条皮肤
class TreeViewSkinVScrollbar : public SSkinScrollbar
{
	SOUI_CLASS_NAME(TreeViewSkinVScrollbar, L"tvvscrollbar")

public:

	TreeViewSkinVScrollbar()
	{
		m_nStates = 4;
	}

	//不支持显示上下箭头
	virtual BOOL HasArrow() { return FALSE; }
	virtual int GetIdealSize() {
		if (!GetImage()) return 0;
		return GetImage()->Width() / m_nStates;
	}
protected:
	//返回源指定部分在原位图上的位置。
	virtual CRect GetPartRect(int nSbCode, int nState, BOOL bVertical)
	{
		CSize sz = GetSkinSize();
		CSize szFrame(sz.cx, sz.cy / 2);

		CRect rc;
		if (!bVertical
			|| nSbCode == SB_LINEDOWN
			|| nSbCode == SB_LINEUP
			|| nSbCode == SB_CORNOR
			|| nSbCode == SB_THUMBGRIPPER)
			return rc;

		int iPart = -1;
		//滚动条正常状态
		if (nState == SBST_NORMAL) {
			nState = 0;
			iPart = 1;
		}
		//失效状态
		else if (nState == SBST_INACTIVE && !m_bHasInactive
			&& nSbCode == SB_THUMBTRACK) {
			nState = 0;
			iPart = 1;
		}
		//hor 状态
		else if (nState == SBST_HOVER && !m_bHasInactive
			&&  nSbCode == SB_THUMBTRACK) {
			nState = 1;
			iPart = 1;
		}
		//按下状态
		else if (nState == SBST_PUSHDOWN && !m_bHasInactive
			&&  nSbCode == SB_THUMBTRACK) {
			nState = 2;
			iPart = 1;
		}
		else
		{
			//背景
			nState = 0;
			iPart = 0;
		}

		return CRect(CPoint(szFrame.cx*nState, szFrame.cy*iPart), szFrame);
	}
};

//其他通用滚动条
class CustomSkinVScrollbar : public SSkinScrollbar
{
	SOUI_CLASS_NAME(CustomSkinVScrollbar, L"vscrollbar")

public:

	CustomSkinVScrollbar()
	{
		m_nStates = 4;
	}

	//不支持显示上下箭头
	virtual BOOL HasArrow() { return FALSE; }
	virtual int GetIdealSize() {
		if (!GetImage()) return 0;
		return GetImage()->Width() / m_nStates;
	}
protected:
	//返回源指定部分在原位图上的位置。
	virtual CRect GetPartRect(int nSbCode, int nState, BOOL bVertical)
	{
		CSize sz = GetSkinSize();
		CSize szFrame(sz.cx, sz.cy / 4);

		CRect rc;
		if (!bVertical
			/*	|| nSbCode == SB_CORNOR*/
			|| nSbCode == SB_THUMBGRIPPER)
			return rc;
		/*if (nSbCode == SB_CORNOR)
		{
			return CRect(CPoint(szFrame.cx * 3, 0), szFrame);
		}*/
		int iPart = -1;

		if (nState == SBST_INACTIVE && !m_bHasInactive) {
			nState = 0;
		}
		if (nState == SBST_NORMAL) {
			nState = 0;
		}
		//hor 状态
		else if (nState == SBST_HOVER && !m_bHasInactive) {
			nState = 1;
		}
		//按下状态
		else if (nState == SBST_PUSHDOWN && !m_bHasInactive) {
			nState = 2;
		}
		else {
			nState = 0;
		}

		switch (nSbCode)
		{
		case SB_LINEUP:
			iPart = 0;
			break;
		case SB_LINEDOWN:
			iPart = 2;
			break;
		case SB_THUMBTRACK:
			iPart = 3;
			break;
		default:
			iPart = 1;
			break;
			// 			case SB_PAGEUP:
			// 			case SB_PAGEDOWN:
			// 				iPart = 3;
			// 				break;
		}
		return CRect(CPoint(szFrame.cx*nState, szFrame.cy*iPart), szFrame);
	}
};

#endif