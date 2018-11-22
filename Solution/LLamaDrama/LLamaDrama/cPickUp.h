/**
	cPickUp.cpp

	Purpose: This interface descibes the methods that cCoin and cHealth classes must implement.
	@author: BlueDynamic
	@version: 1.0.0
*/

#ifndef _cPickUp_HG
#define _cPickUp_HG
#include "../cMeshObject.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
class cPickUp
{
public:
	cPickUp() { ; }
	virtual ~cPickUp() { ; }
	virtual void setModel(cMeshObject* m_model) = 0;
	virtual cMeshObject* getModel() = 0;
	virtual void setValue(int value) = 0;
	virtual int getValue() = 0;
	virtual void setSize(glm::vec2 dimensions) = 0;
	virtual glm::vec2 getSize() = 0;
	virtual std::string getType() = 0;

};

#endif
