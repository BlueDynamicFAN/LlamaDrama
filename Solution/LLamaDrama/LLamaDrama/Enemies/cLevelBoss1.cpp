#include "cLevelBoss1.h";
#include <iostream>

cLevelBoss1::cLevelBoss1()
{
	std::cout << "I am in cLevelBoss1" << std::endl;
}

cLevelBoss1::~cLevelBoss1()
{

}

cLevelBoss1::cLevelBoss1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->model->position = position;
	this->model->meshName = meshName;

	return;
}

cLevelBoss1::cLevelBoss1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cLevelBoss1(health, score, position, meshName)
{
	this->model->friendlyName = name;

	return;
}

void cLevelBoss1::bossSpecialAttack(void)
{
	return;
}
void cLevelBoss1::bossSpecialMove(void)
{
	return;
}