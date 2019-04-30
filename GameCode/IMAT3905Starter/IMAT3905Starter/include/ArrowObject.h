#pragma once

#include "GameObject.h"

class ArrowObject : public GameObject
{
public:

	ArrowObject();

	~ArrowObject();

	// Data Members 

private:

	// Member Functions

public:

	void OnUpdate(float dt);

	void OnMessage(const std::string m);

};