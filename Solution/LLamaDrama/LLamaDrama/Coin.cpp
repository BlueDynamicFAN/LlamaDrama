#include "Coin.h"

Coin::Coin()
{
}

Coin::~Coin()
{
}

void Coin::setModel(cMeshObject* model)
{
	this->m_model = model;
}

cMeshObject* Coin::getModel()
{
	return m_model;
}

void Coin::setValue(int value)
{
	this->m_moneyValue = value;
}

int Coin::getValue()
{
	return m_moneyValue;
}

void Coin::setSize(glm::vec2 dimensions)
{
	this->radius = dimensions.x;
}
glm::vec2 Coin::getSize()
{
	return glm::vec2(radius, radius);
}