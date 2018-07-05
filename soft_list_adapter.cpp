#include "stdafx.h"
#include "soft_list_adapter.h"
#include "favor_button.h"

SoftListAdapter::SoftListAdapter()
{
	Init();
}
SoftListAdapter::~SoftListAdapter()
{
}
void SoftListAdapter::Init() {
	SOFTINFO info[] =
	{
		{
			L"skin_icon1",
			L"³��ʦ",
			L"³��ʦ��һ��רҵ��Ӳ����⣬������װ����",
			5.4f,
			15 * (1 << 20),
			L"2015-8-5",
			L"����"
		},
		{
			L"skin_icon2",
			L"PhotoShop",
			L"ǿ���ͼƬ������",
			9.0f,
			150 * (1 << 20),
			L"2015-8-5",
			L"����"
		},
		{
			L"skin_icon3",
			L"QQ7.0",
			L"��Ѷ��˾��Ʒ�ļ�ʱ���칤��",
			8.0f,
			40 * (1 << 20),
			L"2015-8-5",
			L"����"
		},
		{
			L"skin_icon4",
			L"Visual Studio 2008",
			L"Microsoft��˾�ĳ��򿪷��׼�",
			9.0f,
			40 * (1 << 20),
			L"2015-8-5",
			L"����"
		},
		{
			L"skin_icon5",
			L"YY8",
			L"YY����",
			9.0f,
			20 * (1 << 20),
			L"2015-8-5",
			L"����"
		},
		{
			L"skin_icon6",
			L"��������",
			L"�ٶ����������",
			8.5f,
			35 * (1 << 20),
			L"2015-8-5",
			L"����"
		},
		{
			L"skin_icon7",
			L"Ѹ��",
			L"Ѹ���������",
			7.3f,
			17 * (1 << 20),
			L"2015-8-5",
			L"����"
		}
	};


	for (int i = 0; i < ARRAYSIZE(info); i++)
	{
		m_softInfo.Add(info[i]);
	}
}

int SoftListAdapter::getCount()
{
	return m_softInfo.GetCount()*NUMSCALE;
}

SStringT SoftListAdapter::getSizeText(DWORD dwSize)
{
	int num1 = dwSize / (1 << 20);
	dwSize -= num1 *(1 << 20);
	int num2 = dwSize * 100 / (1 << 20);
	return SStringT().Format(_T("%d.%02dM"), num1, num2);
}

void SoftListAdapter::getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate)
{
	if (pItem->GetChildrenCount() == 0)
	{
		pItem->InitFromXml(xmlTemplate);
	}

	SOFTINFO *psi = m_softInfo.GetData() + position%m_softInfo.GetCount();
	//pItem->FindChildByName(L"img_icon")->SetAttribute(L"skin", psi->pszSkinName);
	pItem->FindChildByName(L"txt_name")->SetWindowText(S_CW2T(psi->pszName));
	pItem->FindChildByName(L"txt_desc")->SetWindowText(S_CW2T(psi->pszDesc));
	//pItem->FindChildByName(L"txt_score")->SetWindowText(SStringT().Format(_T("%1.2f ��"), psi->fScore));
	pItem->FindChildByName(L"txt_installtime")->SetWindowText(S_CW2T(psi->pszInstallTime));
	//pItem->FindChildByName(L"txt_usetime")->SetWindowText(S_CW2T(psi->pszUseTime));
	pItem->FindChildByName(L"txt_size")->SetWindowText(getSizeText(psi->dwSize));
	//pItem->FindChildByName2<SRatingBar>(L"rating_score")->SetValue(psi->fScore / 2);
	//pItem->FindChildByName(L"txt_index")->SetWindowText(SStringT().Format(_T("��%d��"), position + 1));

	FavorButton *pBtnFav = pItem->FindChildByName2<FavorButton>(L"btn_fav");
	pBtnFav->SetUserData(position);
	pBtnFav->GetEventSet()->subscribeEvent(EVT_CMD,
		Subscriber(&SoftListAdapter::OnButtonClick, this));
}

bool SoftListAdapter::OnButtonClick(EventArgs *pEvt)
{
	EventFavChange *event = static_cast<EventFavChange*>(pEvt);
	if (event) {
		std::wstring s = L"������ղ�С���ġ�����";
		SMessageBox(NULL, s.c_str(), s.c_str(), MB_OK);
	}
	return true;
}

//ɾ��һ�У��ṩ�ⲿ���á�
void SoftListAdapter::DeleteItem(int iPosition)
{
	if (iPosition >= 0 && iPosition < getCount())
	{
		int iItem = iPosition % m_softInfo.GetCount();
		m_softInfo.RemoveAt(iItem);
		notifyDataSetChanged();
	}
}

SStringW SoftListAdapter::GetColumnName(int iCol) const {
	return SStringW().Format(L"col%d", iCol + 1);
}

bool SoftListAdapter::OnSort(int iCol, SHDSORTFLAG * stFlags, int nCols)
{
	if (iCol == 5) //���һ�С���������֧������
		return false;

	SHDSORTFLAG stFlag = stFlags[iCol];
	switch (stFlag)
	{
	case ST_NULL:stFlag = ST_UP; break;
	case ST_DOWN:stFlag = ST_UP; break;
	case ST_UP:stFlag = ST_DOWN; break;
	}
	for (int i = 0; i < nCols; i++)
	{
		stFlags[i] = ST_NULL;
	}
	stFlags[iCol] = stFlag;

	SORTCTX ctx = { iCol,stFlag };
	qsort_s(m_softInfo.GetData(), m_softInfo.GetCount(), sizeof(SOFTINFO), SortCmp, &ctx);
	return true;
}

int __cdecl SoftListAdapter::SortCmp(void *context, const void * p1, const void * p2)
{
	SORTCTX *pctx = (SORTCTX*)context;
	const SOFTINFO *pSI1 = (const SOFTINFO*)p1;
	const SOFTINFO *pSI2 = (const SOFTINFO*)p2;
	int nRet = 0;
	switch (pctx->iCol)
	{
	case 0://name
		nRet = wcscmp(pSI1->pszName, pSI2->pszName);
		break;
	case 1://score
	{
		float fCmp = (pSI1->fScore - pSI2->fScore);
		if (fabs(fCmp) < 0.0000001) nRet = 0;
		else if (fCmp > 0.0f) nRet = 1;
		else nRet = -1;
	}
	break;
	case 2://size
		nRet = (int)(pSI1->dwSize - pSI2->dwSize);
		break;
	case 3://install time
		nRet = wcscmp(pSI1->pszInstallTime, pSI2->pszInstallTime);
		break;
	case 4://user time
		nRet = wcscmp(pSI1->pszUseTime, pSI2->pszUseTime);
		break;

	}
	if (pctx->stFlag == ST_UP)
		nRet = -nRet;
	return nRet;
}