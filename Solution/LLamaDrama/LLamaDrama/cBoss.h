#ifndef _cBoss_HG_
#define _cBoss_HG_
#include "cEnemy.h"

class cBoss : public cEnemy
{
public:
	cBoss();
	cBoss(glm::vec3 position, glm::vec3 color, std::string name);
	cBoss(glm::vec3 position, glm::vec3 color, std::string name, std::string meshName);

private:
	std::string meshName = "Dodecahedron.ply";
};

#endif // !_cBoss_HG_