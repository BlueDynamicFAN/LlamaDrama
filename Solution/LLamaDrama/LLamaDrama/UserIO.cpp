/**
	UserIO.cpp
	Purpose: Controls all of the user input
	@author: BlueDynamic
	@version: 1.0.0
*/
#include "global.h"

#include <iostream>
#include <fstream>
#include "cPickUp.h"

const float moveSpeed = 3.0f;
extern std::vector <cPickUp*> pPickUpObj;
unsigned int activePickUpId = 0;
cPickUp* activePickUp = NULL;
void savePickUpToJson();
DAO dao;

/**
	Keyboard input

	@param: the window, key that was pressed, scancode, action and mods
	@return: void
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	activePickUp = pPickUpObj[activePickUpId];

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		std::cout << "Player Id: " << thePlayer->getId() << std::endl;
		std::cout << "Current score: " << thePlayer->getPlayerScore() << std::endl;
		std::cout << "Database scores: " << std::endl;
		dao.getHighScore(thePlayer->getId());
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		top20.clear();
		client->getTop20(top20);

		std::map<int32_t, int32_t>::iterator it;
		std::cout << "[PlayerID][Score]:" << std::endl;
		for (it = top20.begin(); it != top20.end(); it++) {
			std::cout << "[ " << it->first << " ][ " << it->second << " ]" << std::endl;
		}
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		top20.clear();
		client->getTop20(top20);

		std::map<int32_t, int32_t>::iterator it;
		for (it = top20.begin(); it != top20.end(); it++) {
			dao.setTop20HighScore(it->first, it->second);
		}
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		dao.getAllHighScores();
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		std::cout << "I am here" <<std::endl;
		if (activePickUpId == 0) {
			activePickUpId = (unsigned int)pPickUpObj.size();
			activePickUpId -= 1;
		}
		else {
			activePickUpId -= 1;
		}

		activePickUp = pPickUpObj[activePickUpId];
		std::cout << activePickUpId << " " << activePickUp->getModel()->m_friendlyName << std::endl;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		std::cout << "I am here" << std::endl;
		unsigned int num = (unsigned int)pPickUpObj.size();
		if (activePickUpId >= num - 1) {
			activePickUpId = 0;
		}
		else {
			activePickUpId += 1;
		}

		activePickUp = pPickUpObj[activePickUpId];
		std::cout << activePickUpId << " " << activePickUp->getModel()->m_friendlyName << std::endl;
	}

	return;
}

/**
	Checks if shift is pressed

	@param: current window
	@return: true or false
*/
bool IsShiftDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) { return true; }
	// both are up
	return false;
}

/**
	Checks if ctrl is pressed

	@param: current window
	@return: true or false
*/
bool IsCtrlDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL)) { return true; }
	// both are up
	return false;
}

/**
	Checks if alt is pressed

	@param: current window
	@return: true or false
*/
bool IsAltDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT)) { return true; }
	// both are up
	return false;
}

/**
	Checks if all modifiers are not pressed

	@param: current window
	@return: true or false
*/
bool AreAllModifiersUp(GLFWwindow* window)
{
	if (IsShiftDown(window)) { return false; }
	if (IsCtrlDown(window)) { return false; }
	if (IsAltDown(window)) { return false; }
	// Yup, they are all UP
	return true;
}

/**
	Processes the key input

	@param: current window, delatTime
	@return: void
*/
void ProcessAsynKeys(GLFWwindow* window, double deltaTime)
{
	const float CAMERA_SPEED_SLOW = 0.1f;
	const float CAMERA_SPEED_FAST = 1.0f;

	float cameraSpeed = CAMERA_SPEED_SLOW;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		cameraSpeed = CAMERA_SPEED_FAST;
	}

	// If no keys are down, move the player
	if (AreAllModifiersUp(window))
	{
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			if (isPlayerOnTopOfAPlatform())
			{
				thePlayer->setVelocityY(2.0f * moveSpeed);
				isJump = true;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_S))
		{
			//if (!isPlayerOnTopOfAPlatform())
			//{
			//	thePlayer->setVelocityY(-moveSpeed);
			//}
		}

		if (glfwGetKey(window, GLFW_KEY_A))
		{
			thePlayer->setVelocityX(-moveSpeed - 1.5f);
			movesUpdate(deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_D))
		{
			thePlayer->setVelocityX(moveSpeed + 1.5f);
			movesUpdate(deltaTime);
		}
	}//if(AreAllModifiersUp(window)

	if (IsAltDown(window) && IsCtrlDown(window))
	{
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			savePickUpToJson();
		}
	}

	// Control (ctrl) key down? move the camera. Used for debuging
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


	if (IsAltDown(window) && !IsCtrlDown(window))
	{
		//CHANGING POSITION of the Pick up objects
	
		if (glfwGetKey(window, GLFW_KEY_A)) { activePickUp->getModel()->m_position.x -= cameraSpeed; }
		if (glfwGetKey(window, GLFW_KEY_D)) { activePickUp->getModel()->m_position.x += cameraSpeed; }
		if (glfwGetKey(window, GLFW_KEY_W)) { activePickUp->getModel()->m_position.y += cameraSpeed; }
		if (glfwGetKey(window, GLFW_KEY_S)) { activePickUp->getModel()->m_position.y -= cameraSpeed; }

	}//if (IsAltDown(window)
}
