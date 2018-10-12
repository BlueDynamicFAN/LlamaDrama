/**
	global.cpp
	Purpose: Contains the information that needs to be accessed in other files
	@author: BlueDynamic
	@version: 1.0.0
*/
#ifndef _global_HG_
#define _global_HG_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <string>
#include <vector>

#include "sPlyVertex.h"
#include "sPlyTriangle.h"
#include "cMeshObject.h"
#include "sModelDrawInfo.h"
#include "cVAOMeshManager.h"
#include "cPlayer.h"
#include "./Enemies/cEnemy.h"
#include "cPlatform.h"

static const float PI = 3.14159f;

extern glm::vec3 g_CameraEye;
extern glm::vec3 g_CameraAt;

// NOTE: These are JUST FOR NOW!!!
extern glm::vec3 g_lightPos;	
extern float g_lightBrightness;	

// Vector of Models loaded
extern unsigned int SelectedModel;
extern std::vector< cMeshObject* > vec_pObjectsToDraw;
extern std::vector< std::string > vec_ModelFileNames;

//Game entites
extern cPlayer* thePlayer;
extern std::vector <cEnemy*> pEnemies;
extern std::vector <cPlatform*> pPlatforms;

//Meshes
extern cVAOMeshManager* g_pTheVAOMeshManager;
cMeshObject* findObjectByFriendlyName(std::string theNameToFind);
void DrawObject(cMeshObject* pCurrentMesh,
	glm::mat4x4 &matModel,
	GLuint shaderProgramID);

// GFLW keyboard callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//void ProcessAsynKeys(GLFWwindow* window);
void ProcessAsynKeys(GLFWwindow* window, double deltaTime);

//JASON
void loadEnemiesFromJson();
void loadPlatformsFromJson();
void loadPlayerFromJson();
void loadAllMeshes(GLuint program);

//Physics
void gravityUpdate(double deltaTime);
void movesUpdate(double deltaTime);
bool isPlayerOnTopOfAPlatform();

#endif	// _globalStuff_HG_
