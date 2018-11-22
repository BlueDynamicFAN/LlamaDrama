/**
	Coin.cpp

	Purpose: Contains the information for the Coin class
	@author: BlueDynamic
	@version: 1.0.0
*/

#include "cCoin.h"

/**
		Default constructor
*/
cCoin::cCoin()
{
	this->type = "coin";
}

/**
		Default destructor
*/
cCoin::~cCoin()
{
	delete m_model;
}

/**
		Return type of the pick up objects -- coin

	@param void
	@return string
*/
std::string cCoin::getType()
{
	return this->type;
}

/**
		Sets the m_model

	@param cMeshObject* model
	@return void
*/
void cCoin::setModel(cMeshObject* model)
{
	this->m_model = model;
}

/**
		Gets the m_model instance

	@param void
	@return cMeshObject* model
*/
cMeshObject* cCoin::getModel()
{
	return m_model;
}

/**
		Sets the coins value, how much coin would add for playr score

	@param int
	@return void
*/
void cCoin::setValue(int value)
{
	this->m_moneyValue = value;
}

/**
		Gets the coins value, how much coin would add for playr score

	@param void
	@return int
*/
int cCoin::getValue()
{
	return m_moneyValue;
}

/**
		Sets the radius of the coins. Both vec2 params are the same. 

	@param glm::vec2
	@return void
*/
void cCoin::setSize(glm::vec2 dimensions)
{
	this->radius = dimensions.x;
}

/**
		Return the radius of the coins. Both vec2 would be equel the raduis of the coin

	@param void
	@return glm::vec2
*/
glm::vec2 cCoin::getSize()
{
	return glm::vec2(radius, radius);
}