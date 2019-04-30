#pragma once

#include "GameObject.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "SceneStateComponent.h"

#include <iostream>

class ArrowObject : public GameObject
{

public:

	ArrowObject(Model* model, glm::vec3 position, glm::quat orientation);

	~ArrowObject();

private:

	// Data Members 

public:

	// Member Functions 

	void OnUpdate(float dt) override;
	
	void OnMessage(const std::string m) override;

	void MouseInput(float x, float y);

};