#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(Model* model, glm::vec3 position, glm::quat orientation)
{
	TransformComponent* tc = new TransformComponent(position, orientation);

	addComponent(tc);
	addComponent(new ModelComponent(model));
	addComponent(new CameraComponent());
	addComponent(new SceneStateComponent());
	SetCameraPositionFromTransformComponent(tc);

	PassInPlayerState::SetPlayerPosition(position);
}
PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::OnUpdate(float dt)
{
	//Dominic

	//Since camera and turns will be switched automatically, I don't think camera will require any messages to be swithed on Onmessage function

	//Code to switch turns and camera

	if (TurnState::m_currentTurn == Turn::PlayerTurn)
	{
		m_newCameraState = NewCameraViewState::PlayerView;

		//Suggestion: Paste code to drag mouse to shoot from bow here, maybe as a function

		//After Player pressed(released) to shoot, change turn
		TurnState::m_currentTurn = Turn::WaitingTurn;
		TurnState::m_previousTurn = Turn::PlayerTurn;
	}
	else if (TurnState::m_currentTurn == Turn::WaitingTurn)
	{
		//Camera will look at arrow
		m_newCameraState = NewCameraViewState::ArrowView;

		//Suggestion: Paste code to process this code when arrow hits something

		//After it hit something, change turn
		//If it was player before
		if (TurnState::m_previousTurn == Turn::PlayerTurn)
		{
			//NPC turn
			TurnState::m_currentTurn = Turn::NPCTurn;
		}
		//If it was NPC before
		else if (TurnState::m_previousTurn == Turn::NPCTurn)
		{
			//Player turn
			TurnState::m_currentTurn = Turn::PlayerTurn;
		}
	}
	//This will only change camera, all code will be running in NPC character
	else if (TurnState::m_currentTurn == Turn::NPCTurn)
	{
		m_newCameraState = NewCameraViewState::NPCView;
	}
}
void PlayerCharacter::OnMessage(const std::string msg)
{

	TransformComponent* tc = getComponent<TransformComponent>();

	if (msg == "setCameraFirstPerson")
	{
		m_cameraState = CameraViewState::firstPersonCamera;
	}
	else if (msg == "setCameraThirdPerson")
	{
		m_cameraState = CameraViewState::thirdPersonCamera;
	}
	else if (msg == "Level1")
	{
		// pass message on to sceneComponent
		getComponent<SceneStateComponent>()->OnMessage("Level1");
	}
	else if (msg == "Level2")
	{
		getComponent<SceneStateComponent>()->OnMessage("Level2");

	}
	else
	{
		// pass message to transform component
		tc->OnMessage(msg);
	}
	SetCameraPositionFromTransformComponent(tc);
}

void PlayerCharacter::SetCameraPositionFromTransformComponent(TransformComponent* tc)
{
	// get resulting position
	glm::vec3 pos = tc->m_position;
	glm::quat orient = tc->getOrientation();
	// camera behind and above us OR at centre...

	glm::vec3 relativePosition;		// could use ? operator here
	if (m_cameraState == CameraViewState::thirdPersonCamera)
	{
		relativePosition = glm::vec3(0, 1.5, 6);		//above and behind
	}
	else
	{
		relativePosition = glm::vec3(0, 0.5, -0.95);	//just in front of model
	}
	pos += orient * relativePosition;

	// put camera there
	CameraComponent* cc = getComponent<CameraComponent>();
	cc->setPosition(pos);
	cc->setOrientation(orient);
}

glm::vec3 PlayerCharacter::getEulerAngles()
{
	TransformComponent* tc = getComponent<TransformComponent>();

	return tc->getEulerAngles();
}

