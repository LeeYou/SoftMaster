#include "stdafx.h"
#include "soft_house_tree_view_adapter.h"

SoftHouseTreeViewAdapter::SoftHouseTreeViewAdapter()
{
	Initialize();
}
SoftHouseTreeViewAdapter::~SoftHouseTreeViewAdapter()
{
}
void SoftHouseTreeViewAdapter::Initialize() {

	TreeItemData data;
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

	data.name_ = L"软件宝库";
	data.parent_ = true;
	hRoot = InsertItem(data);
	SetItemExpanded(hRoot, TRUE);
	for (int i = 0; i < 16; i++)
	{
		data.name_ = L"测试数据2";
		data.parent_ = false;
		InsertItem(data, hRoot);
	}
}
void SoftHouseTreeViewAdapter::getView(SOUI::HTREEITEM loc,
	SWindow * pItem, pugi::xml_node xmlTemplate) {

	if (pItem->GetChildrenCount() == 0)
	{
		pItem->InitFromXml(xmlTemplate);
	}
	ItemInfo & ii = m_tree.GetItemRef((HSTREEITEM)loc);
	
	SWindow *pTxtName = pItem->FindChildByName(L"txt_name");
	SASSERT(pTxtName);
	pTxtName->SetWindowText(ii.data.name_.c_str());

	SWindow *pImageIcon = pItem->FindChildByName(L"img_icon");
	SASSERT(pImageIcon);
	if (ii.data.parent_) {
		pImageIcon->SetVisible(FALSE);
		pTxtName->SetAttribute(L"pos", L"{0,5,-0,-0");
		pTxtName->SetAttribute(L"colorText", L"#0A0A0A");
		pTxtName->SetAttribute(L"font", L"face:宋体,size:13,bold:1");
	}
	else {
		//474747
		pTxtName->SetAttribute(L"colorText", L"#474747");
		pTxtName->SetAttribute(L"font", L"face:宋体,size:13");
		pTxtName->SetAttribute(L"pos", L"[5,{0,-60,-0");
		pImageIcon->SetVisible(TRUE);
	}

	SWindow *pTxtCount = pItem->FindChildByName(L"txt_count");
	if (pTxtCount) {
		pTxtCount->SetWindowText(L"(10)");
	}

	SToggle *pSwitch = (SToggle*)pItem->FindChildByName(L"tgl_switch");
	SASSERT(pSwitch);
	pSwitch->SetVisible(HasChildren(loc));
	pSwitch->SetToggle(IsItemExpanded(loc));
	pSwitch->GetEventSet()->subscribeEvent(EVT_CMD,
		Subscriber(&SoftHouseTreeViewAdapter::OnSwitchClick, this));
}
bool SoftHouseTreeViewAdapter::OnSwitchClick(EventArgs *pEvt){
	SToggle *pToggle = sobj_cast<SToggle>(pEvt->sender);
	SASSERT(pToggle);
	SItemPanel *pItem = sobj_cast<SItemPanel>(pToggle->GetRoot());
	SASSERT(pItem);
	SOUI::HTREEITEM loc = (SOUI::HTREEITEM)pItem->GetItemIndex();
	ExpandItem(loc, ITvAdapter::TVC_TOGGLE);
	return true;
}