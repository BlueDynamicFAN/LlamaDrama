/**
	cHealth.h

	Purpose: Contains the information for the cHealth class
	@author: BlueDynamic
	@version: 1.0.0
*/
#ifndef _cHealth_HG
#define _cHealth_HG
#include "cPickUp.h"
class cHealth :
	public cPickUp
{
public:
	cHealth();
	~cHealth();
	void setModel(cMeshObject* m_model);
	cMeshObject* getModel();
	void setValue(int value);
	int getValue();
	void setSize(glm::vec2 dimensions);
	std::string getType();
	glm::vec2 getSize();
private:
	int m_healthValue;
	cMeshObject* m_model;
	float width;
	float hight;
	std::string type;
};

#endif

