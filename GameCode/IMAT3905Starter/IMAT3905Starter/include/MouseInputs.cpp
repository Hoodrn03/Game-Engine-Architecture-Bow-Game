#include "MouseInputs.h"

MouseInputs::MouseInputs()
{
}

void MouseInputs::getInitialXY(float x, float y)
{
	initX = x; 
	initY = y;
}

void MouseInputs::getLastXY(float x, float y)
{
	lastX = x;
	lastY = y;
}

glm::vec2 MouseInputs::getDifference()
{
	float finalX, finalY; 

	finalX = lastX - initX; 
	finalY = lastY - initY; 

	return glm::vec2(finalX, finalY);
}

void MouseInputs::checkButtonPress(int button)
{
	std::cout << button << std::endl;
	switch (button)
	{
	case 1: 
		break;
	default:
		break;
	}
}

MouseInputs::~MouseInputs()
{
}