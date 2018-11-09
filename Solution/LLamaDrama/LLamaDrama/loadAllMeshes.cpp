/**
	loadAllMeshes.cpp
	Purpose: Loads the meshes into the program
	@author: BlueDynamic
	@version: 1.0.0
*/
#include "global.h"
#include <iostream>
void loadPickUpFromJson();
/**
	Loads the meshes into the program

	@param: the program to laod it into
	@return: void
*/
void loadAllMeshes(GLuint program) {

	::g_pTheTextureManager->SetBasePath("assets/textures");

	::g_pTheTextureManager->Create2DTextureFromBMPFile("uv3.bmp", true);
	
	::g_pTheTextureManager->Create2DTextureFromBMPFile("apple.bmp", true);
	
	::g_pTheTextureManager->Create2DTextureFromBMPFile("stones.bmp", true);

	::g_pTheTextureManager->Create2DTextureFromBMPFile("coin-texture.bmp", true);

	::g_pTheVAOMeshManager = new cVAOMeshManager();
	
	sModelDrawInfo LevelBoss1Info;
	LevelBoss1Info.meshFileName = "homer.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(LevelBoss1Info, program))
	{
		std::cout << "Didn't load the player mesh" << std::endl;
	}
	vec_ModelFileNames.push_back(LevelBoss1Info.meshFileName);

	sModelDrawInfo grassInfo;
	grassInfo.meshFileName = "grass.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(grassInfo, program))
	{
		std::cout << "Didn't load the grass" << std::endl;
	}
	vec_ModelFileNames.push_back(grassInfo.meshFileName);

	sModelDrawInfo groundInfo;
	groundInfo.meshFileName = "ground_blender_uv.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(groundInfo, program))
	{
		std::cout << "Didn't load the ground" << std::endl;
	}
	vec_ModelFileNames.push_back(groundInfo.meshFileName);

	sModelDrawInfo playerInfo;
	playerInfo.meshFileName = "Llama.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(playerInfo, program))
	{
		std::cout << "Didn't load the player mesh" << std::endl;
	}
	vec_ModelFileNames.push_back(playerInfo.meshFileName);

	sModelDrawInfo block1Info;
	block1Info.meshFileName = "block1_xyz_n.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(block1Info, program))
	{
		std::cout << "Didn't load block1 mesh" << std::endl;
	}
	vec_ModelFileNames.push_back(block1Info.meshFileName);

	sModelDrawInfo block2Info;
	block2Info.meshFileName = "block2_xyz_n.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(block2Info, program))
	{
		std::cout << "Didn't load block2 mesh" << std::endl;
	}
	vec_ModelFileNames.push_back(block2Info.meshFileName);

	sModelDrawInfo block3Info;
	block3Info.meshFileName = "block3_xyz_n.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(block3Info, program))
	{
		std::cout << "Didn't load block3 mesh" << std::endl;
	}
	vec_ModelFileNames.push_back(block3Info.meshFileName);

	sModelDrawInfo block4Info;
	block4Info.meshFileName = "block4_xyz_n.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(block4Info, program))
	{
		std::cout << "Didn't load block4 mesh" << std::endl;
	}
	vec_ModelFileNames.push_back(block4Info.meshFileName);

	sModelDrawInfo block5Info;
	block5Info.meshFileName = "block5_xyz_n.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(block5Info, program))
	{
		std::cout << "Didn't load block5 mesh" << std::endl;
	}
	vec_ModelFileNames.push_back(block5Info.meshFileName);

	sModelDrawInfo coinInfo;
	coinInfo.meshFileName = "coin.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(coinInfo, program))
	{
		std::cout << "Didn't load the coin mesh" << std::endl;
	}
	vec_ModelFileNames.push_back(coinInfo.meshFileName);

}


/**
	Loads the models we are drawing into the vector

	@param: void
	@return: void
*/
void LoadModelsIntoScene(void)
{
	loadPlayerFromJson();
	loadEnemiesFromJson();
	loadPlatformsFromJson();
	loadPickUpFromJson();

	return;
}