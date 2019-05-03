#pragma once
#include "IEngineCore.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/mat4x4.hpp>
#include "CameraComponent.h"
#include <map>

#include "Defs.h"

class Model;
class Game;

/*! \class An engine core using the GLFW functionality for the game. */
class GLFW_EngineCore : public IEngineCore
{
public:

	/*! \fn Deconstructor */
	~GLFW_EngineCore() override;

	/*! \fn Used to initalize a game window. 
	*Param One int The width for the window. 
	*Param Two int The height for the window. 
	*Param Three string The name for the window. 
	*/
	bool initWindow(int width, int height, std::string windowName) override;
	
	/*! \fn Used to run the game loop for the engine. 
	*Param One The game object to run. 
	*/
	bool runEngine(Game* game) override;

	/*! \fn Used to display a coloured background for the game engine. 
	*Param One float The amount of Red.
	*Param Two float The amount of Green.
	*Param Three float The amount of Blue.
	*/
	void renderColouredBackground(float r, float g, float b) override;
	
	/*! \fn Used to render text into the game. 
	*Param One string The text to display. 
	*Param Two float The X position to display. 
	*Param Three float The Y position to display. 
	*Param Four float The scale (Size) of the text. 
	*Param Five vec3 The colour for the text. 
	*/
	void renderText(std::string text, float x, float y, float scale, glm::vec3 colour) override;

	/*! \fn Used to set a primary camera. 
	*Param One CameraComponent The new main camera. 
	*/
	void setCamera(const CameraComponent* cam) override;

	/*! \fn Used to draw a cube object into the game. 
	*Param One mat4 The model matrix for the cube. 
	*/
	void drawCube(const glm::mat4& modelMatrix) override;

	/*! \fn Used to draw a model into the game. 
	*Param One Model The model to draw.
	*Param Two mat4 The model's matrix. 
	*/
	void drawModel(Model* model, const glm::mat4& modelMatrix) override;

	/*! \fn Used to get the duration of this frame. */
	double getFrameDuration();

	/*! \fn Used to get the mouse's current state.
	*Param One double The mouse's X position. 
	*Param Two double The mouse's Y position. 
	*Param Three int The mouse buttons state.
	*/
	void getMouseState(double& mouseX, double& mouseY, int& mouseButtons) override;


private:

	/*! \var The main game window. */
	GLFWwindow* m_window;

	/*! \var The main shader program used within the game. */
	GLuint m_defaultShaderProgram;

	/*! \var The shader program used to diaplay fonts within the game. */
	GLuint m_fontShaderProgram;


	// added PC 

	/*! \var The constant X position of the mouse. */
	static double m_mouseX;

	/*! \var The constant Y position of the mouse. */
	static double m_mouseY;

	/*! \var The state of the mouse buttons. */
	static int m_mouseButtons;

	/*! \var The current mouse action within the game. */
	static int m_mouseAction;

	/*! \struct Holds all state information relevant to a character as loaded using FreeType; 
	*			based on https://learnopengl.com/#!In-Practice/Text-Rendering
	*/
	struct Character {
		GLuint textureID;   /*!< ID handle of the glyph texture */
		glm::ivec2 size;    /*!< Size of glyph */
		glm::ivec2 bearing;  /*!< Offset from baseline to left/top of glyph */
		GLuint advance;    /*!< Horizontal offset to advance to next glyph */
	};

	/*! \var A list of character to be used within the game. */
	std::map<GLchar, Character> Characters;

	/*! \var The VAO and VBO used for displaying the fonts. */
	GLuint font_VAO, font_VBO;
	

	// why are these static?

	/*! \var The screen width for the game; Should be the same everywhere. */
	static int m_screenWidth;

	/*! \var The screen height for the game; Should be the same everywhere. */
	static int m_screenHeight;

	/*! \var The key buffer, (A list of keys in the order they were pressed). */
	static std::vector<bool> m_keyBuffer;

	/*! \var The max number of keys that the buffer can hold at a time. */
	static const int m_keyBufferSize = 400;  //this could easily be smaller...

	// we average 64 frames to get a frame rate
	static const int m_framesToMonitor = 64;
	std::vector<double> m_frameTimes;		//size will be m_framesToMonitor


	// input callbacks

	/*! \fn Used to check if the mouse has been moved. */
	static void mouseMoveCallbackEvent(GLFWwindow* window, double xPos, double yPos);

	/*! \fn Used to check if a mouse button has been pressed. */
	static void mouseButtonCallbackEvent(GLFWwindow* window, int button, int action, int mods);

	/*! \fn Used to check if a button on the keyboard was pressed */
	static void keyCallbackEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

	/*! /fn Usedd to check if the main game window was resized. */
	static void windowResizeCallbackEvent(GLFWwindow* window, int width, int height);
	

	void loadShader(std::string vertexShaderFile, std::string fragmentShaderFile, GLuint& shaderProgram);
	void setDefaultShaders();
	void initCubeModel();
	void setupDefaultFont();

};

