#ifndef SOFT_UPGRADER_ADAPTER_H_
#define SOFT_UPGRADER_ADAPTER_H_

#include <helper\SAdapterBase.h>

class SoftUpgradeAdapter :
	public SAdapterBase
{
public:
	SoftUpgradeAdapter();
	~SoftUpgradeAdapter();

	virtual int getCount();
	virtual void getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate);
protected:
	bool OnCbxSelChange(EventCBSelChange *pEvt);
	bool OnButtonClick(EventCmd *pEvt);
private:
	int * m_pCbxSel;
};

#endif

