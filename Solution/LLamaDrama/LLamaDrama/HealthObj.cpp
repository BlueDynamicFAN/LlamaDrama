/**
	HealthObj.cpp

	Purpose: Contains the information for the HealthObj class
	@author: BlueDynamic
	@version: 1.0.0
*/


#include "HealthObj.h"

/**
		Default constructor
*/
HealthObj::HealthObj()
{
	this->type = "health";
}

/**
		Default destructor
*/
HealthObj::~HealthObj()
{
	delete m_model;
}

/**
		Return type of the pick up objects -- health

	@param void
	@return string
*/
std::string HealthObj::getType()
{
	return this->type;
}

/**
		Sets the m_model

	@param cMeshObject* model
	@return void
*/
void HealthObj::setModel(cMeshObject* model)
{
	this->m_model = model;
}

/**
		Gets the m_model instance

	@param void
	@return cMeshObject* model
*/
cMeshObject* HealthObj::getModel()
{
	return m_model;
}

/**
		Sets the health pack value, how much healh would add to player's health

	@param int
	@return void
*/
void HealthObj::setValue(int value)
{
	this->m_healthValue = value;
}

/**
		Gets the health pack value, how much healh would add to player's health

	@param void
	@return int
*/
int HealthObj::getValue()
{
	return m_healthValue;
}

/**
		Sets the radius of the coins. vec2.x sets width, vec2.y sets hight of the health pack

	@param glm::vec2
	@return void
*/
void HealthObj::setSize(glm::vec2 dimensions)
{
	this->width = dimensions.x;
	this->hight = dimensions.x;
}

/**
		Gets the radius of the coins. vec2.x is the width, and vec2.y is the hight of the health pack

	@param void
	@return glm::vec2
*/
glm::vec2 HealthObj::getSize()
{
	return glm::vec2(this->width, this->hight);
}