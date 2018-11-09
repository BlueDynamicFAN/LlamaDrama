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

struct sSphere
{
	sSphere(float theRadius)
	{
		this->radius = theRadius;
	}
	float radius;
};

struct sTriangle
{
	glm::vec3 v[3];
};

struct sTextureInfo
{
	std::string name;
	int cachedTextureID; 	// Set to -1 by default
	float strength;		// Set to 0.0f by default
};

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

	bool bUseVertexColour;
	bool m_bIsWireFrame;
	bool m_bIsVisible;
	bool bDontLight;

	// Child objects inside this one
	std::vector< cMeshObject* > m_vec_pChildObjectsToDraw;
	std::vector<sTextureInfo> vecTextures;

	glm::vec4 materialDiffuse;		// RGB+Alpha
	void setDiffuseColour(glm::vec3 newDiffuse);
	void setAlphaTransparency(float newAlpha);
	glm::vec4 materialSpecular;		// RGB+specular power
	void setSpecularColour(glm::vec3 colourRGB);
	void setSpecularPower(float specPower);

	enum eShape
	{
		UNKNOWN_SHAPE,
		SPHERE,
		TRIANGLE
	};

	// Allows me to point to anything (any type)
	void* pTheShape;		// Details
	eShape shapeType;		// What shape it is

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
