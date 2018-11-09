#ifndef _PickUpObj_HG
#define _PickUpObj_HG
#include "../cMeshObject.h"
class PickUpObj
{
public:
	PickUpObj() { ; }
	virtual ~PickUpObj() { ; }
	virtual void setModel(cMeshObject* m_model) = 0;
	virtual cMeshObject* getModel() = 0;
	virtual void setValue(int value) = 0;
	virtual int getValue() = 0;

};

#endif
