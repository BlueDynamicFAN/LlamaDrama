/**
	PickUpObjManager.cpp
	Purpose: creates health and coin objects
	@author: BlueDynamic
	@version: 1.0.0
*/
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip> 
#include <fstream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include "Coin.h"
#include "PickUpObj.h"
#include "HealthObj.h"
#include "../cMeshObject.h"

std::vector <PickUpObj*> pPickUpObj;
extern std::vector< cMeshObject* > vec_pObjectsToDraw;

/**
	Loads the pickUp objects from JSON

	@param: void
	@return: void
*/
void loadPickUpFromJson() {
	pPickUpObj;
	std::ifstream i("pickUp.json");
	nlohmann::json j;
	i >> j;
	i.close();

	for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {

		std::string fName = it.key();

		PickUpObj* newPickUp;
		cMeshObject* model = new cMeshObject();
		sTextureInfo texture;
		std::string meshName;
		int value;

		std::string type;


		j[fName]["type"].get_to(type);
		j[fName]["value"].get_to(value);
		j[fName]["meshFileName"].get_to(meshName);
		j[fName]["positionX"].get_to(model->m_position.x);
		j[fName]["positionY"].get_to(model->m_position.y);
		j[fName]["positionZ"].get_to(model->m_position.z);
		j[fName]["textuteName"].get_to(texture.name);
		j[fName]["textureStren"].get_to(texture.strength);
		j[fName]["bIsVisiable"].get_to(model->m_bIsVisible);
		j[fName]["noLight"].get_to(model->bDontLight);
		j[fName]["bUseVertexColour"].get_to(model->bUseVertexColour);

		std::vector<float> diffuse = j[fName]["diffuse"];
		std::vector<float> specular = j[fName]["specular"];
		std::vector<float> dimensions = j[fName]["size"];
		model->m_meshName = meshName;
		model->m_friendlyName = fName;
		model->vecTextures.push_back(texture);
		model->setDiffuseColour(glm::vec3(diffuse[0], diffuse[1], diffuse[2]));
		model->setAlphaTransparency(diffuse[3]);
		model->setSpecularPower(specular[3]);
		model->setSpecularColour(glm::vec3(specular[0], specular[1], specular[2]));


		if (type == "health")
		{
			model->pTheShape = new sSphere(0.4f);
			model->shapeType = cMeshObject::SPHERE;
			newPickUp = new HealthObj();
		}
		else if (type == "coin")
		{
			model->pTheShape = new sSphere(0.4f);
			model->shapeType = cMeshObject::SPHERE;
			newPickUp = new Coin();

		}
		newPickUp->setSize(glm::vec2(dimensions[0], dimensions[1]));
		newPickUp->setModel(model);
		newPickUp->setValue(value);


		pPickUpObj.push_back(newPickUp);
		vec_pObjectsToDraw.push_back(model);
	}
}

void savePickUpToJson() 
{
	std::string filename = "pickUp.json";
	std::ofstream o(filename);
	nlohmann::json j;

	for (int i = 0; i < pPickUpObj.size(); i++)
	{
		cMeshObject* model = pPickUpObj[i]->getModel();
		std::string fName = model->m_friendlyName;

		j[fName]["type"] = pPickUpObj[i]->getType();
		j[fName]["value"] = pPickUpObj[i]->getValue();
		j[fName]["meshFileName"] = model->m_meshName;
		j[fName]["positionX"] = model->m_position.x;
		j[fName]["positionY"] = model->m_position.y;
		j[fName]["positionZ"] = model->m_position.z;
		j[fName]["textuteName"] = model->vecTextures[0].name;
		j[fName]["textureStren"] = model->vecTextures[0].strength;
		j[fName]["bIsVisiable"] = model->m_bIsVisible;
		j[fName]["noLight"] = model->bDontLight;
		j[fName]["bUseVertexColour"] = model->bUseVertexColour;

		std::vector <float> diffuse = { model->materialDiffuse.r, model->materialDiffuse.g,
								model->materialDiffuse.b, model->materialDiffuse.w };

		std::vector <float> specular = {model->materialSpecular.r,model->materialSpecular.g,
								model->materialSpecular.b, model->materialSpecular.w };

		std::vector <float> size = { pPickUpObj[i]->getSize().x,  pPickUpObj[i]->getSize().y };

		j[fName]["diffuse"] = diffuse;
		j[fName]["specular"] = specular;
		j[fName]["size"] = size;
	}

	std::cout << "Saving pick_up to JASON file - " << filename << std::endl;
	o << std::setw(4) << j << std::endl;
	o.close();
}