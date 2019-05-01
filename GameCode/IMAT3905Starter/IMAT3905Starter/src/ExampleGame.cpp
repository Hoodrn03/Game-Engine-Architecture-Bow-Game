#include "ExampleGame.h"

#include "ModelManager.h"
#include "Scene.h"

//needed for test code
#include "GameObject.h"
#include "TransformComponent.h"
#include "SceneStateComponent.h"


//#include <stdio.h>
#include <string>
//#include <vector>
//#include <iostream>
//#include <fstream>
#include <sstream>
//#include "InputHandler.h"


CameraObject CO(glm::vec3(0.f, 0.f, 0.f), glm::quat(0.f, 0.f, 0.f, 0.f));

ExampleGame::ExampleGame(IEngineCore* engine) : Game(engine)
{
	Initialise();

	glm::vec3 * tempOne = new glm::vec3( 0.f, 2.f, 0.f );

	glm::vec3 * tempTwo = new glm::vec3(2.f, 0.f, 0.f);

	glm::vec3 * tempThree = new glm::vec3(0.f, 0.f, 2.f);

	CO.m_SetPlayerPos(tempOne);
	CO.m_SetEnemyPos(tempTwo);
	CO.m_CurrentArrowPos(tempThree); 

	CO.OnUpdate(0.0f, 2); 


}

glm::vec2 result; 

void ExampleGame::update(float dt) 
{
	int desiredSceneIndex = m_scene->getPlayer()->getComponent<SceneStateComponent>()->GetSceneIndex();

	if (desiredSceneIndex != m_sceneIndex)
	{
		delete m_scene;


		m_sceneIndex = desiredSceneIndex;

		m_scene = new Scene(m_levelNames[m_sceneIndex], m_theModelManager, m_engineInterfacePtr);
		m_inputHandler = new InputHandler(m_scene->getPlayer());  // or have a set function perhaps better then a new instance!
	}

	/*if (g_mouseButtons == 1)
	{
		std::cout << g_mouseButtons << std::endl;
	}*/
	
	temp.checkButtonPress(m_mouseButtons);
	temp.getInitialXY(m_mouseX, m_mouseY);
	temp.getLastXY(m_mouseX, m_mouseY);
	result = temp.getDifference(); 
	//temp.getDifference(); 


	//std::cout << "FINAL " << result << std::endl; 
	
}
void ExampleGame::render() 
{
	m_scene->render(m_engineInterfacePtr);

	double frameDuration = m_engineInterfacePtr->getFrameDuration();

	if (frameDuration > 0)
	{
		glm::vec3 eulerAngles = m_scene->getPlayer()->getEulerAngles();

		// convert to deg
		eulerAngles.x = glm::degrees(eulerAngles.x);
		eulerAngles.y = glm::degrees(eulerAngles.y);
		eulerAngles.z = glm::degrees(eulerAngles.z);
		std::ostringstream oss;
		oss << " (" << eulerAngles.x << ", " << eulerAngles.y << ", " << eulerAngles.z << ")"; // fps:" << (1 / frameDuration);
		//oss << frameDuration;
		m_engineInterfacePtr->renderText(oss.str(), 0.01f, 0.01f, 1, glm::vec3(1, 1, 0));
	}
}

//bool ExampleGame::loadLevelJSON(std::string levelJSONFile)
//{
//
//
//}

void ExampleGame::Initialise()
{
	m_theModelManager = new ModelManager();	// singleton later...
	m_scene = new Scene(m_levelNames[m_sceneIndex], m_theModelManager, m_engineInterfacePtr);
	m_inputHandler = new InputHandler(m_scene->getPlayer());

}

void ExampleGame::SetMouseInput(int mouseInput)
{
	m_mouseButtons = mouseInput;
}

void ExampleGame::SetXY(double mouseX, double mouseY)
{
	m_mouseX = mouseX;
	m_mouseY = mouseY; 
}
