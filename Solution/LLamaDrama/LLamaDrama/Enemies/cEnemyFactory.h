#ifndef _cEnemyFactory_HG_
#define _cEnemyFactory_HG_
#include <string>
#include "cEnemy.h"

class cEnemyFactory {
public:
	cEnemyFactory();
	~cEnemyFactory();
	
	bool isEnemyTypeValid(std::string enemyType);
	cEnemy* createEnemy(std::string enemyType);
};

#endif // !_cEnemyFactory_HG_#pragma once
