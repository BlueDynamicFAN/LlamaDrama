/**
	cVAOMeshManager.cpp
	Purpose: Takes cMeshObject and loads it into the VAO (cVAOMeshManager taken from Feeney's graphics class)
	@author: Michael Feeney
	@version: 1.0.0
*/
#include "global.h"

#include "cVAOMeshManager.h"

#include <fstream>
#include <string>
#include <iostream> 
#include <sstream>

cVAOMeshManager::cVAOMeshManager()		// constructor
{
	return;
}

cVAOMeshManager::~cVAOMeshManager()		// destructor
{
	// Will call ShutDown();
	return;
}

// Note: the shader program ID is needed to tie the buffer to the vertex layout of the shader
bool cVAOMeshManager::LoadModelIntoVAO(
	sModelDrawInfo &drawInfo,
	unsigned int shaderProgramID)
{
	// See if this model has already been loaded
	std::map< std::string, sModelDrawInfo >::iterator itModel = this->m_mapModel_to_VAOID.find(drawInfo.meshFileName);

	if (itModel != this->m_mapModel_to_VAOID.end())
	{
		this->m_AppendTextToLastError("Model ", false);
		this->m_AppendTextToLastError(drawInfo.meshFileName, false);
		this->m_AppendTextToLastError(" was already loaded.");
		return false;
	}

	// Load the model from the file
	if (!this->m_LoadModelFromFile(drawInfo))
	{
		return false;
	}

	// Load the model data into the GPU
	//LoadMeshIntoGPUBuffer
	if (!this->m_LoadDrawInfo_Into_VAO(drawInfo, shaderProgramID))
	{
		// Add some error text
		return false;
	}

	// Store this mesh into the map
	this->m_mapModel_to_VAOID[drawInfo.meshFileName] = drawInfo;

	return true;
}

// Looks up draw info by name (meshFileName)			
bool cVAOMeshManager::FindDrawInfoByModelName(sModelDrawInfo &drawInfo)
{
	std::map< std::string /*model name*/, sModelDrawInfo >::iterator itModel = this->m_mapModel_to_VAOID.find(drawInfo.meshFileName);

	if (itModel == this->m_mapModel_to_VAOID.end())
	{
		// Didn't find model
		return false;
	}

	// Copy the draw info back to the caller.
	drawInfo = itModel->second;

	return true;
}

