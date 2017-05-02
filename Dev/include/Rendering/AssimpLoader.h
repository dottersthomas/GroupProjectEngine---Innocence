#ifndef _RENDERING_ASSIMP_LOADER_H_
#define _RENDERING_ASSIMP_LOADER_H_

#include "RawMesh.h"
#include "ResourceManager.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Colour.h"


#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>




class AssimpLoader {

public:
	AssimpLoader() {}

	Model LoadModel(GLchar* path);
private:

	void processNode(aiNode* node, const aiScene* scene, GLchar* path);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene, GLchar* path);

	std::vector<Texture *> processMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);

	std::string m_Directory_;

	int m_Nodes_;

	std::vector<Mesh> meshes;


};


#endif // !_RENDERING_ASSIMP_MODEL_LOADER_H_
