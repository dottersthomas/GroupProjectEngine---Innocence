#include "General\Game.h"
#include "Rendering\ResourceManager.h"
#include "Physics\Components\TransformComponent.h"
#include "Rendering\Components\RenderComponent.h"
#include "Rendering\MeshFactory.h"
#include "Scripting/LuaEngine.h"
#include "Scripting/Script.h"
#include "Scripting/ExtLib.h"
#include "General\Timer.h"

#include "Rendering\ShaderUniform.h"
#include "Rendering\AssimpLoader.h"
#include "Rendering\Components\ThirdPersonCameraComponent.h"

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
	if (WindowManager::getInstance().getSceneManager()->getCurrentScene() != nullptr) {
		WindowManager::getInstance().getSceneManager()->getCurrentScene()->Update(dTime);
	}


	m_Renderer_->update(dTime);


}

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

float timer = 0;

void Game::beginLoop() {

	double m_dTickTime = glfwGetTime();
	double lastTime = 0.0;
	int nbFrames = 0;

	const float TICKS_PER_SECOND = 1.0f / 60.0f;
	double tick = 0.0;

	// Create engine
	auto engine = &LuaEngine::getInstance();
	lua_State* L = engine->L();
	// Register classes with the engine
	ExtLib::registerLua(L);
	Component::registerLua(L);
	TransformComponent::registerLua(L);
	InputHandler::registerLua(L);
	GameObject::registerLua(L);
	AudioEngine::registerLua(L);
	Sound::registerLua(L);
	Light::registerLua(L);
	PointLight::registerLua(L);
	DirectionalLight::registerLua(L);
	Timer::registerLua(L);
	CameraComponent::registerLua(L);
	FirstPersonCameraComponent::registerLua(L);
	ThirdPersonCameraComponent::registerLua(L);
	WindowManager::registerLua(L);
	SceneManager::registerLua(L);
	Scene::registerLua(L);

	// Execute scripts
	//GameObject go = GameObject("TestObject");

	//auto s1 = std::make_shared<Script>("PlayerController.lua", "Test");
	//go.registerComponent(s1.get());

	// TODO Line below causes error, scripts can be executed manually
	//WindowManager::getInstance().getSceneManager()->getCurrentScene()->AddGameObject(go);

	//Start the Scenes Components.
	if(WindowManager::getInstance().getSceneManager()->getCurrentScene() != nullptr)
		WindowManager::getInstance().getSceneManager()->getCurrentScene()->Start();
	//TransformComponent * comp = m_WindowManager_.getSceneManager()->getCurrentScene()->getGameObjects()->at(1).GetComponentByType<TransformComponent>();

	while (!glfwWindowShouldClose(WindowManager::getInstance().getWindow()))

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
		glfwGetFramebufferSize(WindowManager::getInstance().getWindow(), &width, &height);
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

			if (WindowManager::getInstance().getSceneManager()->NewSceneReady()) {
				WindowManager::getInstance().getSceneManager()->switchScene();
				WindowManager::getInstance().getSceneManager()->UpdateRenderers(m_Renderer_, m_GUIRenderer_);
				WindowManager::getInstance().getSceneManager()->getCurrentScene()->Start();
			}
			timer += 3.142f / 1000;

			update(tick * 1/fDelay);
			//comp->setRotation(glm::vec3(comp->getRotation().x, timer, comp->getRotation().z));

			tick -= TICKS_PER_SECOND;

		}


		m_Renderer_->Render();


		m_GUIRenderer_->Render();

		glfwSwapBuffers(WindowManager::getInstance().getWindow());
		glfwPollEvents();
	}

	glfwTerminate();
	std::exit(EXIT_SUCCESS);
}

void Game::switchScene(std::string pPath) {
	WindowManager::getInstance().getSceneManager()->LoadSceneFromPath(pPath);

	//Start the Scenes Components.
	if (WindowManager::getInstance().getSceneManager()->getCurrentScene() != nullptr)
		WindowManager::getInstance().getSceneManager()->getCurrentScene()->Start();

	WindowManager::getInstance().getSceneManager()->UpdateRenderers(m_Renderer_, m_GUIRenderer_);

}


