#ifndef _iEnemy_HG_
#define _iEnemy_HG_
#include <string>
#include "../cMeshObject.h"
#include <vector>

class iEnemy {
public:
	//iEnemy() {};
	virtual ~iEnemy() {};
	virtual void die(void) = 0;
};

#endif // !_iEnemy_HG_