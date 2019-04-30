#include "ArrowObject.h"

ArrowObject::ArrowObject(Model* model, glm::vec3 position, glm::quat orientation)
{
	TransformComponent* tc = new TransformComponent(position, orientation);

	addComponent(tc);
	addComponent(new ModelComponent(model));
}

ArrowObject::~ArrowObject()
{
}

void ArrowObject::OnUpdate(float dt)
{
}

void ArrowObject::OnMessage(const std::string m)
{
}

void ArrowObject::MouseInput(float x, float y)
{
	std::cout << x << " " << y << std::endl;



	//todo add physics 
}
