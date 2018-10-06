#ifndef _cBoss_HG_
#define _cBoss_HG_
#include "cEnemy.h"

class cBoss : public cEnemy
{
public:
	cBoss();
	~cBoss();

	void bossAttack();
	void bossMove();

	virtual void bossSpecialAttack();
	virtual void bossSpecialMove();

};

#endif // !_cBoss_HG_