#ifndef _HealthObj_HG
#define _HealthObj_HG
#include "PickUpObj.h"
class HealthObj :
	public PickUpObj
{
public:
	HealthObj();
	~HealthObj();
	void setModel(cMeshObject* m_model);
	cMeshObject* getModel();
	void setValue(int value);
	int getValue();
	void setSize(glm::vec2 dimensions);
	glm::vec2 getSize();
private:
	int m_healthValue;
	cMeshObject* m_model;
	float width;
	float hight;
};

#endif

