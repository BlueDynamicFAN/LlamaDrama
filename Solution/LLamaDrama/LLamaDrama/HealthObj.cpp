#include "HealthObj.h"

HealthObj::HealthObj()
{
}


HealthObj::~HealthObj()
{
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