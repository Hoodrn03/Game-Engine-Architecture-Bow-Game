#pragma once

#include "GameObject.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "SceneStateComponent.h"

#include <iostream>

class CameraObject : public GameObject
{

public:

	CameraObject(glm::vec3 position, glm::quat orientation);

	//glm::mat4 calculateViewMatrix(); 


	~CameraObject(); 

private:
	
	//data members
	
	void setToPlayer();
	void setToEnemy(); 
	void setToArrow(); 

	glm::vec3 * playerPos = nullptr;
	glm::vec3 * enemyPos = nullptr; 
	glm::vec3 * arrowPos = nullptr;

public:

	//member functions

	void OnUpdate(float dt) override; 

	void OnUpdate(float dt, int currentTurn);

	void OnMessage(const std::string m) override;

	void m_SetPlayerPos(glm::vec3 * newPlayerPos);
	void m_SetEnemyPos(glm::vec3 * newEnemyPos);
	void m_CurrentArrowPos(glm::vec3 * newArrowPos);

	CameraComponent * getCamera(); 

};


