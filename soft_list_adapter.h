#ifndef SOFT_LIST_ADAPTER_H_
#define SOFT_LIST_ADAPTER_H_

#include <helper/SAdapterBase.h>

class SoftListAdapter :
	public SMcAdapterBase
{
#define NUMSCALE 100000
public:
	struct SOFTINFO
	{
		const wchar_t * pszSkinName;
		const wchar_t * pszName;
		const wchar_t * pszDesc;
		float     fScore;
		DWORD     dwSize;
		const wchar_t * pszInstallTime;
		const wchar_t * pszUseTime;
	};

	SArray<SOFTINFO> m_softInfo;
public:
	SoftListAdapter();
	~SoftListAdapter();
protected:
	struct SORTCTX
	{
		int iCol;
		SHDSORTFLAG stFlag;
	};

	void Init();
	virtual int getCount();
	SStringT getSizeText(DWORD dwSize);
	void getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate);
	bool OnButtonClick(EventArgs *pEvt);
	void DeleteItem(int iPosition);
	SStringW GetColumnName(int iCol) const;
	bool OnSort(int iCol, SHDSORTFLAG * stFlags, int nCols);
	static int __cdecl SortCmp(void *context, const void * p1, const void * p2);
};

#endif