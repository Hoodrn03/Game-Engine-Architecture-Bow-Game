#pragma once

/*! \enum Decides which turn is in the game, players or NPC. */
enum class Turn
{
	PlayerTurn, /*!< Player Turn to act. */
	NPCTurn, /*!< NPC Turn to act. */
	WaitingTurn /*!< Waiting Turn when arrow is still flying. */
};

class TurnState
{
public:
	void SetTurn(Turn turn)
	{
		m_Turn = turn;
	}

	Turn GetTurn()
	{
		return m_Turn;
	}

private:
	Turn m_Turn{ Turn::PlayerTurn }; //Default value, might change this if any problems would occure

};