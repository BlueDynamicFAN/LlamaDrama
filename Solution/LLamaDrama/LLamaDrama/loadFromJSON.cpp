#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "./Enemies/cEnemyFactory.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include "cMeshObject.h"

std::vector <cEnemy*> pEnemies;
extern std::vector< cMeshObject* > vec_pObjectsToDraw;

void loadEnemiesfromJson() {

	cEnemyFactory* factory = new cEnemyFactory();

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
		
		newEnemy = factory->createEnemy(eType, healthLevel, score, glm::vec3(x,y,z) , meshName, fName);
		pEnemies.push_back(newEnemy);
		vec_pObjectsToDraw.push_back(newEnemy->model);
	}
}