Game::Game() {

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		std::exit(EXIT_FAILURE);

	WindowManager::getInstance().createWindow("Game", 0, 0, 1280, 720);
	WindowManager::getInstance().toggleVSYNC(false);
	
	glfwMakeContextCurrent(WindowManager::getInstance().getWindow()); 

	if (!WindowManager::getInstance().getWindow())
	{
		glfwTerminate();	
		std::exit(EXIT_FAILURE);
	}

	glewInit();

	glfwSetKeyCallback(WindowManager::getInstance().getWindow(), key_callback);

	::glfwSetMouseButtonCallback(WindowManager::getInstance().getWindow(), Game::mouse_button_callback);

	ResourceManager::getInstance()->LoadShader("Shaders/skybox_shader.vert", "Shaders/skybox_shader.frag", "skybox");
	ResourceManager::getInstance()->LoadShader("Shaders/texture_shader.vert", "Shaders/texture_shader.frag", "default");

	/*ResourceManager::getInstance()->loadTextureSOIL("Textures/container2.png", false, "CrateDiffuse", "texture_diffuse");
	ResourceManager::getInstance()->loadTextureSOIL("Textures/container2_specular.png", false, "CrateSpecular", "texture_specular");*/

	Proxy::getInstance()->AssignWindowManager(&WindowManager::getInstance());
	Proxy::getInstance()->AssignGame(this);

	WindowManager::getInstance().toggleCursorDraw(false);

	m_Renderer_ = new Renderer(WindowManager::getInstance().getWindow());
	m_GUIRenderer_ = new GUIRenderer(WindowManager::getInstance().getWindow());


	//WindowManager::getInstance().getSceneManager()->LoadScene("XML/Scene.xml");
	WindowManager::getInstance().getSceneManager()->LoadScene(LoadTestScene());

	WindowManager::getInstance().getSceneManager()->switchScene();
	WindowManager::getInstance().getSceneManager()->UpdateRenderers(m_Renderer_, m_GUIRenderer_);

}

//Create the Scene here. Should be data driven.
void Game::CreateScene() {

	

}

