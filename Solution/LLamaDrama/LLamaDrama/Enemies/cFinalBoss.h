#ifndef _cFinalBoss_HG_
#define _cFinalBoss_HG_
#include "cBoss.h"

class cFinalBoss : public cBoss
{
public:
	cFinalBoss();
	~cFinalBoss();
	cFinalBoss(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName);
	cFinalBoss(unsigned int health, unsigned int score, glm::vec3 position, std::string meshName, std::string name);

	void die(void);
	void bossSpecialAttack(void);
	void bossSpecialMove(void);


};

#endif // !_cFinalBoss_HG_

