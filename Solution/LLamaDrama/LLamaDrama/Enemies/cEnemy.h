#ifndef _cEnemy_HG_
#define _cEnemy_HG_
#include <string>
#include "../cMeshObject.h"

class cEnemy
{
public:
	cEnemy();
	virtual ~cEnemy();
	virtual void die(void);

	int getHealthLevel(void);
	void setHealthLevel(int levelChange);
	int getScoreValue(void);

	cMeshObject* model;

protected:
	unsigned int m_healthLevel;
	unsigned int m_scoreValue;
};

#endif // !_cEnemy_HG_