bool cVAOMeshManager::m_LoadModelFromFile(sModelDrawInfo &drawInfo)
{
	// Open the file that you asked.
	std::ifstream theFile(drawInfo.meshFileName.c_str());

	if (!theFile.is_open())			// More "c" or "C++" ish
	{
		this->m_AppendTextToLastError("Didn't load the ", false);
		this->m_AppendTextToLastError(drawInfo.meshFileName, false);
		this->m_AppendTextToLastError(" file.");
		return false;
	}//if (!theFile.is_open() 

	// file is open OK
	std::string nextData;
	while (theFile >> nextData)
	{
		if (nextData == "vertex")
		{
			break;		// exit while loop...
		}
	};

	theFile >> drawInfo.numberOfVertices;

	std::cout << "vertices: " << drawInfo.numberOfVertices << std::endl;

	// seach for "face"
	while (theFile >> nextData)
	{
		if (nextData == "face")
		{
			break;		// exit while loop...
		}
	};

	theFile >> drawInfo.numberOfTriangles;

	std::cout << "triangles: " << drawInfo.numberOfTriangles << std::endl;

	while (theFile >> nextData)
	{
		if (nextData == "end_header")
		{
			break;		// exit while loop...
		}
	};

	drawInfo.pVerticesFromFile = new sPlyVertex[drawInfo.numberOfVertices];

	//	ZeroMemory(); win32
	// C call... (clears memory to all zeros)
	memset(drawInfo.pVerticesFromFile, 0, sizeof(sPlyVertex) * drawInfo.numberOfVertices);

	// Read the vertex data into the array
	for (unsigned int index = 0; index != drawInfo.numberOfVertices; index++)
	{
		theFile >> drawInfo.pVerticesFromFile[index].x;
		theFile >> drawInfo.pVerticesFromFile[index].y;
		theFile >> drawInfo.pVerticesFromFile[index].z;
	}

	// Same with triangles
	drawInfo.pTriangles = new sPlyTriangle[drawInfo.numberOfTriangles];

	memset(drawInfo.pTriangles, 0, sizeof(sPlyTriangle) * drawInfo.numberOfTriangles);

	int TossThisAway = 0;
	for (unsigned int index = 0; index != drawInfo.numberOfTriangles; index++)
	{
		theFile >> TossThisAway;
		theFile >> drawInfo.pTriangles[index].vertex_index_1;
		theFile >> drawInfo.pTriangles[index].vertex_index_2;
		theFile >> drawInfo.pTriangles[index].vertex_index_3;
	}

	std::cout << "Read from the file OK." << std::endl;

	// Assume the 1st one is the largest and smallest:
	drawInfo.minX = drawInfo.pVerticesFromFile[0].x;
	drawInfo.minY = drawInfo.pVerticesFromFile[0].y;
	drawInfo.minZ = drawInfo.pVerticesFromFile[0].z;

	drawInfo.maxX = drawInfo.pVerticesFromFile[0].x;
	drawInfo.maxY = drawInfo.pVerticesFromFile[0].y;
	drawInfo.maxZ = drawInfo.pVerticesFromFile[0].z;

	for (unsigned int index = 0; index != drawInfo.numberOfVertices; index++)
	{
		if (drawInfo.pVerticesFromFile[index].x < drawInfo.minX) { drawInfo.minX = drawInfo.pVerticesFromFile[index].x; }
		if (drawInfo.pVerticesFromFile[index].y < drawInfo.minY) { drawInfo.minY = drawInfo.pVerticesFromFile[index].y; }
		if (drawInfo.pVerticesFromFile[index].z < drawInfo.minZ) { drawInfo.minZ = drawInfo.pVerticesFromFile[index].z; }

		if (drawInfo.pVerticesFromFile[index].x > drawInfo.maxX) { drawInfo.maxX = drawInfo.pVerticesFromFile[index].x; }
		if (drawInfo.pVerticesFromFile[index].y > drawInfo.maxY) { drawInfo.maxY = drawInfo.pVerticesFromFile[index].y; }
		if (drawInfo.pVerticesFromFile[index].z > drawInfo.maxZ) { drawInfo.maxZ = drawInfo.pVerticesFromFile[index].z; }
	}//for ( unsigned int index...

	// Calculating extents...
	drawInfo.extentX = drawInfo.maxX - drawInfo.minX;
	drawInfo.extentY = drawInfo.maxY - drawInfo.minY;
	drawInfo.extentZ = drawInfo.maxZ - drawInfo.minZ;

	drawInfo.maxExtent = drawInfo.extentX;
	if (drawInfo.maxExtent < drawInfo.extentY) { drawInfo.maxExtent = drawInfo.extentY; }
	if (drawInfo.maxExtent < drawInfo.extentZ) { drawInfo.maxExtent = drawInfo.extentZ; }

	return true;
}

