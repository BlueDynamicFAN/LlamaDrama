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

bool HACK_bTextureUniformLocationsLoaded = false;
GLint tex00_UniLoc = -1;
GLint tex01_UniLoc = -1;
GLint tex02_UniLoc = -1;
GLint tex03_UniLoc = -1;
GLint tex04_UniLoc = -1;
GLint tex05_UniLoc = -1;
GLint tex06_UniLoc = -1;
GLint tex07_UniLoc = -1;

GLint texBW_0_UniLoc = -1;
GLint texBW_1_UniLoc = -1;


void BindTextures(cMeshObject* pCurrentMesh, GLuint shaderProgramID)
{

	// This is pretty much a hack, so we should likely pass the shader object 
	// (pointer) to this function, and to the DrawObject call, too. 
	// (Another option would be to pass the shader MANAGER instead, so 
	//  that the functions can look up various things in the shader)
	//
	// For now, I'm going to get the uniform location here 
	// (to make it clear (maybe?) that we'll NEED those shader uniform locations)

	// So this is only called once... 
	if (!HACK_bTextureUniformLocationsLoaded)
	{
		tex00_UniLoc = glGetUniformLocation(shaderProgramID, "texture00");		// uniform sampler2D texture00;
		tex01_UniLoc = glGetUniformLocation(shaderProgramID, "texture01");		// uniform sampler2D texture01;
		tex02_UniLoc = glGetUniformLocation(shaderProgramID, "texture02");		// uniform sampler2D texture02;
		tex03_UniLoc = glGetUniformLocation(shaderProgramID, "texture03");		// uniform sampler2D texture03;
		tex04_UniLoc = glGetUniformLocation(shaderProgramID, "texture04");		// uniform sampler2D texture04;
		tex05_UniLoc = glGetUniformLocation(shaderProgramID, "texture05");		// uniform sampler2D texture05;
		tex06_UniLoc = glGetUniformLocation(shaderProgramID, "texture06");		// uniform sampler2D texture06;
		tex07_UniLoc = glGetUniformLocation(shaderProgramID, "texture07");		// uniform sampler2D texture07;

		texBW_0_UniLoc = glGetUniformLocation(shaderProgramID, "texBlendWeights[0]");	// uniform vec4 texBlendWeights[2];
		texBW_1_UniLoc = glGetUniformLocation(shaderProgramID, "texBlendWeights[1]");	// uniform vec4 texBlendWeights[2];

		HACK_bTextureUniformLocationsLoaded = true;

	}//if(!HACK_bTextureUniformLocationsLoaded )

	// For each texture, bind the texture to a texture unit and sampler
	// Texture #0 (on the mesh) -- Texture Unit 0 -- Sampler 0
	// Texture #1 (on the mesh) -- Texture Unit 1 -- Sampler 1
	// ....

	// Set all the blend weights (strengths) to zero
	float blendWeights[8] = { 0 };


	for (int texBindIndex = 0; texBindIndex != pCurrentMesh->vecTextures.size(); texBindIndex++)
	{
		// Bind to the the "texBindIndex" texture unit
		glActiveTexture(GL_TEXTURE0 + texBindIndex);

		// Connect the specific texture to THIS texture unit
		std::string texName = pCurrentMesh->vecTextures[texBindIndex].name;

		GLuint texID = ::g_pTheTextureManager->getTextureIDFromName(texName);

		glBindTexture(GL_TEXTURE_2D, texID);

		// Use a switch to pick the texture sampler and weight (strength)
		// BECAUSE the samplers can't be in an array
		switch (texBindIndex)
		{
		case 0:		// uniform sampler2D texture00  AND texBlendWeights[0].x;
			glUniform1i(tex00_UniLoc, texBindIndex);
			break;
		case 1:		// uniform sampler2D texture01  AND texBlendWeights[0].y;
			glUniform1i(tex01_UniLoc, texBindIndex);
			break;
		case 2:
			glUniform1i(tex02_UniLoc, texBindIndex);
			break;
		case 3:
			glUniform1i(tex03_UniLoc, texBindIndex);
			break;
		case 4:		// uniform sampler2D texture04  AND texBlendWeights[1].x;
			glUniform1i(tex04_UniLoc, texBindIndex);
			break;
		case 5:
			glUniform1i(tex05_UniLoc, texBindIndex);
			break;
		case 6:
			glUniform1i(tex06_UniLoc, texBindIndex);
			break;
		case 7:
			glUniform1i(tex07_UniLoc, texBindIndex);
			break;
		}//switch ( texBindIndex )

		// Set the blend weight (strengty)
		blendWeights[texBindIndex] = pCurrentMesh->vecTextures[texBindIndex].strength;

	}//for ( int texBindIndex

	// Set the weights (strengths) in the shader
	glUniform4f(texBW_0_UniLoc, blendWeights[0], blendWeights[1], blendWeights[2], blendWeights[3]);
	glUniform4f(texBW_1_UniLoc, blendWeights[4], blendWeights[5], blendWeights[6], blendWeights[7]);

	return;
}


