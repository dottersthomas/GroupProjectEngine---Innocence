#include "General\Game.h"
#include "Rendering\ResourceManager.h"
#include "Physics\Components\TransformComponent.h"
#include "Rendering\Components\RenderComponent.h"
#include "Rendering\MeshFactory.h"

#include "Rendering\ShaderUniform.h"

#define TIXML_USE_STL


static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Close the window and thus kill the Engine.
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);


		InputHandler::invokeKey(key, scancode, action, mods);
}



void Game::update(double dTime) {
	//Update the scene, close to the initial loop to minimise time discrepancy.
	//TODO implement custom timer for better time management.
	if (m_WindowManager_.getSceneManager()->getCurrentScene() != nullptr) {
		m_WindowManager_.getSceneManager()->getCurrentScene()->Update(dTime);
	}
}

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


void Game::beginLoop() {

	double m_dTickTime = glfwGetTime();
	double lastTime = 0.0;
	int nbFrames = 0;

	const float TICKS_PER_SECOND = 1.0f / 60.0f;
	double tick = 0.0;

	

	//Start the Scenes Components.
	if(m_WindowManager_.getSceneManager()->getCurrentScene() != nullptr)
		m_WindowManager_.getSceneManager()->getCurrentScene()->Start();

	while (!glfwWindowShouldClose(m_WindowManager_.getWindow()))
	{


		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;

		if (currentTime - lastTime >= 1.0) { 

			std::cout << nbFrames << std::endl;
			nbFrames = 0;
			lastTime += 1.0;

		}

		//float ratio;
		int width, height;
		glfwGetFramebufferSize(m_WindowManager_.getWindow(), &width, &height);
		//ratio = width / (float)height;
		glViewport(0, 0, width, height);


		double currentTickTime = glfwGetTime();

		double frame = currentTickTime - m_dTickTime;
		m_dTickTime = currentTickTime;

		/*
		If Time and Tick difference is more than 0.25 of a second, cap it.
		*/
		if (frame > 0.25f) {
			frame = 0.25f;
		}


		tick += frame;

		while (tick >= TICKS_PER_SECOND) {
			float fDelay = (tick / TICKS_PER_SECOND);


			if (m_WindowManager_.getSceneManager()->NewSceneReady()) {
				m_WindowManager_.getSceneManager()->switchScene();
				m_WindowManager_.getSceneManager()->UpdateRenderers(m_Renderer_, m_GUIRenderer_);
				m_WindowManager_.getSceneManager()->getCurrentScene()->Start();
			}

			update(fDelay);

			tick -= TICKS_PER_SECOND;

		}
		m_Renderer_->Render();
		m_GUIRenderer_->Render();


		glfwSwapBuffers(m_WindowManager_.getWindow());
		glfwPollEvents();
	}

	glfwTerminate();
	std::exit(EXIT_SUCCESS);
}

void Game::switchScene(std::string pPath) {
	m_WindowManager_.getSceneManager()->LoadScene(pPath);

	//Start the Scenes Components.
	if (m_WindowManager_.getSceneManager()->getCurrentScene() != nullptr)
		m_WindowManager_.getSceneManager()->getCurrentScene()->Start();

	m_WindowManager_.getSceneManager()->UpdateRenderers(m_Renderer_, m_GUIRenderer_);

}


Game::Game() {

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		std::exit(EXIT_FAILURE);

	m_WindowManager_.createWindow("Game", 0, 0, 1280, 720);
	m_WindowManager_.toggleVSYNC(false);
	
	glfwMakeContextCurrent(m_WindowManager_.getWindow()); 

	if (!m_WindowManager_.getWindow())
	{
		glfwTerminate();	
		std::exit(EXIT_FAILURE);
	}

	glewInit();

	glfwSetKeyCallback(m_WindowManager_.getWindow(), key_callback);

	::glfwSetMouseButtonCallback(m_WindowManager_.getWindow(), Game::mouse_button_callback);

	ResourceManager::getInstance()->LoadShader("Shaders/default_shader.vert", "Shaders/default_shader.frag", "default");
	ResourceManager::getInstance()->LoadShader("Shaders/texture_shader.vert", "Shaders/texture_shader.frag", "texture");

	Proxy::getInstance()->AssignWindowManager(&m_WindowManager_);
	Proxy::getInstance()->AssignGame(this);

	m_WindowManager_.toggleCursorDraw(false);

	m_Renderer_ = new Renderer(m_WindowManager_.getWindow());
	m_GUIRenderer_ = new GUIRenderer(m_WindowManager_.getWindow());

	//m_WindowManager_.getSceneManager()->LoadScene("XML/Scene.xml");
	m_WindowManager_.getSceneManager()->LoadScene(LoadTestScene());
}

