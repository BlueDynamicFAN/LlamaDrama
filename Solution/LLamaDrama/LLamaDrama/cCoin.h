/**
	cCoin.h

	Purpose: Contains the information for the cCoin class
	@author: BlueDynamic
	@version: 1.0.0
*/
#ifndef _cCoin_HG
#define _cCoin_HG
#include "cPickUp.h"
class cCoin :
	public cPickUp
{
public:
	cCoin();
	~cCoin();
	void setModel(cMeshObject* m_model);
    cMeshObject* getModel();
	void setValue(int value);
	int getValue();
	void setSize(glm::vec2 dimensions);
	std::string getType();
	glm::vec2 getSize();

private:
	int m_moneyValue;
	cMeshObject* m_model;
	float radius;
	std::string type;
};

#endif

