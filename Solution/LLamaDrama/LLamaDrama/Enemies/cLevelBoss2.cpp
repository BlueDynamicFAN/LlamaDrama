/**
	cLevelBoss2.cpp

	@author: BlueDynamic
	@version: 1.0.0
*/
#include "cLevelBoss2.h";

/**
		Default constructor
*/
cLevelBoss2::cLevelBoss2()
{
	return;
}

/**
		Default destructor
*/
cLevelBoss2::~cLevelBoss2()
{
	return;
}

/**
		cLevelBoss2 constructor

	@parm: unsigned int health, unsigned int score, glm::vec3 position, std::string meshName
*/
cLevelBoss2::cLevelBoss2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->m_model->m_position = position;
	this->m_model->m_meshName = meshName;

	return;
}

/**
		cLevelBoss2 constructor

	@parm: unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name
*/
cLevelBoss2::cLevelBoss2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cLevelBoss2(health, score, position, meshName)
{
	this->m_model->m_friendlyName = name;

	return;
}

/**
		Overrides the base class method. Describes the level 2 boss special attack.

	@parm: void
	@retun: void
*/
void cLevelBoss2::bossSpecialAttack(void)
{
	return;
}

/**
		Overrides the base class method. Describes the level 1 boss special move

	@parm: void
	@retun: void
*/
void cLevelBoss2::bossSpecialMove(void)
{
	return;
}