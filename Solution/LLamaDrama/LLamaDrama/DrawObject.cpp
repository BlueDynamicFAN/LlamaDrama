/**
	DrawObject.cpp
	Purpose: Draws the object
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
#include <iostream>

#include "cMeshObject.h"

/**
	Draws an object

	@param: current object to draw, model, and sharder program
	@return: void
*/
void DrawObject(cMeshObject* pCurrentMesh, glm::mat4x4 &matModel, GLuint shaderProgramID)
{
	// Is this object visible
	if (!pCurrentMesh->bIsVisible)
	{
		return;
	}

	//************************************
	matModel = glm::mat4x4(1.0f);

	// Pre movement rotation
	glm::mat4 preRot_X = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->preRotation.x,
		glm::vec3(1.0f, 0.0, 0.0f));
	matModel = matModel * preRot_X;

	glm::mat4 preRot_Y = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->preRotation.y,
		glm::vec3(0.0f, 1.0, 0.0f));
	matModel = matModel * preRot_Y;

	glm::mat4 preRot_Z = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->preRotation.z,
		glm::vec3(0.0f, 0.0, 1.0f));
	matModel = matModel * preRot_Z;

	// Movement
	glm::mat4 matTranslation = glm::translate(glm::mat4(1.0f),
		pCurrentMesh->position);

	matModel = matModel * matTranslation;

	// Post movement rotation
	glm::mat4 postRot_X = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->postRotation.x,
		glm::vec3(1.0f, 0.0, 0.0f));
	matModel = matModel * postRot_X;

	glm::mat4 postRot_Y = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->postRotation.y,
		glm::vec3(0.0f, 1.0, 0.0f));
	matModel = matModel * postRot_Y;

	glm::mat4 postRot_Z = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->postRotation.z,
		glm::vec3(0.0f, 0.0, 1.0f));
	matModel = matModel * postRot_Z;

	// Scale
	glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
		pCurrentMesh->nonUniformScale);
	matModel = matModel * matScale;

	//************************************

	glUseProgram(shaderProgramID);

	// Loading the uniform variables here (rather than the inner draw loop)
	GLint objectColour_UniLoc = glGetUniformLocation(shaderProgramID, "objectColour");
	GLint lightPos_UniLoc = glGetUniformLocation(shaderProgramID, "lightPos");
	GLint lightBrightness_UniLoc = glGetUniformLocation(shaderProgramID, "lightBrightness");
	GLint matModel_location = glGetUniformLocation(shaderProgramID, "matModel");
	GLint matView_location = glGetUniformLocation(shaderProgramID, "matView");
	GLint matProj_location = glGetUniformLocation(shaderProgramID, "matProj");

	glUniformMatrix4fv(matModel_location, 1, GL_FALSE, glm::value_ptr(matModel));

	// Set the object to fill
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUniform3f(objectColour_UniLoc,
		pCurrentMesh->objColour.r,
		pCurrentMesh->objColour.g,
		pCurrentMesh->objColour.b);

	glUniform3f(lightPos_UniLoc, g_lightPos.x, g_lightPos.y, g_lightPos.z);
	glUniform1f(lightBrightness_UniLoc, ::g_lightBrightness);


	if (pCurrentMesh->bIsWireFrame)
	{
		// Yes, draw it wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);	// Discared "back facing" triangles
		//glDisable( GL_DEPTH );		// Enables the KEEPING of the depth information
		//glDisable( GL_DEPTH_TEST );	// When drawing, checked the existing depth
	}
	else
	{
		// No, it's "solid" (or "Filled")
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);	// Discared "back facing" triangles
		//glEnable( GL_DEPTH );		// Enables the KEEPING of the depth information
		//glEnable( GL_DEPTH_TEST );	// When drawing, checked the existing depth
	}


	sModelDrawInfo modelInfo;
	modelInfo.meshFileName = pCurrentMesh->meshName;

	if (g_pTheVAOMeshManager->FindDrawInfoByModelName(modelInfo))
	{
		glBindVertexArray(modelInfo.VAO_ID);

		glDrawElements(GL_TRIANGLES,
			modelInfo.numberOfIndices,
			GL_UNSIGNED_INT,
			0);

		glBindVertexArray(0);
	}

	return;
}//void DrawObject(void)
