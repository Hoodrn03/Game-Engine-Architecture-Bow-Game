#pragma once
#include <glm/glm.hpp>
#include <iostream>

class MouseInputs
{
public: 
	MouseInputs(); 

	void getInitialXY(float x, float y);

	void getLastXY(float x, float y); 

	void checkButtonPress(int button);

	glm::vec2 getDifference(); 

	~MouseInputs(); 


private:
	float initX; 
	float initY;
	float lastX; 
	float lastY;
	glm::vec2 difference;
};
