#ifndef _global_HG_
#define _global_HG_
// global.h 

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
#include "Player.h"
#include "./Enemies/cEnemy.h"
#include "Platform.h"

extern glm::vec3 g_CameraEye;	// = glm::vec3( 0.0, 0.0, +10.0f );
extern glm::vec3 g_CameraAt;	// = glm::vec3( 0.0, 0.0, 0.0f );

// NOTE: These are JUST FOR NOW!!!
extern glm::vec3 g_lightPos;	// = glm::vec3( 4.0f, 4.0f, 0.0f );
extern float g_lightBrightness;	// = 1.0f;

// Signature for the ply loader function
bool LoadPlyFileData(std::string fileName);

// GFLW keyboard callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//void ProcessAsynKeys(GLFWwindow* window);
void ProcessAsynKeys(GLFWwindow* window, double deltaTime);

cMeshObject* findObjectByFriendlyName(std::string theNameToFind);
cMeshObject* findObjectByUniqueID(unsigned int IDToFind);

// This is part of the physics stuff
//void CalculateClosestPointsOnMesh(sModelDrawInfo theMeshDrawInfo,
//	glm::vec3 pointToTest,
//	std::vector<glm::vec3> &vecPoints);

// function 
void DrawObject(cMeshObject* pCurrentMesh,
	glm::mat4x4 &matModel,
	GLuint shaderProgramID);

extern cVAOMeshManager* g_pTheVAOMeshManager;

// Vector of Models loaded
extern unsigned int SelectedModel;
extern std::vector< cMeshObject* > vec_pObjectsToDraw;
extern std::vector< std::string > vec_ModelFileNames;

static const float PI = 3.14159f;


//Keeping distance to not cause a git merge conflict
void loadEnemiesFromJson();
void loadPlatformsFromJson();
void loadPlayerFromJson();
void loadAllMeshes(GLuint program);
extern Player* thePlayer;
extern std::vector <cEnemy*> pEnemies;
extern std::vector <Platform*> pPlatforms;
void gravityUpdate(double deltaTime);
void movingsUpdate(double deltaTime);
bool isPlayerOnTopOfPlatfrom();


#endif	// _globalStuff_HG_
