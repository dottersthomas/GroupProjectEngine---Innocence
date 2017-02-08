#ifndef _GameObject_LOADER_H_
#define _GameObject_LOADER_H_

#include <vector>
#include <glm\glm.hpp>

//Load the Object.
bool LoadGameObject(const char * pPath,
	std::vector<glm::vec3>& vertices,
	std::vector<glm::vec2>& uvs,
	std::vector<glm::vec3>& normals
);


#endif