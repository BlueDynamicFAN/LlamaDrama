#ifndef _cBoss_HG_
#define _cBoss_HG_
#include "cEnemy.h"
#include "iEnemy.h"


class cBoss : public cEnemy, public iEnemy
{
public:
	cBoss();
	~cBoss();

	void bossAttack();
	void bossMove();
	void die();

	void bossSpecialAttack(void) { ; }
	void bossSpecialMove(void) { ; }
};

#endif // !_cBoss_HG_