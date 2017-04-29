#include "Rendering\AssimpLoader.h"

Model AssimpLoader::LoadModel(GLchar* path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return Model();
	}

	m_Directory_ = std::string(path).substr(0, std::string(path).find_last_of('/'));
	m_Nodes_ = 1;
	processNode(scene->mRootNode, scene, path);

	return Model(meshes);

}

void AssimpLoader::processNode(aiNode* node, const aiScene* scene, GLchar* path) {
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		m_Nodes_++;
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene, path));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, path);
	}
}

Mesh AssimpLoader::processMesh(aiMesh* mesh, const aiScene* scene, GLchar* path) {

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<std::string> textures;

	std::string registerPath;
	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
						  // Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// Normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	
	//Process Materials below.

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<std::string> diffuseMaps = processMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<std::string> specularMaps = processMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	registerPath = path + std::to_string(m_Nodes_);

	RawMesh rMesh(vertices, indices);
	ResourceManager::getInstance()->RegisterMesh(registerPath, rMesh);
	Material material = Material(textures, 32.0f);
	
	return Mesh(ResourceManager::getInstance()->GetRawMesh(registerPath), material);
}


std::vector<std::string> AssimpLoader::processMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName) {

	std::vector<std::string> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		std::string filePath = std::string(str.C_Str());
		filePath = m_Directory_ + '/' + filePath;
		std::cout << filePath << std::endl;
		ResourceManager::getInstance()->loadTextureSOIL(filePath.c_str(), false, filePath, typeName);
		textures.push_back(filePath);
	}

	return textures;

}


