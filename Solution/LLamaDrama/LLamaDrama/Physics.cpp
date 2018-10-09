//Psysics.cpp
#include "global.h"
#include <glm/glm.hpp>
#include "sMOdelDrawInfo.h"
#include <algorithm>
#include <iostream>
#include <vector>

const float GROUND_PLANE_Y = -3.0f;

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


//Called every frame
void gravityUpdate(double deltaTime)
{
	const double LARGEST_DELTATIME = 0.10; //10 ms = 10Hz
	if (deltaTime > LARGEST_DELTATIME) 
	{
		deltaTime = LARGEST_DELTATIME;
	}

		//thePlayer->velocity.x += thePlayer->accel.x * deltaTime;
		thePlayer->velocity.y += thePlayer->accel.y * deltaTime;

		//thePlayer->m_model->position.x += thePlayer->velocity.x * deltaTime;
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

void movingsUpdate(double deltaTime)
{
	const double LARGEST_DELTATIME = 0.10; //10 ms = 10Hz
	if (deltaTime > LARGEST_DELTATIME) {
		deltaTime = LARGEST_DELTATIME;
	}

	thePlayer->velocity.x += thePlayer->accel.x * deltaTime;

	thePlayer->m_model->position.x += thePlayer->velocity.x * deltaTime;
}