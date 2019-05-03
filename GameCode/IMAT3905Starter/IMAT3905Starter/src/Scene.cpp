#include "Scene.h"

#include "IEngineCore.h"
#include "Model.h"
#include "Game.h"
#include "TransformComponent.h"
#include "ColourComponent.h"
#include "ModelComponent.h"
#include "CameraComponent.h"
#include "ModelManager.h"
#include "JSON\json.h"

//#include "PlayerCharacter.h" already included in Scene.h
#include "StaticEnvironmentObject.h"
#include "BackgroundColourGameObject.h"

#include <fstream>
#include <sstream>

Scene::Scene(std::string filename, ModelManager* theModelManager, IEngineCore* engineCore) : m_theModelManager(theModelManager)
{
	m_playerBackground = new BackgroundColourGameObject();
	m_levelLoaded = loadLevelJSON(filename);

	m_CollisionDetector.m_SetPlayerObject(getPlayer());
	m_CollisionDetector.m_SetEnemyObject(getNPCharacter()); 

	m_CollisionDetector.m_SetMainMapPoints(mapPoints1); 

	engineCore->getMouseState(m_mouseX, m_mouseY, m_mouseButtons);

	m_oldMouseX = m_mouseX;
	m_oldMouseY = m_mouseY;
	m_oldMouseButtons = m_mouseButtons;
}


Scene::~Scene()
{

}


void Scene::update(float dt)
{
	for (unsigned int i = 0; i < v_gameObjects.size(); i++)
	{
		v_gameObjects[i]->OnUpdate(dt); 
	}

	for (unsigned int i = 0; i < v_Arrows.size(); i++)
	{
		v_Arrows[i]->OnUpdate(dt);
	}

	m_CollisionDetector.m_Update(); 

	std::cout << std::boolalpha << m_CollisionDetector.m_GetEnemyHit() << std::endl; 
	std::cout << std::boolalpha << m_CollisionDetector.m_GetPlayerHit() << std::endl; 

}

void Scene::render(IEngineCore* engineCore)
{
	// try mouse code here?

	PlayerCharacter* playerCharacter = getPlayer();

	
	// keep the old mouse position and button state
	m_oldMouseX = m_mouseX;
	m_oldMouseY = m_mouseY;
	m_oldMouseButtons = m_mouseButtons;

	// get the current mouse pos and button state
	engineCore->getMouseState(m_mouseX, m_mouseY, m_mouseButtons);
	
	double xDelta = m_mouseX - m_oldMouseX;
	double yDelta = m_mouseY - m_oldMouseY;

	// do we have a new button press
	if ((m_mouseButtons & 0x1) & !(m_oldMouseButtons & 0x1))
	{
		m_mouseEnabled = !m_mouseEnabled;
	}


	if (m_mouseEnabled)
	{
		const float mouseSensitivity = 200.0f;	// related to scrfeenwidth later might be better!

		float theta = static_cast<float>(xDelta) / mouseSensitivity;
		float thi = static_cast<float>(yDelta) / mouseSensitivity;		// use screen width later...

		TransformComponent* transformComponent = playerCharacter->getComponent<TransformComponent>();

		// apply the transforms seperately to avoid roll
		transformComponent->pitch(thi);
		transformComponent->yaw(theta);

	}


	// do open gl setup for the frame (renderColourBackground is not the most informative name)
	float redValue = 0, greenValue = 0, blueValue = 1;
	if (m_playerBackground->getComponent<RedComponent>())
		redValue = m_playerBackground->getComponent<RedComponent>()->m_colourValue;
	if (m_playerBackground->getComponent<GreenComponent>())
		greenValue = m_playerBackground->getComponent<GreenComponent>()->m_colourValue;
	if (m_playerBackground->getComponent<BlueComponent>())
		blueValue = m_playerBackground->getComponent<BlueComponent>()->m_colourValue;

	engineCore->renderColouredBackground(redValue, greenValue, blueValue);

	// update the camera
	if (v_Arrows.size() <= 0)
	{
		engineCore->setCamera(getPlayer()->getComponent<CameraComponent>());
	}
	else
	{
		engineCore->setCamera(v_Arrows.at(v_Arrows.size() - 1)->getComponent<CameraComponent>()); 
	}

	// draw the game objects
	for (auto gameObject : v_gameObjects)
	{
		Model* model = gameObject->getComponent<ModelComponent>()->getModel();
		glm::mat4 matrix = gameObject->getComponent<TransformComponent>()->getModelMatrix();
		engineCore->drawModel(model, matrix);

	}

	// draw the game objects
	for (auto gameObject : v_Arrows)
	{
		Model* model = gameObject->getComponent<ModelComponent>()->getModel();
		glm::mat4 matrix = gameObject->getComponent<TransformComponent>()->getModelMatrix();
		engineCore->drawModel(model, matrix);

	}
}

