/**
	cHealth.cpp

	Purpose: Contains the information for the cHealth class
	@author: BlueDynamic
	@version: 1.0.0
*/


#include "cHealth.h"

/**
		Default constructor
*/
cHealth::cHealth()
{
	this->type = "health";
}

/**
		Default destructor
*/
cHealth::~cHealth()
{
	delete m_model;
}

/**
		Return type of the pick up objects -- health

	@param void
	@return string
*/
std::string cHealth::getType()
{
	return this->type;
}

/**
		Sets the m_model

	@param cMeshObject* model
	@return void
*/
void cHealth::setModel(cMeshObject* model)
{
	this->m_model = model;
}

/**
		Gets the m_model instance

	@param void
	@return cMeshObject* model
*/
cMeshObject* cHealth::getModel()
{
	return m_model;
}

/**
		Sets the health pack value, how much healh would add to player's health

	@param int
	@return void
*/
void cHealth::setValue(int value)
{
	this->m_healthValue = value;
}

/**
		Gets the health pack value, how much healh would add to player's health

	@param void
	@return int
*/
int cHealth::getValue()
{
	return m_healthValue;
}

/**
		Sets the radius of the coins. vec2.x sets width, vec2.y sets hight of the health pack

	@param glm::vec2
	@return void
*/
void cHealth::setSize(glm::vec2 dimensions)
{
	this->width = dimensions.x;
	this->hight = dimensions.x;
}

/**
		Gets the radius of the coins. vec2.x is the width, and vec2.y is the hight of the health pack

	@param void
	@return glm::vec2
*/
glm::vec2 cHealth::getSize()
{
	return glm::vec2(this->width, this->hight);
}