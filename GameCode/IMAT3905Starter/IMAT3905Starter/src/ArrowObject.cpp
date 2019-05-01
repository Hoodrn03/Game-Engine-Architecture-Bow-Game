#include "ArrowObject.h"

ArrowObject::ArrowObject(Model* model, glm::vec3 position, glm::quat orientation)
{
	TransformComponent* tc = new TransformComponent(position, orientation);

	addComponent(tc);
	addComponent(new ModelComponent(model));
}

void ArrowObject::OnUpdate(float dt)
{
}

void ArrowObject::OnMessage(const std::string m)
{
}

void ArrowObject::MouseInput(glm::vec2 xy)
{	
	std::cout << xy.x << xy.y << std::endl;

	//todo add physics 
}

ArrowObject::~ArrowObject()
{
}
