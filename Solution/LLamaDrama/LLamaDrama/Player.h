#ifndef _Player_HG_
#define _Player_HG_
#include <string>
#include "../cMeshObject.h"
//#include <glm/glm.hpp>
//#include <glm/vec3.hpp>

class Player
{
public:
	Player()
	{
		this->m_model = new cMeshObject();
		this->m_model->objColour = glm::vec3(1.0f, 1.0f, 1.0f);
		this->velocity = glm::vec3(1.0f, 0.0f, 0.0f);
		this->accel = glm::vec3(0.0f, -9.8f, 0.0f);
	}
	~Player() { ; }

	Player(std::string meshName, std::string fName, glm::vec3 position) : Player()
	{
		this->m_model->meshName = meshName;
		this->m_model->friendlyName = fName;
		this->m_model->position = position;
	}

	cMeshObject* m_model;
	glm::vec3 velocity;
	glm::vec3 accel;
};

#endif


