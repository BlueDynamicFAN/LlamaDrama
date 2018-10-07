#ifndef _cBoss_HG_
#define _cBoss_HG_
#include "cEnemy.h"


class cBoss : public cEnemy
{
public:
	cBoss();
	virtual ~cBoss();

	void bossAttack(void);
	void bossMove(void);
	void die(void);

	virtual void bossSpecialAttack(void) { ; }
	virtual void bossSpecialMove(void) { ; }
};

#endif // !_cBoss_HG_