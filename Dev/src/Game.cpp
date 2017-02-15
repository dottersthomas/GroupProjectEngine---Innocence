#include "General\Game.h"
#include "Rendering\ResourceManager.h"
#include "Physics\Components\TransformComponent.h"
#include "Rendering\Components\RenderComponent.h"
#include "Rendering\MeshFactory.h"

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


	Proxy::getInstance()->AssignWindowManager(&m_WindowManager_);
	Proxy::getInstance()->AssignGame(this);

	m_WindowManager_.toggleCursorDraw(false);

	m_Renderer_ = new Renderer(m_WindowManager_.getWindow());
	m_GUIRenderer_ = new GUIRenderer(m_WindowManager_.getWindow());
}

//Create the Scene here. Should be data driven.
void Game::CreateScene() {

	

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