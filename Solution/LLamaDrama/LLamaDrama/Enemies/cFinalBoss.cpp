/**
	cFinalBoss.cpp

	@author: BlueDynamic
	@version: 1.0.0
*/
#include "cFinalBoss.h";
#include <iostream>

/**
		Default constructor
*/
cFinalBoss::cFinalBoss()
{
	std::cout << "I am in finalBoss" << std::endl;
}

/**
		Default destructor
*/
cFinalBoss::~cFinalBoss()
{

}

/**
		cFinalBoss constructor

	@parm: unsigned int health, unsigned int score, glm::vec3 position, std::string meshName
*/
cFinalBoss::cFinalBoss(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->m_model->position = position;
	this->m_model->meshName = meshName;

	return;
}

/**
		cFinalBoss constructor

	@parm: unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name
*/
cFinalBoss::cFinalBoss(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cFinalBoss(health, score, position, meshName)
{
	this->m_model->friendlyName = name;

	return;
}

/**
		Overrides the base class method. Describes the final-boss special attack.

	@parm: void
	@retun: void
*/
void cFinalBoss::bossSpecialAttack(void)
{
	return;
}

/**
		Overrides the base class method. Describes the final-boss special move

	@parm: void
	@retun: void
*/
void cFinalBoss::bossSpecialMove(void)
{
	return;
}