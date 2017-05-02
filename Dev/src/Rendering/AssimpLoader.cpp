#include "Rendering\AssimpLoader.h"

Model AssimpLoader::LoadModel(GLchar* path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);

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
	std::vector<Texture *> textures;
	std::vector<Colour> colours;

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


		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.Tangent = vector;

		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.BiTangent = vector;

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
		std::vector<Texture *> diffuseMaps = processMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture *> specularMaps = processMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<Texture *> normalMaps = processMaterialTexture(material, aiTextureType_NORMALS, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	
		aiColor4D colour;
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &colour))
			colours.push_back(Colour(glm::vec3(colour.r, colour.g, colour.b), "colour_diffuse"));

		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &colour))
			colours.push_back(Colour(glm::vec3(colour.r, colour.g, colour.b), "colour_specular"));


	}

	registerPath = path + std::to_string(m_Nodes_);

	RawMesh rMesh(vertices, indices);
	ResourceManager::getInstance()->RegisterMesh(registerPath, rMesh);
	Material material;
	if(textures.size() > 0)
		material = Material(textures, 32.0f);
	else
		material = Material(colours, 32.0f);

	return Mesh(ResourceManager::getInstance()->GetRawMesh(registerPath), material);
}


std::vector<Texture *> AssimpLoader::processMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName) {

	std::vector<Texture *> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		std::string filePath = std::string(str.C_Str());
		filePath = m_Directory_ + '/' + filePath;
		std::cout << filePath << std::endl;
		textures.push_back(ResourceManager::getInstance()->loadTextureSOIL(filePath.c_str(), false, filePath, typeName));
	}

	return textures;

}


