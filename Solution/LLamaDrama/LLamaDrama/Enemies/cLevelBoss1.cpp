/**
	cLevelBoss1.cpp

	Purpose: Contains the information for the level-boss in level 1
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

	@parm: health level, score value of enemy, position in the screem and mesh file name
*/
cLevelBoss1::cLevelBoss1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->m_model->m_position = position;
	this->m_model->m_meshName = meshName;
	this->m_model->m_objColour = glm::vec3(1.0f, 1.0f, 0.0f); //Will be removed when we will add textures

	return;
}

/**
		cLevelBoss1 constructor

	@parm: health level, score value of enemy, position in the screem, mesh file name, and friendly name of the mesh
*/
cLevelBoss1::cLevelBoss1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string fname) : cLevelBoss1(health, score, position, meshName)
{
	this->m_model->m_friendlyName = fname;

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