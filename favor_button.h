#ifndef FAVORBUTTON_H_
#define FAVORBUTTON_H_

class  EventFavChange : public TplEventArgs<EventFavChange>
{
	SOUI_CLASS_NAME(EventCBSelChange, L"on_fav_change")
public:
	EventFavChange(SObject *pSender, bool status) :TplEventArgs<EventFavChange>(pSender),
		status_(status) {}
	enum {EventID = EVT_EXTERNAL_BEGIN + 1000};
	bool status_;
};

class FavorButton :public SButton
{
	SOUI_CLASS_NAME(FavorButton, L"favorbutton")
public:
	FavorButton();
	~FavorButton();

	void SetFav(BOOL fav);
	virtual void OnPaint(IRenderTarget *pRT);
	virtual void OnLButtonUp(UINT nFlags, CPoint pt);
protected:
	SOUI_MSG_MAP_BEGIN()
		MSG_WM_PAINT_EX(OnPaint)
		MSG_WM_LBUTTONUP(OnLButtonUp)
	SOUI_MSG_MAP_END()

	SOUI_ATTRS_BEGIN()
		ATTR_INT(L"fav", fav_, FALSE)
	SOUI_ATTRS_END()
private:
	bool fav_;
};

#endif

