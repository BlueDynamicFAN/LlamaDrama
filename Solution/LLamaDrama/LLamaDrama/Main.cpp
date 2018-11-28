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

#include <fmod.hpp>


#define NUM_OF_SOUNDS 10
#define NUM_OF_CHANNELS 10

//FMOD Globals
FMOD_RESULT _result = FMOD_OK;
FMOD::System *_system;
FMOD::Sound* soundArray[NUM_OF_SOUNDS];
FMOD::Channel* channelArray[NUM_OF_CHANNELS];
const char* fileNameArray[NUM_OF_SOUNDS];
bool isJump = false;
bool coinGot = false;

//THRIFT
extern LeaderboardClient* client;

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
bool init_fmod();
bool shutdown_fmod();

// Loads the models we are drawing into the vector
void LoadModelsIntoScene(void);
//Delete models objects
void deleteModels();

//THRIFT 
void connectToLeaderBoard();

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
	//Init FMOD
	init_fmod();

	GLFWwindow* window;
	pLightManager = new cLightManager();
	glfwSetErrorCallback(error_callback);
	connectToLeaderBoard();

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

	// Load sounds from .txt file
	LoadSoundsFromFile();

	// Play background music
	_result = _system->playSound(soundArray[0], 0, false, &channelArray[0]);
	std::cout << CheckFmodResult(_result) << std::endl;

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

		// Jump sound
		if (isJump)
		{
			_result = _system->playSound(soundArray[1], 0, false, &channelArray[1]);
			isJump = false;
		}

		// Coin sound
		if (coinGot)
		{
			_result = _system->playSound(soundArray[2], 0, false, &channelArray[2]);
			coinGot = false;
		}

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

	int newScore = dao.setHighScore(thePlayer->getId(), thePlayer->getPlayerScore());
	client->setHighScore(thePlayer->getId(), newScore);

	client->setHighScore(1, thePlayer->getPlayerScore());
	client->getTop20(top20);

	std::map<int32_t, int32_t>::iterator it;
	std::cout << "[PlayerID][Score]:" << std::endl;
	for (it = top20.begin(); it != top20.end(); it++) {
		std::cout << "[ "<<it->first << " ][ " << it->second << " ]"<<std::endl;
	}


	// Delete stuff
	delete pTheShaderManager;
	delete ::g_pTheVAOMeshManager;
	void deleteModels();
	delete pLightManager;

	//Shut down FMOD
	shutdown_fmod();

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
	std::cout << CheckFmodResult(_result) << std::endl;
	//Initializes the system object, and the msound device. This has to be called at the start of the user's program
	_result = _system->init(512, FMOD_INIT_NORMAL, NULL);
	std::cout << CheckFmodResult(_result) << std::endl;

	return true;
}

/*
	Safely shuts down FMOD

*/
bool shutdown_fmod() {

	for (unsigned int i = 0; i < NUM_OF_SOUNDS; i++)
	{
		if (soundArray[i]) {
			_result = soundArray[i]->release();
			std::cout << CheckFmodResult(_result) << std::endl;
		}
	}

	if (_system) {
		_result = _system->close();
		std::cout << CheckFmodResult(_result) << std::endl;
		_result = _system->release();
		std::cout << CheckFmodResult(_result) << std::endl;
	}

	return true;
}

//Load mp3 files from a text file so that they can be changed without the need to recompile.
void LoadSoundsFromFile()
{
	std::ifstream myfile("soundFiles.txt");

	if (myfile.is_open())
	{
		std::string path_start = "assets/SoundFiles/";
		std::string file_path;
		const char* full_path;
		unsigned int index = 0;

		for (std::string line; getline(myfile, line); )
		{
			// Get full file name
			file_path = "";
			file_path += path_start;
			file_path += line;

			// Convert to char*
			full_path = file_path.c_str();

			// Slap into fileNameArray
			fileNameArray[index] = full_path;

			// Turn it into a sound and put that into soundArray
			_result = _system->createSound(fileNameArray[index], FMOD_DEFAULT, 0, &soundArray[index]);
			std::cout << CheckFmodResult(_result) << std::endl;

			// Increment index
			index++;
		}
		myfile.close();
	}
	else
		std::cout << "Can't open .MP3 file" << std::endl;
}

