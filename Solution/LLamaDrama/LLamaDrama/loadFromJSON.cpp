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
		sTextureInfo texture;
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


		j[fName]["textuteName"].get_to(texture.name);
		j[fName]["textureStren"].get_to(texture.strength);
		j[fName]["bIsVisiable"].get_to(newEnemy->m_model->m_bIsVisible);
		j[fName]["noLight"].get_to(newEnemy->m_model->bDontLight);
		j[fName]["bUseVertexColour"].get_to(newEnemy->m_model->bUseVertexColour);
		std::vector<float> diffuse = j[fName]["diffuse"];
		std::vector<float> specular = j[fName]["specular"];

		newEnemy->m_model->vecTextures.push_back(texture);
		newEnemy->m_model->setDiffuseColour(glm::vec3(diffuse[0], diffuse[1], diffuse[2]));
		newEnemy->m_model->setAlphaTransparency(diffuse[3]);
		newEnemy->m_model->setSpecularPower(specular[3]);
		newEnemy->m_model->setSpecularColour(glm::vec3(specular[0], specular[1], specular[2]));

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
		sTextureInfo texture;
		float h, w, x, y, z, r, g, b;

		cPlatform* thePlatform = new cPlatform();
		j[fName]["meshFileName"].get_to(thePlatform->m_model->m_meshName);
		j[fName]["height"].get_to(thePlatform->m_height);
		j[fName]["width"].get_to(thePlatform->m_width);
		j[fName]["positionX"].get_to(thePlatform->m_model->m_position.x);
		j[fName]["positionY"].get_to(thePlatform->m_model->m_position.y);
		j[fName]["positionZ"].get_to(thePlatform->m_model->m_position.z);
	
		j[fName]["bIsVisiable"].get_to(thePlatform->m_model->m_bIsVisible);
		j[fName]["bUseVertexColour"].get_to(thePlatform->m_model->bUseVertexColour);
		std::vector<float> diffuse = j[fName]["diffuse"];
		std::vector<float> specular = j[fName]["specular"];
		j[fName]["noLight"].get_to(thePlatform->m_model->bDontLight);
		j[fName]["textureStren"].get_to(texture.strength);
		j[fName]["textuteName"].get_to(texture.name);

		thePlatform->m_model->vecTextures.push_back(texture);
		thePlatform->m_model->setDiffuseColour(glm::vec3(diffuse[0], diffuse[1], diffuse[2]));
		thePlatform->m_model->setAlphaTransparency(diffuse[3]);
		thePlatform->m_model->setSpecularPower(specular[3]);
		thePlatform->m_model->setSpecularColour(glm::vec3(specular[0], specular[1], specular[2]));

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
		sTextureInfo texture;
		std::string meshName;
		float x, y, z;
		int healthLevel;

		j[fName]["meshFileName"].get_to(meshName);
		j[fName]["positionX"].get_to(x);
		j[fName]["positionY"].get_to(y);
		j[fName]["positionZ"].get_to(z);
		j[fName]["health"].get_to(healthLevel);

		thePlayer = cPlayer::getThePlayer(meshName, fName, glm::vec3(x, y, z), healthLevel);


		j[fName]["textuteName"].get_to(texture.name);
		j[fName]["textureStren"].get_to(texture.strength);
		j[fName]["bIsVisiable"].get_to(thePlayer->m_model->m_bIsVisible);
		j[fName]["noLight"].get_to(thePlayer->m_model->bDontLight);
		j[fName]["bUseVertexColour"].get_to(thePlayer->m_model->bUseVertexColour);
		std::vector<float> diffuse = j[fName]["diffuse"];
		std::vector<float> specular = j[fName]["specular"];

		thePlayer->m_model->vecTextures.push_back(texture);
		thePlayer->m_model->setDiffuseColour(glm::vec3(diffuse[0], diffuse[1], diffuse[2]));
		thePlayer->m_model->setAlphaTransparency(diffuse[3]);
		thePlayer->m_model->setSpecularPower(specular[3]);
		thePlayer->m_model->setSpecularColour(glm::vec3(specular[0], specular[1], specular[2]));


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