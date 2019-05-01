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

	glm::vec3 m_fGravity = { 0.f, 0.98f, 0.f };

	GameObject * m_ThisObject = nullptr;

public:

	// Member Functions 

	void OnUpdate(float dt)
	{
		// This should stop is the connected object is at ground level. 
		if (m_ThisObject->getComponent<TransformComponent>()->m_position.y > 0)
		{
			m_ThisObject->getComponent<TransformComponent>()->m_position += (-m_fGravity * dt);
		}
	}
	
	void OnMessage(const std::string m)
	{

	}

};