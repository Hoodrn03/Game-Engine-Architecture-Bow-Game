#pragma once

#include "GameObject.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "SceneStateComponent.h"

// Physics. 
#include "Velocity.h"
#include "Gravity.h"

#include <iostream>

class ArrowObject : public GameObject
{

public:

	ArrowObject(Model* model, glm::vec3 position, glm::quat orientation);

	~ArrowObject();

private:

	// Data Members 

	glm::vec3 m_CurrMouseInput;

	bool m_bOnce = true; 

public:

	// Member Functions 

	void OnUpdate(float dt) override;
	
	void OnMessage(const std::string m) override;

	void MouseInput(glm::vec2 xy);

	void m_FireArrow(bool fired, float power, float powerDec, glm::vec3 mouseInput);
};