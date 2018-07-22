#include "stdafx.h"
#include "main_tab_button.h"


MainTabButton::MainTabButton() :m_pIconSkin(NULL),
m_nSepSize(5), m_ptPushOffet(2, 2)
{
}

MainTabButton::~MainTabButton() {
}
CSize MainTabButton::GetIconSize()
{
	return m_pIconSkin->GetSkinSize();
}
CSize MainTabButton::GetDesiredSize(IRenderTarget *pRT, LPCRECT pRcContainer)
{
	SASSERT(m_pIconSkin);
	CSize szIcon = GetIconSize();
	CSize szText;
	pRT->MeasureText(GetWindowText(), GetWindowText().GetLength(), &szText);

	CSize szRet;
	szRet.cy = max(szIcon.cy, szText.cy);
	szRet.cx = szIcon.cx + szText.cx + m_nSepSize;

	CRect rcPadding = GetStyle().GetPadding();
	szRet.cx += rcPadding.left + rcPadding.right;
	szRet.cy += rcPadding.top + rcPadding.bottom;
	return szRet;
}
void MainTabButton::OnPaint(IRenderTarget *pRT) {

	SPainter painter;
	BeforePaint(pRT, painter);

	if (!m_pBgSkin)
		return;

	CRect rcClient;
	GetClientRect(&rcClient);

	//draw background, copy from SButton
	if (m_pBgSkin)
	{
		if (m_byAlphaAni == 0xFF)
		{//不在动画过程中
			m_pBgSkin->Draw(
				pRT, rcClient,
				IIF_STATE4(GetState(), 0, 1, 2, 3)
			);
		}
		else
		{//在动画过程中
			BYTE byNewAlpha = (BYTE)(((UINT)m_byAlphaAni*m_pBgSkin->GetAlpha()) >> 8);
			if (GetState()&WndState_Hover)
			{
				//get hover
				m_pBgSkin->Draw(pRT, rcClient, 0, m_pBgSkin->GetAlpha());
				m_pBgSkin->Draw(pRT, rcClient, 1, byNewAlpha);
			}
			else
			{
				//lose hover
				m_pBgSkin->Draw(pRT, rcClient, 0, m_pBgSkin->GetAlpha());
				m_pBgSkin->Draw(pRT, rcClient, 1, m_pBgSkin->GetAlpha() - byNewAlpha);
			}
		}
	}

	//偏移 xx 个像素
	//if (GetState() & (WndState_PushDown | WndState_Check))
	{
		rcClient.OffsetRect(m_ptPushOffet);
	}
	CRect rcPadding = GetStyle().GetPadding();

	rcClient.DeflateRect(rcPadding);

	//draw icon and text
	CPoint ptIcon = rcClient.TopLeft(), ptText = ptIcon;
	CSize szIcon = GetIconSize();
	CSize szDesired = GetDesiredSize(pRT, &rcClient);
	szDesired.cx -= rcPadding.left + rcPadding.right;
	szDesired.cy -= rcPadding.top + rcPadding.bottom;

	CSize szText;
	pRT->MeasureText(GetWindowText(), GetWindowText().GetLength(), &szText);


	if (m_pIconSkin) {

		DWORD nState = 0;
		if (IsChecked()) {
			nState = 1;
		}
		else
			nState = 0;

		ptIcon.x += (rcClient.Width() - szDesired.cx) / 2;
		ptIcon.y += (rcClient.Height() - szIcon.cy) / 2;

		m_pIconSkin->Draw(pRT, CRect(ptIcon, szIcon), nState);
		ptText.x = ptIcon.x + szIcon.cx + m_nSepSize;
		ptText.y += (rcClient.Height() - szText.cy) / 2;
		pRT->TextOut(ptText.x, ptText.y, GetWindowText(),
			GetWindowText().GetLength());
	}

	AfterPaint(pRT, painter);
}
HRESULT MainTabButton::OnAttrCheck(const SStringW& strValue, BOOL bLoading)
{
	if (bLoading)
	{
		GetEventSet()->setMutedState(true);
		SetCheck(strValue != L"0");
		GetEventSet()->setMutedState(false);
	}
	else
	{
		SetCheck(strValue != L"0");
	}
	return S_FALSE;
}
SWindow * MainTabButton::GetSelectedSiblingInGroup()
{
	SWindow *pParent = GetParent();
	SASSERT(pParent);
	SWindow *pSibling = pParent->GetWindow(GSW_FIRSTCHILD);
	while (pSibling)
	{
		if (pSibling->IsClass(GetClassName()))
		{
			MainTabButton * pRadio = (MainTabButton*)pSibling;
			if (pRadio->IsChecked()) 
				return pRadio;
		}
		pSibling = pSibling->GetWindow(GSW_NEXTSIBLING);
	}
	return NULL;
}
void MainTabButton::OnStateChanging(DWORD dwOldState, DWORD dwNewState)
{
	if ((dwNewState & WndState_Check) && !(dwOldState & WndState_Check))
	{
		MainTabButton *pCurChecked = (MainTabButton*)GetSelectedSiblingInGroup();
		if (pCurChecked)
		{
			pCurChecked->GetEventSet()->setMutedState(true);
			pCurChecked->SetCheck(FALSE);
			pCurChecked->GetEventSet()->setMutedState(false);
		}
	}
}
void MainTabButton::OnSetFocus(SWND wndOld)
{
	if (!IsChecked()) {
		SetCheck(TRUE);
	}
	Invalidate();
}

void MainTabButton::OnLButtonUp(UINT nFlags, CPoint pt)
{
	__super::OnLButtonUp(nFlags, pt);
	if (!IsChecked()) 
		SetCheck(TRUE);
}
