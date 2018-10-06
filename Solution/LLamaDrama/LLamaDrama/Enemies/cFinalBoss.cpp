#include "cFinalBoss.h";

cFinalBoss::cFinalBoss()
{

}

cFinalBoss::~cFinalBoss()
{

}

cFinalBoss::cFinalBoss(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->model->position = position;
	this->model->meshName = meshName;

	return;
}

cFinalBoss::cFinalBoss(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cFinalBoss(health, score, position, meshName)
{
	this->model->friendlyName = name;

	return;
}

void cFinalBoss::bossSpecialAttack()
{
	return;
}
void cFinalBoss::bossSpecialMove()
{
	return;
}