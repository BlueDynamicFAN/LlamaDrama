/**
	cMeshObject.cpp
	Purpose: Contains all information for cMeshObject
	@author: BlueDynamic
	@version: 1.0.0
*/
#include "cMeshObject.h"

cMeshObject::cMeshObject()
{
	this->m_preRotation = glm::vec3(0.0f);
	this->m_position = glm::vec3(0.0f);
	this->m_postRotation = glm::vec3(0.0f);
	this->m_nonUniformScale = glm::vec3(1.0f);
	this->m_bIsVisible = true;
	this->m_bIsWireFrame = false;
	this->bDontLight = false;
	this->bUseVertexColour = false;
	// Set unique ID
	this->m_uniqueID = cMeshObject::m_NextID;
	// Increment
	cMeshObject::m_NextID++;

	return;
}

//static 
unsigned int cMeshObject::m_NextID = cMeshObject::STARTING_ID_VALUE;


void cMeshObject::setDiffuseColour(glm::vec3 newDiffuse)
{
	this->materialDiffuse = glm::vec4(newDiffuse, this->materialDiffuse.a);
	return;
}

void cMeshObject::setAlphaTransparency(float newAlpha)
{
	this->materialDiffuse.a = newAlpha;
	return;
}

void cMeshObject::setSpecularColour(glm::vec3 colourRGB)
{
	this->materialSpecular = glm::vec4(colourRGB, this->materialSpecular.a);
	return;
}

void cMeshObject::setSpecularPower(float specPower)
{
	this->materialSpecular.a = specPower;
	return;
}
