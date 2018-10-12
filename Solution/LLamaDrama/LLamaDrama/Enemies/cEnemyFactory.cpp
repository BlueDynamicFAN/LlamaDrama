/**
	cEnemyFactory.cpp

	Purpose: Contains the information of EnemyFactory
	@author: BlueDynamic
	@version: 1.0.0
*/
#include "cEnemyFactory.h"
#include "cLevelEnemyType1.h"
#include "cLevelEnemyType2.h"
#include "clevelBoss1.h"
#include "clevelBoss2.h"
#include "cFinalBoss.h"
#include "cEnemy.h"

#include <vector>
#include <iostream>
#include <algorithm>

/**
		Default constructor
*/
cEnemyFactory::cEnemyFactory()
{
	return;
}

/**
		Default destructor
*/
cEnemyFactory::~cEnemyFactory()
{
	return;
}

/**
			Checking if provided enemy type is correct. 

	@param enemy type
	@return true or false
*/
bool cEnemyFactory::isEnemyTypeValid(std::string enemyType)
{
	std::vector<std::string> enemyTypes = {"levelboss1", "levelboss2", "finalboss", "levelenemytype1", "levelenemytype2"};
	for (std::vector<std::string>::iterator itType = enemyTypes.begin(); itType != enemyTypes.end(); itType++)
	{
		std::string temp = *itType;

		if (temp == enemyType)
		{
			return true;
		}
	}
	std::cerr << "Error:: invalid enemy type" << std::endl;
	return false;
}

/**
			Creates a cEnemy according to type provided in params

	@param Enemy type, health level, score value of the enemy, position, name of the mesh file, friendly mesh name
	@return cEnemy*
*/
cEnemy* cEnemyFactory::createEnemy(std::string enemyType, unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string fname)
{
	cEnemy* newEnemy = nullptr;
	std::transform(enemyType.begin(), enemyType.end(), enemyType.begin(), ::tolower);

	if (isEnemyTypeValid(enemyType))
	{
		if (enemyType == "levelboss1")
		{
			std::cout << "I am in create boss 1" << std::endl;
			newEnemy = new cLevelBoss1(health, score, position, meshName, fname);
		}
		else if (enemyType == "levelboss2")
		{
			newEnemy = new cLevelBoss2(health, score, position, meshName, fname);
		}
		else if (enemyType == "finalboss")
		{
			std::cout << "I am in create bosfinals" << std::endl;
			newEnemy = new cFinalBoss(health, score, position, meshName, fname);
		}
		else if (enemyType == "levelenemytype1")
		{
			newEnemy = new cLevelEnemyType1(health, score, position, meshName, fname);
		}
		else if (enemyType == "levelenemytype2")
		{
			newEnemy = new cLevelEnemyType2(health, score, position, meshName, fname);
		}
	}
	
	return newEnemy;
}