#ifndef _MESH_FACTORY_H_
#define _MESH_FACTORY_H_

#include <iostream>
#include <vector>

#include "glm\glm.hpp"

#include "Mesh.h"
#include "RawMesh.h"


//Creates A Mesh from the given data and returns it as a pointer.
class MeshFactory {
private:

public:

	MeshFactory();
	//Create a Mesh from a loaded path.
	Mesh * create(std::string pPath, glm::vec3 pPos, glm::vec3 pRot, glm::vec3 pScale, glm::vec4 m_Colour_ = glm::vec4(0.6, 0.6, 0.6, 1.0));

	Mesh * create(std::string pPath, glm::vec3 pPos, glm::vec3 pRot, glm::vec3 pScale, std::string pTexture);

	//Create a square Mesh.
	Mesh * create(glm::vec3 pPos, glm::vec3 pRot, glm::vec3 pScale);

};


#endif