#include "cLevelEnemyType1.h"


cLevelEnemyType1::cLevelEnemyType1()
{
	return;
}

cLevelEnemyType1::cLevelEnemyType1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->model->position = position;
	this->model->meshName = meshName;

	return;
}

cLevelEnemyType1::cLevelEnemyType1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cLevelEnemyType1(health, score, position, meshName)
{
	this->model->friendlyName = name;

	return;
}

cLevelEnemyType1::~cLevelEnemyType1()
{
	return;
}

void cLevelEnemyType1::attack()
{
	return;
}