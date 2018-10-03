#ifndef _sModelDrawInfo_HG_
#define _sModelDrawInfo_HG_

#include <string>
#include "sPlyVertex.h"
#include "sPlyTriangle.h"

// This is very tightly tied to this method
struct sVert_xyz_rgb
{
	sVert_xyz_rgb() :
		x(0.0f), y(0.0f), z(0.0f),
		r(0.0f), g(0.0f), b(0.0f) {};
	float x, y, z;		// vec3    
	float r, g, b;		// vec3 
};

struct sModelDrawInfo
{
	sModelDrawInfo();

	std::string meshFileName;

	unsigned int VAO_ID;					//***

	unsigned int vertexBufferID;
	unsigned int vertexBuffer_start_index;
	unsigned int numberOfVertices;

	unsigned int indexBufferID;
	unsigned int indexBuffer_start_index;
	unsigned int numberOfIndices;			//***
	unsigned int numberOfTriangles;

	// This is the vertex information as read from the file
	sPlyVertex* pVerticesFromFile;	// = 0
	// These are the original triangle values from file,
	//	but in the 'triangle' (or face) format
	sPlyTriangle* pTriangles;	// = 0;

	// This is the vertex information being passed to the GPU
	// (is in format that the shader needs)
	sVert_xyz_rgb* pVerticesToVBO;	// = new sVert_xyz_rgb[ARRAYSIZE]
	// This buffer is indices as a 1D array (that the GPU needs)
	unsigned int* pIndices;		// = new unsigned int[ARRAYSIZE]

	float maxX, maxY, maxZ;
	float minX, minY, minZ;
	float extentX, extentY, extentZ;
	float maxExtent;
};

#endif 
