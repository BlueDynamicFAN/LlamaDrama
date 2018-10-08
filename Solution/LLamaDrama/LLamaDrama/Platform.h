#ifndef _Platform_HG_
#define _Platform_HG_
#include <string>
#include "../cMeshObject.h"

class Platform
{
public:
	Platform()
	{
		this->model = new cMeshObject;
		this->height = 0.0f;
		this->width = 0.0f;
		return;
	}

	Platform(std::string meshName, std::string fName, float h, float w, glm::vec3 position, glm::vec3 colour) : Platform()
	{
		this->height = h;
		this->width = w;
		this->model->meshName = meshName;
		this->model->friendlyName = fName;
		this->model->position = position;
		this->model->objColour = colour;
		return;
	}
	~Platform() { ; }

	float height;
	float width;
	cMeshObject* model;
};

#endif // !_Platform_HG_

