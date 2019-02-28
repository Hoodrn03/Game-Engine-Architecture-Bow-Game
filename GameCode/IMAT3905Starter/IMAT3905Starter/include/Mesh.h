#pragma once

//#include <glad/glad.h> 
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
using namespace std;

/*! \struct Used to create a vertext for the mesh. */
struct Vertex 
{
	glm::vec3 position; /*!< The mesh's (X, Y, Z). */
	glm::vec3 normal; /*!< The mesh's directional normal. */
	glm::vec2 textureCoords; /*!< The Texture coordinates for the mesh. */
};

/*!\ struct A texture structure for the mesh. */
struct Texture {

	unsigned int id; /*!< The texture ID. */
	string type; /*!< The texture type to use. */
	aiString filepath; /*!< The file location for the texture. */
};

/*! \class Used to give a model a texture.  */
class Mesh 
{
public:

	/*! \var A list of vertices used by the textrure. */
	vector<Vertex> vertices;

	/*! \var A list of indices used by the textrure. */
	vector<unsigned int> indices;

	/*! \var A list of textures used by the model. */
	vector<Texture> textures;

	unsigned int VAO;

	/*! \fn Constructor. */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	// render the mesh with a given shader program
	void render(const unsigned int shaderProgram);

private:
	// buffer objects
	unsigned int VBO, EBO;

	// initialises all the buffer arrays
	void setupMesh();
	
};