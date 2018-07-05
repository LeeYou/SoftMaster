#ifndef VSCROLLBAR_EX_H_
#define VSCROLLBAR_EX_H_



//treeview ������
//ʵ��һ��ֻ�����������Ƥ��
class TreeViewSkinVScrollbar : public SSkinScrollbar
{
	SOUI_CLASS_NAME(TreeViewSkinVScrollbar, L"tvvscrollbar")

public:

	TreeViewSkinVScrollbar()
	{
		m_nStates = 4;
	}

	//��֧����ʾ���¼�ͷ
	virtual BOOL HasArrow() { return FALSE; }
	virtual int GetIdealSize() {
		if (!GetImage()) return 0;
		return GetImage()->Width() / m_nStates;
	}
protected:
	//����Դָ��������ԭλͼ�ϵ�λ�á�
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
		//����������״̬
		if (nState == SBST_NORMAL) {
			nState = 0;
			iPart = 1;
		}
		//ʧЧ״̬
		else if (nState == SBST_INACTIVE && !m_bHasInactive
			&& nSbCode == SB_THUMBTRACK) {
			nState = 0;
			iPart = 1;
		}
		//hor ״̬
		else if (nState == SBST_HOVER && !m_bHasInactive
			&&  nSbCode == SB_THUMBTRACK) {
			nState = 1;
			iPart = 1;
		}
		//����״̬
		else if (nState == SBST_PUSHDOWN && !m_bHasInactive
			&&  nSbCode == SB_THUMBTRACK) {
			nState = 2;
			iPart = 1;
		}
		else
		{
			//����
			nState = 0;
			iPart = 0;
		}

		return CRect(CPoint(szFrame.cx*nState, szFrame.cy*iPart), szFrame);
	}
};

//����ͨ�ù�����
class CustomSkinVScrollbar : public SSkinScrollbar
{
	SOUI_CLASS_NAME(CustomSkinVScrollbar, L"vscrollbar")

public:

	CustomSkinVScrollbar()
	{
		m_nStates = 4;
	}

	//��֧����ʾ���¼�ͷ
	virtual BOOL HasArrow() { return FALSE; }
	virtual int GetIdealSize() {
		if (!GetImage()) return 0;
		return GetImage()->Width() / m_nStates;
	}
protected:
	//����Դָ��������ԭλͼ�ϵ�λ�á�
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
		//hor ״̬
		else if (nState == SBST_HOVER && !m_bHasInactive) {
			nState = 1;
		}
		//����״̬
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