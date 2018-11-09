/**
	Player.h
	Purpose: Contains the information for the player
	@author: BlueDynamic
	@version: 1.0.0
*/
#include "cPlayer.h"

// static
cPlayer* cPlayer::pOnlyPlayer = NULL;

/**
	Gets the only instance of the player if it exists, creates a new one if it does not

	@param: the name of the mesh, friendly name and the position of the player
	@return: the player
*/
cPlayer* cPlayer::getThePlayer(std::string meshName, std::string fName, glm::vec3 position, int healthLevel)
{
	if (pOnlyPlayer == NULL)
	{
		pOnlyPlayer = new cPlayer(meshName, fName, position, healthLevel);
	}
	return pOnlyPlayer;
}

/**
	Default constructor

	@param: void
	@return: void
*/
cPlayer::cPlayer()
{
	this->m_model = new cMeshObject();
	this->m_model->m_objColour = glm::vec3(1.0f, 1.0f, 1.0f); //Will be removed when we add textures
	this->m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_playerScore = 0;
	this->m_numberOfKeys = 0;
}

/**
	Constructor with info, calls default constractor for initial set up

	@param: the name of the mesh, friendly name and the position of the player
	@return: void
*/
cPlayer::cPlayer(std::string meshName, std::string fName, glm::vec3 position, int healthLevel) : cPlayer()
{
	this->m_model->m_meshName = meshName;
	this->m_model->m_friendlyName = fName;
	this->m_model->m_position = position;
	this->m_playerHealth = healthLevel;
}

/**
	Deconstructor

	@param: void
	@return: void
*/
cPlayer::~cPlayer()
{

}

/**
	Getter for the model info

	@param: void
	@return: the model
*/
cMeshObject* cPlayer::getModel()
{
	return this->m_model;
}

/**
	Getter for the velocity

	@param: void
	@return: velocity
*/
glm::vec3 cPlayer::getVelocity()
{
	return this->m_velocity;
}

/**
	Getter for the acceleration

	@param: void
	@return: acceleration
*/
glm::vec3 cPlayer::getAccel()
{
	return this->m_accel;
}

/**
	Getter for the position

	@param: void
	@return: position
*/
glm::vec3 cPlayer::getPosition()
{
	return this->m_model->m_position;
}

/**
	Getter for the player health

	@param: void
	@return: player health
*/
unsigned int cPlayer::getPlayerHealth()
{
	return this->m_playerHealth;
}

/**
	Getter for the player score

	@param: void
	@return: player score
*/
unsigned int cPlayer::getPlayerScore()
{
	return this->m_playerScore;
}

/**
	Getter for the number of keys

	@param: void
	@return: number of keys
*/
unsigned int cPlayer::getNumberOfKeys()
{
	return this->m_numberOfKeys;
}

/**
	Setter for the x velocity

	@param: the new value
	@return: void
*/
void cPlayer::setVelocityX(float value)
{
	this->m_velocity.x = value;
}

/**
	Setter for the y velocity

	@param: the new value
	@return: void
*/
void cPlayer::setVelocityY(float value)
{
	this->m_velocity.y = value;
}

/**
	Setter for the x acceleration

	@param: the new value
	@return: void
*/
void cPlayer::setAccelY(float value)
{
	this->m_accel.y = value;
}

/**
	Setter for the x position

	@param: the new value
	@return: void
*/
void cPlayer::setPositionX(float value)
{
	this->m_model->m_position.x = value;
}

/**
	Setter for the y position

	@param: the new value
	@return: void
*/
void cPlayer::setPositionY(float value)
{
	this->m_model->m_position.y = value;
}

/**
	Setter for the player health

	@param: the value
	@return: void
*/
void setPlayerHealth(unsigned int playerHealth)
{

}

/**
	Setter for the player score

	@param: the value
	@return: void
*/
void setPlayerScore(unsigned int playerScore)
{

}

/**
	Setter for the number of keys

	@param: the value
	@return: void
*/
void setNumberOfKeys(unsigned int playerKeys)
{

}
