#include "UI\GUIMesh.h"



GUIMesh::GUIMesh(int pDrawtype, std::vector<GLfloat> verts) {
	VAO = new GLuint;
	GLuint VBO;


	glGenVertexArrays(1, this->VAO);
	glBindVertexArray(*VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	if(pDrawtype == GL_STATIC_DRAW)
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), &verts[0], GL_STATIC_DRAW);
	if (pDrawtype == GL_DYNAMIC_DRAW)
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), &verts[0], GL_DYNAMIC_DRAW);

	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}