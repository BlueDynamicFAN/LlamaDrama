#include "global.h"

#include <iostream>
#include <fstream>

// This has all the keyboard, mouse, and controller stuff

// Some helper functions... 
inline bool isShiftDownAlone(int mods);
inline bool isCrtlDownAlone(int mods);
inline bool isAltDownAlone(int mods);

const float moveSpeed = 1.0f;
int meshNumber = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (isCrtlDownAlone(mods))
	{
		switch (key)
		{
			// MOVE OBJECTS AROUND SPACE
		case GLFW_KEY_W:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->position.y += moveSpeed;
			}
			break;
		case GLFW_KEY_S:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->position.y -= moveSpeed;
			}
			break;
		case GLFW_KEY_A:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->position.x -= moveSpeed;
			}
			break;
		case GLFW_KEY_D:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->position.x += moveSpeed;
			}
			break;
		case GLFW_KEY_Q:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->position.z += moveSpeed;
			}
			break;
		case GLFW_KEY_E:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->position.z -= moveSpeed;
			}
			break;

			// ROTATE OBJECTS AROUND SPACE
		case GLFW_KEY_U:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->postRotation.x += moveSpeed;
			}
			break;
		case GLFW_KEY_J:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->postRotation.x -= moveSpeed;
			}
			break;
		case GLFW_KEY_H:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->postRotation.y += moveSpeed;
			}
			break;
		case GLFW_KEY_K:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->postRotation.y -= moveSpeed;
			}
			break;
		case GLFW_KEY_Y:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->postRotation.z += moveSpeed;
			}
			break;
		case GLFW_KEY_I:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->postRotation.z -= moveSpeed;
			}
			break;

			// NON UNIFORM SCALE
		case GLFW_KEY_N:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->nonUniformScale *= 1.10f;
			}
			break;
		case GLFW_KEY_M:
			if (action == GLFW_PRESS)
			{
				vec_pObjectsToDraw[SelectedModel]->nonUniformScale *= 0.90f;
			}
			break;

			// CHANGE MODEL MESH
		case GLFW_KEY_B:
			if (action == GLFW_PRESS)
			{
				if (meshNumber == vec_ModelFileNames.size())
					meshNumber = 0;

				vec_pObjectsToDraw[SelectedModel]->meshName = vec_ModelFileNames.at(meshNumber);
				meshNumber++;
			}
			break;

			// PRINT OUT MODEL STUFF
		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS)
			{
				std::cout << "\nCoordinates for model: " << vec_pObjectsToDraw[SelectedModel]->friendlyName << std::endl;
				std::cout << "Position x: " << vec_pObjectsToDraw[SelectedModel]->position.x << std::endl;
				std::cout << "Position y: " << vec_pObjectsToDraw[SelectedModel]->position.y << std::endl;
				std::cout << "Position z: " << vec_pObjectsToDraw[SelectedModel]->position.z << std::endl;

				std::cout << "Rotation x: " << vec_pObjectsToDraw[SelectedModel]->postRotation.x * 180.0 / PI << std::endl;
				std::cout << "Rotation y: " << vec_pObjectsToDraw[SelectedModel]->postRotation.y * 180.0 / PI << std::endl;
				std::cout << "Rotation z: " << vec_pObjectsToDraw[SelectedModel]->postRotation.z * 180.0 / PI << std::endl;

			}
			break;

		case GLFW_KEY_O:
			if (action == GLFW_PRESS && SelectedModel < vec_pObjectsToDraw.size() - 1)
			{
				SelectedModel++;
			}
			break;
		case GLFW_KEY_P:
			if (action == GLFW_PRESS && SelectedModel > 0)
			{
				SelectedModel--;
			}
			break;
		}

	}//if ( isCrtlDownAlone(mods) && (pGalac != NULL) )


	return;
}

bool IsShiftDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) { return true; }
	// both are up
	return false;
}

bool IsCtrlDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL)) { return true; }
	// both are up
	return false;
}

bool IsAltDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT)) { return true; }
	// both are up
	return false;
}

bool AreAllModifiersUp(GLFWwindow* window)
{
	if (IsShiftDown(window)) { return false; }
	if (IsCtrlDown(window)) { return false; }
	if (IsAltDown(window)) { return false; }
	// Yup, they are all UP
	return true;
}

bool isShiftDownAlone(int mods)
{
	if ((mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT)
	{
		return true;
	}
	return false;
}

bool isCrtlDownAlone(int mods)
{
	if ((mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
	{
		return true;
	}
	return false;
}

bool isAltDownAlone(int mods)
{
	if ((mods & GLFW_MOD_ALT) == GLFW_MOD_ALT)
	{
		return true;
	}
	return false;
}

void ProcessAsynKeys(GLFWwindow* window)
{
	const float CAMERA_SPEED_SLOW = 0.1f;
	const float CAMERA_SPEED_FAST = 1.0f;

	float cameraSpeed = CAMERA_SPEED_SLOW;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		cameraSpeed = CAMERA_SPEED_FAST;
	}

	// If no keys are down, move the camera
	if (AreAllModifiersUp(window))
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			g_CameraEye.z += cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	// "backwards"
		{
			g_CameraEye.z -= cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	// "left"
		{
			g_CameraEye.x -= cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// "right"
		{
			g_CameraEye.x += cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	// "up"
		{
			g_CameraEye.y += cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)	// "down"
		{
			g_CameraEye.y -= cameraSpeed;
		}
	}//if(AreAllModifiersUp(window)

	const float MIN_LIGHT_BRIGHTNESS = 0.001f;

	// Control (ctrl) key down? Move light
	if (IsCtrlDown(window))
	{

	}//if(!IsShiftDown(window) )

	if (IsAltDown(window))
	{
		if (glfwGetKey(window, GLFW_KEY_W)) { ::g_lightPos.z += cameraSpeed; }
		if (glfwGetKey(window, GLFW_KEY_S)) { ::g_lightPos.z -= cameraSpeed; }
		if (glfwGetKey(window, GLFW_KEY_A)) { ::g_lightPos.x -= cameraSpeed; }
		if (glfwGetKey(window, GLFW_KEY_D)) { ::g_lightPos.x += cameraSpeed; }
		if (glfwGetKey(window, GLFW_KEY_Q)) { ::g_lightPos.y += cameraSpeed; }
		if (glfwGetKey(window, GLFW_KEY_E)) { ::g_lightPos.y -= cameraSpeed; }
		if (glfwGetKey(window, GLFW_KEY_PERIOD))
		{	// Increase the "brightness"
			::g_lightBrightness *= 1.01f;		// Increase by 1 percent
		}
		if (glfwGetKey(window, GLFW_KEY_COMMA))
		{	// Decrease the "brightness"
			::g_lightBrightness *= 0.99f;		// Decrease by 1 percent
			if (::g_lightBrightness < MIN_LIGHT_BRIGHTNESS)
			{
				::g_lightBrightness = MIN_LIGHT_BRIGHTNESS;
			}
		}
	}//if(!IsShiftDown(window) )	

	return;
}
