#include "cBoss.h"

cBoss::cBoss() 
{
	this->setHealthLevel(100);
	this->model.meshName = this->meshName;
	this->model.bIsWireFrame = true;
}

cBoss::cBoss(glm::vec3 position, glm::vec3 color, std::string name) : cBoss() 
{
	this->model.position = position;
	this->model.objColour = color;
	this->model.friendlyName = name;
}

cBoss::cBoss(glm::vec3 position, glm::vec3 color, std::string name, std::string meshName) : cBoss(position, color, name) 
{
	this->model.meshName = meshName;
}
