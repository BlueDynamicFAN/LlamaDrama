#include "cBoss.h"

cBoss::cBoss() 
{
	this->m_healthLevel = 0;
	this->m_scoreValue = 0;
	this->model=nullptr;

	return;
}

cBoss::~cBoss()
{

}

cBoss::cBoss(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->model->position = position;
	this->model->meshName = meshName;

	return;
}

cBoss::cBoss(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cBoss(health, score, position, meshName)
{
	this->model->friendlyName = name;

	return;
}

void cBoss::bossAttack()
{
	return;
}
void cBoss::bossMove()
{
	return;
}

void cBoss::bossSpecialAttack()
{
	return;
}
void cBoss::bossSpecialMove()
{
	return;
}
