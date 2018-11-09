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
	void setSize(glm::vec2 dimensions);
	glm::vec2 getSize();

private:
	int m_moneyValue;
	cMeshObject* m_model;
	float radius;
};

#endif

