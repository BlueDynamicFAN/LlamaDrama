/**
	loadFromJSON.cpp
	Purpose: Loads objects from JSON
	@author: BlueDynamic
	@version: 1.0.0
*/
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "./Enemies/cEnemyFactory.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include "cMeshObject.h"
#include "cPlatform.h"
#include "cPlayer.h"

std::vector <cEnemy*> pEnemies;
std::vector <cPlatform*> pPlatforms;
cPlayer* thePlayer;
cEnemyFactory* factory;
extern std::vector< cMeshObject* > vec_pObjectsToDraw;


/**
	Loads the ememies from JSON

	@param: void
	@return: void
*/
void loadEnemiesFromJson() {

	factory = new cEnemyFactory();

	std::ifstream i("enemies.json");
	nlohmann::json j;
	i >> j;
	i.close();

	for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {

		cEnemy* newEnemy;

		std::string fName = it.key();
		std::string eType;
		std::string meshName;
		unsigned int score;
		unsigned int healthLevel;
		float x, y, z;

		j[fName]["type"].get_to(eType);
		j[fName]["meshFileName"].get_to(meshName);
		j[fName]["score"].get_to(score);
		j[fName]["health"].get_to(healthLevel);
		j[fName]["positionX"].get_to(x);
		j[fName]["positionY"].get_to(y);
		j[fName]["positionZ"].get_to(z);

		newEnemy = factory->createEnemy(eType, healthLevel, score, glm::vec3(x, y, z), meshName, fName);
		pEnemies.push_back(newEnemy);
		vec_pObjectsToDraw.push_back(newEnemy->m_model);
	}
}

/**
	loads the platforms from JSON

	@param: void
	@return: void
*/
void loadPlatformsFromJson() {
	std::ifstream i("platforms.json");
	nlohmann::json j;
	i >> j;
	i.close();

	for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
		std::string fName = it.key();
		std::string meshName;
		float h, w, x, y, z, r, g, b;

		j[fName]["meshFileName"].get_to(meshName);
		j[fName]["height"].get_to(h);
		j[fName]["width"].get_to(w);
		j[fName]["positionX"].get_to(x);
		j[fName]["positionY"].get_to(y);
		j[fName]["positionZ"].get_to(z);
		j[fName]["r"].get_to(r);
		j[fName]["g"].get_to(g);
		j[fName]["b"].get_to(b);

		cPlatform* thePlatform = new cPlatform(meshName, fName, h, w, glm::vec3(x, y, z), glm::vec3(r, g, b));
		pPlatforms.push_back(thePlatform);
		vec_pObjectsToDraw.push_back(thePlatform->m_model);
	}
}

/**
	loads the player from JSON

	@param: void
	@return: void
*/
void loadPlayerFromJson() {
	std::ifstream i("player.json");
	nlohmann::json j;
	i >> j;
	i.close();

	for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
		std::string fName = it.key();
		std::string meshName;
		float x, y, z;
		int healthLevel;

		j[fName]["meshFileName"].get_to(meshName);
		j[fName]["positionX"].get_to(x);
		j[fName]["positionY"].get_to(y);
		j[fName]["positionZ"].get_to(z);
		j[fName]["health"].get_to(healthLevel);

		thePlayer = cPlayer::getThePlayer(meshName, fName, glm::vec3(x, y, z), healthLevel);
		vec_pObjectsToDraw.push_back(thePlayer->getModel());
	}
}

/**
	deleted created here objects

	@param: void
	@return: void
*/
void deleteModels()
{
	for (int i = 0; i != pEnemies.size(); i++)
	{
		delete pEnemies[i];
	}

	for (int i = 0; i != pPlatforms.size(); i++)
	{
		delete pPlatforms[i];
	}

	delete thePlayer;
	delete factory;
}