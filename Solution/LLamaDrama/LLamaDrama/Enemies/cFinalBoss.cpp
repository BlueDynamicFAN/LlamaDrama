/**
	cFinalBoss.cpp

	Purpose: Contains the information for the Final boss
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

	@parm: health level, score value of enemy, position in the screem and mesh file name
*/
cFinalBoss::cFinalBoss(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->m_model->m_position = position;
	this->m_model->m_meshName = meshName;

	return;
}

/**
		cFinalBoss constructor

	@parm: health level, score value of enemy, position in the screem, mesh file name, and friendly name of the mesh
*/
cFinalBoss::cFinalBoss(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string fname) : cFinalBoss(health, score, position, meshName)
{
	this->m_model->m_friendlyName = fname;

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