std::string CheckFmodResult(int result)
{
	std::string res = "";

	switch (result)
	{
	case FMOD_OK:
		res = "FMOD_OK";
		break;
	case FMOD_ERR_BADCOMMAND:
		res = "FMOD_ERR_BADCOMMAND";
		break;
	case FMOD_ERR_CHANNEL_ALLOC:
		res = "FMOD_ERR_CHANNEL_ALLOC";
		break;
	case FMOD_ERR_CHANNEL_STOLEN:
		res = "FMOD_ERR_CHANNEL_STOLEN";
		break;
	case FMOD_ERR_DMA:
		res = "FMOD_ERR_DMA";
		break;
	case FMOD_ERR_DSP_CONNECTION:
		res = "FMOD_ERR_DSP_CONNECTION";
		break;
	case FMOD_ERR_DSP_DONTPROCESS:
		res = "FMOD_ERR_DSP_DONTPROCESS";
		break;
	case FMOD_ERR_DSP_FORMAT:
		res = "FMOD_ERR_DSP_FORMAT";
		break;
	case FMOD_ERR_DSP_INUSE:
		res = "FMOD_ERR_DSP_INUSE";
		break;
	case FMOD_ERR_DSP_NOTFOUND:
		res = "FMOD_ERR_DSP_NOTFOUND";
		break;
	case FMOD_ERR_DSP_RESERVED:
		res = "FMOD_ERR_DSP_RESERVED";
		break;
	case FMOD_ERR_DSP_SILENCE:
		res = "FMOD_ERR_DSP_SILENCE";
		break;
	case FMOD_ERR_DSP_TYPE:
		res = "FMOD_ERR_DSP_TYPE";
		break;
	case FMOD_ERR_FILE_BAD:
		res = "FMOD_ERR_FILE_BAD";
		break;
	case FMOD_ERR_FILE_COULDNOTSEEK:
		res = "FMOD_ERR_FILE_COULDNOTSEEK";
		break;
	case FMOD_ERR_FILE_DISKEJECTED:
		res = "FMOD_ERR_FILE_DISKEJECTED";
		break;
	case FMOD_ERR_FILE_EOF:
		res = "FMOD_ERR_FILE_EOF";
		break;
	case FMOD_ERR_FILE_ENDOFDATA:
		res = "FMOD_ERR_FILE_ENDOFDATA";
		break;
	case FMOD_ERR_FILE_NOTFOUND:
		res = "FMOD_ERR_FILE_NOTFOUND";
		break;
	case FMOD_ERR_FORMAT:
		res = "FMOD_ERR_FORMAT";
		break;
	case FMOD_ERR_HEADER_MISMATCH:
		res = "FMOD_ERR_HEADER_MISMATCH";
		break;
	case FMOD_ERR_HTTP:
		res = "FMOD_ERR_HTTP";
		break;
	case FMOD_ERR_HTTP_ACCESS:
		res = "FMOD_ERR_HTTP_ACCESS";
		break;
	case FMOD_ERR_HTTP_PROXY_AUTH:
		res = "FMOD_ERR_HTTP_PROXY_AUTH";
		break;
	case FMOD_ERR_HTTP_SERVER_ERROR:
		res = "FMOD_ERR_HTTP_SERVER_ERROR";
		break;
	case FMOD_ERR_HTTP_TIMEOUT:
		res = "FMOD_ERR_HTTP_TIMEOUT";
		break;
	case FMOD_ERR_INITIALIZATION:
		res = "FMOD_ERR_INITIALIZATION";
		break;
	case FMOD_ERR_INITIALIZED:
		res = "FMOD_ERR_INITIALIZED";
		break;
	case FMOD_ERR_INTERNAL:
		res = "FMOD_ERR_INTERNAL";
		break;
	case FMOD_ERR_INVALID_FLOAT:
		res = "FMOD_ERR_INVALID_FLOAT";
		break;
	case FMOD_ERR_INVALID_HANDLE:
		res = "FMOD_ERR_INVALID_HANDLE";
		break;
	case FMOD_ERR_INVALID_PARAM:
		res = "FMOD_ERR_INVALID_PARAM";
		break;
	case FMOD_ERR_INVALID_POSITION:
		res = "FMOD_ERR_INVALID_POSITION";
		break;
	case FMOD_ERR_INVALID_SPEAKER:
		res = "FMOD_ERR_INVALID_SPEAKER";
		break;
	case FMOD_ERR_INVALID_SYNCPOINT:
		res = "FMOD_ERR_INVALID_SYNCPOINT";
		break;
	case FMOD_ERR_INVALID_THREAD:
		res = "FMOD_ERR_INVALID_THREAD";
		break;
	case FMOD_ERR_INVALID_VECTOR:
		res = "FMOD_ERR_INVALID_VECTOR";
		break;
	case FMOD_ERR_MAXAUDIBLE:
		res = "FMOD_ERR_MAXAUDIBLE";
		break;
	case FMOD_ERR_MEMORY:
		res = "FMOD_ERR_MEMORY";
		break;
	case FMOD_ERR_MEMORY_CANTPOINT:
		res = "FMOD_ERR_MEMORY_CANTPOINT";
		break;
	case FMOD_ERR_NEEDS3D:
		res = "FMOD_ERR_NEEDS3D";
		break;
	case FMOD_ERR_NEEDSHARDWARE:
		res = "FMOD_ERR_NEEDSHARDWARE";
		break;
	case FMOD_ERR_NET_CONNECT:
		res = "FMOD_ERR_NET_CONNECT";
		break;
	case FMOD_ERR_NET_SOCKET_ERROR:
		res = "FMOD_ERR_NET_SOCKET_ERROR";
		break;
	case FMOD_ERR_NET_URL:
		res = "FMOD_ERR_NET_URL";
		break;
	case FMOD_ERR_NET_WOULD_BLOCK:
		res = "FMOD_ERR_NET_WOULD_BLOCK";
		break;
	case FMOD_ERR_NOTREADY:
		res = "FMOD_ERR_NOTREADY";
		break;
	case FMOD_ERR_OUTPUT_ALLOCATED:
		res = "FMOD_ERR_OUTPUT_ALLOCATED";
		break;
	case FMOD_ERR_OUTPUT_CREATEBUFFER:
		res = "FMOD_ERR_OUTPUT_CREATEBUFFER";
		break;
	case FMOD_ERR_OUTPUT_DRIVERCALL:
		res = "FMOD_ERR_OUTPUT_FORMAT";
		break;
	case FMOD_ERR_OUTPUT_FORMAT:
		res = "FMOD_ERR_OUTPUT_FORMAT";
		break;
	case FMOD_ERR_OUTPUT_INIT:
		res = "FMOD_ERR_OUTPUT_INIT";
		break;
	case FMOD_ERR_OUTPUT_NODRIVERS:
		res = "FMOD_ERR_OUTPUT_NODRIVERS";
		break;
	case FMOD_ERR_PLUGIN:
		res = "FMOD_ERR_PLUGIN";
		break;
	case FMOD_ERR_PLUGIN_MISSING:
		res = "FMOD_ERR_PLUGIN_MISSING";
		break;
	case FMOD_ERR_PLUGIN_RESOURCE:
		res = "FMOD_ERR_PLUGIN_RESOURCE";
		break;
	case FMOD_ERR_PLUGIN_VERSION:
		res = "FMOD_ERR_PLUGIN_VERSION";
		break;
	case FMOD_ERR_RECORD:
		res = "FMOD_ERR_RECORD";
		break;
	case FMOD_ERR_REVERB_CHANNELGROUP:
		res = "FMOD_ERR_REVERB_CHANNELGROUP";
		break;
	case FMOD_ERR_REVERB_INSTANCE:
		res = "FMOD_ERR_REVERB_INSTANCE";
		break;
	case FMOD_ERR_SUBSOUNDS:
		res = "FMOD_ERR_SUBSOUNDS";
		break;
	case FMOD_ERR_SUBSOUND_ALLOCATED:
		res = "FMOD_ERR_SUBSOUND_ALLOCATED";
		break;
	case FMOD_ERR_SUBSOUND_CANTMOVE:
		res = "FMOD_ERR_SUBSOUND_CANTMOVE";
		break;
	case FMOD_ERR_TAGNOTFOUND:
		res = "FMOD_ERR_TAGNOTFOUND";
		break;
	case FMOD_ERR_TOOMANYCHANNELS:
		res = "FMOD_ERR_TOOMANYCHANNELS";
		break;
	case FMOD_ERR_TRUNCATED:
		res = "FMOD_ERR_TRUNCATED";
		break;
	case FMOD_ERR_UNIMPLEMENTED:
		res = "FMOD_ERR_UNIMPLEMENTED";
		break;
	case FMOD_ERR_UNINITIALIZED:
		res = "FMOD_ERR_UNINITIALIZED";
		break;
	case FMOD_ERR_UNSUPPORTED:
		res = "FMOD_ERR_UNSUPPORTED";
		break;
	case FMOD_ERR_VERSION:
		res = "FMOD_ERR_VERSION";
		break;
	case FMOD_ERR_EVENT_ALREADY_LOADED:
		res = "FMOD_ERR_EVENT_ALREADY_LOADED";
		break;
	case FMOD_ERR_EVENT_LIVEUPDATE_BUSY:
		res = "FMOD_ERR_EVENT_LIVEUPDATE_BUSY";
		break;
	case FMOD_ERR_EVENT_LIVEUPDATE_MISMATCH:
		res = "FMOD_ERR_EVENT_LIVEUPDATE_MISMATCH";
		break;
	case FMOD_ERR_EVENT_LIVEUPDATE_TIMEOUT:
		res = "FMOD_ERR_EVENT_LIVEUPDATE_TIMEOUT";
		break;
	case FMOD_ERR_EVENT_NOTFOUND:
		res = "FMOD_ERR_EVENT_NOTFOUND";
		break;
	case FMOD_ERR_STUDIO_UNINITIALIZED:
		res = "FMOD_ERR_STUDIO_UNINITIALIZED";
		break;
	case FMOD_ERR_STUDIO_NOT_LOADED:
		res = "FMOD_ERR_STUDIO_NOT_LOADED";
		break;
	case FMOD_ERR_INVALID_STRING:
		res = "FMOD_ERR_INVALID_STRING";
		break;
	case FMOD_ERR_ALREADY_LOCKED:
		res = "FMOD_ERR_ALREADY_LOCKED";
		break;
	case FMOD_ERR_NOT_LOCKED:
		res = "FMOD_ERR_NOT_LOCKED";
		break;
	case FMOD_ERR_RECORD_DISCONNECTED:
		res = "FMOD_ERR_RECORD_DISCONNECTED";
		break;
	case FMOD_ERR_TOOMANYSAMPLES:
		res = "FMOD_ERR_TOOMANYSAMPLES";
		break;
	}

	return res;
}