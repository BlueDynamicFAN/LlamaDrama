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

	glm::vec3 preRotation;		// Happens BEFORE translation (move)
	glm::vec3 position;
	glm::vec3 postRotation;		// Happens AFTER translation (move)
	glm::vec3 nonUniformScale;
	std::string meshName;	// Model to draw
	std::string friendlyName;	
	glm::vec3 objColour;

	bool bIsWireFrame;	//  = true;  C++
	bool bIsVisible;


	// Child objects inside this one
	std::vector< cMeshObject* > vec_pChildObjectsToDraw;


	// In theory, it's faster. 
	// Not likely. Suggestion, not a command
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
