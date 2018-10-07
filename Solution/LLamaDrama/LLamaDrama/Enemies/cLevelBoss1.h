#ifndef _cLevelBoss1_HG_
#define _cLevelBoss1_HG_
#include "cBoss.h"

class cLevelBoss1 : public cBoss
{
public:
	cLevelBoss1();
	~cLevelBoss1();
	cLevelBoss1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName);
	cLevelBoss1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name);

	void bossSpecialAttack(void);
	void bossSpecialMove(void);

};

#endif // !_cLevelBoss1_HG_
