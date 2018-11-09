#ifndef _Coin_HG
#define _Coin_HG
#include "PickUpObj.h"
class Coin :
	public PickUpObj
{
public:
	Coin();
	~Coin();
	void setModel(cMeshObject* m_model);
    cMeshObject* getModel();
	void setValue(int value);
	int getValue();
private:
	int m_moneyValue;
	cMeshObject* m_model;
};

#endif

