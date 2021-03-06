/**
	cLevelBoss2.h

	Purpose: Contains the information for the level-boss in level 2
	@author: BlueDynamic
	@version: 1.0.0
*/
#ifndef _cLevelBoss2_HG_
#define _cLevelBoss2_HG_
#include "cBoss.h"

class cLevelBoss2 : public cBoss
{
public:
	cLevelBoss2();
	~cLevelBoss2();
	cLevelBoss2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName);
	cLevelBoss2(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string fname);

	void bossSpecialAttack(void);
	void bossSpecialMove(void);

};

#endif // !_cLevelBoss2_HG_
