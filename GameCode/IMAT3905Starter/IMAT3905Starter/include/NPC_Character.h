#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "ModelComponent.h"

#include "TurnState.h"
#include "AI_Component.h"

/*! \class This will act as the player's main object. */
class NPC_Character : public GameObject
{
public:
	/*! \fn Constructor. */
	NPC_Character(Model* model, glm::vec3 position, glm::quat orientation);

	/*! \fn Deconstructor. */
	~NPC_Character();

	/*! \fn Used to update this component. */
	void OnUpdate(float dt) override;

	/*! \fn Used to react to certain inputs within the game loop. */
	void OnMessage(const std::string msg) override;

private:

	/*! \var The current Turn in the game. */
	TurnState m_CurrentTurnState;
	/*! \var The previous Turn in the game. */
	TurnState m_PreviousTurnState;
};

