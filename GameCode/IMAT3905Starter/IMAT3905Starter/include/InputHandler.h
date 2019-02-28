#pragma once
#include <map>
#include <vector>
#include "InputCommand.h"

class GameObject;

// much better here as a class, not a struct

/*! \class Used to handle all of the inputs within the game. */
class InputHandler
{	
private:

	/*! \fn The main game object controled by the player. */
	GameObject* m_playerCube;

	/*! \var This will be used to link a connamd to an input value (Character on keyboard). */
	std::map<int, InputCommand*> m_controlMapping;

public:

	/*! \fn Constructor */
	InputHandler(GameObject* playerCube);	// : m_playerCube(playerCube);

	/*! \fn Used to handle the game inputs. */
	void handleInputs(const std::vector<bool>& keyBuffer);
};
