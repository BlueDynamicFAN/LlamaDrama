/**
	cEnemyFactory.h

	@author: BlueDynamic
	@version: 1.0.0
*/
#ifndef _cEnemyFactory_HG_
#define _cEnemyFactory_HG_
#include <string>
#include "cEnemy.h"

class cEnemyFactory {
public:
	cEnemyFactory();
	~cEnemyFactory();
	
	bool isEnemyTypeValid(std::string enemyType);
	cEnemy* createEnemy(std::string enemyType, unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name);

};

#endif // !_cEnemyFactory_HG_#pragma once
