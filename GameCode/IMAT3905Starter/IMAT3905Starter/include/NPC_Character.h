#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "ModelComponent.h"

#include "MessageSender.h"
#include "AI_Component.h"
#include "PlayerCharacter.h"

/*! \class This will act as the NPC's main object. */
class NPC_Character : public GameObject
{
public:
	/*! \fn Constructor.
	*Param One Model pointer.
	*Param Two Position of model.
	*Param Three Orientation of model.
	*/
	NPC_Character(Model* model, glm::vec3 position, glm::quat orientation);

	/*! \fn Deconstructor. */
	~NPC_Character();

	/*! \fn Used to update this class every frame.
	*Param One float The current delta (change in) time since last frame.
	*/
	void OnUpdate(float dt) override;

	/*! \fn Used to respond to inputs.
	*Param One String The input message.
	*/
	void OnMessage(const std::string msg) override;

private:
	/*! \var Player Character Object position */
	glm::vec3 m_playerPosition;
	/*! \var Distance between Player and NPC. */
	float m_playerNPCDistance;
	/*! \var Distance between NPC Arrow and NPC. */
	float m_arrowNPCDistance;
	/*! \var NPC Health */
	unsigned short m_NPCHealth = 100;
	/*! \var Boolen to analyse arrow position when hit something */
	bool m_analyseCurrentShot = false;

	float m_currentAngle;
	float m_desiredAngle;
	float m_startingAngle;
	glm::vec3 m_arrowPosition;
};

