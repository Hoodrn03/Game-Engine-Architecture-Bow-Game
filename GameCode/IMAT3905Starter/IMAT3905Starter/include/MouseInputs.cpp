#include "MouseInputs.h"

MouseInputs::MouseInputs()
{
}

void MouseInputs::getInitialXY(double x, double y)
{
	if (getInit)
	{
		initX = x;
		initY = y;

		std::cout << initX << " " << initY << std::endl;
		getInit = false; 
		initGot = true; 
	}
}

void MouseInputs::getLastXY(double x, double y)
{
	if (getLast)
	{
		lastX = x;
		lastY = y;

		std::cout << "SEC " << lastX << " " << lastY << std::endl;
		getLast = false; 
		lastGot = true; 
	}
}

glm::vec2 MouseInputs::getDifference()
{
	double finalX = 0, finalY = 0;

	if (initGot && lastGot)
	{
		finalX = lastX - initX;
		finalY = lastY - initY;

		std::cout << "FINAL " << finalX << " " << finalY << std::endl;
		
		initGot = false; 
		lastGot = false; 
	}

	return glm::vec2(finalX, finalY);
}

/*void MouseInputs::getDifference()
{
	double finalX = 0, finalY = 0;

	if (initGot && lastGot)
	{
		finalX = lastX - initX;
		finalY = lastY - initY;

		//std::cout << "FINAL " << finalX << " " << finalY << std::endl;

		std::cout << "FINAL " << finalX << "," << finalY << std::endl;

		initGot = false;
		lastGot = false;
	}
}*/

void MouseInputs::checkButtonPress(int button)
{
	if (button == 1 && !firstClick)
	{
		std::cout << "PRESSED" << std::endl;
		releasable = true; 
		firstClick = true; 
		getInit = true; 
	}
	if (button == 0 && releasable == true)
	{
		std::cout << "RELEASED" << std::endl; 
		releasable = false; 
		firstClick = false; 
		getLast = true; 
	}
}

MouseInputs::~MouseInputs()
{
}