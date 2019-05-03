#pragma once

#include "Component.h"

#include "GameObject.h"
#include "TransformComponent.h"

#include <cmath>
#include <iostream>

class Velocity : public Component
{
public:

	// Constructor 

	Velocity()
	{

	}

	Velocity(GameObject *connectedObject) : m_ThisObject(connectedObject)
	{

	}

	Velocity(GameObject* connectedObject, glm::vec3 position) : m_ThisObject(connectedObject), m_StartVelocity(position)
	{
		m_Direction = m_CalculateMoveVector();

		// std::cout << m_Direction.x << ", " << m_Direction.y << ", " << m_Direction.z << std::endl;
	}

	Velocity(GameObject* connectedObject, glm::vec3 position, float speed, float power) : 
		m_ThisObject(connectedObject), m_StartVelocity(position), m_fSpeed(speed), m_fPower(power)
	{
		m_Direction = m_CalculateMoveVector();

		m_fDecelAmount = m_fPower * 0.01f; 

		// std::cout << m_Direction.x << ", " << m_Direction.y << ", " << m_Direction.z << std::endl;
	}

	// Deconstructor 

	~Velocity()
	{

	}

private:

	// Data Members 

	glm::vec3 m_StartVelocity = { 0.f, 0.f, 0.f };

	GameObject* m_ThisObject = nullptr; 

	// Accel
	float m_fSpeed = 0.f;

	// Time
	float m_fPower = 0.f;

	float m_fDecelAmount = 0.f; 

	// Vector Normal
	glm::vec3 m_Direction = { 0.f, 0.f, 0.f };

	bool m_bCollided = false; 

public:

	// Member Functions 

	void OnUpdate(float dt)
	{
		if (m_bCollided != true)
		{
			glm::vec3 l_MoveAmount = glm::vec3(m_Direction.x * (m_fSpeed * dt), m_Direction.y * (m_fPower * dt), 0);

			if (m_fPower > 0)
			{
				m_fPower -= m_fDecelAmount;
			}
			else if (m_fPower < 0)
			{
				m_fPower = 0;
			}

			// std::cout << "Speed : " << m_fSpeed << " , Power : " << m_fPower << std::endl;

			m_ThisObject->getComponent<TransformComponent>()->m_position += l_MoveAmount;
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

	glm::vec3 m_CalculateMoveVector()
	{
		float l_fXOne, l_fYOne;

		l_fXOne = m_StartVelocity.x;
		l_fYOne = m_StartVelocity.y;

		float l_fMagnitude = sqrt((pow(l_fXOne, 2)) + pow(l_fYOne, 2));

		m_StartVelocity.z = 0;

		glm::vec3 l_Normal = m_StartVelocity / l_fMagnitude;

		return l_Normal;
	}
};