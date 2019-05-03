#include "ExampleGame.h"

#include "ModelManager.h"
#include "Scene.h"

//needed for test code
#include "GameObject.h"
#include "TransformComponent.h"
#include "SceneStateComponent.h"

#include "PlayerCharacter.h"
#include "NPC_Character.h"
#include "ArrowObject.h"
#include "MessageSender.h"


//#include <stdio.h>
#include <string>
//#include <vector>
//#include <iostream>
//#include <fstream>
#include <sstream>
//#include "InputHandler.h"

ExampleGame::ExampleGame(IEngineCore* engine) : Game(engine)
{
	Initialise();

}


void ExampleGame::update(float dt) 
{
	m_scene->update(dt);

	PlayerCharacter* Player = m_scene->getPlayer();
	NPC_Character* NPC = m_scene->getNPCCharacter();


	//Just to start from NPCTurn
	if (m_tempbool)
	{
		TurnState::m_currentTurn = Turn::PlayerTurn;
		m_tempbool = false;
	}

	if (NPC != nullptr && Player != nullptr)
	{
		if (Player->GetPlayerHealth() <= 0)
		{
			m_bNPCWon = true;
			TurnState::m_currentTurn == Turn::WaitingTurn;
		}
		if (NPC->GetNPCHealth() <= 0)
		{
			m_bPlayerWon = true;
			TurnState::m_currentTurn == Turn::WaitingTurn;
		}


		bool l_bIsPlayerHit = m_scene->m_CollisionDetector.m_GetPlayerHit();

		if (TurnState::m_currentTurn == Turn::NPCTurn)
		{
			timer += dt;
			if (timer > 30)
			{
				float l_Angle;
				float l_fPower;

				if (l_bIsPlayerHit)
				{
					l_Angle = NPC->getComponent<AI_Component>()->GetStableRandomAngle();
					l_fPower = NPC->getComponent<AI_Component>()->GetStableRandomPower();
				}
				else
				{
					l_Angle = NPC->getComponent<AI_Component>()->GetRandomAngle();
					l_fPower = NPC->getComponent<AI_Component>()->GetRandomPower();
				}

				glm::vec3 velocity = NPC->getComponent<AI_Component>()->ConvertAnglesToVelocity(l_Angle);

				m_scene->m_AddEnemyArrow(2);
				m_scene->m_SetEnemyArrowMoving(l_fPower / 100, velocity);

				//After execution
				TurnState::m_currentTurn = Turn::WaitingTurn; //waiting turn
				TurnState::m_previousTurn = Turn::NPCTurn;  // npc turn
				timer = 0;
			}
		}
		if (TurnState::m_currentTurn == Turn::PlayerTurn)
		{
			//After mouse released or arrow shot

			/*if (m_iMouseButtons == 1)
			{
				m_scene->m_AddArrow(1);
			}
			else if (m_iMouseButtons == 0)
			{
				m_scene->m_SetArrowMoving();
				//After execution
				TurnState::m_currentTurn = Turn::WaitingTurn;
				TurnState::m_previousTurn = Turn::PlayerTurn;
			}*/
		}

		if (TurnState::m_currentTurn == Turn::WaitingTurn)
		{
			//hit ground
			if (m_scene->m_CollisionDetector.m_GetGroundHit())
			{
				//If it was NPC arrow
				if (TurnState::m_previousTurn == Turn::NPCTurn)
				{
					ArrowObject* arrow = m_scene->getLatestArrow();
					glm::vec3 l_arrowPosition = arrow->getComponent<TransformComponent>()->m_position;
					glm::vec3 l_NPCPosition = NPC->getComponent<TransformComponent>()->m_position;
					glm::vec3 l_PlayerPosition = Player->getComponent<TransformComponent>()->m_position;

					float l_fArrowNPCDistance = NPC->getComponent<AI_Component>()->CalculateDistanceBetweenTwoObjects(l_arrowPosition, l_NPCPosition);
					float l_playerNPCDistance = NPC->getComponent<AI_Component>()->CalculateDistanceBetweenTwoObjects(l_PlayerPosition, l_NPCPosition);
					NPC->getComponent<AI_Component>()->ExecuteAlgorithm(l_playerNPCDistance, l_fArrowNPCDistance);

					TurnState::m_currentTurn = Turn::PlayerTurn;
				}

				if (TurnState::m_previousTurn == Turn::PlayerTurn)
				{
					TurnState::m_currentTurn = Turn::NPCTurn;
				}
			}
			//Check if player hit only once per turn
			if (m_scene->m_CollisionDetector.m_GetPlayerHit())
			{
				Player->ReducePlayerHealthBy(25);
				
				if (TurnState::m_previousTurn == Turn::NPCTurn)
				{
					TurnState::m_currentTurn = Turn::PlayerTurn;
				}
				if (TurnState::m_previousTurn == Turn::PlayerTurn)
				{
					TurnState::m_currentTurn = Turn::NPCTurn;
				}
			}

			//Check if NPC hit only once per turn
			if (m_scene->m_CollisionDetector.m_GetEnemyHit())
			{
				NPC->ReduceNPCHealthBy(25);

				if (TurnState::m_previousTurn == Turn::NPCTurn)
				{
					TurnState::m_currentTurn = Turn::PlayerTurn;
				}
				if (TurnState::m_previousTurn == Turn::PlayerTurn)
				{
					TurnState::m_currentTurn = Turn::NPCTurn;
				}
			}
		}
	}


	if (m_iMouseButtons == 1)
	{
		m_scene->m_AddArrow(1);
	}
	else if (m_iMouseButtons == 0)
	{
		m_scene->m_SetArrowMoving();
	}

	int desiredSceneIndex = m_scene->getPlayer()->getComponent<SceneStateComponent>()->GetSceneIndex();

	if (desiredSceneIndex != m_sceneIndex)
	{
		delete m_scene;


		m_sceneIndex = desiredSceneIndex;

		m_scene = new Scene(m_sLevelNames[m_sceneIndex], m_theModelManager, m_engineInterfacePtr);
		m_inputHandler = new InputHandler(m_scene->getPlayer());  // or have a set function perhaps better then a new instance!

	}
}

