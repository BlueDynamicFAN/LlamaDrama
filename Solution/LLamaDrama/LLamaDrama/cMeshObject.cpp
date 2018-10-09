/**
	cMeshObject.cpp
	Purpose: Contains all information for cMeshObject
	@author: BlueDynamic
	@version: 1.0.0
*/
#include "cMeshObject.h"

cMeshObject::cMeshObject()
{
	this->preRotation = glm::vec3(0.0f);
	this->position = glm::vec3(0.0f);
	this->postRotation = glm::vec3(0.0f);
	this->nonUniformScale = glm::vec3(1.0f);
	this->bIsVisible = true;
	this->bIsWireFrame = false;

	// Set unique ID
	this->m_uniqueID = cMeshObject::m_NextID;
	// Increment
	cMeshObject::m_NextID++;	

	return;
}

//static 
unsigned int cMeshObject::m_NextID = cMeshObject::STARTING_ID_VALUE;
