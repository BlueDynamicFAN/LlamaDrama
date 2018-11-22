/**
	Main.cpp
	Purpose: Starting point of the program
	@author: BlueDynamic
	@version: 1.0.0
*/
#include "global.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "cShaderManager.h"
#include "cMeshObject.h"
#include "cVAOMeshManager.h"
#include "./Enemies/cEnemyFactory.h"
#include "./Enemies/cFinalBoss.h"
#include "cLightHelper.h"

#include <fmod/fmod.hpp>

//FMOD Globals
FMOD_RESULT _result = FMOD_OK;
FMOD::System *_system = NULL;
FMOD::Sound *_sound = NULL;
FMOD::Channel *_channel = NULL;

unsigned int SelectedModel = 0;
std::vector< cMeshObject* > vec_pObjectsToDraw;
std::vector< std::string > vec_ModelFileNames;

glm::vec3 g_lightPos = glm::vec3(4.0f, 4.0f, 0.0f);
float g_lightBrightness = 6.0f;

unsigned int numberOfObjectsToDraw = 0;

glm::vec3 g_CameraEye;
glm::vec3 g_CameraAt;

cMeshObject* pRogerRabbit = NULL;

cShaderManager* pTheShaderManager = NULL;
cVAOMeshManager* g_pTheVAOMeshManager = NULL;
cBasicTextureManager* g_pTheTextureManager = NULL;
cLightManager* pLightManager = NULL;

// Loads the models we are drawing into the vector
void LoadModelsIntoScene(void);
//Delete models objects
void deleteModels();

