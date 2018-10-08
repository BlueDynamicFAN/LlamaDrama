//Psysics.cpp
#include "global.h"
#include <glm/glm.hpp>
#include "sMOdelDrawInfo.h"
#include <algorithm>
#include <iostream>
#include <vector>

const float GROUND_PLANE_Y = -3.0f;

//Called every frame
void DoPhysicsUpdate(double deltaTime)
{
	const double LARGEST_DELTATIME = 0.10; //10 ms = 10Hz
	if (deltaTime > LARGEST_DELTATIME) {
		deltaTime = LARGEST_DELTATIME;
	}

		//Euler integration
		float delatX;

		//thePlayer->velocity.x += thePlayer->accel.x * deltaTime;
		thePlayer->velocity.y += thePlayer->accel.y * deltaTime;
		//thePlayer->velocity.z += thePlayer->accel.z * deltaTime;

		//thePlayer->m_model->position.x += thePlayer->velocity.x * deltaTime;
		thePlayer->m_model->position.y += thePlayer->velocity.y * deltaTime;
		//thePlayer->m_model->position.z += thePlayer->velocity.z * deltaTime;

		//The object can't go any lower than "the ground"

		
		for (std::vector <Platform*>::iterator itPlatform = pPlatforms.begin();
			itPlatform != pPlatforms.end(); itPlatform++)
		{
			Platform* tempPlatform = *itPlatform;
			float yLimit = tempPlatform->model->position.y + (tempPlatform->height) / 2;
			bool inXLimitsNeg = (thePlayer->m_model->position.x >= tempPlatform->model->position.x - tempPlatform->width / 2);
			bool inXLimitsPos = (thePlayer->m_model->position.x <= tempPlatform->model->position.x + tempPlatform->width / 2);

			if ((thePlayer->m_model->position.y <= yLimit) && inXLimitsNeg && inXLimitsPos)
			{
				//normal to the ground level is 0, 1, 0 (1 in the y)
				//glm::vec3 normalToGraound = glm::vec3(0.0f, 1.0f, 0.0f);

				thePlayer->velocity.y = 0.0;
				thePlayer->accel.y = 0.0;
				break;
			}
			else {
				thePlayer->accel.y = -9.8;
			}
		}

	return;
}

void DoMovingsUpdate(double deltaTime)
{
	const double LARGEST_DELTATIME = 0.10; //10 ms = 10Hz
	if (deltaTime > LARGEST_DELTATIME) {
		deltaTime = LARGEST_DELTATIME;
	}

	//Euler integration
	//float delatX;

	thePlayer->velocity.x += thePlayer->accel.x * deltaTime;
	//thePlayer->velocity.y += thePlayer->accel.y * deltaTime;

	thePlayer->m_model->position.x += thePlayer->velocity.x * deltaTime;
	//thePlayer->m_model->position.y += thePlayer->velocity.y * deltaTime;
}