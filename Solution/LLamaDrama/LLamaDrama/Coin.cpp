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