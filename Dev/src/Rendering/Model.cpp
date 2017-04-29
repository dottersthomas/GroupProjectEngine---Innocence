#include "Rendering\Model.h"


Model::Model(std::vector<Mesh> mesh) {
	m_Meshes_ = mesh;

}


void Model::Render(std::string pShader) {

	for (std::vector<Mesh>::iterator iter = m_Meshes_.begin(); iter != m_Meshes_.end(); ++iter){

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down

		ResourceManager::getInstance()->GetShader(pShader).SetMatrix4("mModel", model);

		(*iter).getMaterial().UpdateUniforms(pShader);
		(*iter).getMaterial().BindTextures(pShader);


		glBindVertexArray(*(*iter).getRenderData());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		if ((*iter).getIndices() > 0)
			glDrawElements(GL_TRIANGLES, (*iter).getIndices(), GL_UNSIGNED_INT, 0);


	}
}