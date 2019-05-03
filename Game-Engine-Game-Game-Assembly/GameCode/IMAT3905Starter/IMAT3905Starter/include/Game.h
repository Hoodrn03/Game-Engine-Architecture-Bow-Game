#pragma once
#include "IEngineCore.h"
#include "InputHandler.h"

class Model;
class Scene;

/*! \calss An empty game object to initalize a finished game to run. */
class Game
{
public:

	/*! \fn Constructor */
	Game(IEngineCore* engine);

	/*! \fn Deconstructor */
	virtual ~Game();

	/*! \fn Used to update this class every frame.
	*Param One float The current delta (change in) time since last frame.
	*/
	virtual void update(float dt) = 0;
	
	/*! \fn Used to render all game objects into the current scene. */
	virtual void render() = 0;
	
	/*! \fn Used to gain access to the current input handler. */
	InputHandler* getInputHandler();

	virtual void SetMouseInput(int mouseInput) = 0;

	virtual void SetXY(double mouseX, double mouseY) = 0;

protected:

	/*! \var The game core the game is running on; (Which platform).*/
	IEngineCore* m_engineInterfacePtr;
	
	/*! \var An input handler for the game used to manage all inputs. */
	InputHandler* m_inputHandler;
	
	/*! \var The current scene the game is using. */
	Scene* m_scene;
};
