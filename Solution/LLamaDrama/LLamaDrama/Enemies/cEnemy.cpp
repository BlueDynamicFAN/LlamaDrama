/**
	cEnemy.cpp

	@author: BlueDynamic
	@version: 1.0.0
*/
#include "cEnemy.h"
#include<algorithm>
#include<iostream>

/**
		Default constructor
*/
cEnemy::cEnemy() 
{
	this->m_healthLevel = 0;
	this->m_scoreValue = 0;
	this->m_model = new cMeshObject;
	return;
}

/**
		Default destructor
*/
cEnemy:: ~cEnemy()
{
	return;
}

/**
			Returns the current health level

	@param void
	@return m_healthLevel
*/

int cEnemy::getHealthLevel(void) 
{
	return this->m_healthLevel;
}

/**
			Changes the current health level on passed parameter

	@param levelChange
	@return void
*/

void cEnemy::setHealthLevel(int levelChange) 
{
	this->m_healthLevel += levelChange;
}

/**
			Returns how much score the enemy is valued.

	@param void
	@return m_scoreValue
*/

int cEnemy::getScoreValue(void)
{
	return this->m_scoreValue;
}

/**
			Removes enemy from the screen.

	@param void
	@return void
*/

void cEnemy::die(void) 
{
	return;
}