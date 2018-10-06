#ifndef _cEnemy_HG_
#define _cEnemy_HG_
#include <string>
#include "cMeshObject.h"
#include <vector>

class cEnemy {
public:
	cEnemy();
	virtual ~cEnemy();
	int getHealthLevel();
	void setHealthLevel(int levelChange);
	int getScoreValue();
	void die(void);

	cMeshObject* model;

protected:
	unsigned int m_healthLevel;
	unsigned int m_scoreValue;
};

#endif // !_cEnemy_HG_

