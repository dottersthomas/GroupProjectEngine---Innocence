#ifndef _RAW_MESH_H_
#define _RAW_MESH_H_

#include <gl\glew.h>
#include <glm\glm.hpp>
#include <vector>

//Raw Mesh data for the Mesh class.
struct RawMesh{

	//The Raw Data.
	GLuint * VAO;
	bool m_hasUVData_;

	int m_drawSize_;

	glm::vec3 m_MinPos_;
	glm::vec3 m_MaxPos_;

	RawMesh() {

	}

	RawMesh(std::vector<GLfloat> vertices);
	RawMesh(std::vector<GLfloat> vertices, std::vector<GLfloat> UV);
	RawMesh(std::vector<GLfloat> vertices, std::vector<GLfloat> UV, std::vector<GLfloat> Normals);

};

#endif