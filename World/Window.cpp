#include "Window.h"
#include <exception>

#include <iostream>

#include "UserInputGLFWKeyboardComponent.h"

// GENERAL TODO:
//	- Create Job class
//		* Processes Component data
//		* Essentially contain update logic
//		* Should be able to complete and exit at any time
//		* Has completed, start pending, started, stop pending, stopped, failed states
//		* They only manipulate the Components
//		* GPU what you can!
//
//	- Create System class
//		* System work on all Entities with specific Components
//		* Filter Entities and pass them to one or more Jobs
//		* Thread what you can!
//
//	- Add better Entity Component and System access
//  - Find way to optimize parallelization
//	- Package (namespace) core engine features
//
//	- Create base engine classes
//		* Transform Component
//		* Velocity Component
//		* UserInput Component ?
//		* ObjectLabel Component (name tag?)
//		* Mesh Component
//		* InstancedMesh Component
//		* IndexedMesh Component
//		* InstancedIndexedMesh Component
//		* Material Component
//		* Shader Component
//		* ColliderMesh Component
//		* RigidBody Component (mass, bounciness, etc.)
//		* FrameBuffer Component
//		* Camera Component (fov, lens, etc.)
//		* UIElement Component
//		* UILabel Component
//		* UIImage Component
//		* UIButton Component
//		* UIInput Component
//		* UITextInput Component
//		* UISliderInput Component
//		* Rendering System ( Mesh+Material+Transform+Shader, Camera+FrameBuffer+Shader, ... )
//		* Physics System ( Transform+RigibBody+Velocity+ColliderMesh+... )
//		* UserInput System ?
//		* UI System
//		
//
//

Window::Window(const std::string & title, int width, int height, GLFWmonitor * monitor, GLFWwindow * shareWindow)
	: m_title(title)
	, m_width(width)
	, m_height(height)
	, m_monitor(monitor)
	, m_shareWindow(shareWindow)
{
	init();
}

Window::~Window()
{
	if (m_window) {
		UserInputKeyboardComponent::destroyInstance();
		glfwDestroyWindow(m_window);
	}
}

int Window::init()
{
	if (m_window) {
		glfwDestroyWindow(m_window);
	}

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), m_monitor, m_shareWindow);

	if (nullptr == m_window) {
		std::throw_with_nested(std::exception(std::string("FATAL: Failed to create window \"" + m_title + "\"").c_str(), -1));
	}

	UserInputKeyboardComponent::instance()->hookWindow(m_window);

	glfwMakeContextCurrent(m_window);
	glewExperimental = true;

	if (GLEW_OK != glewInit()) {
		std::throw_with_nested(std::exception(std::string("FATAL: Failed to initialize glew").c_str(), -2));
	}

	m_sceneManager = std::shared_ptr<SceneManager>(new SceneManager());

	return 0;
}

std::shared_ptr<SceneManager> Window::getSceneManager()const
{
	return m_sceneManager;
}

void Window::run()
{
	if (m_window) {
		try {
			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

			start();

			do {
				tick();

			} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(m_window));
			
			stop();
		}
		catch (...) {
			stop();
			std::throw_with_nested("Exception during Window::run");
		}
	}

}

void Window::tick()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_sceneManager->getCurrentScene()->update();

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Window::start()
{
	try {
		m_sceneManager->setCurrentScene(0);
		m_sceneManager->getCurrentScene()->start();
	}catch(std::exception& e)
	{
		std::throw_with_nested(e);
	}
}

void Window::stop()
{
	try {
		m_sceneManager->getCurrentScene()->stop();
	}
	catch (std::exception& e)
	{
		std::throw_with_nested(e);
	}
}