bool Scene::loadLevelJSON(std::string levelJSONFile)
{
	bool loadOK = true;

	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;

	jsonData.open(levelJSONFile.c_str());
	// check for errors
	if (!reader.parse(jsonData, root))
	{
		std::cout << "Failed to parse data from: "
			<< levelJSONFile
			<< reader.getFormattedErrorMessages();

		loadOK = false;
		return loadOK;
	}
	const Json::Value gameObjects = root["GameObjects"];

	//

	int numberOfCubes = gameObjects.size();
	//v_GameObjects.resize(numberOfCubes);

	// size() tells us how large the array is
	for (int i = 0; i < (int)gameObjects.size(); i++)
	{



		////////////////////////////////////////////////////////

		// get string
		std::cout << gameObjects[i]["name"].asString() << " loaded\n";




		// link this to model

		const Json::Value modelNode = gameObjects[i]["model"];

		std::string modelName = modelNode.asString();	// no index as not an array

		Model* model{ nullptr };

		if (modelNode.type() != Json::nullValue)
		{
			model = m_theModelManager->getModel("assets/models/" + modelName);
		}
		else
		{
			model = m_theModelManager->getModel("assets/models/nothing.obj");			// change to error model later....
		}

		// test for no model later!!!!!

		if (model == nullptr)
		{
			loadOK = false;
		}

		float x, y, z;
		// get the position node
		const Json::Value posNode = gameObjects[i]["position"];
		x = posNode[0].asFloat(); // get float
		y = posNode[1].asFloat();
		z = posNode[2].asFloat();



		glm::vec3 position(x, y, z);

		float h, w, d;
		// get the dimention node
		const Json::Value dimNode = gameObjects[i]["height&width"];
		h = dimNode[0].asFloat(); // get float
		w = dimNode[1].asFloat();
		d = dimNode[2].asFloat();



		glm::vec3 dimention(h, w, d);

		glm::quat orientation(1.0f, 0.0f, 0.0f, 0.0f);


		const Json::Value orientNode = gameObjects[i]["orientation"];
		if (orientNode.type() != Json::nullValue)
		{

			// get orientation here e.t.c.

		}


		glm::vec3 scale(1.0f, 1.0f, 1.0f);
		const Json::Value scaleNode = gameObjects[i]["scale"];
		if (scaleNode.type() != Json::nullValue)
		{

			// get scale here e.t.c.

		}

		std::cout << x << "," << y << "," << z << std::endl;

		// todo - fix this to be data dependent
		int m_enemyIndex = 2;
		if (i == m_playerIndex)
		{
			v_gameObjects.push_back(new PlayerCharacter(model, position, orientation, 2.f, 2.5f));
		}
		else if (i == m_enemyIndex)
		{
			v_gameObjects.push_back(new NPC_Character(model, position, orientation, 2.f, 2.5f));
		}
		else
		{
			v_gameObjects.push_back(new StaticEnvironmentObject(model, position, orientation));
		}
	}

	mapPoints1.clear(); 
	mapPoints1.push_back(glm::vec3(0, 0, 0));
	mapPoints1.push_back(glm::vec3(100, 0, 0));


	mapPoints2.clear();
	mapPoints2.push_back(glm::vec3(0, 0, 0));
	mapPoints2.push_back(glm::vec3(60, 0, 0));
	mapPoints2.push_back(glm::vec3(67, 8, 0));
	mapPoints2.push_back(glm::vec3(73, 8, 0));
	mapPoints2.push_back(glm::vec3(80, 0, 0));
	mapPoints2.push_back(glm::vec3(100, 0, 0));

	height.clear();
	height.push_back(glm::vec3(0, 0, 0));
	height.push_back(glm::vec3(1, 0, 0));

	width.clear();
	width.push_back(glm::vec3(0, 0, 0));
	width.push_back(glm::vec3(0, 0.7, 0));
	return loadOK;
}

