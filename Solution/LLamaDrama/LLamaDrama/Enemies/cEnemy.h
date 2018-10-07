#ifndef _cEnemy_HG_
#define _cEnemy_HG_
#include <string>
#include "../cMeshObject.h"
#include "iEnemy.h"

class cEnemy// : public iEnemy 
{
public:
	cEnemy();
	~cEnemy();
	int getHealthLevel(void);
	void setHealthLevel(int levelChange);
	int getScoreValue(void);
	//void die(void);

	cMeshObject* model;

protected:
	unsigned int m_healthLevel;
	unsigned int m_scoreValue;
};

#endif // !_cEnemy_HG_

