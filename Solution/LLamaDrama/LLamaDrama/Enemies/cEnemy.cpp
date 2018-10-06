#include "cEnemy.h"
#include<algorithm>
#include<iostream>

cEnemy::cEnemy() 
{
	this->m_healthLevel = 0;
	this->m_scoreValue = 0;
	this->model->meshName = "Not assigned";
	this->model->friendlyName = "NA";
	return;
}

cEnemy:: ~cEnemy()
{
	return;
}

int cEnemy::getHealthLevel() 
{
	return this->m_healthLevel;
}

void cEnemy::setHealthLevel(int levelChange) 
{
	this->m_healthLevel += levelChange;
}

int cEnemy::getScoreValue()
{
	return this->m_scoreValue;
}


void cEnemy::die(void) 
{
	return;
}