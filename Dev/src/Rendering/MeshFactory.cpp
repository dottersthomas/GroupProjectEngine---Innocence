#include "Rendering\MeshFactory.h"
#include "General\OBJLoader.h"
#include "Rendering\ResourceManager.h"

MeshFactory::MeshFactory() {

}

Mesh * MeshFactory::create(std::string pPath, glm::vec3 pPos, glm::vec3 pRot, glm::vec3 pScale, glm::vec4 m_Colour_) {
	RawMesh rawMesh;
	Mesh * mesh;
	if (ResourceManager::getInstance()->checkMeshExists(pPath)) {

		rawMesh = ResourceManager::getInstance()->GetRawMesh(pPath);
	}
	else {

		std::vector<glm::vec3> inVerts;
		std::vector<glm::vec2> inUVs;
		std::vector<glm::vec3> inNormals;
		
		std::vector<GLfloat> verts;
		std::vector<GLfloat> UVs;
		std::vector<GLfloat> Normals;


		if (LoadGameObject(pPath.c_str(), inVerts, inUVs, inNormals)) {
			verts.reserve(inVerts.size() * 3);
			UVs.reserve(inUVs.size() * 2);
			Normals.reserve(inNormals.size() * 3);
			for (std::vector<glm::vec3>::iterator iter = inVerts.begin(); iter != inVerts.end(); ++iter) {
				verts.push_back((*iter).x);
				verts.push_back((*iter).y);
				verts.push_back((*iter).z);

			}

			for (std::vector<glm::vec2>::iterator iter = inUVs.begin(); iter != inUVs.end(); ++iter) {
				UVs.push_back((*iter).x);
				UVs.push_back((*iter).y);

			}

			for (std::vector<glm::vec3>::iterator iter = inNormals.begin(); iter != inNormals.end(); ++iter) {
				Normals.push_back((*iter).x);
				Normals.push_back((*iter).y);
				Normals.push_back((*iter).z);

			}

			rawMesh = RawMesh(verts, UVs, Normals);
			ResourceManager::getInstance()->RegisterMesh(pPath, rawMesh);
		}
	}

	mesh = new Mesh(rawMesh, m_Colour_);
	mesh->setPosition(pPos);
	mesh->setRotation(pRot);
	mesh->setScale(pScale);

	return mesh;
}
Mesh * MeshFactory::create(std::string pPath, glm::vec3 pPos, glm::vec3 pRot, glm::vec3 pScale, std::string pTexture) {
	RawMesh rawMesh;
	Mesh * mesh;
	if (ResourceManager::getInstance()->checkMeshExists(pPath)) {

		rawMesh = ResourceManager::getInstance()->GetRawMesh(pPath);
	}
	else {

		std::vector<glm::vec3> inVerts;
		std::vector<glm::vec2> inUVs;
		std::vector<glm::vec3> inNormals;

		std::vector<GLfloat> verts;
		std::vector<GLfloat> UVs;
		std::vector<GLfloat> Normals;

		if (LoadGameObject(pPath.c_str(), inVerts, inUVs, inNormals)) {
			verts.reserve(inVerts.size() * 3);
			UVs.reserve(inUVs.size() * 2);
			Normals.reserve(inNormals.size() * 3);

			for (std::vector<glm::vec3>::iterator iter = inVerts.begin(); iter != inVerts.end(); ++iter) {
				verts.push_back((*iter).x);
				verts.push_back((*iter).y);
				verts.push_back((*iter).z);

			}

			for (std::vector<glm::vec2>::iterator iter = inUVs.begin(); iter != inUVs.end(); ++iter) {
				UVs.push_back((*iter).x);
				UVs.push_back((*iter).y);

			}

			for (std::vector<glm::vec3>::iterator iter = inNormals.begin(); iter != inNormals.end(); ++iter) {
				Normals.push_back((*iter).x);
				Normals.push_back((*iter).y);
				Normals.push_back((*iter).z);

			}

			rawMesh = RawMesh(verts, UVs, Normals);
			ResourceManager::getInstance()->RegisterMesh(pPath, rawMesh);
		}
	}

	mesh = new Mesh(rawMesh);
	mesh->setTexture(pTexture);
	mesh->setPosition(pPos);
	mesh->setRotation(pRot);
	mesh->setScale(pScale);

	return mesh;
}


Mesh * MeshFactory::create(glm::vec3 pPos, glm::vec3 pRot, glm::vec3 pScale) {
	std::vector<GLfloat> vertices = {
		0.0f, 0.0f, 0.0f, // triangle 1 : begin
		0.0f, 0.0f, -1.0f,
		0.0f, -1.0f, -1.0f, // triangle 1 : end
		-1.0f, -1.0f, 0.0f, // triangle 2 : begin
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, // triangle 2 : end
		-1.0f, 0.0f, -1.0f,
		0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, -1.0f,
		0.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		0.0f, -1.0f, -1.0f,
		-1.0f, 0.0f, -1.0f
	};


	RawMesh rawMesh(vertices);

	Mesh * mesh = new Mesh(rawMesh);
	mesh->setPosition(pPos);
	mesh->setRotation(pRot);
	mesh->setScale(pScale);



	return mesh;
}
