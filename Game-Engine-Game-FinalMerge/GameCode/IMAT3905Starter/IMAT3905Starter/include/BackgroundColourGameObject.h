#pragma once
#include "GameObject.h"

/*! \class THis will be used to control the background colour for the game engine. */
class BackgroundColourGameObject : public GameObject
{
public:
	// has no model or transform
	
	/*! \fn Constructor */
	BackgroundColourGameObject();

	/*! \fn Used to update this class every frame. 
	*Param One float The current delta (change in) time since last frame. 
	*/
	void OnUpdate(float dt) override;
	
	/*! \fn Used to respond to inputs. 
	*Param One String The input message. 
	*/
	void OnMessage(const std::string msg) override;

};
