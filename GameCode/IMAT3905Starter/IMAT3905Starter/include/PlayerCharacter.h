#pragma once
#include "GameObject.h"
#include "ColourComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "SceneStateComponent.h"

/*! \class This will act as the player's main object. */
class PlayerCharacter : public GameObject
{
	/*! \enum The current state of the camera. */
	enum class CameraViewState { 
		firstPersonCamera, /*!< Use to make a first person camera. */
		thirdPersonCamera /*!< Use to make a third person camera. */
	};

public:

	// constructor

	/*! \fn Constructor. */
	PlayerCharacter(Model* model, glm::vec3 position, glm::quat orientation);
	
	/*! \fn Deconstructor. */
	~PlayerCharacter();
	
	/*! \fn Used to update this component. */
	void OnUpdate(float dt) override;

	/*! \fn Used to react to certain inputs within the game loop. */
	void OnMessage(const std::string msg) override;

	/*! \fn Used to set the camera's position using the current transform. */
	void SetCameraPositionFromTransformComponent(TransformComponent* tc);
	
	/*! \fn USed to get Euler Angles? */
	glm::vec3 getEulerAngles();


private:

	/*! \var The current state of the player's camera. */
	CameraViewState m_cameraState{ CameraViewState::thirdPersonCamera };
};