/**
	Displays an error message

	@param: error number and the description
	@return: void
*/
static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(void)
{
	GLFWwindow* window;
	pLightManager = new cLightManager();
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(1600, 900, "Llama Drama", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	// Create the shader manager...
	pTheShaderManager = new cShaderManager();
	pTheShaderManager->setBasePath("assets/shaders/");

	cShaderManager::cShader vertexShader;
	cShaderManager::cShader fragmentShader;

	vertexShader.fileName = "vertex01.glsl";
	vertexShader.shaderType = cShaderManager::cShader::VERTEX_SHADER;

	fragmentShader.fileName = "fragment.glsl";
	fragmentShader.shaderType = cShaderManager::cShader::FRAGMENT_SHADER;

	if (pTheShaderManager->createProgramFromFile("myShader",
		vertexShader,
		fragmentShader))
	{
		std::cout << "Compiled shaders OK." << std::endl;
	}
	else
	{
		std::cout << "OH NO! Compile error" << std::endl;
		std::cout << pTheShaderManager->getLastError() << std::endl;
	}

	// Load the uniform location values (some of them, anyway)
	cShaderManager::cShaderProgram* pSP = ::pTheShaderManager->pGetShaderProgramFromFriendlyName("myShader");
	pSP->LoadUniformLocation("texture00");
	pSP->LoadUniformLocation("texture01");
	pSP->LoadUniformLocation("texture02");
	pSP->LoadUniformLocation("texture03");
	pSP->LoadUniformLocation("texture04");
	pSP->LoadUniformLocation("texture05");
	pSP->LoadUniformLocation("texture06");
	pSP->LoadUniformLocation("texture07");
	pSP->LoadUniformLocation("texBlendWeights[0]");
	pSP->LoadUniformLocation("texBlendWeights[1]");

	// Create the texture manager
	::g_pTheTextureManager = new cBasicTextureManager();

	GLuint program = pTheShaderManager->getIDFromFriendlyName("myShader");

	pLightManager->setLights(program, "lights1.json");
	loadAllMeshes(program);

	// Loading models was moved into this function
	LoadModelsIntoScene();

	// Loading the uniform variables here (rather than the inner draw loop)
	GLint objectColour_UniLoc = glGetUniformLocation(program, "objectColour");
	
	GLint matModel_location = glGetUniformLocation(program, "matModel");
	GLint matView_location = glGetUniformLocation(program, "matView");
	GLint matProj_location = glGetUniformLocation(program, "matProj");

	GLint eyeLocation_location = glGetUniformLocation(program, "eyeLocation");

	//Init FMOD
	assert(init_fmod());

	// Draw the "scene" (run the program)
	while (!glfwWindowShouldClose(window))
	{
		// Set the window title for the camera location
		std::stringstream ssTitle;
		ssTitle << "Model Selected: "
			<< ::vec_pObjectsToDraw[SelectedModel]->m_friendlyName;

		glfwSetWindowTitle(window, ssTitle.str().c_str());

		float ratio;
		int width, height;

		glm::mat4x4 matProjection = glm::mat4(1.0f);
		glm::mat4x4	matView = glm::mat4(1.0f);

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);

		glEnable(GL_DEPTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		// Colour and depth buffers are TWO DIFF THINGS.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		matProjection = glm::perspective(0.6f, ratio, 0.1f, 1000.0f);

		g_CameraEye = glm::vec3(thePlayer->getPosition().x, thePlayer->getPosition().y, thePlayer->getPosition().z + 15.0f);
		g_CameraAt = glm::vec3(thePlayer->getPosition());

		// Camera eye, at origin, looking up
		matView = glm::lookAt(g_CameraEye, g_CameraAt, glm::vec3(0.0f, 5.0f, 0.0f));

		//glUniformMatrix4fv(matMoldel_location, 1, GL_FALSE, glm::value_ptr(m));
		glUniform3f(eyeLocation_location, ::g_CameraEye.x, ::g_CameraEye.y, ::g_CameraEye.z);
		glUniformMatrix4fv(matView_location, 1, GL_FALSE, glm::value_ptr(matView));
		glUniformMatrix4fv(matProj_location, 1, GL_FALSE, glm::value_ptr(matProjection));

		double lastTime = glfwGetTime();

		pLightManager->setLights(program, "lights1.json");
		// Draw all the objects in the "scene"
		for (unsigned int objIndex = 0; objIndex != (unsigned int)vec_pObjectsToDraw.size(); objIndex++)
		{
			glm::mat4x4 matModel = glm::mat4(1.0f);
			cMeshObject* pCurrentMesh = vec_pObjectsToDraw[objIndex];
			DrawObject(pCurrentMesh, matModel, program);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//Update physics
		gravityUpdate(deltaTime);

		for (cMeshObject* pPickup : vec_pObjectsToDraw)
		{
			if (pPickup->m_meshName == "coin.ply" || pPickup->m_meshName == "health.ply")
			{
				sModelDrawInfo playerMesh;
				playerMesh.meshFileName = "Llama.ply";
				::g_pTheVAOMeshManager->FindDrawInfoByModelName(playerMesh);

				// Change the terrain mesh (in the GPU)
				::g_pTheVAOMeshManager->UpdateModelVertexInformation(playerMesh);

				std::vector<sClosestPointData> vecClosestPointsRing;
				CalculateClosestPointsOnMesh(playerMesh, pPickup->m_position, vecClosestPointsRing);

				// Find the "closest triangle"
				// Go through each point and compare, finding the closest
				// (What if you have more than one that's the same distance?)
				// Assume the 1st one is the closet one.
				if (vecClosestPointsRing.size() != 0)
				{
					float minDistance = glm::distance(pPickup->m_position, vecClosestPointsRing[0].thePoint);
					unsigned int minTriangleIndex = vecClosestPointsRing[0].triangleIndex;

					for (unsigned int triIndex = 0; triIndex != vecClosestPointsRing.size(); triIndex++)
					{

						// glm::length() seems to work here, too 
						float curDist = glm::distance(pPickup->m_position, vecClosestPointsRing[triIndex].thePoint);

						if (curDist < minDistance)
						{
							minDistance = curDist;
							minTriangleIndex = vecClosestPointsRing[triIndex].triangleIndex;
						}
					}

					sTriangle* pTri = new sTriangle();
					// This is the "phsyics object" for this triangle
					// This is "model space"
					pTri->v[0] = glm::vec3(playerMesh.pVerticesFromFile[playerMesh.pTriangles[minTriangleIndex].vertex_index_1].x, playerMesh.pVerticesFromFile[playerMesh.pTriangles[minTriangleIndex].vertex_index_1].y, playerMesh.pVerticesFromFile[playerMesh.pTriangles[minTriangleIndex].vertex_index_1].z);
					pTri->v[1] = glm::vec3(playerMesh.pVerticesFromFile[playerMesh.pTriangles[minTriangleIndex].vertex_index_2].x, playerMesh.pVerticesFromFile[playerMesh.pTriangles[minTriangleIndex].vertex_index_2].y, playerMesh.pVerticesFromFile[playerMesh.pTriangles[minTriangleIndex].vertex_index_2].z);
					pTri->v[2] = glm::vec3(playerMesh.pVerticesFromFile[playerMesh.pTriangles[minTriangleIndex].vertex_index_3].x, playerMesh.pVerticesFromFile[playerMesh.pTriangles[minTriangleIndex].vertex_index_3].y, playerMesh.pVerticesFromFile[playerMesh.pTriangles[minTriangleIndex].vertex_index_3].z);

					vec_pObjectsToDraw[0]->pTheShape = pTri;
					vec_pObjectsToDraw[0]->shapeType = cMeshObject::TRIANGLE;

				}//if ( vecClosestPoints.size() != 0 )

				collisionDetection(pPickup);
			}
		}

		ProcessAsynKeys(window, deltaTime);

	}//while (!glfwWindowShouldClose(window))

	// Delete stuff
	delete pTheShaderManager;
	delete ::g_pTheVAOMeshManager;
	void deleteModels();
	delete pLightManager;

	//Shut down FMOD
	assert(shutdown_fmod());

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

/**
	Finds an object by their "friendly name"

	@param: the name to find
	@return: the object with that name
*/
cMeshObject* findObjectByFriendlyName(std::string theNameToFind)
{
	for (unsigned int index = 0; index != vec_pObjectsToDraw.size(); index++)
	{
		// Is this it? 
		if (vec_pObjectsToDraw[index]->m_friendlyName == theNameToFind)
		{
			return vec_pObjectsToDraw[index];
		}
	}
	// Didn't find it.
	return NULL;	// 0 or nullptr
}

/*
	Initializes FMOD

*/
bool init_fmod() {

	//Create the main system object
	_result = FMOD::System_Create(&_system);
	//TODO: CHECK FOR FMOD ERRORS, IMPLEMENT YOUR OWN FUNCTION
	assert(!_result);
	//Initializes the system object, and the msound device. This has to be called at the start of the user's program
	_result = _system->init(512, FMOD_INIT_NORMAL, NULL);
	assert(!_result);


	return true;
}

/*
	Safely shuts down FMOD
	
*/
bool shutdown_fmod() {

	if (_sound) {
		_result = _sound->release();
		assert(!_result);
	}
	if (_system) {
		_result = _system->close();
		assert(!_result);
		_result = _system->release();
		assert(!_result);
	}

	return true;
}