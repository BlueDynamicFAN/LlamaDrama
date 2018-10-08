#include "global.h"
#include <iostream>

void loadAllMeshes(GLuint program) {
	::g_pTheVAOMeshManager = new cVAOMeshManager();
	
	sModelDrawInfo bunnyInfo;
	bunnyInfo.meshFileName = "bun_res3_xyz.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(bunnyInfo, program))
	{
		std::cout << "Didn't load the bunny" << std::endl;
	}
	vec_ModelFileNames.push_back(bunnyInfo.meshFileName);

	sModelDrawInfo grassInfo;
	grassInfo.meshFileName = "grass.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(grassInfo, program))
	{
		std::cout << "Didn't load the grass" << std::endl;
	}
	vec_ModelFileNames.push_back(grassInfo.meshFileName);

	sModelDrawInfo groundInfo;
	groundInfo.meshFileName = "ground.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(groundInfo, program))
	{
		std::cout << "Didn't load the ground" << std::endl;
	}
	vec_ModelFileNames.push_back(groundInfo.meshFileName);

	sModelDrawInfo playerInfo;
	playerInfo.meshFileName = "bun_res3_xyz_big.ply";
	if (!::g_pTheVAOMeshManager->LoadModelIntoVAO(playerInfo, program))
	{
		std::cout << "Didn't load the player mesh" << std::endl;
	}
	vec_ModelFileNames.push_back(playerInfo.meshFileName);
}