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

	glm::vec3 m_fGravity = { 0.f, 0.098f, 0.f };

	GameObject * m_ThisObject = nullptr;

	bool m_bCollided = false;

public:

	// Member Functions 

	void OnUpdate(float dt)
	{
		if (m_bCollided != true)
		{
			// This should stop is the connected object is at ground level. 
			if (m_ThisObject->getComponent<TransformComponent>()->m_position.y > 0)
			{
				m_ThisObject->getComponent<TransformComponent>()->m_position += (-m_fGravity * dt);
			}

			if (m_ThisObject->getComponent<TransformComponent>()->m_position.y <= 0)
			{
				m_ThisObject->getComponent<TransformComponent>()->m_position.y = 0;
			}
		}
	}
	
	void OnMessage(const std::string m)
	{

	}
	void m_HitObject(bool stopMoving)
	{
		if (this != nullptr)
		{
			if (stopMoving == true)
			{
				m_bCollided = true;
			}
		}
	}
};