bool cVAOMeshManager::m_LoadDrawInfo_Into_VAO(
	sModelDrawInfo &drawInfo,
	unsigned int shaderProgramID)
{
	//sVert_xyz_rgb* pVertices = new sVert_xyz_rgb[g_numberOfVertices];
	drawInfo.pVerticesToVBO = new sVert_xyz_rgb[drawInfo.numberOfVertices];

	// Copy the data from the PLY format to the vertex buffer format
	for (unsigned int index = 0; index != drawInfo.numberOfVertices; index++)
	{
		drawInfo.pVerticesToVBO[index].x = drawInfo.pVerticesFromFile[index].x;
		drawInfo.pVerticesToVBO[index].y = drawInfo.pVerticesFromFile[index].y;
		drawInfo.pVerticesToVBO[index].z = drawInfo.pVerticesFromFile[index].z;

		// Set all the colours to white (1,1,1) for now
		drawInfo.pVerticesToVBO[index].r = 1.0f;
		drawInfo.pVerticesToVBO[index].g = 1.0f;
		drawInfo.pVerticesToVBO[index].b = 1.0f;
	}

	// Creates a VAO (Vertex Array Object)
	glGenVertexArrays(1, &(drawInfo.VAO_ID));
	glBindVertexArray(drawInfo.VAO_ID);


	// Allocate a buffer and copy

	// Just to confuse you, this is called VBO (Vertex Buffer Object)
	// NOTE: OpenGL error checks have been omitted for brevity
	glGenBuffers(1, &(drawInfo.vertexBufferID));
	// "Vertex" buffer
	// - Sets the "type" of buffer
	// - Makes it the 'current' buffer
	glBindBuffer(GL_ARRAY_BUFFER, drawInfo.vertexBufferID);

	unsigned int vertexBufferSizeInBytes =
		sizeof(sVert_xyz_rgb) * drawInfo.numberOfVertices;

	glBufferData(GL_ARRAY_BUFFER,
		vertexBufferSizeInBytes,	// sizeof(vertices), 
		drawInfo.pVerticesToVBO,	// vertices, 
		GL_STATIC_DRAW);

	// Three indices (of vertices) per triangle
	drawInfo.numberOfIndices = drawInfo.numberOfTriangles * 3;
	drawInfo.pIndices = new unsigned int[drawInfo.numberOfIndices];
	memset(drawInfo.pIndices, 0, sizeof(unsigned int) * drawInfo.numberOfIndices);

	// Load the index buffer...
	unsigned int indexIndex = 0;
	for (unsigned int triIndex = 0; triIndex != drawInfo.numberOfTriangles;
		triIndex++, indexIndex += 3)
	{
		drawInfo.pIndices[indexIndex + 0] = drawInfo.pTriangles[triIndex].vertex_index_1;
		drawInfo.pIndices[indexIndex + 1] = drawInfo.pTriangles[triIndex].vertex_index_2;
		drawInfo.pIndices[indexIndex + 2] = drawInfo.pTriangles[triIndex].vertex_index_3;
	}

	glGenBuffers(1, &(drawInfo.indexBufferID));			// vertex_buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawInfo.indexBufferID);

	unsigned int indexBufferSizeInBytes = sizeof(unsigned int) * drawInfo.numberOfIndices;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indexBufferSizeInBytes,	// sizeof(vertices), 
		drawInfo.pIndices,			// vertices, 
		GL_STATIC_DRAW);

	GLint vpos_location = glGetAttribLocation(shaderProgramID, "vPosition");
	GLint vcol_location = glGetAttribLocation(shaderProgramID, "vColour");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location,	// "vPosition"
		3,				//  vec3 (xyz)
		GL_FLOAT,
		GL_FALSE,		// DON'T "normalize"
		sizeof(float) * 6,
		(void*)0);

	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location,		// cColour
		3,					// vec3 (rgb)
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 6,
		(void*)(sizeof(float) * 3));

	// Set the "current" VAO to nothing.
	glBindVertexArray(0);

	return true;
}

void cVAOMeshManager::m_AppendTextToLastError(std::string text, bool addNewLineBefore /*=true*/)
{
	std::stringstream ssError;
	ssError.str() = this->m_lastErrorString;

	if (addNewLineBefore)
	{
		ssError << std::endl;
	}
	ssError << text;

	this->m_lastErrorString = ssError.str();

	return;
}

std::string cVAOMeshManager::GetLastError(bool bAndClear /*=true*/)
{
	std::string errorText = this->m_lastErrorString;
	if (bAndClear)
	{
		this->m_lastErrorString = "";
	}
	return errorText;
}

void cVAOMeshManager::ShutDown(void)
{

	// TODO: Clear the map

	return;
}


