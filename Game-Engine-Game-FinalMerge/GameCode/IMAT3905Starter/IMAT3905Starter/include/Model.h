#pragma once
#include <string>
#include <vector>
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

/*! \class Used to create a model and place it into the game. */
class Model
{
public:

	/*! \fn Constructor */
	Model(string filepath);

	/*! \fn Render the model into the game. */
	void render(const unsigned int shaderProgram);

	/*! Used to load a texture from a file onto the model. */
	static unsigned int TextureFromFile(const char* filepath, const string& directory, bool gamma = false);

private:

	// Data Members 

	/*! \var A list of meshes used on the model. */
	std::vector<Mesh> v_meshes;

	/*! \var The directory where to find the model. */
	string directory;

	/*! \var A list of textures used o the model. */
	vector<Texture> v_textures;

	// Member Functions 

	/*! \fn Used to initalize the model by loading it from a file. */
	void loadModel(string path);

	/*! \fn Used to process the model node. */
	void processNode(aiNode* node, const aiScene* scene);

	/*! \fn Used to process the model's mesh. */
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	
	/*! \fn Load the textures to form the textured model. */
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
