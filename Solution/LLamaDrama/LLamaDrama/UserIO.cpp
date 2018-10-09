#include "global.h"

#include <iostream>
#include <fstream>

// This has all the keyboard, mouse, and controller stuff

const float moveSpeed = 2.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
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

void ProcessAsynKeys(GLFWwindow* window, double deltaTime)
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
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			if (isPlayerOnTopOfPlatfrom())
			{
				thePlayer->velocity.y = 2.5f * moveSpeed;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_S))
		{
			if (!isPlayerOnTopOfPlatfrom())
			{
				thePlayer->velocity.y = -moveSpeed;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_A))
		{
			thePlayer->velocity.x = -moveSpeed;
			movingsUpdate(deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_D))
		{
			thePlayer->velocity.x = moveSpeed;
			movingsUpdate(deltaTime);
		}
	}//if(AreAllModifiersUp(window)


	// Control (ctrl) key down? Player moves 
	if (IsCtrlDown(window))
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

	}//if(!IsCtrltDown(window) )
}
