#ifndef _cLevelEnemyType1_HG_
#define _cLevelEnemyType1_HG_
#include "cEnemy.h"

class cLevelEnemyType1 : public cEnemy
{
public:
	cLevelEnemyType1();
	~cLevelEnemyType1();

	cLevelEnemyType1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName);
	cLevelEnemyType1(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name);

	void attack(void);
	void die(void);
};

#endif // !_cLevelEnemyType1_HG_