Scene * Game::LoadTestScene() {
	Scene * _Scene = new Scene("");

	std::vector<const GLchar*> faces;

	faces.push_back("Textures/hw_hourglass/hourglass_rt.png");
	faces.push_back("Textures/hw_hourglass/hourglass_lf.png");
	faces.push_back("Textures/hw_hourglass/hourglass_up.png");
	faces.push_back("Textures/hw_hourglass/hourglass_dn.png");
	faces.push_back("Textures/hw_hourglass/hourglass_bk.png");
	faces.push_back("Textures/hw_hourglass/hourglass_ft.png");

	_Scene->getEnvironment()->setSkyBox(new SkyBox("skybox", faces));

	AssimpLoader loader;
	Model model = loader.LoadModel("Models/nanosuit/nanosuit.obj");
	//Model model = loader.LoadModel("Models/Talia/Talia.dae");
	//Model model = loader.LoadModel("Models/raw/newScene.fbx");
	//Model model;
	GameObject object("Model");
	int index = _Scene->AddGameObject(object);
	TransformComponent * tc = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc->setParent(&_Scene->getGameObjects()->at(index));
	tc->setPosition(glm::vec3(-2.0f, -2.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc->setScale(glm::vec3(2.0f, 2.0f, 2.0f));

	RenderComponent * render = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");

	glm::vec3 position, rotation, scale, pivot = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec4 colour = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

	Script* s1 = new Script("RandomSound.lua", "RandomSound");

	render->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render);
	_Scene->getGameObjects()->at(index).registerComponent(s1);
	render->setParent(&_Scene->getGameObjects()->at(index));
	s1->setParent(&_Scene->getGameObjects()->at(index));

	index = _Scene->AddGameObject(GameObject("OBJ"));
	tc = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc->setParent(&_Scene->getGameObjects()->at(index));
	tc->setPosition(glm::vec3(0.0f, -2.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	RenderComponent * render2 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Grass pack/Grass_02.obj");

	render2->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render2);
	render2->setParent(&_Scene->getGameObjects()->at(index));




	////////////////////////////////////////////
	//Uniforms

	DirectionalLight * dirLight = new DirectionalLight("default", glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f, 0.05f, 0.1f), glm::vec3(0.2f, 0.2f, 0.7f), glm::vec3(0.7f, 0.7f, 0.7f));

	m_Renderer_->getLightManager().RegisterDirectionalLight(dirLight);
	
	ShaderUniform camera;
	camera.M_Address = "viewPos";
	camera.M_Type = VEC3;
	camera.M_Vec3 = glm::vec3(40.0f, 40.0f, 40.0f);

	ResourceManager::getInstance()->useShader("default");

	ResourceManager::getInstance()->GetShader("default")->SetUniform(camera);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glm::vec3 pointLightColors[] = {

		glm::vec3(0.7f, 0.7f, 0.7f),
		glm::vec3(0.7f, 0.7f, 0.7f),
		glm::vec3(0.7f, 0.7f, 0.7f),
		glm::vec3(0.7f, 0.7f, 0.7f)
	};

	

	/*glm::vec3 pointLightColors[] = {
		glm::vec3(1.0f, 0.6f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0, 0.0),
		glm::vec3(0.2f, 0.2f, 1.0f)
	};*/


	for (int i = 0; i < 4; i++) {
		ShaderUniform position;
		position.M_Address = "pointLights[" + to_string(i) + "].position";
		position.M_Type = VEC3;
		position.M_Vec3 = glm::vec3(pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);

		ShaderUniform ambient;
		ambient.M_Address = "pointLights[" + to_string(i) + "].ambient";
		ambient.M_Type = VEC3;
		ambient.M_Vec3 = glm::vec3(pointLightColors[i].x * 0.1, pointLightColors[i].y * 0.1, pointLightColors[i].z * 0.1);

		ShaderUniform diffuse;
		diffuse.M_Address = "pointLights[" + to_string(i) + "].diffuse";
		diffuse.M_Type = VEC3;
		diffuse.M_Vec3 = glm::vec3(pointLightColors[i].x, pointLightColors[i].y, pointLightColors[i].z);

		ShaderUniform specular;
		specular.M_Address = "pointLights[" + to_string(i) + "].specular";
		specular.M_Type = VEC3;
		specular.M_Vec3 = glm::vec3(pointLightColors[i].x, pointLightColors[i].y, pointLightColors[i].z);

		ShaderUniform constant;
		constant.M_Address = "pointLights[" + to_string(i) + "].constant";
		constant.M_Type = FLOAT;
		constant.M_Float = 1.0f;

		ShaderUniform linear;
		linear.M_Address = "pointLights[" + to_string(i) + "].linear";
		linear.M_Type = FLOAT;
		linear.M_Float = 0.09f;

		ShaderUniform quadratic;
		quadratic.M_Address = "pointLights[" + to_string(i) + "].quadratic";
		quadratic.M_Type = FLOAT;
		quadratic.M_Float = 0.032f;

		PointLight * pointLight = new PointLight("default", glm::vec3(pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z), glm::vec3(pointLightColors[i].x * 0.1, pointLightColors[i].y * 0.1, pointLightColors[i].z * 0.1), glm::vec3(pointLightColors[i].x, pointLightColors[i].y, pointLightColors[i].z), glm::vec3(pointLightColors[i].x, pointLightColors[i].y, pointLightColors[i].z), 1.0f, 0.09f, 0.032f);


		m_Renderer_->getLightManager().RegisterPointLight(pointLight);

	}


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