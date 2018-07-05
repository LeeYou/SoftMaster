#include "stdafx.h"
#include "soft_upgrade_history_tree_view_adapter.h"

SoftUpgradeHistoryTreeViewAdapter::SoftUpgradeHistoryTreeViewAdapter()
{
	Initialize();
}
SoftUpgradeHistoryTreeViewAdapter::~SoftUpgradeHistoryTreeViewAdapter()
{
}
void SoftUpgradeHistoryTreeViewAdapter::Initialize() {

	TreeItemData2 data;
	data.name_ = L"精选软件";
	data.parent_ = true;

	HSTREEITEM hRoot = InsertItem(data);
	SetItemExpanded(hRoot, TRUE);
 	for (int i = 0; i < 6; i++)
 	{
		data.name_ = L"测试数据";
 		data.parent_ = false;
 		InsertItem(data, hRoot);
 	}

}
void SoftUpgradeHistoryTreeViewAdapter::getView(SOUI::HTREEITEM loc,
	SWindow * pItem, pugi::xml_node xmlTemplate) {

	if (pItem->GetChildrenCount() == 0)
	{
		pItem->InitFromXml(xmlTemplate);
	}

	SWindow *pImageIcon = pItem->FindChildByName(L"img_icon");
	SWindow *pTxtName = pItem->FindChildByName(L"txt_name");
	SWindow *pTxtDesc = pItem->FindChildByName(L"txt_desc");
	SWindow *pTxtNew = pItem->FindChildByName(L"txt_new");
	SWindow *pTxtOld = pItem->FindChildByName(L"txt_old");
	SWindow *pTxtNewVer = pItem->FindChildByName(L"txt_new_ver");
	SWindow *pTxtOldVer = pItem->FindChildByName(L"txt_old_ver");
	SWindow *pTxtSize = pItem->FindChildByName(L"txt_size");
	SWindow *pTxtInstallTime = pItem->FindChildByName(L"txt_installtime");

	ItemInfo & ii = m_tree.GetItemRef((HSTREEITEM)loc);
	
	SToggle *pSwitch = (SToggle*)pItem->FindChildByName(L"tgl_switch");
	SASSERT(pSwitch);
	pSwitch->SetVisible(HasChildren(loc));
	pSwitch->SetToggle(IsItemExpanded(loc));
	pSwitch->GetEventSet()->subscribeEvent(EVT_CMD,
		Subscriber(&SoftUpgradeHistoryTreeViewAdapter::OnSwitchClick, this));

	//
	if (HasChildren(loc)) {
		SButton *pBtnMustRun = (SButton*)pItem->FindChildByName(L"btn_mustrun");
		pBtnMustRun->SetVisible(false);
		pImageIcon->SetVisible(FALSE);
		//pTxtName->SetVisible(FALSE);
		pTxtDesc->SetVisible(FALSE);
		pTxtNew->SetVisible(FALSE);
		pTxtOld->SetVisible(FALSE);
		pTxtNewVer->SetVisible(FALSE);
		pTxtOldVer->SetVisible(FALSE);
		pTxtSize->SetVisible(FALSE);
		pTxtInstallTime->SetVisible(FALSE);

		pTxtName->SetAttribute(L"pos", L"[0,15");
		pTxtName->SetAttribute(L"font", L"face:宋体,size:15,bold:1");
		pTxtName->SetAttribute(L"colorText", L"#030303");
	}
	else {
		SButton *pBtnHistoryDelete = (SButton*)pItem->FindChildByName(L"btn_history_delete");
		pBtnHistoryDelete->SetVisible(false);
		pTxtName->SetAttribute(L"pos",L"[10,5");
		pTxtName->SetAttribute(L"font", L"face:宋体,size:12");
		pTxtName->SetAttribute(L"colorText", L"#030303");
	}
}
bool SoftUpgradeHistoryTreeViewAdapter::OnSwitchClick(EventArgs *pEvt){
	SToggle *pToggle = sobj_cast<SToggle>(pEvt->sender);
	SASSERT(pToggle);
	SItemPanel *pItem = sobj_cast<SItemPanel>(pToggle->GetRoot());
	SASSERT(pItem);
	SOUI::HTREEITEM loc = (SOUI::HTREEITEM)pItem->GetItemIndex();
	ExpandItem(loc, ITvAdapter::TVC_TOGGLE);
	return true;
}