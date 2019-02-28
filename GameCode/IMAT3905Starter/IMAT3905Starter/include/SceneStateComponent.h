#pragma once
#include "Component.h"

/*! \class USed to check the current scene state within the game. */
class SceneStateComponent : public Component
{
public:

	/*! \fn Constructor. */
	SceneStateComponent();

	/*! \fn Deconstructor. */
	~SceneStateComponent();

	/*! \fn Used to update this component. */
	void OnUpdate(float dt) override;
	
	/*! \fn Used to react to certain inputs within the game loop. */
	void OnMessage(const std::string msg) override;

	/*! \fn Used to get the current scene index (which level is currently loaded). */
	int GetSceneIndex();

	/*! \fn USed to set the current scene index (to switch between levels). */
	void SetSceneIndex(int newSceneIndex);

private:

	/*! \var The current scene loaded. */
	int m_sceneIndex;

};