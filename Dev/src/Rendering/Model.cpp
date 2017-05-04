#include "Rendering\Model.h"


Model::Model(std::vector<Mesh> mesh) {
	m_Meshes_ = mesh;

	if (m_Meshes_.size() > 0) {
		m_MinPos_ = m_Meshes_[0].getRawMesh().m_MinPos_;
		m_MaxPos_ = m_Meshes_[0].getRawMesh().m_MaxPos_;
	}

	for (int i = 1; i < m_Meshes_.size(); i++) {
		if (m_MinPos_.x > m_Meshes_[i].getRawMesh().m_MinPos_.x) m_MinPos_.x = m_Meshes_[i].getRawMesh().m_MinPos_.x;
		if (m_MinPos_.y > m_Meshes_[i].getRawMesh().m_MinPos_.y) m_MinPos_.y = m_Meshes_[i].getRawMesh().m_MinPos_.y;
		if (m_MinPos_.z > m_Meshes_[i].getRawMesh().m_MinPos_.z) m_MinPos_.z = m_Meshes_[i].getRawMesh().m_MinPos_.z;
	}

	for (int i = 1; i < m_Meshes_.size(); i++) {
		if (m_MaxPos_.x < m_Meshes_[i].getRawMesh().m_MaxPos_.x) m_MaxPos_.x = m_Meshes_[i].getRawMesh().m_MaxPos_.x;
		if (m_MaxPos_.y < m_Meshes_[i].getRawMesh().m_MaxPos_.y) m_MaxPos_.y = m_Meshes_[i].getRawMesh().m_MaxPos_.y;
		if (m_MaxPos_.z < m_Meshes_[i].getRawMesh().m_MaxPos_.z) m_MaxPos_.z = m_Meshes_[i].getRawMesh().m_MaxPos_.z;

	}
	
}

void Model::Update(TransformComponent * transform, float dt) {
	for (std::vector<Mesh>::iterator iter = m_Meshes_.begin(); iter != m_Meshes_.end(); ++iter) {
		glm::vec3 p, r, s;
		p = transform->getPosition() + (*iter).getPosition();
		r = transform->getRotation();
		s = transform->getScale() * (*iter).getScale();

		glm::vec3 temp = p - transform->getPosition();


		glm::mat4 model(1.0f);
		model = glm::translate(model, p); // Translate it down a bit so it's at the center of the scene

		model = glm::translate(model, glm::vec3(-temp.x, -temp.y, -temp.z));
		model = glm::rotate(model, r.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, r.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, r.z, glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(temp.x, temp.y, temp.z));

		//Rotate the mesh itself around its pivot point.
		model = glm::translate(model, (*iter).getPivotPoint());
		model = glm::rotate(model, (*iter).getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (*iter).getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, (*iter).getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, -(*iter).getPivotPoint());
		model = glm::scale(model, s);

		(*iter).setModelMatrix(model);
	}
}

float rotation = 0;

void Model::Render(std::string pShader, TransformComponent * transform) {


	for (std::vector<Mesh>::iterator iter = m_Meshes_.begin(); iter != m_Meshes_.end(); ++iter){

		
		(*iter).getMaterial().UpdateUniforms(pShader);
		(*iter).getMaterial().BindTextures(pShader);

		ResourceManager::getInstance()->GetShader(pShader)->SetMatrix4("mModel", (*iter).getModelMatrix());


		glBindVertexArray(*(*iter).getRenderData());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);


		if ((*iter).getIndices() > 0)
			glDrawElements(GL_TRIANGLES, (*iter).getIndices(), GL_UNSIGNED_INT, 0);


	}

	rotation = 1;
}