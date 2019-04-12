#pragma once
#include "Component.h"

class AI_Component : public Component
{
private:
public:
	AI_Component()
	{

	}

	/*! \fn Used to update this class every frame.
	*Param One float The current delta (change in) time since last frame.
	*/
	void OnUpdate(float dt) override
	{
	}

	/*! \fn Used to respond to inputs.
	*Param One String The input message.
	*/
	void OnMessage(const std::string m) override
	{

	}
};