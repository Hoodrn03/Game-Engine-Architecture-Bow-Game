#pragma once

#include <string>

/*! \class The base component structure, inherited from to create new components.*/
class Component
{
public:
	// pure virtual methods - this is an interface
	virtual void OnUpdate(float dt) = 0;
	virtual void OnMessage(const std::string m) = 0;
};

