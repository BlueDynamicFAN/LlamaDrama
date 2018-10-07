#include "cLevelEnemyType1.h"
#include <iostream>


cLevelEnemyType1::cLevelEnemyType1()
{
	std::cout << "I am in cLevelEnemyType1" << std::endl;
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

cLevelEnemyType1::~cLevelEnemyType1(void)
{
	return;
}

void cLevelEnemyType1::attack(void)
{
	return;
}

void cLevelEnemyType1::die(void)
{
	return;
}