#include "ArrowObject.h"

ArrowObject::ArrowObject(Model* model, glm::vec3 position, glm::quat orientation)
{
	TransformComponent* tc = new TransformComponent(position, orientation);

	glm::vec3 m_CurrMouseInput = glm::vec3{ 1.f, 1.f, 0.f };

	addComponent(tc);
	addComponent(new ModelComponent(model));

	addComponent(new CameraComponent()); 
}

void ArrowObject::OnUpdate(float dt)
{
	if (getComponent<Velocity>() != nullptr)
	{
		getComponent<Velocity>()->OnUpdate(dt);
	}
	if (getComponent<Gravity>() != nullptr)
	{
		getComponent<Gravity>()->OnUpdate(dt);
	}

	if (getComponent<CameraComponent>() != nullptr)
	{
		getComponent<CameraComponent>()->setPosition(getComponent<TransformComponent>()->m_position + glm::vec3(0.f, 0.f, 5.f));
	}
}

void ArrowObject::OnMessage(const std::string m)
{
}

void ArrowObject::MouseInput(glm::vec2 xy)
{	
	// std::cout << xy.x << xy.y << std::endl;

	m_CurrMouseInput.x = xy.x;
	m_CurrMouseInput.y = xy.y; 
}

void ArrowObject::m_FireArrow(bool fired, float power, float powerDec, glm::vec3 mouseInput)
{
	if (this != nullptr)
	{
		if (fired == true)
		{
			if (m_bOnce == true)
			{
				addComponent(new Velocity(this, mouseInput, power, powerDec));
				addComponent(new Gravity(this));

				m_bOnce = false; 

				std::cout << "Hello There" << std::endl;
			}
		}
	}
}

ArrowObject::~ArrowObject()
{
}
