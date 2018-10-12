/**
	cLevelEnemyType1.cpp

	Purpose: Contains the information for the simple enemy in level 1
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

	@parm: health level, score value of enemy, position in the screem and mesh file name
*/
cLevelEnemyType1::cLevelEnemyType1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->m_model->m_position = position;
	this->m_model->m_meshName = meshName;

	return;
}

/**
		cLevelEnemyType1 constructor

	@parm: health level, score value of enemy, position in the screem, mesh file name, and friendly name of the mesh
*/
cLevelEnemyType1::cLevelEnemyType1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string fname) : cLevelEnemyType1(health, score, position, meshName)
{
	this->m_model->m_friendlyName = fname;

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