#ifndef _GUI_MESH_H_
#define _GUI_MESH_H_

#include <gl\glew.h>
#include <vector>

struct GUIMesh {
	//Vertex Array Object of the mesh.
	GLuint * VAO;
	GUIMesh() {}


	GUIMesh(int pDrawtype, std::vector<GLfloat> verts = {
		// Pos      // Tex


		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f


	});





};

#endif