/**
	Draws an object

	@param: current object to draw, model, and shader program
	@return: void
*/
void DrawObject(cMeshObject* pCurrentMesh, glm::mat4x4 &matModel, GLuint shaderProgramID)
{
	// Is this object visible
	if (!pCurrentMesh->m_bIsVisible)
	{
		return;
	}

	// Set up the texture binding for this object
	BindTextures(pCurrentMesh, shaderProgramID);

	//************************************
	matModel = glm::mat4x4(1.0f);

	// Pre movement rotation
	glm::mat4 preRot_X = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->m_preRotation.x,
		glm::vec3(1.0f, 0.0, 0.0f));
	matModel = matModel * preRot_X;

	glm::mat4 preRot_Y = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->m_preRotation.y,
		glm::vec3(0.0f, 1.0, 0.0f));
	matModel = matModel * preRot_Y;

	glm::mat4 preRot_Z = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->m_preRotation.z,
		glm::vec3(0.0f, 0.0, 1.0f));
	matModel = matModel * preRot_Z;

	// Movement
	glm::mat4 matTranslation = glm::translate(glm::mat4(1.0f),
		pCurrentMesh->m_position);

	matModel = matModel * matTranslation;

	// Post movement rotation
	glm::mat4 postRot_X = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->m_postRotation.x,
		glm::vec3(1.0f, 0.0, 0.0f));
	matModel = matModel * postRot_X;

	glm::mat4 postRot_Y = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->m_postRotation.y,
		glm::vec3(0.0f, 1.0, 0.0f));
	matModel = matModel * postRot_Y;

	glm::mat4 postRot_Z = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->m_postRotation.z,
		glm::vec3(0.0f, 0.0, 1.0f));
	matModel = matModel * postRot_Z;

	glm::mat4 matModelInvTrans = glm::inverse(glm::transpose(matModel));


	// Scale
	glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
		pCurrentMesh->m_nonUniformScale);
	matModel = matModel * matScale;

	//************************************

	glUseProgram(shaderProgramID);
	
	BindTextures(pCurrentMesh, shaderProgramID);


	// Set the object to fill
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLint objectDiffuse_UniLoc = glGetUniformLocation(shaderProgramID, "objectDiffuse");
	GLint objectSpecular_UniLoc = glGetUniformLocation(shaderProgramID, "objectSpecular");

	GLint lightPos_UniLoc = glGetUniformLocation(shaderProgramID, "lightPos");
	GLint lightBrightness_UniLoc = glGetUniformLocation(shaderProgramID, "lightBrightness");
	GLint useVertexColour_UniLoc = glGetUniformLocation(shaderProgramID, "useVertexColour");

	GLint matModel_location = glGetUniformLocation(shaderProgramID, "matModel");
	GLint matView_location = glGetUniformLocation(shaderProgramID, "matView");
	GLint matProj_location = glGetUniformLocation(shaderProgramID, "matProj");
	GLint matModelInvTrans_location = glGetUniformLocation(shaderProgramID, "matModelInvTrans");

	GLint bDontUseLighting_UniLoc = glGetUniformLocation(shaderProgramID, "bDontLight");//"bDontUseLighting");


	glUniformMatrix4fv(matModel_location, 1, GL_FALSE, glm::value_ptr(matModel));
	glUniformMatrix4fv(matModelInvTrans_location, 1, GL_FALSE, glm::value_ptr(matModelInvTrans));


	// Set the object to "wireframe"
//			glPolygonMode( GL_FRONT_AND_BACK , GL_LINE );	//GL_FILL
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//GL_FILL

	
	glUniform4f(objectDiffuse_UniLoc,
		pCurrentMesh->materialDiffuse.r,
		pCurrentMesh->materialDiffuse.g,
		pCurrentMesh->materialDiffuse.b,
		pCurrentMesh->materialDiffuse.a);
	glUniform4f(objectSpecular_UniLoc,
		pCurrentMesh->materialSpecular.r,
		pCurrentMesh->materialSpecular.g,
		pCurrentMesh->materialSpecular.b,
		pCurrentMesh->materialSpecular.a);

	if (pCurrentMesh->bUseVertexColour)
	{
		glUniform1f(useVertexColour_UniLoc, (float)GL_TRUE);
	}
	else
	{
		glUniform1f(useVertexColour_UniLoc, (float)GL_FALSE);
	}

	if (pCurrentMesh->bDontLight)
	{
		glUniform1f(bDontUseLighting_UniLoc, (float)GL_TRUE);
	}
	else
	{
		glUniform1f(bDontUseLighting_UniLoc, (float)GL_FALSE);
	}

	if (pCurrentMesh->m_bIsWireFrame)
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
	modelInfo.meshFileName = pCurrentMesh->m_meshName;

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
