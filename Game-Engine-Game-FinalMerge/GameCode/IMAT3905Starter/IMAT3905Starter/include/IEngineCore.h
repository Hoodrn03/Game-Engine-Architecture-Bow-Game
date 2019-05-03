#pragma once
#include <string>
#include <iostream>
#include <glm/mat4x4.hpp>

// high definition timer code...
#include <chrono>

using namespace std::chrono_literals;

// use a fixed timestep of 1 / (60 fps) approx = 16 milliseconds
constexpr std::chrono::milliseconds dt(16ms);


class Model;
class CameraComponent;
class Game;

class IEngineCore
{
public:

	/*! \fn Deconstructor */
	virtual ~IEngineCore() {}

	/*! \fn Used to initalize a game window.
	*Param One int The width for the window.
	*Param Two int The height for the window.
	*Param Three string The name for the window.
	*/
	virtual bool initWindow(int width, int height, std::string windowName) = 0;

	/*! \fn Used to run the game loop for the engine.
	*Param One The game object to run.
	*/
	virtual bool runEngine(Game* game) = 0;

	// some simple drawing tools - will want to move these to a proper renderer class later

	/*! \fn Used to display a coloured background for the game engine.
	*Param One float The amount of Red.
	*Param Two float The amount of Green.
	*Param Three float The amount of Blue.
	*/
	virtual void renderColouredBackground(float r, float g, float b) = 0;

	/*! \fn Used to render text into the game.
	*Param One string The text to display.
	*Param Two float The X position to display.
	*Param Three float The Y position to display.
	*Param Four float The scale (Size) of the text.
	*Param Five vec3 The colour for the text.
	*/
	virtual void renderText(std::string text, float x, float y, float scale, glm::vec3 colour) = 0;
	
	/*! \fn Used to set a primary camera.
	*Param One CameraComponent The new main camera.
	*/
	virtual	void setCamera(const CameraComponent* cam) = 0;
	
	/*! \fn Used to draw a cube object into the game.
	*Param One mat4 The model matrix for the cube.
	*/
	virtual void drawCube(const glm::mat4& modelMatrix) = 0;

	/*! \fn Used to draw a model into the game.
	*Param One Model The model to draw.
	*Param Two mat4 The model's matrix.
	*/
	virtual void drawModel(Model* model, const glm::mat4& modelMatrix) = 0;

	/*! \fn Used to get the duration of this frame. */
	virtual double getFrameDuration() = 0;

	// new for mouse

	/*! \fn Used to get the mouse's current state.
	*Param One double The mouse's X position.
	*Param Two double The mouse's Y position.
	*Param Three int The mouse buttons state.
	*/
	virtual void getMouseState(double& mouseX, double& mouseY, int& mouseButtons) = 0;

};