#pragma once

#include <glm/glm.hpp>

/*! \enum Decides which turn is in the game, players or NPC. */
enum class Turn
{
	PlayerTurn, /*!< Player Turn to act. */
	NPCTurn, /*!< NPC Turn to act. */
	WaitingTurn /*!< Waiting Turn when arrow is still flying. */
};

/*! \class TurnState, which has saved turns in the game */
class TurnState
{
public:
	/*! \var static, The current Turn in the game. */
	static Turn m_currentTurn;
	/*! \var static, The previous Turn in the game. */
	static Turn m_previousTurn;
};

/*! \class PassInPlayerState, sends Player status to NPC */
class PassInPlayerState
{
public:
	/*! \fn static, Used to set player position.
	*Param One glm vec3 Player position.
	*/
	static void SetPlayerPosition(glm::vec3 playerPosition);
	/*! \fn static, Used to get player position. */
	static glm::vec3 GetPlayerPosition();

	/*! \var static, boolean to inform if Player got hit from NPC arrow */
	static bool m_isPlayerHit;
private:
	/*! \var static, player position */
	static glm::vec3 m_playerPosition;
};