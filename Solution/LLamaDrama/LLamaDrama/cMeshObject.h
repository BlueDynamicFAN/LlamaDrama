/**
	cMeshObject.cpp
	Purpose: Contains the information for a model
	@author: BlueDynamic
	@version: 1.0.0
*/
#ifndef _cMeshObject_HG_
#define _cMeshObject_HG_

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <vector>

class cMeshObject
{
public:
	cMeshObject();

	glm::vec3 m_preRotation;		// Happens BEFORE translation (move)
	glm::vec3 m_position;
	glm::vec3 m_postRotation;		// Happens AFTER translation (move)
	glm::vec3 m_nonUniformScale;
	std::string m_meshName;		// Model to draw
	std::string m_friendlyName;
	glm::vec3 m_objColour;

	bool m_bIsWireFrame;
	bool m_bIsVisible;

	// Child objects inside this one
	std::vector< cMeshObject* > m_vec_pChildObjectsToDraw;

	inline unsigned int getUniqueID(void)
	{
		return this->m_uniqueID;
	}

private:
	unsigned int m_uniqueID;			// Number that's unique to this instance
	static unsigned int m_NextID; 	    // Can't assign as is static

	static const unsigned int STARTING_ID_VALUE = 1000;
};

#endif 
