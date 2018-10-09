/**
	Physics.cpp
	Purpose: Deals with all the physics
	@author: BlueDynamic
	@version: 1.0.0
*/
#include "global.h"
#include <glm/glm.hpp>
#include "sModelDrawInfo.h"
#include <algorithm>
#include <iostream>
#include <vector>

const float GROUND_PLANE_Y = -3.0f;

/**
	Checks if the player is on top of a platform

	@param: void
	@return: true or false
*/
bool isPlayerOnTopOfPlatfrom()
{
	for (std::vector <Platform*>::iterator itPlatform = pPlatforms.begin();
		itPlatform != pPlatforms.end(); itPlatform++)
	{
		Platform* thePlatform = *itPlatform;
		float yLimit = thePlatform->model->position.y + (thePlatform->height) / 2;
		bool inXLimitsNeg = (thePlayer->m_model->position.x >= thePlatform->model->position.x - thePlatform->width / 2);
		bool inXLimitsPos = (thePlayer->m_model->position.x <= thePlatform->model->position.x + thePlatform->width / 2);
		if ((thePlayer->m_model->position.y <= yLimit) && inXLimitsNeg && inXLimitsPos)
		{
			return true;
		}
	}
	return false;
}

/**
	Updates the gravity of the player each frame

	@param: the time
	@return: void
*/
void gravityUpdate(double deltaTime)
{
	const double LARGEST_DELTATIME = 0.10; //10 ms = 10Hz
	if (deltaTime > LARGEST_DELTATIME) 
	{
		deltaTime = LARGEST_DELTATIME;
	}

		thePlayer->velocity.y += thePlayer->accel.y * deltaTime;

		thePlayer->m_model->position.y += thePlayer->velocity.y * deltaTime;

		//The object can't go any lower than "the ground"
		if(isPlayerOnTopOfPlatfrom())
		{
			thePlayer->velocity.y = 0.0;
			thePlayer->accel.y = 0.0;
		}
		else {
			thePlayer->accel.y = -9.8;
		}

	return;
}

/**
	Updates the movement of the player each frame

	@param: the time
	@return: void
*/
void movingsUpdate(double deltaTime)
{
	const double LARGEST_DELTATIME = 0.10; //10 ms = 10Hz
	if (deltaTime > LARGEST_DELTATIME) {
		deltaTime = LARGEST_DELTATIME;
	}

	thePlayer->velocity.x += thePlayer->accel.x * deltaTime;

	thePlayer->m_model->position.x += thePlayer->velocity.x * deltaTime;
}