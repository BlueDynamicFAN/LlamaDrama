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
private:
	int m_healthValue;
	cMeshObject* m_model;
};

#endif

