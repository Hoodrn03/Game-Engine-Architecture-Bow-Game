#include "MessageSender.h"

Turn TurnState::m_currentTurn = Turn::PlayerTurn;
Turn TurnState::m_previousTurn = Turn::NPCTurn;

glm::vec3 PassInPlayerState::m_playerPosition;
bool PassInPlayerState::m_isPlayerHit;

void PassInPlayerState::SetPlayerPosition(glm::vec3 playerPosition)
{
	m_playerPosition = playerPosition;
}

glm::vec3 PassInPlayerState::GetPlayerPosition()
{
	return m_playerPosition;
}