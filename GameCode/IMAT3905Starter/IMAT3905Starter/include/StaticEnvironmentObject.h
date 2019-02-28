#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

class Model;

/*! \class Used to create a game object which will remain static within the scene. */
class StaticEnvironmentObject : public GameObject
{
public:

	/*! \fn Constructor. */
	StaticEnvironmentObject(Model* model, glm::vec3 position, glm::quat orientation);

	/*! \fn Deconstructor. */
	~StaticEnvironmentObject();

	/*! \fn Used to update this component. */
	void OnUpdate(float dt) override;

	/*! \fn Used to react to certain inputs within the game loop. */
	void OnMessage(const std::string msg) override;
};