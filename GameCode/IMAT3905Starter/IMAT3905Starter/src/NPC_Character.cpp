#include "NPC_Character.h"

NPC_Character::NPC_Character(Model* model, glm::vec3 position, glm::quat orientation)
{
	addComponent(new TransformComponent(position, orientation));
	addComponent(new ModelComponent(model));
	addComponent(new AI_Component);
}
NPC_Character::~NPC_Character()
{
}

void NPC_Character::OnUpdate(float dt)
{
	if (m_CurrentTurnState.GetTurn() == Turn::NPCTurn)
	{
		//DO AI STUFF
		//PseudoCode:
		//Majority calculations will be in AI_Component
		//Set Random Angle from 90 to 180
		//Set Random Power from 0 to 100(or other values, based on what vaues will be used in player character)
		//Animate the movement??? or move bow smoothly with dt until desired angle
		//Spawn ArrowObject(shoot)

		//After execution
		m_CurrentTurnState.SetTurn(Turn::WaitingTurn);
		m_PreviousTurnState.SetTurn(Turn::NPCTurn);
	}

	//PseudoCode:
	//Get info if undershot or overshot
	//If undershot
	//if angle was <135, increase power
	//else increase angle
	//If overshot
	//if angle was <135, decrease power
	//else decrease angle

	//Obviously this needs to be tested out to achieve optimal results
}
void NPC_Character::OnMessage(const std::string msg)
{
}

