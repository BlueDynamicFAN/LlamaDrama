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

unsigned int SelectedModel = 0;
std::vector< cMeshObject* > vec_pObjectsToDraw;
std::vector< std::string > vec_ModelFileNames;

// To the right, up 4.0 units, along the x axis
glm::vec3 g_lightPos = glm::vec3(4.0f, 4.0f, 0.0f);
float g_lightBrightness = 4.0f;

unsigned int numberOfObjectsToDraw = 0;

glm::vec3 g_CameraEye;
glm::vec3 g_CameraAt;

cMeshObject* pRogerRabbit = NULL;

cShaderManager* pTheShaderManager = NULL;
cVAOMeshManager* g_pTheVAOMeshManager = NULL;

// Loads the models we are drawing into the vector
void LoadModelsIntoScene(void);

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

	fragmentShader.fileName = "fragment01.glsl";
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

	GLuint program = pTheShaderManager->getIDFromFriendlyName("myShader");

	loadAllMeshes(program);

	// Loading models was moved into this function
	LoadModelsIntoScene();

	// Loading the uniform variables here (rather than the inner draw loop)
	GLint objectColour_UniLoc = glGetUniformLocation(program, "objectColour");
	GLint lightPos_UniLoc = glGetUniformLocation(program, "lightPos");
	GLint lightBrightness_UniLoc = glGetUniformLocation(program, "lightBrightness");

	GLint matModel_location = glGetUniformLocation(program, "matModel");
	GLint matView_location = glGetUniformLocation(program, "matView");
	GLint matProj_location = glGetUniformLocation(program, "matProj");

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
		matView = glm::lookAt(g_CameraEye, g_CameraAt, glm::vec3(0.0f, 1.0f, 0.0f));

		//glUniformMatrix4fv(matMoldel_location, 1, GL_FALSE, glm::value_ptr(m));
		glUniformMatrix4fv(matView_location, 1, GL_FALSE, glm::value_ptr(matView));
		glUniformMatrix4fv(matProj_location, 1, GL_FALSE, glm::value_ptr(matProjection));

		double lastTime = glfwGetTime();

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

		ProcessAsynKeys(window, deltaTime);

	}//while (!glfwWindowShouldClose(window))

	// Delete stuff
	delete pTheShaderManager;
	delete ::g_pTheVAOMeshManager;

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

/**
	Loads the models we are drawing into the vector

	@param: void
	@return: void
*/
void LoadModelsIntoScene(void)
{
	loadPlayerFromJson();
	loadEnemiesFromJson();
	loadPlatformsFromJson();

	return;
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
