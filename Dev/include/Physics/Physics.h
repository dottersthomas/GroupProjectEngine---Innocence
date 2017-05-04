#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <gl\glew.h>
#include <GLFW\glfw3.h>


#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "General\Scene.h"
#include "General\GameObjectVectorWrapper.h"

#include "Physics\Components\BoxCollider.h"
#include "Physics\Components\RigidBodyh.h"
#include "Physics\Components\TransformComponent.h"



//The main game renderer for rendering all the RenderComponents within the scene.
class Physics {

private:

	//The current scene.
	Scene * m_CurrentScene_ = nullptr;

	//Vector of all game objects with a render component.
	GameObjectVectorWrapper::t_GameObject_Vector_ m_sceneGameObjectsCollide_;
	GameObjectVectorWrapper::t_GameObject_Vector_ m_sceneGameObjectsMove_;
	GLFWwindow * m_Window_;
	
	float gravity = 9.8f;
	float friction = 0.8f;

public:
	Physics() {

	}
	Physics(GLFWwindow * pWindow);

	void Render();

	void CollisionDetection();

	void EulerMove(float dt);

	bool AABBAABBCollision(BoxCollider * boxC1, BoxCollider * boxC2);
	
	void ResolveCollision();

	void setScene(Scene * pScene);

	void update(float dt);



};



#endif