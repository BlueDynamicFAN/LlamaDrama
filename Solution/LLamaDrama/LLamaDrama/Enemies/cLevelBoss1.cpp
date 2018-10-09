/**
	cLevelBoss1.cpp

	@author: BlueDynamic
	@version: 1.0.0
*/
#include "cLevelBoss1.h";
#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 

/**
		Default constructor
*/
cLevelBoss1::cLevelBoss1()
{

}

/**
		Default destructor
*/
cLevelBoss1::~cLevelBoss1()
{

}

/**
		cLevelBoss1 constructor

	@parm: unsigned int health, unsigned int score, glm::vec3 position, std::string meshName
*/
cLevelBoss1::cLevelBoss1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->m_model->position = position;
	this->m_model->meshName = meshName;
	this->m_model->objColour = glm::vec3(1.0f, 1.0f, 0.0f);

	return;
}

/**
		cLevelBoss1 constructor

	@parm: unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name
*/
cLevelBoss1::cLevelBoss1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cLevelBoss1(health, score, position, meshName)
{
	this->m_model->friendlyName = name;

	return;
}


/**
		Overrides the base class method. Describes the level 1 boss special attack.

	@parm: void
	@retun: void
*/
void cLevelBoss1::bossSpecialAttack(void)
{
	return;
}

/**
		Overrides the base class method. Describes the level 1 boss special move

	@parm: void
	@retun: void
*/
void cLevelBoss1::bossSpecialMove(void)
{
	return;
}