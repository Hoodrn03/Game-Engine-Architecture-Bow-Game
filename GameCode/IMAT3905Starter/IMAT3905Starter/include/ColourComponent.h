#pragma once
#include "Component.h"

/*! \class This will be used to control colour within the game engine. */
class ColourComponent : public Component
{
public:
	
	/*! \fn Constructor */
	ColourComponent() : m_colourValue(0.25) {};

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
		if (m == "increase")
		{
			m_colourValue += ColourAdjustmentValue;
		}
		else if (m == "decrease")
		{
			m_colourValue -= ColourAdjustmentValue;
		}

	}

	/*! \var The Current colour value. */
	float m_colourValue;

private:

	/*! \var The constant value the current colour value will change by. */
	const float ColourAdjustmentValue = 0.001f;
	
};

/*! \class The amount of Red the object will have. */
class RedComponent : public ColourComponent {};

/*! \class The amount of Green the object will have. */
class GreenComponent : public ColourComponent {};

/*! \class The amount of Blue the object will have. */
class BlueComponent : public ColourComponent {};