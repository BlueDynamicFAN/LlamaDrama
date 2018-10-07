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

cEnemyFactory::cEnemyFactory()
{
	return;
}
cEnemyFactory::~cEnemyFactory()
{
	return;
}

bool cEnemyFactory::isEnemyTypeValid(std::string enemyType)
{
	std::vector<std::string> enemyTypes = {"levelboss1", "levelboss2", "finalboss", "levelenemytype1", "levelenemytype2"};
	//std::transform(enemyType.begin(), enemyType.end(), enemyType.begin(), ::tolower);

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
cEnemy* cEnemyFactory::createEnemy(std::string enemyType, unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name)
{
	cEnemy* newEnemy = nullptr;

	std::cout << "I am in createEnemy" << std::endl;
	if(true)
	//if (isEnemyTypeValid(enemyType))
	{
		if (enemyType == "levelboss1")
		{
			std::cout << "I am in create boss 1" << std::endl;
			newEnemy = new cLevelBoss1(health, score, position, meshName, name);
		}
		else if (enemyType == "levelboss2")
		{
			newEnemy = new cLevelBoss2(health, score, position, meshName, name);
		}
		else if (enemyType == "finalboss")
		{
			std::cout << "I am in create bosfinals" << std::endl;
			newEnemy = new cFinalBoss(health, score, position, meshName, name);
		}
		else if (enemyType == "levelenemytype1")
		{
			newEnemy = new cLevelEnemyType1(health, score, position, meshName, name);
		}
		else if (enemyType == "levelenemytype2")
		{
			newEnemy = new cLevelEnemyType2(health, score, position, meshName, name);
		}
	}
	
	return newEnemy;
}