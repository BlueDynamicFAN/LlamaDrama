/**
	cLevelEnemyType1.cpp

	@author: BlueDynamic
	@version: 1.0.0
*/
#include "cLevelEnemyType1.h"
#include <iostream>

/**
		Default constructor
*/
cLevelEnemyType1::cLevelEnemyType1()
{
	std::cout << "I am in cLevelEnemyType1" << std::endl;
	return;
}

/**
		Default destructor
*/
cLevelEnemyType1::~cLevelEnemyType1()
{

}

/**
		cLevelEnemyType1 constructor

	@parm: unsigned int health, unsigned int score, glm::vec3 position, std::string meshName
*/
cLevelEnemyType1::cLevelEnemyType1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->m_model->position = position;
	this->m_model->meshName = meshName;

	return;
}

/**
		cLevelEnemyType1 constructor

	@parm: unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name
*/
cLevelEnemyType1::cLevelEnemyType1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cLevelEnemyType1(health, score, position, meshName)
{
	this->m_model->friendlyName = name;

	return;
}

/**
		Describes the level 1 enemies attack.

	@parm: void
	@retun: void
*/
void cLevelEnemyType1::attack(void)
{
	return;
}

/**
		Describes the way enemies die.

	@parm: void
	@retun: void
*/
void cLevelEnemyType1::die(void)
{
	return;
}