#pragma once
#include "Component.h"


class Model;

/*! \class Used to give a game object a model item to display in the game. */
class ModelComponent :  public Component
{
public:

	/*! \fn Constructor */
	ModelComponent(Model* model) : m_model(model)
	{
		//m_model = model;
	};

	/*! \fn Used to get the current model attached to this component. */
	Model* getModel()
	{
		return m_model;
	}

	/*! \fn Used to update this component. */
	void OnUpdate(float dt) override
	{

	}

	/*! \fn Used to react to certain inputs within the game loop. */
	void OnMessage(const std::string m) override
	{
	}

private:

	/*! \var The model attached to this component. */
	Model* m_model;
};

