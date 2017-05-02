#ifndef _RAW_MESH_H_
#define _RAW_MESH_H_

#include <gl\glew.h>
#include <glm\glm.hpp>
#include <vector>


struct Vertex {
	// Position
	glm::vec3 Position;
	// Normal
	glm::vec3 Normal;
	// TexCoords
	glm::vec2 TexCoords;

	glm::vec3 Tangent;

	glm::vec3 BiTangent;
};

//Raw Mesh data for the Mesh class.
struct RawMesh{

	//The Raw Data.
	GLuint * VAO;
	bool m_hasUVData_;
	int M_Indices = 0;

	int m_drawSize_;

	glm::vec3 m_MinPos_;
	glm::vec3 m_MaxPos_;

	RawMesh() {

	}

	RawMesh(std::vector<GLfloat> vertices);
	RawMesh(std::vector<GLfloat> vertices, std::vector<GLfloat> UV);
	RawMesh(std::vector<GLfloat> vertices, std::vector<GLfloat> UV, std::vector<GLfloat> Normals);


	RawMesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
};

#endif