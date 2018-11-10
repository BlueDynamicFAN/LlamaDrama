/**
	Physics.cpp
	Purpose: Deals with all the physics
	@author: BlueDynamic
	@version: 1.0.0
*/
#include "global.h"
#include <glm/glm.hpp>
#include "sModelDrawInfo.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::vec3 Point;
typedef glm::vec3 Vector;

/**
	Checks if the player is on top of a platform

	@param: void
	@return: true or false
*/
bool isPlayerOnTopOfAPlatform()
{
	const float EPSILON = 0.1f;
	const float OFFSET = 0.1f;
	for (std::vector <cPlatform*>::iterator itPlatform = pPlatforms.begin();
		itPlatform != pPlatforms.end(); itPlatform++)
	{
		cPlatform* thePlatform = *itPlatform;
		float yLimit = thePlatform->m_model->m_position.y + (thePlatform->m_height) / 2;
		bool inYLimit = abs(thePlayer->getPosition().y - yLimit) <= EPSILON;
		/*bool inXLimitsNeg = (thePlayer->getPosition().x >= thePlatform->m_model->m_position.x - thePlatform->m_width / 2);
		bool inXLimitsPos = (thePlayer->getPosition().x <= thePlatform->m_model->m_position.x + thePlatform->m_width / 2);*/
		bool inXLimitsNeg = (thePlayer->getPosition().x + OFFSET >= thePlatform->m_model->m_position.x - thePlatform->m_width / 2);
		bool inXLimitsPos = (thePlayer->getPosition().x - OFFSET <= thePlatform->m_model->m_position.x + thePlatform->m_width / 2);
		if (inYLimit && inXLimitsNeg && inXLimitsPos)
		{
			return true;
		}
	}
	return false;
}

/**
	Updates the gravity of the player each frame

	@param: the time
	@return: void
*/
void gravityUpdate(double deltaTime)
{
	const double LARGEST_DELTATIME = 0.10; //10 ms = 10Hz
	if (deltaTime > LARGEST_DELTATIME)
	{
		deltaTime = LARGEST_DELTATIME;
	}

	thePlayer->setVelocityY(thePlayer->getVelocity().y + (thePlayer->getAccel().y * deltaTime));

	thePlayer->setPositionY(thePlayer->getPosition().y + (thePlayer->getVelocity().y * deltaTime));

	//The object can't go any lower than "the ground"
	if (isPlayerOnTopOfAPlatform())
	{
		thePlayer->setVelocityY(0.0f);
		thePlayer->setAccelY(0.0f);
	}
	else {
		thePlayer->setAccelY(-9.8f);
	}

	return;
}

/**
	Updates the movement of the player on user input

	@param: the time
	@return: void
*/
void movesUpdate(double deltaTime)
{
	const double LARGEST_DELTATIME = 0.10; //10 ms = 10Hz
	if (deltaTime > LARGEST_DELTATIME) {
		deltaTime = LARGEST_DELTATIME;
	}

	thePlayer->setVelocityX(thePlayer->getVelocity().x + (thePlayer->getAccel().x * deltaTime));

	thePlayer->setPositionX(thePlayer->getPosition().x + (thePlayer->getVelocity().x * deltaTime));
}

Point ClosestPtPointTriangle(Point p, Point a, Point b, Point c)
{
	Vector ab = b - a;
	Vector ac = c - a;
	Vector bc = c - b;

	// Compute parametric position s for projection P' of P on AB,
	// P' = A + s*AB, s = snom/(snom+sdenom)
 //   float snom = Dot(p - a, ab), sdenom = Dot(p - b, a - b);
	float snom = glm::dot(p - a, ab);
	float sdenom = glm::dot(p - b, a - b);

	// Compute parametric position t for projection P' of P on AC,
	// P' = A + t*AC, s = tnom/(tnom+tdenom)
//    float tnom = Dot(p - a, ac), tdenom = Dot(p - c, a - c);
	float tnom = glm::dot(p - a, ac);
	float tdenom = glm::dot(p - c, a - c);

	if (snom <= 0.0f && tnom <= 0.0f) return a; // Vertex region early out

	// Compute parametric position u for projection P' of P on BC,
	// P' = B + u*BC, u = unom/(unom+udenom)
//    float unom = Dot(p - b, bc), udenom = Dot(p - c, b - c);
	float unom = glm::dot(p - b, bc);
	float udenom = glm::dot(p - c, b - c);

	if (sdenom <= 0.0f && unom <= 0.0f) return b; // Vertex region early out
	if (tdenom <= 0.0f && udenom <= 0.0f) return c; // Vertex region early out


	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
//    Vector n = Cross(b - a, c - a);
	Vector n = glm::cross(b - a, c - a);
	//    float vc = Dot(n, Cross(a - p, b - p));

	float vc = glm::dot(n, glm::cross(a - p, b - p));

	// If P outside AB and within feature region of AB,
	// return projection of P onto AB
	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
		return a + snom / (snom + sdenom) * ab;

	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
//    float va = Dot(n, Cross(b - p, c - p));
	float va = glm::dot(n, glm::cross(b - p, c - p));


	// If P outside BC and within feature region of BC,
	// return projection of P onto BC
	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
		return b + unom / (unom + udenom) * bc;

	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
//    float vb = Dot(n, Cross(c - p, a - p));
	float vb = glm::dot(n, glm::cross(c - p, a - p));

	// If P outside CA and within feature region of CA,
	 // return projection of P onto CA
	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
		return a + tnom / (tnom + tdenom) * ac;

	// P must project inside face region. Compute Q using barycentric coordinates
	float u = va / (va + vb + vc);
	float v = vb / (va + vb + vc);
	float w = 1.0f - u - v; // = vc / (va + vb + vc)
	return u * a + v * b + w * c;
}

