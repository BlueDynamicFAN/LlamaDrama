#include "HealthObj.h"

HealthObj::HealthObj()
{
	this->type = "health";
}


HealthObj::~HealthObj()
{
}

std::string HealthObj::getType()
{
	return this->type;
}

void HealthObj::setModel(cMeshObject* model)
{
	this->m_model = model;
}

cMeshObject* HealthObj::getModel()
{
	return m_model;
}

void HealthObj::setValue(int value)
{
	this->m_healthValue = value;
}

int HealthObj::getValue()
{
	return m_healthValue;
}

void HealthObj::setSize(glm::vec2 dimensions)
{
	this->width = dimensions.x;
	this->hight = dimensions.x;
}
glm::vec2 HealthObj::getSize()
{
	return glm::vec2(this->width, this->hight);
}