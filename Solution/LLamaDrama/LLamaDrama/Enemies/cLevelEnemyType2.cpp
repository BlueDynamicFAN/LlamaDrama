#include "cLevelEnemyType2.h"


cLevelEnemyType2::cLevelEnemyType2()
{
	return;
}


cLevelEnemyType2::cLevelEnemyType2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->model->position = position;
	this->model->meshName = meshName;

	return;
}

cLevelEnemyType2::cLevelEnemyType2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cLevelEnemyType2(health, score, position, meshName)
{
	this->model->friendlyName = name;

	return;
}

cLevelEnemyType2::~cLevelEnemyType2(void)
{
	return;
}

void cLevelEnemyType2::move(void)
{
	return;
}

void cLevelEnemyType2::die(void)
{
	return;
}