// Pass in the terrain
// Pass in the location of the Bunny (the one I can move)
// "return" (by reference) as list of points
// --> then I can draw those points

void CalculateClosestPointsOnMesh(sModelDrawInfo theMeshDrawInfo,
	glm::vec3 pointToTest,
	std::vector<sClosestPointData> &vecPoints)
{
	vecPoints.clear();

	// For each triangle in the mesh information...
	for (unsigned int triIndex = 0; triIndex != theMeshDrawInfo.numberOfTriangles; triIndex++)
	{
		sPlyTriangle CurTri = theMeshDrawInfo.pTriangles[triIndex];

		sClosestPointData closestTri;
		closestTri.triangleIndex = triIndex;

		// ... call the ClosestPointToTriangle...
		// Need to get the 3 vertices of the triangle
		sPlyVertex corner_1 = theMeshDrawInfo.pVerticesFromFile[CurTri.vertex_index_1];
		sPlyVertex corner_2 = theMeshDrawInfo.pVerticesFromFile[CurTri.vertex_index_2];
		sPlyVertex corner_3 = theMeshDrawInfo.pVerticesFromFile[CurTri.vertex_index_3];

		// Convert this to glm::vec3
		glm::vec3 vert_1 = glm::vec3(corner_1.x, corner_1.y, corner_1.z);
		glm::vec3 vert_2 = glm::vec3(corner_2.x, corner_2.y, corner_2.z);
		glm::vec3 vert_3 = glm::vec3(corner_3.x, corner_3.y, corner_3.z);

		closestTri.thePoint = ClosestPtPointTriangle(pointToTest, vert_1, vert_2, vert_3);

		vecPoints.push_back(closestTri);
	}//for ( unsigned int triIndex = 0
}

bool SphereTraingleTest(cMeshObject* pTriangle, cMeshObject* pSphere)
{
	sTriangle* pTri = (sTriangle*)(pTriangle->pTheShape);
	sSphere* pSphereB = (sSphere*)(pSphere->pTheShape);

	// Calcualte where the triangle vertices ACTUALLY are...

	glm::vec3 vActual[3];

	glm::mat4 matWorld = glm::mat4(1.0f);

	// Take into account the rotation in the world
	//glm::mat4 preRot_X = glm::rotate(glm::mat4(1.0f),
	//	pTriangle->m_preRotation.x,
	//	glm::vec3(1.0f, 0.0, 0.0f));
	//matWorld = matWorld * preRot_X;

	//glm::mat4 preRot_Y = glm::rotate(glm::mat4(1.0f),
	//	pTriangle->m_preRotation.y,
	//	glm::vec3(0.0f, 1.0, 0.0f));
	//matWorld = matWorld * preRot_Y;

	//glm::mat4 preRot_Z = glm::rotate(glm::mat4(1.0f),
	//	pTriangle->m_preRotation.z,
	//	glm::vec3(0.0f, 0.0, 1.0f));
	//matWorld = matWorld * preRot_Z;


	// Move it (translation)
	glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f),
		pTriangle->m_position);

	// Get the "final" world matrix
	matWorld = matWorld * matTranslate;

	vActual[0] = matWorld * glm::vec4(pTri->v[0], 1.0f);
	vActual[1] = matWorld * glm::vec4(pTri->v[1], 1.0f);
	vActual[2] = matWorld * glm::vec4(pTri->v[2], 1.0f);

	glm::vec3 closestPointToTri = ClosestPtPointTriangle(pSphere->m_position,
		vActual[0], vActual[1], vActual[2]);

	//std::cout << "DIS: " << glm::distance(closestPointToTri, pSphere->m_position) << std::endl;
	//std::cout << "RADIUS: " << pSphereB->radius << std::endl;

	// is this point LESS THAN the radius of the sphere? 
	if (glm::distance(closestPointToTri, pSphere->m_position) <= pSphereB->radius)
	{
		return true;
	}

	return false;
}

bool TestForCollision(cMeshObject* pA, cMeshObject* pB)
{
	if (pA->pTheShape == NULL) { return false; }
	if (pB->pTheShape == NULL) { return false; }

	if ((pA->shapeType == cMeshObject::TRIANGLE) && (pB->shapeType == cMeshObject::SPHERE))
	{
		return SphereTraingleTest(pA, pB);
	}

	return false;
}

void collisionDetection(cMeshObject* pickupObject)
{
	// Test for collisions

		cMeshObject* pObjectA = thePlayer->getModel();
		cMeshObject* pObjectB = pickupObject;

		// Same?
		if (pObjectA != pObjectB)
		{

			if ((pObjectA->pTheShape != NULL) && (pObjectB->pTheShape != NULL))
			{
				if (TestForCollision(pObjectA, pObjectB))
				{
					if ((pObjectA->shapeType == cMeshObject::TRIANGLE) && (pObjectB->shapeType == cMeshObject::SPHERE))
					{
						pObjectB->m_bIsVisible = false;
						pObjectB->shapeType = cMeshObject::UNKNOWN_SHAPE;

						if (pObjectB->m_meshName == "coin.ply")
						{
							int score = thePlayer->getPlayerScore();
							score += 10;
							thePlayer->setPlayerScore(score);
							std::cout << "Score: " << score << std::endl;
						}
						else if (pObjectB->m_meshName == "health.ply")
						{
							int health = thePlayer->getPlayerHealth();
							health += 10;
							thePlayer->setPlayerHealth(health);
							std::cout << "Health: " << health << std::endl;
						}
					}
				}//if(TestForCollision(...
			}
		}//if(pObjectA != pObjectB)
	}// inner loop

