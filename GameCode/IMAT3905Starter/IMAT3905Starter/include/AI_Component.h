#pragma once
#include "Component.h"
#include "MessageSender.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

class AI_Component : public Component
{
private:
	/*! \var const Minimum Angle of NPC to shoot. */
	const float MIN_ANGLE = 90;
	/*! \var const Maximum Angle of NPC to shoot. */
	const float MAX_ANGLE = 180;
	/*! \var const Minimum Power of NPC to shoot. */
	const float MIN_POWER = 0;
	/*! \var const Maximum Power of NPC to shoot. */
	const float MAX_POWER = 100;


	/*! \var Minimum Angle current range of NPC to shoot. */
	float m_minAngleRange = MIN_ANGLE;
	/*! \var Maximum Angle current range of NPC to shoot. */
	float m_maxAngleRange = MAX_ANGLE;
	/*! \var Angle of NPC to shoot. */
	float m_angle;
	/*! \var Minimum Power current range of NPC to shoot. */
	float m_minPowerRange = MIN_POWER;
	/*! \var Maximum Power current range of NPC to shoot. */
	float m_maxPowerRange = MAX_POWER;
	/*! \var Power of NPC to shoot. */
	float m_power;

public:
	/*! \fn Construtor.*/
	AI_Component()
	{
		srand(time(NULL));
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
	/*! \fn Used to get random angle to inputs.
	*/
	float GetRandomAngle()
	{
		m_angle = RandomFloat(m_minAngleRange, m_maxAngleRange);
		// std::cout << "m_minAngleRange = " << m_minAngleRange << " m_maxAngleRange " << m_maxAngleRange << std::endl;

		return m_angle;
	}
	/*! \fn Used to get more stable random angle to inputs.
	*/
	float GetStableRandomAngle()
	{
		//make slight randomness when NPC shoots at the same target
		m_angle = RandomFloat(m_angle - 5, m_angle + 5);

		return m_angle;
	}
	/*! \fn Used to get random power to inputs.
	*/
	float GetRandomPower()
	{
		m_power = RandomFloat(m_minPowerRange, m_maxPowerRange);
		// std::cout << "m_minPowerRange = " << m_minPowerRange << " m_maxPowerRange " << m_maxPowerRange << std::endl;

		return m_power;
	}
	/*! \fn Used to get more stable random power to inputs.
	*/
	float GetStableRandomPower()
	{
		//make slight randomness when NPC shoots at the same target
		//if not hit, use range
		m_power = RandomFloat(m_power - 5, m_power + 5);

		return m_power;
	}
	/*! \fn General Random function.
	*/
	float RandomFloat(float minimum, float maximum)
	{
		float rangeSpan = maximum - minimum;
		return ((float)rand() / RAND_MAX) * rangeSpan + minimum; //from current min - current max
	}

	/*! \fn Used to Calculate Distance Between Two Objects.
	*Param One glm vec3 position of first object.
	*Param Two glm vec3 position of second object.
	*/
	float CalculateDistanceBetweenTwoObjects(glm::vec3 position1, glm::vec3 position2)
	{
		//for now
		return abs(position1.x - position2.x);
	}

	/*! \fn Used to execute AI behaviour.
	*Param One float distance between Player and NPC.
	*Param Two float distance between Arrow and NPC.
	*/
	void ExecuteAlgorithm(float playerNPCDistance, float arrowNPCDistance)
	{
		if (this != nullptr)
		{
			// std::cout << "m_angle = " << m_angle << " m_power = " << m_power << std::endl;
			//If undershot
			if (playerNPCDistance >= arrowNPCDistance)
			{
				if (m_angle <= (m_minAngleRange + m_maxAngleRange) / 2)
				{
					IncreaseRange(m_minPowerRange, m_maxPowerRange, MAX_POWER, 10);
				}
				else
				{
					IncreaseRange(m_minAngleRange, m_maxAngleRange, MAX_ANGLE, 15);
				}
			}
			//If overshot
			else if (playerNPCDistance < arrowNPCDistance)
			{
				if (m_angle <= (m_minAngleRange + m_maxAngleRange) / 2)
				{
					DecreaseRange(m_minPowerRange, m_maxPowerRange, MIN_POWER, 10);
				}
				else
				{
					DecreaseRange(m_minAngleRange, m_maxAngleRange, MIN_ANGLE, 15);
				}
			}
		}
		// std::cout << "m_angle = " << m_angle << "m_power = " << m_power << std::endl;
	}

	/*! \fn Used to increase range.
	*Param One float minimum current range.
	*Param Two float maximum current range.
	*Param Three float absolute maximum range value.
	*Param Four float increment of range.
	*/
	void IncreaseRange(float &minRange, float &maxRange, float absoluteMaxValue, float increment)
	{
		//If minimum reached current maximum range
		if (minRange + increment > maxRange)
		{
			//stop making it bigger that max range
			minRange = maxRange;
		}
		else
		{
			//Increase minimum
			minRange += increment;
		}
		//Do not increase more than absolute allowed max value
		if (maxRange + increment > absoluteMaxValue)
		{
			maxRange = absoluteMaxValue;
		}
		else
		{
			maxRange += increment;
		}
	}

	/*! \fn Used to decrease range.
	*Param One float minimum current range.
	*Param Two float maximum current range.
	*Param Three float absolute minimum range value.
	*Param Four float decrement of range.
	*/
	void DecreaseRange(float &minRange, float &maxRange, float absoluteMinValue, float decrement)
	{
		//Decrease range of power
		//Until it hits min
		if (minRange - decrement < absoluteMinValue)
		{
			minRange = absoluteMinValue;
		}
		else
		{
			minRange -= decrement;
		}
		//Do not decrease more than curret minimum range
		if (maxRange - decrement < minRange)
		{
			maxRange = minRange;
		}
		else
		{
			maxRange -= decrement;
		}
	}

	float GetAngle()
	{
		return m_angle;
	}

	float GetStartingAngle()
	{
		return MIN_ANGLE;
	}

	glm::vec3 ConvertAnglesToVelocity(float angle)
	{
		//X is from 1 to 0, so [90;180] - 90, then divide by 90 so [0;1], make this negative and add 1 to flip [1;0]
		float x = 1 + (-1 * (angle - 90) / 90);
		//Y is from 0 to 1, so just [90;180] - 90 and [0;90] divide by 90
		float y = (angle - 90) / 90;

		return glm::vec3(-x, y, 0);

		//return glm::vec3(-sin(angle), abs(cos(angle)), 0);
	}
};