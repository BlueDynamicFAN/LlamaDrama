/**
	Player.h
	Purpose: Contains the information for the player
	@author: BlueDynamic
	@version: 1.0.0
*/
#ifndef _cPlayer_HG_
#define _cPlayer_HG_
#include <string>
#include "../cMeshObject.h"

class cPlayer
{
public:
	~cPlayer();
	static cPlayer* getThePlayer(std::string meshName, std::string fName, glm::vec3 position, int healthLevel);

	cMeshObject* getModel();
	glm::vec3 getVelocity();
	glm::vec3 getAccel();
	glm::vec3 getPosition();

	unsigned int getPlayerHealth();
	unsigned int getPlayerScore();
	unsigned int getNumberOfKeys();
	unsigned int getId();

	void setVelocityX(float value);
	void setVelocityY(float value);
	void setAccelY(float value);
	void setPositionX(float value);
	void setPositionY(float value);

	void setPlayerHealth(unsigned int playerHealth);
	void setPlayerScore(unsigned int playerScore);
	void setNumberOfKeys(unsigned int playerKeys);
	cMeshObject* m_model;

private:
	cPlayer();

	cPlayer(std::string meshName, std::string fName, glm::vec3 position, int healthLevel);

	static cPlayer* pOnlyPlayer;

	//cMeshObject* m_model;
	glm::vec3 m_velocity;
	glm::vec3 m_accel;

	unsigned int m_playerHealth;
	unsigned int m_playerScore;
	unsigned int m_numberOfKeys;

	unsigned int m_id;
};

#endif