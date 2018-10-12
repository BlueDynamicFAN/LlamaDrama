/**
	cLevelBoss1.h

	Purpose: Contains the information for the level-boss in level 1
	@author: BlueDynamic
	@version: 1.0.0
*/
#ifndef _cLevelBoss1_HG_
#define _cLevelBoss1_HG_
#include "cBoss.h"

class cLevelBoss1 : public cBoss
{
public:
	cLevelBoss1();
	~cLevelBoss1();
	cLevelBoss1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName);
	cLevelBoss1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string fname);

	void bossSpecialAttack(void);
	void bossSpecialMove(void);

};

#endif // !_cLevelBoss1_HG_
