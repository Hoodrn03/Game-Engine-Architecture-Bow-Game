#pragma once
#include "GameObject.h"
#include "ColourComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "SceneStateComponent.h"

#include "Gravity.h"
#include "Velocity.h"

//Dominic
#include "MessageSender.h"

/*! \class This will act as the player's main object. */
class PlayerCharacter : public GameObject
{
	//Dominic: I will need those states in my turn state decision
	/*! \enum The current state of the camera. */
	enum class NewCameraViewState
	{
		PlayerView, /*!< Used to look at player character. */
		NPCView, /*!< Used to look at NPC character. */
		ArrowView /*!< Used to look at last shot flying arrow object. */
	};

public:

	// constructor

	/*! \fn Constructor. */
	PlayerCharacter(Model* model, glm::vec3 position, glm::quat orientation);
	PlayerCharacter(Model* model, glm::vec3 position, glm::quat orientation, float height, float width);
	
	/*! \fn Deconstructor. */
	~PlayerCharacter();
	
	/*! \fn Used to update this component. */
	void OnUpdate(float dt) override;

	/*! \fn Used to react to certain inputs within the game loop. */
	void OnMessage(const std::string msg) override;
	
	//Dominic's note: this is used because of Text to screen feature, Pete uses this to update text rendered on screen
	//with fps limitations in ExampleGame render() function

	//Do we need need this feature at all here?

	/*! \fn USed to get Euler Angles? */
	glm::vec3 getEulerAngles();

	/*! \fn Used to Reduce health points.
	*Param One unsigned short damage dealth to health.
	*/
	void ReducePlayerHealthBy(unsigned short damage);

	/*! \fn Health Getter
	*/
	unsigned short GetPlayerHealth();


private:

	//Dominic

	/*! \var Player Health */
	unsigned short m_playerHealth = 100;
};

