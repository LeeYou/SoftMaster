#include "stdafx.h"
#include "soft_upgrade_adapter.h"

SoftUpgradeAdapter::SoftUpgradeAdapter()
{
	m_pCbxSel = new int[getCount()];
	memset(m_pCbxSel, 0, sizeof(int)*getCount());
}
SoftUpgradeAdapter::~SoftUpgradeAdapter()
{
	delete[]m_pCbxSel;
}
int SoftUpgradeAdapter::getCount()
{
	return 50000;
}

void SoftUpgradeAdapter::getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate)
{
	if (pItem->GetChildrenCount() == 0)
	{
		pItem->InitFromXml(xmlTemplate);
	}

	SWindow *pTextName = pItem->FindChildByName(L"txt_name");
	pTextName->SetWindowTextW(L"QQ浏览器");
	SWindow *pTextDesc = pItem->FindChildByName(L"txt_desc");
	pTextDesc->SetWindowTextW(L"垃圾浏览器，不要用啊 ");

	SWindow *pTextInstallVer = pItem->FindChildByName(L"txt_installed_ver");
	pTextInstallVer->SetWindowTextW(L"1.0.0.1");

	SWindow *pTextNewVer = pItem->FindChildByName(L"txt_new_ver");
	pTextNewVer->SetWindowTextW(L"1.12.12.1 ");

	SWindow *pTextSize = pItem->FindChildByName(L"txt_size");
	pTextSize->SetWindowTextW(L"10MB");

	SWindow *pTextInstallTime = pItem->FindChildByName(L"txt_installtime");
	pTextInstallTime->SetWindowTextW(L"2018-08-08");

	//SButton *pBtn = pItem->FindChildByName2<SButton>(L"btn_test");
	//pBtn->SetWindowText(SStringT().Format(_T("button %d"), position));
	//pBtn->GetRoot()->SetUserData(position);

	//由网友“从未来过” 修改的新事件订阅方式,采用模板函数从响应函数中自动提取事件类型，2016.12.13
	//pBtn->GetEventSet()->subscribeEvent(&SoftUpgradeAdapter::OnButtonClick, this);

	//SComboBox * pCbx = pItem->FindChildByName2<SComboBox>(L"cbx_in_lv");
	//if (pCbx)
	//{9AEBCE
	//	pCbx->SetCurSel(m_pCbxSel[position]);
	//	pCbx->GetEventSet()->subscribeEvent(&SoftUpgradeAdapter::OnCbxSelChange, this);
	//}
}

bool SoftUpgradeAdapter::OnCbxSelChange(EventCBSelChange *pEvt)
{
	SComboBox *pCbx = sobj_cast<SComboBox>(pEvt->sender);
	int iItem = pCbx->GetRoot()->GetUserData();
	m_pCbxSel[iItem] = pCbx->GetCurSel();
	return true;
}

bool SoftUpgradeAdapter::OnButtonClick(EventCmd *pEvt)
{
	SButton *pBtn = sobj_cast<SButton>(pEvt->sender);
	int iItem = pBtn->GetRoot()->GetUserData();
	SMessageBox(NULL, SStringT().Format(_T("button of %d item was clicked"), iItem), _T("haha"), MB_OK);
	return true;
}