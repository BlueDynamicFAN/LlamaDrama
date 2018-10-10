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

	// Set unique ID
	this->m_uniqueID = cMeshObject::m_NextID;
	// Increment
	cMeshObject::m_NextID++;

	return;
}

//static 
unsigned int cMeshObject::m_NextID = cMeshObject::STARTING_ID_VALUE;
