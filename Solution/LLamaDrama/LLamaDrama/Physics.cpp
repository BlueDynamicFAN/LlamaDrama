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

/**
	Checks if the player is on top of a platform

	@param: void
	@return: true or false
*/
bool isPlayerOnTopOfAPlatform()
{
	const float EPSILON = 0.05f;
	const float OFFSET = 0.1f;
	for (std::vector <cPlatform*>::iterator itPlatform = pPlatforms.begin();
		itPlatform != pPlatforms.end(); itPlatform++)
	{
		cPlatform* thePlatform = *itPlatform;
		float yLimit = thePlatform->m_model->m_position.y + (thePlatform->m_height) / 2;
		bool inYLimit = abs(thePlayer->getPosition().y - yLimit) <= EPSILON;
		/*bool inXLimitsNeg = (thePlayer->getPosition().x >= thePlatform->m_model->m_position.x - thePlatform->m_width / 2);
		bool inXLimitsPos = (thePlayer->getPosition().x <= thePlatform->m_model->m_position.x + thePlatform->m_width / 2);*/
		bool inXLimitsNeg = (thePlayer->getPosition().x + OFFSET >= thePlatform->m_model->m_position.x - thePlatform->m_width / 2);
		bool inXLimitsPos = (thePlayer->getPosition().x - OFFSET <= thePlatform->m_model->m_position.x + thePlatform->m_width / 2);
		if (inYLimit && inXLimitsNeg && inXLimitsPos)
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

	thePlayer->setVelocityY(thePlayer->getVelocity().y + (thePlayer->getAccel().y * deltaTime));

	thePlayer->setPositionY(thePlayer->getPosition().y + (thePlayer->getVelocity().y * deltaTime));

	//The object can't go any lower than "the ground"
	if (isPlayerOnTopOfAPlatform())
	{
		thePlayer->setVelocityY(0.0f);
		thePlayer->setAccelY(0.0f);
	}
	else {
		thePlayer->setAccelY(-9.8f);
	}

	return;
}

/**
	Updates the movement of the player on user input

	@param: the time
	@return: void
*/
void movesUpdate(double deltaTime)
{
	const double LARGEST_DELTATIME = 0.10; //10 ms = 10Hz
	if (deltaTime > LARGEST_DELTATIME) {
		deltaTime = LARGEST_DELTATIME;
	}

	thePlayer->setVelocityX(thePlayer->getVelocity().x + (thePlayer->getAccel().x * deltaTime));

	thePlayer->setPositionX(thePlayer->getPosition().x + (thePlayer->getVelocity().x * deltaTime));
}