/**
	cLevelEnemyType2.cpp

	@author: BlueDynamic
	@version: 1.0.0
*/
#include "cLevelEnemyType2.h"

/**
		Default constructor
*/
cLevelEnemyType2::cLevelEnemyType2()
{
	return;
}

/**
		Default destructor
*/
cLevelEnemyType2::~cLevelEnemyType2(void)
{
	return;
}

/**
		cLevelEnemyType2 constructor

	@parm: unsigned int health, unsigned int score, glm::vec3 position, std::string meshName
*/
cLevelEnemyType2::cLevelEnemyType2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->m_model->m_position = position;
	this->m_model->m_meshName = meshName;

	return;
}

/**
		cLevelEnemyType2 constructor

	@parm: unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name
*/
cLevelEnemyType2::cLevelEnemyType2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cLevelEnemyType2(health, score, position, meshName)
{
	this->m_model->m_friendlyName = name;

	return;
}

/**
		Describes the level 2 enemies movement.

	@parm: void
	@retun: void
*/
void cLevelEnemyType2::move(void)
{
	return;
}

/**
		Describes the way enemies die in level 2.

	@parm: void
	@retun: void
*/
void cLevelEnemyType2::die(void)
{
	return;
}