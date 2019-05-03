#pragma once
#include "Game.h"

#include "Defs.h"

#include "MouseInputs.h"
#include "../CameraObject.h"

#include "CollisionDetection.h"


class ModelManager;

/*! \class A game created with the game engine's functionality. */
class ExampleGame : public Game
{
public:

	/*! \fn Constructor */
	ExampleGame(IEngineCore* engine);

	/*! \fn Used to update this class every frame.
	*Param One float The current delta (change in) time since last frame.
	*/
	void update(float dt) override;

	/*! \fn Used to render all game objects into the current scene. */
	void render() override;

	/*! \fn Used for setting up the game. */
	void Initialise();

	void SetMouseInput(int mouseInput);

	void SetXY(double mouseX, double mouseY);


	CameraObject * m_CamObj = nullptr;

	CollisionDetection* m_CollDect = nullptr; 



private:

	/*! \var This will manage all of teh models used within this game. */
	ModelManager* m_theModelManager = nullptr;

	MouseInputs temp; 

	/*! \var Used to keep track of the current scene or level. */
	int m_sceneIndex{ 0 };

	//these could be loaded from a file...
	/*! \var A list of levels via their file path. */
	std::string m_sLevelNames[2] = {
		"assets/levels/levelOne.json",
		"assets/levels/levelTwo.json"
	};

	int m_iMouseButtons = 0; /*! < Used to check the current state of the mouse buttons.  */
	double m_dMouseX = 0; /*! < The current X position of the mouse. */
	double m_dMouseY = 0; /*! < The current Y position of the mouse. */

	bool m_tempbool = true;
	float timer = 0;

	bool m_bPlayerWon = false;
	bool m_bNPCWon = false;
};
