#ifndef _cEnemyFactory_HG_
#define _cEnemyFactory_HG_
#include <string>
#include "iEnemy.h"
#include "cEnemy.h"

class cEnemyFactory {
public:
	cEnemyFactory();
	~cEnemyFactory();
	
	bool isEnemyTypeValid(std::string enemyType);
	iEnemy* createEnemy(std::string enemyType);
};

#endif // !_cEnemyFactory_HG_#pragma once
