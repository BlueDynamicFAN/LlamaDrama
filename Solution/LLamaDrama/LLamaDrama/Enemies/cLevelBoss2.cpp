#include "cLevelBoss2.h";

cLevelBoss2::cLevelBoss2()
{

}

cLevelBoss2::~cLevelBoss2()
{

}

cLevelBoss2::cLevelBoss2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName)
{
	this->m_healthLevel = health;
	this->m_scoreValue = score;
	this->model->position = position;
	this->model->meshName = meshName;

	return;
}

cLevelBoss2::cLevelBoss2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name) : cLevelBoss2(health, score, position, meshName)
{
	this->model->friendlyName = name;

	return;
}

void cLevelBoss2::bossSpecialAttack()
{
	return;
}
void cLevelBoss2::bossSpecialMove()
{
	return;
}