void ExampleGame::render() 
{
	m_scene->render(m_engineInterfacePtr);

	PlayerCharacter* Player = m_scene->getPlayer();
	NPC_Character* NPC = m_scene->getNPCCharacter();

	double frameDuration = m_engineInterfacePtr->getFrameDuration();

	if (frameDuration > 0)
	{
		if (NPC != nullptr && Player != nullptr)
		{
			float l_fPlayerHealth = Player->GetPlayerHealth();
			float l_fNPCHealth = NPC->GetNPCHealth();

			std::ostringstream oss;
			oss << " HP: " << l_fPlayerHealth; // fps:" << (1 / frameDuration);
			//oss << frameDuration;
			m_engineInterfacePtr->renderText(oss.str(), 0.01f, 0.9f, 1, glm::vec3(0, 1, 0));
			
			std::ostringstream oss2;
			oss2 << " HP: " << l_fNPCHealth; // fps:" << (1 / frameDuration);
			//oss << frameDuration;
			m_engineInterfacePtr->renderText(oss2.str(), 0.75f, 0.9f, 1, glm::vec3(0, 1, 0));

			if (m_bPlayerWon)
			{
				std::ostringstream oss3;
				oss3 << " Player Won! ";
				m_engineInterfacePtr->renderText(oss3.str(), 0.3f, 0.9f, 1, glm::vec3(0, 0, 1));
			}
			else if (m_bNPCWon)
			{
				std::ostringstream oss4;
				oss4 << " Player Lost! ";
				m_engineInterfacePtr->renderText(oss4.str(), 0.3f, 0.9f, 1, glm::vec3(0, 0, 1));
			}
		}
		/*glm::vec3 eulerAngles = m_scene->getPlayer()->getEulerAngles();

		// convert to deg
		eulerAngles.x = glm::degrees(eulerAngles.x);
		eulerAngles.y = glm::degrees(eulerAngles.y);
		eulerAngles.z = glm::degrees(eulerAngles.z);
		std::ostringstream oss;
		oss << " (" << eulerAngles.x << ", " << eulerAngles.y << ", " << eulerAngles.z << ")"; // fps:" << (1 / frameDuration);
		//oss << frameDuration;
		m_engineInterfacePtr->renderText(oss.str(), 0.01f, 0.01f, 1, glm::vec3(1, 1, 0));*/
	}
}

void ExampleGame::Initialise()
{
	m_theModelManager = new ModelManager();	// singleton later...
	m_scene = new Scene(m_sLevelNames[m_sceneIndex], m_theModelManager, m_engineInterfacePtr);
	m_inputHandler = new InputHandler(m_scene->getPlayer());

}

void ExampleGame::SetMouseInput(int mouseInput)
{
	m_iMouseButtons = mouseInput;
}

void ExampleGame::SetXY(double mouseX, double mouseY)
{
	m_dMouseX = mouseX;
	m_dMouseY = mouseY; 
}
