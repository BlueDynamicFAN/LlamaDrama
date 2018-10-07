#include "global.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>		// printf();
#include <iostream>		// cout (console out)
#include <sstream>
#include <vector>		// "smart array" dynamic array

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

glm::vec3 g_CameraEye = glm::vec3(0.0, 0.0, +10.0f);
glm::vec3 g_CameraAt = glm::vec3(0.0, 0.0, 0.0f);

cMeshObject* pRogerRabbit = NULL;

// Stack based variable
//cShaderManager Ted;		

cShaderManager* pTheShaderManager = NULL;		// "Heap" variable
cVAOMeshManager* g_pTheVAOMeshManager = NULL;

// Loads the models we are drawing into the vector
void LoadModelsIntoScene(void);
void UpdateWindowTitle(void);


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

	window = glfwCreateWindow(1600, 900, "INFO 6044, Checkpoint 1", NULL, NULL);
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
	{		// Shaders are OK
		std::cout << "Compiled shaders OK." << std::endl;
	}
	else
	{
		std::cout << "OH NO! Compile error" << std::endl;
		std::cout << pTheShaderManager->getLastError() << std::endl;
	}

	GLuint program = pTheShaderManager->getIDFromFriendlyName("myShader");
	::g_pTheVAOMeshManager = new cVAOMeshManager();

	sModelDrawInfo bunnyInfo;
	bunnyInfo.meshFileName = "bun_res3_xyz.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(bunnyInfo, program))
	{
		std::cout << "Didn't load the bunny" << std::endl;
		std::cout << pTheShaderManager->getLastError() << std::endl;
	}
	vec_ModelFileNames.push_back(bunnyInfo.meshFileName);

	//loadEnemiesfromJson();
	//sModelDrawInfo airplaneInfo;
	//airplaneInfo.meshFileName = "ssj100_xyz.ply";
	//::g_pTheVAOMeshManager->LoadModelIntoVAO(airplaneInfo, program);
	//vec_ModelFileNames.push_back(airplaneInfo.meshFileName);

	//sModelDrawInfo backToTheFuture;
	//backToTheFuture.meshFileName = "de--lorean.ply";
	//::g_pTheVAOMeshManager->LoadModelIntoVAO(backToTheFuture, program);
	//vec_ModelFileNames.push_back(backToTheFuture.meshFileName);

	//sModelDrawInfo migInfo;
	//migInfo.meshFileName = "mig29_xyz.ply";
	//::g_pTheVAOMeshManager->LoadModelIntoVAO(migInfo, program);
	//vec_ModelFileNames.push_back(migInfo.meshFileName);

	//sModelDrawInfo teapotInfo;
	//teapotInfo.meshFileName = "Utah_Teapot_xyz.ply";
	//::g_pTheVAOMeshManager->LoadModelIntoVAO(teapotInfo, program);
	//vec_ModelFileNames.push_back(teapotInfo.meshFileName);

	//sModelDrawInfo fishInfo;
	//fishInfo.meshFileName = "PacificCod0_rotated_xyz.ply";
	//::g_pTheVAOMeshManager->LoadModelIntoVAO(fishInfo, program);
	//vec_ModelFileNames.push_back(fishInfo.meshFileName);

	//sModelDrawInfo terrainInfo;
	//terrainInfo.meshFileName = "MeshLab_Fractal_Terrain_xyz.ply";
	//::g_pTheVAOMeshManager->LoadModelIntoVAO(terrainInfo, program);
	//vec_ModelFileNames.push_back(terrainInfo.meshFileName);

	// At this point, mesh in in GPU
	std::cout << "Mesh was loaded OK" << std::endl;

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
			<< ::vec_pObjectsToDraw[SelectedModel]->friendlyName;

		glfwSetWindowTitle(window, ssTitle.str().c_str());

		float ratio;
		int width, height;
		glm::mat4x4 matModel = glm::mat4(1.0f);			// mat4x4 m, p, mvp;
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

		// Draw all the objects in the "scene"
		for (unsigned int objIndex = 0;
			objIndex != (unsigned int)vec_pObjectsToDraw.size();
			objIndex++)
		{

			// Is this object visible
			if (!vec_pObjectsToDraw[objIndex]->bIsVisible)
			{
				continue;
			}

			//************************************
			matModel = glm::mat4x4(1.0f);		// mat4x4_identity(m);

			// Calculate some rotation matrix values;
			glm::mat4 preRot_X = glm::rotate(glm::mat4(1.0f),
				vec_pObjectsToDraw[objIndex]->preRotation.x,
				glm::vec3(1.0f, 0.0, 0.0f));
			matModel = matModel * preRot_X;

			glm::mat4 preRot_Y = glm::rotate(glm::mat4(1.0f),
				vec_pObjectsToDraw[objIndex]->preRotation.y,
				glm::vec3(0.0f, 1.0, 0.0f));
			matModel = matModel * preRot_Y;

			glm::mat4 preRot_Z = glm::rotate(glm::mat4(1.0f),
				vec_pObjectsToDraw[objIndex]->preRotation.z,
				glm::vec3(0.0f, 0.0, 1.0f));
			matModel = matModel * preRot_Z;

			glm::mat4 matTranslation = glm::translate(glm::mat4(1.0f),
				vec_pObjectsToDraw[objIndex]->position);

			matModel = matModel * matTranslation;		// matMove

			glm::mat4 postRot_X = glm::rotate(glm::mat4(1.0f),
				vec_pObjectsToDraw[objIndex]->postRotation.x,
				glm::vec3(1.0f, 0.0, 0.0f));
			matModel = matModel * postRot_X;

			glm::mat4 postRot_Y = glm::rotate(glm::mat4(1.0f),
				vec_pObjectsToDraw[objIndex]->postRotation.y,
				glm::vec3(0.0f, 1.0, 0.0f));
			matModel = matModel * postRot_Y;

			glm::mat4 postRot_Z = glm::rotate(glm::mat4(1.0f),
				vec_pObjectsToDraw[objIndex]->postRotation.z,
				glm::vec3(0.0f, 0.0, 1.0f));
			matModel = matModel * preRot_Z;

			// And now scale

			glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
				vec_pObjectsToDraw[objIndex]->nonUniformScale);
			matModel = matModel * matScale;


			//************************************

						//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
			matProjection = glm::perspective(0.6f,			// FOV
				ratio,		// Aspect ratio
				0.1f,			// Near clipping plane
				1000.0f);	// Far clipping plane

			matView = glm::lookAt(g_CameraEye,	// Eye
				g_CameraAt,		// At
				glm::vec3(0.0f, 1.0f, 0.0f));// Up

			//mat4x4_mul(mvp, p, m);
			//mvp = p * view * m; 

			glUseProgram(program);
			glUniformMatrix4fv(matModel_location, 1, GL_FALSE, glm::value_ptr(matModel));
			glUniformMatrix4fv(matView_location, 1, GL_FALSE, glm::value_ptr(matView));
			glUniformMatrix4fv(matProj_location, 1, GL_FALSE, glm::value_ptr(matProjection));

			// Set the object to "wireframe"
			//glPolygonMode( GL_FRONT_AND_BACK , GL_LINE );	//GL_FILL
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//GL_FILL

			//GLint objectColour_UniLoc 
			glUniform3f(objectColour_UniLoc,
				vec_pObjectsToDraw[objIndex]->objColour.r,
				vec_pObjectsToDraw[objIndex]->objColour.g,
				vec_pObjectsToDraw[objIndex]->objColour.b);

			glUniform3f(lightPos_UniLoc, g_lightPos.x, g_lightPos.y, g_lightPos.z);
			glUniform1f(lightBrightness_UniLoc, ::g_lightBrightness);

			if (vec_pObjectsToDraw[objIndex]->bIsWireFrame)
			{
				// Yes, draw it wireframe
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDisable(GL_CULL_FACE);	// Discared "back facing" triangles
			}
			else
			{
				// No, it's "solid" (or "Filled")
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glEnable(GL_CULL_FACE);	// Discared "back facing" triangles
			}


			sModelDrawInfo modelInfo;
			modelInfo.meshFileName = vec_pObjectsToDraw[objIndex]->meshName;

			if (::g_pTheVAOMeshManager->FindDrawInfoByModelName(modelInfo))
			{
				//glDrawArrays(GL_TRIANGLES, 0, bunnyInfo.numberOfIndices );

				glBindVertexArray(modelInfo.VAO_ID);

				glDrawElements(GL_TRIANGLES,
					modelInfo.numberOfIndices,
					GL_UNSIGNED_INT,
					0);

				glBindVertexArray(0);

			}

		}//for ( unsigned int objIndex = 0; 

		UpdateWindowTitle();

		glfwSwapBuffers(window);
		glfwPollEvents();

		ProcessAsynKeys(window);

	}//while (!glfwWindowShouldClose(window))

	// Delete stuff
	delete pTheShaderManager;
	delete ::g_pTheVAOMeshManager;

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


// Loads the models we are drawing into the vector
void LoadModelsIntoScene(void)
{

	{
		cMeshObject* pBunny = new cMeshObject();
		pBunny->position = glm::vec3(0.0f, 0.0f, 0.0f);
		pBunny->nonUniformScale = glm::vec3(5.0f, 5.0f, 5.0f);
		pBunny->objColour = glm::vec3(1.0f, 1.0f, 1.0f);
		pBunny->meshName = "bun_res3_xyz.ply";
		pBunny->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pBunny);
	}

	return;
}

void UpdateWindowTitle(void)
{



	return;
}

cMeshObject* findObjectByFriendlyName(std::string theNameToFind)
{
	for (unsigned int index = 0; index != vec_pObjectsToDraw.size(); index++)
	{
		// Is this it? 
		if (vec_pObjectsToDraw[index]->friendlyName == theNameToFind)
		{
			return vec_pObjectsToDraw[index];
		}
	}
	// Didn't find it.
	return NULL;	// 0 or nullptr
}
