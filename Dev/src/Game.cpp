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
#include "UI\Text2D.h"


#define TIXML_USE_STL

SpotLight * spotLight;


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

	m_Physics_->update(dTime);
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
	RenderComponent::registerLua(L);

	CanvasComponent::registerLua(L);

	WindowManager::registerLua(L);
	SceneManager::registerLua(L);
	Scene::registerLua(L);
	RigidBody::registerLua(L);
	Collider::registerLua(L);
	BoxCollider::registerLua(L);
	Box::registerLua(L);
	CollisionData::registerLua(L);

	// Execute scripts
	//GameObject go = GameObject("TestObject");

	//auto s1 = std::make_shared<Script>("PlayerController.lua", "Test");
	//go.registerComponent(s1.get());

	// TODO Line below causes error, scripts can be executed manually
	//WindowManager::getInstance().getSceneManager()->getCurrentScene()->AddGameObject(go);

	//Start the Scenes Components.
	if (WindowManager::getInstance().getSceneManager()->getCurrentScene() != nullptr)
		WindowManager::getInstance().getSceneManager()->getCurrentScene()->Start();
	//TransformComponent * comp = m_WindowManager_.getSceneManager()->getCurrentScene()->getGameObjects()->at(1).GetComponentByType<TransformComponent>();
	float rotation = 0;
	bool toggle = false;
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
			
			rotation += 1 / 100.0f;
			//TransformComponent* temp = WindowManager::getInstance().getSceneManager()->getCurrentScene()->getGameObjects()->at(1).GetComponentByType<TransformComponent>();
			//temp->setRotation(glm::vec3(temp->getRotation().x, temp->getRotation().y,  rotation));
			if (rotation > 1.0f) {
				rotation = -1.0f;
			}
			TransformComponent * tc = WindowManager::getInstance().getSceneManager()->getCurrentScene()->getGameObjects()->at(2).GetComponentByType<TransformComponent>();

			spotLight->setDirection(tc->getDirection());
			spotLight->setPosition(tc->getPosition() + glm::vec3(0.0f, 5.0f, 0.0f));
			
			update(tick * 1/ fDelay);
			//RigidBody * rb = WindowManager::getInstance().getSceneManager()->getCurrentScene()->getGameObjects()->at(2).GetComponentByType<RigidBody>();
			//rb->SetAcc(glm::vec3(-2, 0, 0));

			tick -= TICKS_PER_SECOND;

		}

		m_Physics_->updateObjects();
		
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
	ResourceManager::getInstance()->LoadShader("Shaders/gui_plain_shader.vert", "Shaders/gui_plain_shader.frag", "gui_plain");
	ResourceManager::getInstance()->LoadShader("Shaders/text_shader.vert", "Shaders/text_shader.frag", "text_shader");
	ResourceManager::getInstance()->LoadShader("Shaders/post_process_fbo.vert", "Shaders/post_process_fbo.frag", "post_process_fbo");

	ResourceManager::getInstance()->loadTextureSOIL("Textures/font.png", GL_TRUE, "FONT", "texture_font");

	ResourceManager::getInstance()->setupTextCharacters("FONT");

	Proxy::getInstance()->AssignWindowManager(&WindowManager::getInstance());
	Proxy::getInstance()->AssignGame(this);

	WindowManager::getInstance().toggleCursorDraw(false);
	
	m_Physics_ = new Physics(WindowManager::getInstance().getWindow());

	m_Physics_ = new Physics(WindowManager::getInstance().getWindow());

	m_Renderer_ = new Renderer(WindowManager::getInstance().getWindow());
	m_GUIRenderer_ = new GUIRenderer(WindowManager::getInstance().getWindow());


	//WindowManager::getInstance().getSceneManager()->LoadScene("XML/Scene.xml");
	WindowManager::getInstance().getSceneManager()->LoadScene(LoadTestScene());

	WindowManager::getInstance().getSceneManager()->switchScene();
	WindowManager::getInstance().getSceneManager()->UpdateRenderers(m_Renderer_, m_GUIRenderer_);

	WindowManager::getInstance().getSceneManager()->UpdatePhysics(m_Physics_);


}

//Create the Scene here. Should be data driven.
void Game::CreateScene() {

	

}

