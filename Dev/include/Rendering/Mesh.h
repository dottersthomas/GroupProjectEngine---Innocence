#ifndef _MESH_H_
#define _MESH_H_

#include <gl\glew.h>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include <vector>

#include "RawMesh.h"

class Mesh {
private:
	//The raw data (VAO) for the mesh.
	RawMesh rawMesh;


	//Local position data relative to the master transform.
	glm::vec3 m_LocalPosition_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_LocalRotation_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Scale_;

	//By Default is the origin. This is the pivot point to rotate around.
	glm::vec3 m_PivotPoint_ = glm::vec3(0.0f, 0.0f, 0.0f);

	//Colour of the mesh.
	glm::vec4 m_Colour_ = glm::vec4(0.6, 0.6, 0.6, 1.0);
	//Possible texture Id.
	std::string m_TextureId_;
	
public:

	Mesh();
	Mesh(RawMesh rMesh, glm::vec4 m_Colour_ = glm::vec4(0.6, 0.6, 0.6, 1.0));
	~Mesh() {
	/*	if(VAO != 0)
			delete VAO;*/
	}

	//toggle If UV data is present.
	void setUVToggle(bool pToggle) {
		rawMesh.m_hasUVData_ = pToggle;
	}

	//Get the raw render data to be passed to the GPU.
	GLuint * getRenderData() {
		return rawMesh.VAO;
	}


	glm::vec3 getPosition() {
		return m_LocalPosition_;
	}

	glm::vec3 getRotation() {
		return m_LocalRotation_;
	}

	glm::vec3 getScale() {
		return m_Scale_;
	}

	glm::vec3 getPivotPoint() {
		return m_PivotPoint_;
	}

	void setPosition(glm::vec3 pPosition) {
		m_LocalPosition_ = pPosition;
	}

	void setRotation(glm::vec3 pRotation) {
		m_LocalRotation_ = pRotation;
	}

	void setScale(glm::vec3 pScale) {
		m_Scale_ = pScale;
	}

	void setPivotPoint(glm::vec3 pPivot) {
		m_PivotPoint_ = pPivot;
	}

	int getDrawSize() {
		return rawMesh.m_drawSize_;
	}

	void setColour(glm::vec4 pColour) {
		m_Colour_ = pColour;
	}

	glm::vec4 getColour() {
		return m_Colour_;
	}

	void setTexture(std::string pTexture) {
		m_TextureId_ = pTexture;
	}

	std::string getTextureID() {
		return m_TextureId_;
	}

};

#endif