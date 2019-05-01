#include "NPC_Character.h"

NPC_Character::NPC_Character(Model* model, glm::vec3 position, glm::quat orientation)
{
	addComponent(new TransformComponent(position, orientation));
	addComponent(new ModelComponent(model));
	addComponent(new AI_Component);

	m_playerPosition = PassInPlayerState::GetPlayerPosition();
	//m_playerNPCDistance = getComponent<AI_Component>()->CalculateDistanceBetweenTwoObjects(m_playerPosition, position);
	m_playerNPCDistance = getComponent<AI_Component>()->CalculateDistanceBetweenTwoObjects(glm::vec3(0,0,0), glm::vec3(50, 0, 0));
}
NPC_Character::~NPC_Character()
{
}

void NPC_Character::OnUpdate(float dt)
{
	//NPCTurn
	if (TurnState::m_currentTurn == Turn::NPCTurn)
	{
		//Pass in boolean is hit player or not here
		getComponent<AI_Component>()->GetRandomAngle();
		getComponent<AI_Component>()->GetRandomPower();

		m_desiredAngle = getComponent<AI_Component>()->GetAngle();
		m_startingAngle = getComponent<AI_Component>()->GetStartingAngle();

		m_currentAngle = m_startingAngle;

		int speed = 1;
		while (m_currentAngle < m_desiredAngle)
		{
			m_currentAngle += speed * dt;
			//Rotate bow at the same time
			//Get orientation from bow and change it
			//Same with arrow
			glm::quat rotation = glm::quat(glm::vec3(0, 0, m_currentAngle));
		}

		//Spawn ArrowObject(shoot)

		//m_arrowPosition = glm::vec3(10, 0, 0);


		//After execution
		TurnState::m_currentTurn = Turn::WaitingTurn; //waiting turn
		TurnState::m_previousTurn = Turn::NPCTurn;  // npc turn
	}

	//Code to find if arrow hit something
	//bool m_HitGround = true;
	//bool m_HitPlayer = false;

	//Will need to access this, but right now I don't have arrow object
	//m_arrowNPCDistance = getComponent<AI_Component>()->CalculateDistanceBetweenTwoObjects(arrowposition, position);


	//Obviously this needs to be tested out to achieve optimal results
	//By tweaking little by little variables and adding more algorithms

	//Execute if player was not hit
	//if (!PassInPlayerState::m_isPlayerHit)
	//{
		m_arrowNPCDistance = getComponent<AI_Component>()->CalculateDistanceBetweenTwoObjects(glm::vec3(-5, 0, 0), glm::vec3(50, 0, 0));
		getComponent<AI_Component>()->ExecuteAlgorithm(m_playerNPCDistance, m_arrowNPCDistance);
	//}

	//Do not do anything else since I want to keep same range and same power to hit player, the Get Range and power will change values themselves
}
void NPC_Character::OnMessage(const std::string msg)
{
}

