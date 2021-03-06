
#ifndef MAIN_DIALOG_H_
#define MAIN_DIALOG_H_

#include "core\windows_view.h"
#include "main_tab_button.h"


class AbstractSoftStripView;
class SoftStrip;
class MainTabButton;

class MainDialog : public SHostWnd, public WindowsView
 {
public:
	MainDialog();
	~MainDialog();

	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);

	void OnBtnMsgBox();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

	void Init();

	AbstractSoftStripView *softstip() ;
	virtual HWND GetNativeHwnd() const;

	void UpdatePageStatus();

	void OnBtnSelectSoftHouse();
	void OnBtnSelectDownload();
	void OnBtnSelectUnstall();
	void OnBtnSelectUpgrade();

	void OnBtnSelectPageUpgrade();
	void OnBtnSelectPageUpgradeHistory();

protected:
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)

		EVENT_NAME_COMMAND(L"btn_select_update", OnBtnSelectPageUpgrade)
		EVENT_NAME_COMMAND(L"btn_select_updatehistory", OnBtnSelectPageUpgradeHistory)

		EVENT_NAME_COMMAND(L"btn_softhouse", OnBtnSelectSoftHouse)
		EVENT_NAME_COMMAND(L"btn_download", OnBtnSelectDownload)
		EVENT_NAME_COMMAND(L"btn_unstall", OnBtnSelectUnstall)
		EVENT_NAME_COMMAND(L"btn_upgrade", OnBtnSelectUpgrade)

		EVENT_MAP_END()

		//HostWnd真实窗口消息处理
		BEGIN_MSG_MAP_EX(MainDialog)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()
private:
	BOOL	layout_inited_;	
	AbstractSoftStripView *abstract_soft_strip_view_;
	MainTabButton	*wnd_softhouse_;
	MainTabButton	*wnd_download_;
	MainTabButton	*wnd_unstall_;
	MainTabButton	*wnd_upgrade_;
	STreeView		*tree_view_soft_list_;
	//
	SWindow			*wnd_upgrade_list_; //更新列表控件
	SWindow			*wnd_upgrade_history_; //更新历史记录
	SButton			*btn_upgrade_list;
	SButton			*btn_upgrade_history;
	SWindow			*wnd_upgrade_cap1, *wnd_upgrade_cap2;
	//
	STreeView		*tree_view_upgrade_history_;
};

#endif