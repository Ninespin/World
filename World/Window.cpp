#include "Window.h"
#include <exception>

#include "Entity.h"
#include "TransformComponent.h"
#include "ColorComponent.h"
#include "EntityFilter.h"

#include <iostream>

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
		glfwDestroyWindow(m_window);
	}
	delete m_sceneManager;
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

	glfwMakeContextCurrent(m_window);
	glewExperimental = true;

	if (GLEW_OK != glewInit()) {
		std::throw_with_nested(std::exception(std::string("FATAL: Failed to initialize glew").c_str(), -2));
	}

	m_sceneManager = new SceneManager();

	// TESTS 
	// Scenes
	std::shared_ptr<Scene> s1( new Scene("scene1") );
	std::shared_ptr<Scene> s2( new Scene("scene2") );
	std::shared_ptr<Scene> s3( new Scene("scene3") );
	std::shared_ptr<Scene> s4( new Scene("scene4") );
	m_sceneManager->addScene(s1);
	m_sceneManager->addScene(s2);
	m_sceneManager->addScene(s3);
	m_sceneManager->addScene(s4);

	// Entities
	std::shared_ptr<Entity> e1( new Entity("entity1") );
	std::shared_ptr<Entity> e2( new Entity("entity2") );
	std::shared_ptr<Entity> e3( new Entity("entity3") );
	std::shared_ptr<Entity> e4( new Entity("entity4") );
	s1->addEntity(e1).addEntity(e2).addEntity(e4);
	s4->addEntity(e4).addEntity(e2);
	s3->addEntity(e3);

	// Components
	std::shared_ptr<TransformComponent> c2(new TransformComponent() );
	std::shared_ptr<ColorComponent> c3( new ColorComponent(8) );
	std::shared_ptr<TransformComponent> c4(new TransformComponent());
		
	std::cout << "x:" << c2->getX() << " y:" << c2->getY() << " z:" << c2->getZ() << std::endl;
	c2->setPosition(-50,10,12);
	std::cout << "x:" << c2->getX() << " y:" << c2->getY() << " z:" << c2->getZ() << std::endl;

	e1->addComponent(c2).addComponent(c3);
	e2->addComponent(c2).addComponent(c3);
	e4->addComponent(c4);

	TransformComponent* p1;
	if(s1->getEntityAt(0)->getComponent<TransformComponent>(p1))
	{
		std::cout << "x:" << p1->getX() << " y:" << p1->getY() << " z:" << p1->getZ() << std::endl;
	}

	EntityFilter ef;
	std::cout << std::boolalpha << "entity 1 has Tcomponent and color: " << ef.hasAllComponents<TransformComponent, ColorComponent>(*e1.get()) << std::endl;

	std::cout << std::boolalpha << "entity 2 has Tcomponent and color: " << ef.hasAllComponents<TransformComponent, ColorComponent>(*e2.get()) << std::endl;
	std::cout << std::boolalpha << "entity 3 has Tcomponent: " << ef.hasAllComponents<TransformComponent>(*e4.get()) << std::endl;

	auto allTransformed = ef.filterByComponents<TransformComponent>(s1->getEntities());
	auto allColored = ef.filterByComponents<ColorComponent>(s1->getEntities());

	std::cout << "all entities with TransformComponent:" << std::endl;
	for(auto& e: *allTransformed.get())
	{
		std::cout << "  " << e.get()->getName() << std::endl;
	}

	std::cout << "all entities with ColorComponent:" << std::endl;
	for (auto& e : *allColored.get())
	{
		std::cout << "  " << e.get()->getName() << std::endl;
	}


	m_sceneManager->removeScene(2);

	// END TESTS

	return 0;
}


void Window::run()
{
	if (m_window) {
		try {
			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

			do {
				tick();

			} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(m_window));
		}
		catch (...) {

			std::throw_with_nested("Exception during Window::run");
		}
	}

}

void Window::tick()
{
	glClear(GL_COLOR_BUFFER_BIT);



	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
