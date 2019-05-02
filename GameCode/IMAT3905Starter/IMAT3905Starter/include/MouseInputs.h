#pragma once
#include <glm/glm.hpp>
#include <iostream>

class MouseInputs
{
public: 
	MouseInputs(); 

	void getInitialXY(double x, double y);

	void getLastXY(double x, double y); 

	void checkButtonPress(int button);

	glm::vec2 getDifference();    //to get a vector by which to translate the player arrow. Does not output final values to console. 

	//void getDifference();    //Just to output the final values to console as separate double values. For actual vector use the glm::vec2 function above. 

	~MouseInputs(); 


private:
	double initX; 
	double initY;
	double lastX; 
	double lastY;

	bool releasable = false; 
	bool firstClick = false; 
	bool getInit = false;
	bool getLast = false; 
	bool initGot = false; 
	bool lastGot = false; 
	bool calcDifference = false; 

	double finalX, finalY; 
	glm::vec2 difference;
};
