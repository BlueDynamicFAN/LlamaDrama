/**
	cEnemy.h

	Purpose: Contains the information for the generic enemy
	@author: BlueDynamic
	@version: 1.0.0
*/
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

	cMeshObject* m_model;

protected:
	unsigned int m_healthLevel;
	unsigned int m_scoreValue;
};

#endif // !_cEnemy_HG_