Scene * Game::LoadTestScene() {
	Scene * _Scene = new Scene("");

	std::vector<const GLchar*> faces;

	faces.push_back("Textures/World/fire-storm_rt.png");
	faces.push_back("Textures/World/fire-storm_lf.png");
	faces.push_back("Textures/World/fire-storm_up.png");
	faces.push_back("Textures/World/fire-storm_dn.png");
	faces.push_back("Textures/World/fire-storm_bk.png");
	faces.push_back("Textures/World/fire-storm_ft.png");

	_Scene->getEnvironment()->setSkyBox(new SkyBox("skybox", faces));

	AssimpLoader loader;

	//Model model = loader.LoadModel("Models/nanosuit/nanosuit.obj");
	Model model = loader.LoadModel("Models/Scene/Ground.fbx");
	//Model model = loader.LoadModel("Models/plane.obj");
	//Model model = loader.LoadModel("Models/TaylorWhiskers.fbx");
	//Model model;



	GameObject object("Model");
	int index = _Scene->AddGameObject(object);


	TransformComponent * tc = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc->setParent(&_Scene->getGameObjects()->at(index));
	//tc->setPosition(glm::vec3(-2.0f, -3.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));

	tc->setScale(glm::vec3(1.5f, 1.5f, 1.5f));

	CanvasComponent * canvas = new CanvasComponent(&_Scene->getGameObjects()->at(index));


	CanvasRect * rect = new CanvasRect(nullptr, glm::vec4(1.0f, 0.0f, 0.0f, 0.5f));
	rect->SetShader("gui_plain");
	rect->setPosition(glm::vec2(1.0, 1.0));
	rect->setScale(glm::vec2(100, 100));


	canvas->AddElement(rect);

	Text2D * text = new Text2D("text_shader", "abcdefghijklmnopqrstuvwxyz , 1234567890 - + _ = @#~;:?><\\");
	text->SetShader("text_shader");
	text->setPosition(glm::vec2(100,100));
	//text->setUsesID(usesID);
	text->setScale(glm::vec2(1,1));
	text->setColour(glm::vec4(1.0, 1.0, 1.0, 1.0));

	canvas->AddElement(text);


	_Scene->getGameObjects()->at(index).registerComponent(canvas);
	canvas->setParent(&_Scene->getGameObjects()->at(index));





	/////
	RenderComponent * render = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");

	glm::vec3 position, rotation, scale, pivot = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec4 colour = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

	//Script* s1 = new Script("RandomSound.lua", "RandomSound");

	render->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render);

	render->setParent(&_Scene->getGameObjects()->at(index));

	
	BoxCollider * bc = new BoxCollider(&_Scene->getGameObjects()->at(index),false);
	_Scene->getGameObjects()->at(index).registerComponent(bc);
	bc->setParent(&_Scene->getGameObjects()->at(index));

	
	
	
	index = _Scene->AddGameObject(GameObject("Player"));
	TransformComponent * tc2 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc2 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc2->setParent(&_Scene->getGameObjects()->at(index));
	tc2->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc2->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	RenderComponent * render2 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/nanosuit/nanosuit.obj");
	render2->toggleBackCulling(false);
	render2->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render2);
	render2->setParent(&_Scene->getGameObjects()->at(index));
	render2->toggleDrawing(false);

	BoxCollider * bc2 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc2);
	bc2->setParent(&_Scene->getGameObjects()->at(index));

	RigidBody * rb = new RigidBody();
	_Scene->getGameObjects()->at(index).registerComponent(rb);
	rb->setParent(&_Scene->getGameObjects()->at(index));
	rb->SetAcc(glm::vec3(0, 0, 0));

	FirstPersonCameraComponent * cameraComponent = new FirstPersonCameraComponent(&_Scene->getGameObjects()->at(index), "camera", glm::vec3(0.0f, 10.0f, 0.0f));

	_Scene->getGameObjects()->at(index).registerComponent(cameraComponent);
	cameraComponent->setParent(&_Scene->getGameObjects()->at(index));

	_Scene->attachMainCameraComponent(_Scene->getGameObjects()->at(index).GetComponentByType<FirstPersonCameraComponent>());

	Script* s1 = new Script("PlayerController3.lua", "Test");
	_Scene->getGameObjects()->at(index).registerComponent(s1);
	s1->setParent(&_Scene->getGameObjects()->at(index));

	index = _Scene->AddGameObject(GameObject("Ghost"));
	tc2 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc2->setParent(&_Scene->getGameObjects()->at(index));

	render2 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/nanosuit/nanosuit.obj");
	render2->toggleBackCulling(false);
	render2->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render2);
	render2->setParent(&_Scene->getGameObjects()->at(index));
	render2->toggleDrawing(false);

	bc2 = new BoxCollider(&_Scene->getGameObjects()->at(index), true);
	_Scene->getGameObjects()->at(index).registerComponent(bc2);
	bc2->setParent(&_Scene->getGameObjects()->at(index));
	bc2->CustomBounds(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1));
	s1 = new Script("Ghost.lua", "Ghost");
	_Scene->getGameObjects()->at(index).registerComponent(s1);
	s1->setParent(&_Scene->getGameObjects()->at(index));



	index = _Scene->AddGameObject(GameObject("House"));
	TransformComponent * tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));

	RenderComponent * render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/House.fbx");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));
	
	Script* s2 = new Script("Collectible.lua", "Collectible");
	_Scene->getGameObjects()->at(index).registerComponent(s2);
	s2->setParent(&_Scene->getGameObjects()->at(index));

	BoxCollider * bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), true);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));

	index = _Scene->AddGameObject(GameObject("Items"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/items.fbx");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));

	index = _Scene->AddGameObject(GameObject("Logs"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/Logs.fbx");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), true);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));
	
	index = _Scene->AddGameObject(GameObject("Rocks"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/Rocks.obj");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));

	
	index = _Scene->AddGameObject(GameObject("RocksFront"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/RocksFront.obj");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	//bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	//_Scene->getGameObjects()->at(index).registerComponent(bc3);
	//bc3->setParent(&_Scene->getGameObjects()->at(index));

	index = _Scene->AddGameObject(GameObject("RocksBack"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/RocksBack.obj");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));

	index = _Scene->AddGameObject(GameObject("GateUp"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/GateUp.fbx");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));

	index = _Scene->AddGameObject(GameObject("GateDown"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/GateDown.fbx");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));

	index = _Scene->AddGameObject(GameObject("Truck"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/Truck.fbx");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));

	index = _Scene->AddGameObject(GameObject("Wall"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/Wall.fbx");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));
	bc3->CustomBounds(glm::vec3(-90, 0, -118), glm::vec3(-86, 19, -71.6));

	index = _Scene->AddGameObject(GameObject("Wall2"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));
	bc3->CustomBounds(glm::vec3(-131, 0, -114), glm::vec3(-89.5, 19, -113));

	index = _Scene->AddGameObject(GameObject("Wall3"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));
	bc3->CustomBounds(glm::vec3(-132, 0, -236.9), glm::vec3(-123, 19, -115));

	index = _Scene->AddGameObject(GameObject("Wall4"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));
	bc3->CustomBounds(glm::vec3(-250, 0, -234.4), glm::vec3(-123.5, 19, -227.5));

	index = _Scene->AddGameObject(GameObject("Wall5"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));
	bc3->CustomBounds(glm::vec3(-57.8, 0, -118), glm::vec3(-53.8, 19, -68));

	index = _Scene->AddGameObject(GameObject("Wall6"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));
	bc3->CustomBounds(glm::vec3(-59.7, 0, -114.6), glm::vec3(-7.9, 19, -110.8));

	index = _Scene->AddGameObject(GameObject("Wall7"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));
	bc3->CustomBounds(glm::vec3(-15.5, 0, -236.4), glm::vec3(-11.08, 19, -109.1));

	index = _Scene->AddGameObject(GameObject("Wall8"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));
	bc3->CustomBounds(glm::vec3(-17, 0, -233.4), glm::vec3(227.2, 19, -229.8));


	index = _Scene->AddGameObject(GameObject("Well"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/Well.fbx");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	_Scene->getGameObjects()->at(index).registerComponent(bc3);
	bc3->setParent(&_Scene->getGameObjects()->at(index));

	index = _Scene->AddGameObject(GameObject("Fence"));
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
	tc3->setParent(&_Scene->getGameObjects()->at(index));
	//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
	//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
	tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
	model = loader.LoadModel("Models/Scene/Fence.fbx");

	render3->AttachModel(model);
	_Scene->getGameObjects()->at(index).registerComponent(render3);
	render3->setParent(&_Scene->getGameObjects()->at(index));

	//bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
	//_Scene->getGameObjects()->at(index).registerComponent(bc3);
	//bc3->setParent(&_Scene->getGameObjects()->at(index));

	// Paper objects
	for (int i = 1; i < 6; i++)
	{
		index = _Scene->AddGameObject(GameObject("Paper" + i));
		tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
		tc3 = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
		tc3->setParent(&_Scene->getGameObjects()->at(index));
		//tc3->setPosition(glm::vec3(10.0f, 1.0f, 0.0f));
		//tc->setRotation(glm::vec3(-3.142 / 2.0f, 0.0f, 0.0f));
		tc3->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


		render3 = new RenderComponent(&_Scene->getGameObjects()->at(index), "default");
		std::string path = "Models/Scene/Paper" + std::to_string(i) + ".fbx";
		model = loader.LoadModel((GLchar*)path.c_str());

		render3->AttachModel(model);
		_Scene->getGameObjects()->at(index).registerComponent(render3);
		render3->setParent(&_Scene->getGameObjects()->at(index));

		bc3 = new BoxCollider(&_Scene->getGameObjects()->at(index), false);
		_Scene->getGameObjects()->at(index).registerComponent(bc3);
		bc3->setParent(&_Scene->getGameObjects()->at(index));
	}

	////////////////////////////////////////////
	//Uniforms

	DirectionalLight * dirLight = new DirectionalLight("default", glm::vec3(-0.0f, -1.0f, -0.5f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	m_Renderer_->getLightManager().RegisterDirectionalLight(dirLight);

	spotLight = new SpotLight("default", glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(-0.0f, -1.0f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 24.0f);

	spotLight->setConstant(1.0f);
	spotLight->setLinear(0.0014f);
	spotLight->setQuadratic(0.000007f);

	m_Renderer_->getLightManager().RegisterSpotLight(spotLight);


	ShaderUniform camera;
	camera.M_Address = "viewPos";
	camera.M_Type = ShaderType::VEC3;
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

		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f)
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
		position.M_Type = ShaderType::VEC3;
		position.M_Vec3 = glm::vec3(pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);

		ShaderUniform ambient;
		ambient.M_Address = "pointLights[" + to_string(i) + "].ambient";
		ambient.M_Type = ShaderType::VEC3;
		ambient.M_Vec3 = glm::vec3(pointLightColors[i].x * 0.1, pointLightColors[i].y * 0.1, pointLightColors[i].z * 0.1);

		ShaderUniform diffuse;
		diffuse.M_Address = "pointLights[" + to_string(i) + "].diffuse";
		diffuse.M_Type = ShaderType::VEC3;
		diffuse.M_Vec3 = glm::vec3(pointLightColors[i].x, pointLightColors[i].y, pointLightColors[i].z);

		ShaderUniform specular;
		specular.M_Address = "pointLights[" + to_string(i) + "].specular";
		specular.M_Type = ShaderType::VEC3;
		specular.M_Vec3 = glm::vec3(pointLightColors[i].x, pointLightColors[i].y, pointLightColors[i].z);

		ShaderUniform constant;
		constant.M_Address = "pointLights[" + to_string(i) + "].constant";
		constant.M_Type = ShaderType::UNIFORM_FLOAT;
		constant.M_Float = 1.0f;

		ShaderUniform linear;
		linear.M_Address = "pointLights[" + to_string(i) + "].linear";
		linear.M_Type = ShaderType::UNIFORM_FLOAT;
		linear.M_Float = 0.09f;

		ShaderUniform quadratic;
		quadratic.M_Address = "pointLights[" + to_string(i) + "].quadratic";
		quadratic.M_Type = ShaderType::UNIFORM_FLOAT;
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



////Move somewhere else at some point. Preferably a Launcher file all on its own, isolated from other function calls.
//int main(int argc, char* argv[]) {
//	Game game = Game();
//
//	game.beginLoop();
//
//	//Should never reach here, if we do, something has gone terribly wrong. Upon termination, the beginLoop function will close GLFW and exit the program itself.
//	return EXIT_FAILURE;
//
//}