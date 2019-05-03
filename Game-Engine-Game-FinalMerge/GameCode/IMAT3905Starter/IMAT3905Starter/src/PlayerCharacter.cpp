#include "PlayerCharacter.h"


// constructor
PlayerCharacter::PlayerCharacter(Model* model, glm::vec3 position, glm::quat orientation)
{
	TransformComponent* tc = new TransformComponent(position, orientation);

	addComponent(tc);
	addComponent(new ModelComponent(model));

	addComponent(new CameraComponent());

	addComponent(new SceneStateComponent());

	PassInPlayerState::SetPlayerPosition(position);
}

PlayerCharacter::PlayerCharacter(Model* model, glm::vec3 position, glm::quat orientation, float height, float width)
{
	TransformComponent* tc = new TransformComponent(position, orientation);

	tc->height = height;
	tc->width = width;

	addComponent(tc);
	addComponent(new ModelComponent(model));

	addComponent(new CameraComponent());

	addComponent(new SceneStateComponent());

	PassInPlayerState::SetPlayerPosition(position);
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::OnUpdate(float dt)
{
	if (getComponent<CameraComponent>() != nullptr)
	{
		getComponent<CameraComponent>()->setPosition(getComponent<TransformComponent>()->m_position + glm::vec3(0.f, 0.f, 10.f));
	}
}

void PlayerCharacter::OnMessage(const std::string msg)
{

	
}

glm::vec3 PlayerCharacter::getEulerAngles()
{
	TransformComponent* tc = getComponent<TransformComponent>();

	return tc->getEulerAngles();
}

void PlayerCharacter::ReducePlayerHealthBy(unsigned short damage)
{
	m_playerHealth -= damage;
}

unsigned short PlayerCharacter::GetPlayerHealth()
{
	return m_playerHealth;
}

