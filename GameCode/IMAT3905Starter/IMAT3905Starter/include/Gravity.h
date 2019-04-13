#pragma once

#include "Component.h"

#include "GameObject.h"
#include "TransformComponent.h"

class Gravity : public Component
{
public:

	// Constructor 

	Gravity()
	{

	}

	Gravity(GameObject * connectedObject) : m_ThisObject(connectedObject)
	{

	}

	// Deconstructor 

	~Gravity()
	{
	}

private:

	// Data Members 

	glm::vec3 m_fGravity = { 0.f, 0.0098f, 0.f };

	GameObject * m_ThisObject;

public:

	// Member Functions 

	void OnUpdate(float dt)
	{
		m_ThisObject->getComponent<TransformComponent>()->m_position -= (m_fGravity * dt);
	}
	
	void OnMessage(const std::string m)
	{

	}

};