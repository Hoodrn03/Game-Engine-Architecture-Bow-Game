#pragma once

// include assimp first - error C2589 for 
#include "Model.h"

#include "GameObject.h"
#include "PlayerCharacter.h"
#include "IEngineCore.h"

#include <string>


//class Model;
class ModelManager;

/*! \class Used to create a scene within the game. */
class Scene
{

public:

	/*! \fn Constructor. */
	Scene(std::string filename, ModelManager* theModelManager, IEngineCore* engineCore);
	
	/*! \fn Deconstructor. */
	~Scene();

	/*! \fn Used to update this component. */
	void update(float dt);
	
	/*! \fn Used to render the currently loaded scene. */
	void render(IEngineCore* engineCore);
	
	/*! \fn Used to load a level from file. */
	void loadLevel(std::string levelFile);

	/*! \fn Used to load a level from file. */
	bool loadLevelJSON(std::string levelJSONFile);

	/*! \fn Used to gain access to the player object. */
	PlayerCharacter* getPlayer();
	std::vector <glm::vec3> mapPoints1;
	std::vector <glm::vec3> mapPoints2;

private:

	/*! \var USed to ensure a level is loaded. */
	bool m_levelLoaded{ false };

	/*! \var The index to find the player from a list of game objects. */
	int m_playerIndex{ 1 };

	/*! \var Used to get the background object. */
	GameObject* m_playerBackground;

	/*! \var A list of game objects within the game. */
	std::vector<GameObject*> v_gameObjects;

	/*! \var The model manager used to load all of the game's models. */
	ModelManager* m_theModelManager;

	// mouse data - we keep old position (last frame or update) so we can get delta's

	double m_oldMouseX;
	double m_oldMouseY;
	double m_mouseX;
	double m_mouseY;
	int m_mouseButtons;
	int m_oldMouseButtons;
	bool m_mouseEnabled{ false };
};
