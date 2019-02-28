#pragma once

#include <string>
#include <unordered_map>

class Model;

/*! \class This will load all of the models into local storage upon startup. */
class ModelManager
{
public:

	/*! \fn Constructor. */
	ModelManager()
	{

	}

	/*! \fn Deconstructor. */
	~ModelManager()
	{
		// would delete models later....
	}
	
	/*! \fn Used to get a model from the map, use the name of the model you wish to access. */
	Model* getModel(std::string filename);


private:

	/*! \var A list of models which use a string (name) as a unique identifier. */
	std::unordered_map<std::string, Model*> m_models;


};