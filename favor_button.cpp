#include "stdafx.h"
#include "favor_button.h"

FavorButton::FavorButton():fav_(false)
{
	m_evtSet.addEvent(EVENTID(EventFavChange));
}
FavorButton::~FavorButton()
{
}
void FavorButton::SetFav(BOOL fav) {
	fav_ = fav;
}
void FavorButton::OnPaint(IRenderTarget *pRT) {
	if (!m_pBgSkin) return;
	CRect rcClient;
	GetClientRect(&rcClient);

	if (m_byAlphaAni == 0xFF)
	{
		if (!fav_) {
			//不在动画过程中
			m_pBgSkin->Draw(pRT, rcClient,
				IIF_STATE4(GetState(), 0, 1, 0, 1)
			);
		}
		else {
			//不在动画过程中
			m_pBgSkin->Draw(pRT, rcClient,
				IIF_STATE4(GetState(), 2, 3, 2, 3)
			);
		}
	}
}
void FavorButton::OnLButtonUp(UINT nFlags, CPoint pt) {
	fav_ = !fav_;
	EventFavChange evt(this, fav_);
	FireEvent(evt);
	__super::OnLButtonUp(nFlags, pt);
}