NPC_Character* Scene::getNPCCharacter()
{
	return (NPC_Character*)v_gameObjects[m_iNPCIndex];
}

PlayerCharacter* Scene::getPlayer()
{
	return (PlayerCharacter*)v_gameObjects[m_playerIndex];
}

ArrowObject* Scene::getLatestArrow()
{
	return v_Arrows[v_Arrows.size() - 1];
}

void Scene::m_AddArrow()
{
	ArrowObject * temp = new ArrowObject(m_theModelManager->getModel("assets/models/arrow.obj"), glm::vec3(0, 0, 0), glm::quat(0, 0, 0, 0));

	v_Arrows.push_back(temp); 
}

void Scene::m_AddArrow(int index)
{
	ArrowObject* temp = new ArrowObject(m_theModelManager->getModel("assets/models/arrow.obj"), getPlayer()->getComponent<TransformComponent>()->m_position + glm::vec3(3, 1, 0), glm::quat(0, 1, 0, 0));

	m_CollisionDetector.m_SetCurrArrowObject(temp); 

	v_Arrows.push_back(temp);
}

void Scene::m_SetArrowMoving()
{
	if (v_Arrows.size() > 0)
	{
		unsigned int l_iIndex = v_Arrows.size() - 1;

		v_Arrows.at(l_iIndex)->m_FireArrow(true, 1.f, 1.f, glm::vec3(0.5, 0.5, 0));
	}
}

void Scene::m_SetEnemyArrowMoving(float powerDec, glm::vec3 Direction)
{
	if (v_Arrows.size() > 0)
	{
		unsigned int l_iIndex = v_Arrows.size() - 1;

		v_Arrows.at(l_iIndex)->m_FireArrow(true, 1.f, powerDec, Direction);
	}
}

void Scene::m_AddEnemyArrow(int index)
{
	ArrowObject* temp = new ArrowObject(m_theModelManager->getModel("assets/models/enemyarrow.obj"), getNPCCharacter()->getComponent<TransformComponent>()->m_position + glm::vec3(0, 1, 0), glm::quat(1, 0, 0, 0));

	m_CollisionDetector.m_SetCurrArrowObject(temp);

	v_Arrows.push_back(temp);
}


void Scene::loadLevel(std::string levelFile)
{

	Model* model = nullptr;;	//fix if we use this

	std::ifstream myInputFile;
	myInputFile.open(levelFile, std::ios_base::in);

	std::stringstream ss;
	std::string s;

	int numCubesToRead;

	if (myInputFile.is_open())
	{
		// read the first line which has the number of elements
		std::getline(myInputFile, s);
		ss.str(s);
		ss.ignore(17); // ignore the first 20 chars

		//std::string title;
		//ss >> title;
		ss >> numCubesToRead;

		// resize the correct size for the vector
		v_gameObjects.resize(numCubesToRead);
		ss.clear();

		for (int i = 0; i < numCubesToRead; i++)
		{
			getline(myInputFile, s);
			ss.clear();
			ss.str(s);

			// cube x - just ignore for now..

			// use a stringstream to get integer values
			getline(myInputFile, s);
			ss.clear();
			ss.str(s);

			float x;
			float y;
			float z;

			ss >> x;
			ss >> y;
			ss >> z;
			glm::vec3 position(x, y, z);

			getline(myInputFile, s);
			ss.clear();
			ss.str(s);

			float ow;
			float ox;
			float oy;
			float oz;

			ss >> ow;
			ss >> ox;
			ss >> oy;
			ss >> oz;
			glm::quat orientation(ow, ox, oy, oz);

			getline(myInputFile, s);
			ss.clear();
			ss.str(s);

			float sx;
			float sy;
			float sz;

			ss >> sx;
			ss >> sy;
			ss >> sz;

			glm::vec3 scale(sx, sy, sz);

			v_gameObjects.push_back(new StaticEnvironmentObject(model, position, orientation));
		}
	}
}