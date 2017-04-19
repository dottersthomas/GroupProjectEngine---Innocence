#include "Rendering\RawMesh.h"

RawMesh::RawMesh(std::vector<GLfloat> vertices) {

	int x = vertices[0];
	int y = vertices[1];
	int z = vertices[2];

	for (int i = 3; i < vertices.size(); i + 2) {
		if (x > vertices[i] + 0) x = vertices[i] + 0;
		if (y > vertices[i] + 1) z = vertices[i] + 1;
		if (z > vertices[i] + 2) x = vertices[i] + 2;

	}
	m_MinPos_ = glm::vec3(x, y, z);

	for (int i = 3; i < vertices.size(); i + 2) {
		if (x < vertices[i] + 0) x = vertices[i] + 0;
		if (y < vertices[i] + 1) z = vertices[i] + 1;
		if (z < vertices[i] + 2) x = vertices[i] + 2;
	}
	m_MaxPos_ = glm::vec3(x, y, z);


	//Create the VAO Data and populate it with the raw data passed.
	VAO = new GLuint;
	m_drawSize_ = vertices.size();
	GLuint VBO;

	glGenVertexArrays(1, this->VAO);
	glBindVertexArray(*VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


RawMesh::RawMesh(std::vector<GLfloat> vertices, std::vector<GLfloat> UV) {

	int x = vertices[0];
	int y = vertices[1];
	int z = vertices[2];

	for (int i = 3; i < vertices.size(); i + 2) {
		if (x > vertices[i] + 0) x = vertices[i] + 0;
		if (y > vertices[i] + 1) z = vertices[i] + 1;
		if (z > vertices[i] + 2) x = vertices[i] + 2;

	}
	m_MinPos_ = glm::vec3(x, y, z);

	for (int i = 3; i < vertices.size(); i + 2) {
		if (x < vertices[i] + 0) x = vertices[i] + 0;
		if (y < vertices[i] + 1) z = vertices[i] + 1;
		if (z < vertices[i] + 2) x = vertices[i] + 2;
	}
	m_MaxPos_ = glm::vec3(x, y, z);

	//Create the VAO Data and populate it with the raw data passed.

	m_drawSize_ = vertices.size();

	GLuint VBO;
	GLuint UVBO;

	VAO = new GLuint;


	glGenVertexArrays(1, this->VAO);
	glBindVertexArray(*VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glGenBuffers(1, &UVBO);

	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, UV.size() * sizeof(GLfloat), &UV[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

RawMesh::RawMesh(std::vector<GLfloat> vertices, std::vector<GLfloat> UV, std::vector<GLfloat> Normals) {

	int x = vertices[0];
	int y = vertices[1];
	int z = vertices[2];

	for (int i = 3; i < vertices.size(); i + 2) {
		if (x > vertices[i] + 0) x = vertices[i] + 0;
		if (y > vertices[i] + 1) z = vertices[i] + 1;
		if (z > vertices[i] + 2) x = vertices[i] + 2;

	}
	m_MinPos_ = glm::vec3(x, y, z);

	for (int i = 3; i < vertices.size(); i + 2) {
		if (x < vertices[i] + 0) x = vertices[i] + 0;
		if (y < vertices[i] + 1) z = vertices[i] + 1;
		if (z < vertices[i] + 2) x = vertices[i] + 2;
	}
	m_MaxPos_ = glm::vec3(x, y, z);

	//Create the VAO Data and populate it with the raw data passed.

	m_drawSize_ = vertices.size();

	GLuint VBO;
	GLuint UVBO;
	GLuint NBO;

	VAO = new GLuint;


	glGenVertexArrays(1, this->VAO);
	glBindVertexArray(*VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glGenBuffers(1, &NBO);

	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(GLfloat), &Normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size : 
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glGenBuffers(1, &UVBO);

	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, UV.size() * sizeof(GLfloat), &UV[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glVertexAttribPointer(
		2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}