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
	NPC_Character* NPC = m_scene->getNPCharacter();


	//Just to start from NPCTurn
	if (m_tempbool)
	{
		TurnState::m_currentTurn = Turn::NPCTurn;
		m_tempbool = false;
	}

	if (NPC != nullptr && Player != nullptr)
	{
		if (TurnState::m_currentTurn == Turn::NPCTurn)
		{
			//Pass in boolean is hit player or not here

			float l_Angle = NPC->getComponent<AI_Component>()->GetRandomAngle();
			float l_fPower = NPC->getComponent<AI_Component>()->GetRandomPower();

			glm::vec3 velocity = NPC->getComponent<AI_Component>()->ConvertAnglesToVelocity(l_Angle);

			m_scene->m_AddEnemyArrow(2);
			m_scene->m_SetEnemyArrowMoving(l_fPower / 100, velocity);

			//After execution
			TurnState::m_currentTurn = Turn::WaitingTurn; //waiting turn
			TurnState::m_previousTurn = Turn::NPCTurn;  // npc turn
		}

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
			}
		}
		if (m_scene->m_CollisionDetector.m_GetPlayerHit())
		{
			//Need to test out the behaviour of AI to see how it keeps dealing with this stuff
			//Right now get angle and get power will basically stay in almost same range as before, so this should work
			//But if not as planned, I'll change algorithm

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

	double frameDuration = m_engineInterfacePtr->getFrameDuration();

	if (frameDuration > 0)
	{
		glm::vec3 eulerAngles = m_scene->getPlayer()->getEulerAngles();

		// convert to deg
		eulerAngles.x = glm::degrees(eulerAngles.x);
		eulerAngles.y = glm::degrees(eulerAngles.y);
		eulerAngles.z = glm::degrees(eulerAngles.z);
		std::ostringstream oss;
		oss << " (" << eulerAngles.x << ", " << eulerAngles.y << ", " << eulerAngles.z << ")"; // fps:" << (1 / frameDuration);
		//oss << frameDuration;
		m_engineInterfacePtr->renderText(oss.str(), 0.01f, 0.01f, 1, glm::vec3(1, 1, 0));
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
