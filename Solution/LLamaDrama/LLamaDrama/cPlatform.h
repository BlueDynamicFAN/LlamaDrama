/**
	Platform.cpp
	Purpose: Contains the information for a platform
	@author: BlueDynamic
	@version: 1.0.0
*/
#ifndef _Platform_HG_
#define _Platform_HG_
#include <string>
#include "../cMeshObject.h"

class cPlatform
{
public:
	cPlatform()
	{
		this->m_model = new cMeshObject;
		this->m_height = 0.0f;
		this->m_width = 0.0f;
		return;
	}

	cPlatform(std::string meshName, std::string fName, float h, float w, glm::vec3 position, glm::vec3 colour) : cPlatform()
	{
		this->m_height = h;
		this->m_width = w;
		this->m_model->m_meshName = meshName;
		this->m_model->m_friendlyName = fName;
		this->m_model->m_position = position;
		this->m_model->m_objColour = colour;
		return;
	}
	~cPlatform() { ; }

	float m_height;
	float m_width;
	cMeshObject* m_model;
};

#endif // _Platform_HG_