//Create the Scene here. Should be data driven.
void Game::CreateScene() {

	

}

Scene * Game::LoadTestScene() {
	Scene * _Scene = new Scene("");

	GameObject object("Cube");
	int index = _Scene->AddGameObject(object);
	TransformComponent * tc = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc->setParent(&_Scene->getGameObjects()->at(index));
	tc->setPosition(glm::vec3(0.0f,0.0f,0.0f));

	MeshFactory factory;
	RenderComponent * render = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");

	glm::vec3 position, rotation, scale, pivot = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec4 colour = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

	Mesh * mesh;

	mesh = factory.create("Models/Crate.obj", position, rotation, scale, colour);
	mesh->setPivotPoint(pivot);
	mesh->setColour(colour);


	render->AttachMesh(mesh);
	_Scene->getGameObjects()->at(index).registerComponent(render);
	render->setParent(&_Scene->getGameObjects()->at(index));
	////////////////////////////////////////////
	//Uniforms

	glm::vec3 lightColor;
	lightColor.x = sin(glfwGetTime() * 2.0f);
	lightColor.y = sin(glfwGetTime() * 0.7f);
	lightColor.z = sin(glfwGetTime() * 1.3f);
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // Decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // Low influence

	ShaderUniform lightPos;
	lightPos.M_Address = "light.position";
	lightPos.M_Type = VEC3;
	lightPos.M_Vec3 = glm::vec3(3.0f, 1.0f, 2.0f);

	ShaderUniform lightAmb;
	lightAmb.M_Address = "light.ambient";
	lightAmb.M_Type = VEC3;
	lightAmb.M_Vec3 = glm::vec3(0.2f, 0.2f, 0.2f);

	ShaderUniform lightDiff;
	lightDiff.M_Address = "light.diffuse";
	lightDiff.M_Type = VEC3;
	lightDiff.M_Vec3 = glm::vec3(0.5f, 0.5f, 0.5f);

	ShaderUniform lightSpec;
	lightSpec.M_Address = "light.specular";
	lightSpec.M_Type = VEC3;
	lightSpec.M_Vec3 = glm::vec3(1.0f, 1.0f, 1.0f);

	ShaderUniform materialAmb;
	materialAmb.M_Address = "material.ambient";
	materialAmb.M_Type = VEC3;
	materialAmb.M_Vec3 = glm::vec3(1.0f, 0.5f, 0.31f);

	ShaderUniform materialDiff;
	materialDiff.M_Address = "material.diffuse";
	materialDiff.M_Type = VEC3;
	materialDiff.M_Vec3 = glm::vec3(1.0f, 0.5f, 0.31f);

	ShaderUniform materialSpec;
	materialSpec.M_Address = "material.specular";
	materialSpec.M_Type = VEC3;
	materialSpec.M_Vec3 = glm::vec3(0.5f, 0.5f, 0.5f);

	ShaderUniform materialShine;
	materialShine.M_Address = "material.shininess";
	materialShine.M_Type = FLOAT;
	materialShine.M_Float = 32.0f;

	ShaderUniform camera;
	camera.M_Address = "viewPos";
	camera.M_Type = VEC3;
	camera.M_Vec3 = glm::vec3(2.0f, 1.0f, 5.0f);

	ResourceManager::getInstance()->useShader("default");
	ResourceManager::getInstance()->GetShader("default").SetUniform(lightAmb);
	ResourceManager::getInstance()->GetShader("default").SetUniform(lightDiff);
	ResourceManager::getInstance()->GetShader("default").SetUniform(lightSpec);
	ResourceManager::getInstance()->GetShader("default").SetUniform(materialAmb);
	ResourceManager::getInstance()->GetShader("default").SetUniform(materialDiff);
	ResourceManager::getInstance()->GetShader("default").SetUniform(materialSpec);
	ResourceManager::getInstance()->GetShader("default").SetUniform(materialShine);
	ResourceManager::getInstance()->GetShader("default").SetUniform(camera);



	////////////////////////////////////////////



	return _Scene;
}




void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	InputHandler::invokeButton(button, action, mods);
}



//Move somewhere else at some point. Preferably a Launcher file all on its own, isolated from other function calls.
int main(int argc, char* argv[]) {
	Game game = Game();

	game.beginLoop();

	//Should never reach here, if we do, something has gone terribly wrong. Upon termination, the beginLoop function will close GLFW and exit the program itself.
	return EXIT_FAILURE;

}