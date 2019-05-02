#pragma once

#include <iostream>
#include <cmath>

#include "GameObject.h"
#include "TransformComponent.h"
#include "Velocity.h"
#include "Gravity.h"

class CollisionDetection
{
public:

	// Constructor 

	CollisionDetection();

	// Deconstructor 

	~CollisionDetection();

private:

	// Data Members 

	bool m_bHitPlayer = false;

	bool m_bHitEnemy = false;

	bool m_bHitGround = false; 

	GameObject* m_PlayerObject = nullptr;

	GameObject* m_EnemyObject = nullptr;

	GameObject* m_CurrentArrowObject = nullptr; 

	std::vector<glm::vec3> m_MainLevelPoints; 



	// Member Functions

protected:

	float m_CalcDist(glm::vec3 pointOne, glm::vec3 pointTwo); 

public:

	// Used to see if a point has hit the player, (Using AABB - Axis-Aligned Bounding Box). 
	bool m_CheckForObjectBoxColl(GameObject* objectToCheck);

	// Used to see if a point has hit the ground, (Using Point Line Collision). 
	bool m_CheckForLineColl(glm::vec3 pointOne, glm::vec3 pointTwo);

	void m_Update(); 

	// Setters

	void m_SetPlayerObject(GameObject* currPlayer);

	void m_SetEnemyObject(GameObject* currEnemy); 

	void m_SetMainMapPoints(std::vector<glm::vec3> mapPoints); 

	void m_SetCurrArrowObject(GameObject* currArrow); 

	// Getters 

	bool m_GetPlayerHit();

	bool m_GetEnemyHit(); 

	bool m_GetGroundHit(); 

};