#pragma once
#include "Component.h"
#include <unordered_map>
#include <typeindex>

/*! \class An object in the game will be made of a single game object with one or more components attached to it
*			a single object should only contain a Single Game Object.  
*/
class GameObject
{
public:

	/*! \fn This will allow for the access of a single game object. 
	*Param T the component to be accessed. 
	*/
	template <typename T>
	T* getComponent()
	{

		auto iter = m_components.find(typeid(T));

		if(iter != std::end(m_components))
		{
			// if found dynamic cast the component pointer and return it
			return dynamic_cast<T*>(iter->second);
		}
		
		// return null if we don't have a component of that type
		return nullptr;
		
	}

	/*! \fn Used to add a new compoent to this game object. 
	*Param T the new component to add. 
	*/
	template <typename T>
	void addComponent(T* comp)
	{
		// add the component to unoreder map with hash of its typeid
		m_components[typeid(T)] = comp;
	}

	// we add these - class is now abstract...
	virtual void OnUpdate(float dt) = 0;
	virtual void OnMessage(const std::string m) = 0;


	std::string m_sTag = "Null";

private:

	/*! \var The list of components currently on this game object. */
	std::unordered_map<std::type_index, Component*> m_components;
};


