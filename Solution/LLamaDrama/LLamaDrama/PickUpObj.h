#ifndef _PickUpObj_HG
#define _PickUpObj_HG
#include "../cMeshObject.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
class PickUpObj
{
public:
	PickUpObj() { ; }
	virtual ~PickUpObj() { ; }
	virtual void setModel(cMeshObject* m_model) = 0;
	virtual cMeshObject* getModel() = 0;
	virtual void setValue(int value) = 0;
	virtual int getValue() = 0;
	virtual void setSize(glm::vec2 dimensions) = 0;
	virtual glm::vec2 getSize() = 0;

};

#endif
