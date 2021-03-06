/**
	cLevelEnemyType2.h

	Purpose: Contains the information for the simple enemy in level 2
	@author: BlueDynamic
	@version: 1.0.0
*/
#ifndef _cLevelEnemyType2_HG_
#define _cLevelEnemyType2_HG_
#include "cEnemy.h"

class cLevelEnemyType2 : public cEnemy
{
public:
	cLevelEnemyType2();
	~cLevelEnemyType2();

	cLevelEnemyType2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName);
	cLevelEnemyType2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string fname);

	void move(void);
	void die(void);
};

#endif // !_cLevelEnemyType2_HG_
