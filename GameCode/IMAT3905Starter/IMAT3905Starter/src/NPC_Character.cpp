#include "NPC_Character.h"

NPC_Character::NPC_Character(Model* model, glm::vec3 position, glm::quat orientation)
{
	addComponent(new TransformComponent(position, orientation));
	addComponent(new ModelComponent(model));
	addComponent(new AI_Component);

	m_playerPosition = PassInPlayerState::GetPlayerPosition();
	m_playerNPCDistance = getComponent<AI_Component>()->CalculateDistanceBetweenTwoObjects(m_playerPosition, position);
}
NPC_Character::~NPC_Character()
{
}

void NPC_Character::OnUpdate(float dt)
{
	if (TurnState::m_currentTurn == Turn::NPCTurn)
	{
		//Pass in boolean is hit player or not here
		getComponent<AI_Component>()->GetRandomAngle();
		getComponent<AI_Component>()->GetRandomPower();

		//Animate the movement??? or move bow smoothly with dt until desired angle, will be in AI component
		//Spawn ArrowObject(shoot)

		//After execution
		TurnState::m_currentTurn = Turn::WaitingTurn;
		TurnState::m_previousTurn = Turn::NPCTurn;
	}

	//Code to find if arrow hit something
	//If hit,
	m_analyseCurrentShot = true;

	//Will need to access this, but right now I don't have arrow object
	//m_arrowNPCDistance = getComponent<AI_Component>()->CalculateDistanceBetweenTwoObjects(arrowposition, position);


	//Obviously this needs to be tested out to achieve optimal results
	//By tweaking little by little variables and adding more algorithms

	if (m_analyseCurrentShot)
	{
		//Execute if player was not hit
		if (!PassInPlayerState::m_isPlayerHit)
		{
			getComponent<AI_Component>()->ExecuteAlgorithm(m_playerNPCDistance, m_arrowNPCDistance);
		}
		//else just ignore
		m_analyseCurrentShot = false;
	}
}
void NPC_Character::OnMessage(const std::string msg)
{
}

