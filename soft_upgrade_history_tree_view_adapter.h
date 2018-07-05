#ifndef SOFT_UPGRADE_HISTORY_TREEVIEW_ADAPTER_H_
#define SOFT_UPGRADE_HISTORY_TREEVIEW_ADAPTER_H_

#include <helper/SAdapterBase.h>
#include <helper/SMenuEx.h>
#include <helper/SDibHelper.h>

struct TreeItemData2{
	std::wstring name_; //����
	std::wstring icon_;// icon
	int		 soft_count_;//�������
	bool	 parent_;//�Ƿ��Ǹ��ڵ�

	TreeItemData2():name_(L""),icon_(L""),
	soft_count_(0),parent_(false){
	}
};

class SoftUpgradeHistoryTreeViewAdapter 
	:public STreeAdapterBase<TreeItemData2>
{
public:
	SoftUpgradeHistoryTreeViewAdapter();
	~SoftUpgradeHistoryTreeViewAdapter();

	virtual void getView(SOUI::HTREEITEM loc, 
		SWindow * pItem, pugi::xml_node xmlTemplate);
protected:
	 bool OnSwitchClick(EventArgs *pEvt);
	 void Initialize();
};

#endif
