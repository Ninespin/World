
#include <iostream>
#include <string>
#include <sstream>
#include "Window.h"

#include "Entity.h"
#include "TransformComponent.h"
#include "ColorComponent.h"
#include "EntityFilter.h"
#include "SimplePrintSystem.h"


#define WORLD_VERSION_MAJOR 0
#define WORLD_VERSION_MINOR 0

void printException(const std::exception& e, int level = 0) {
	if (level == 0) {
		std::cerr << "EXCEPTION: \n";
	}
	std::cerr << std::string(level+1, ' ') << e.what() << "\n";
	try {
		std::rethrow_if_nested(e);
	}
	catch (const std::exception& e) {
		printException(e, 1 + level);
	}
	catch (...) {
		std::cerr << "unknown exception";
	}
	std::cerr << std::endl;
}

void createScene(Window& window)
{
	auto sceneManager = window.getSceneManager();

	// Scenes
	std::shared_ptr<Scene> s1(new Scene("scene1"));
	sceneManager->addScene(s1);

	// Entities
	std::shared_ptr<Entity> e1(new Entity("entity1"));
	std::shared_ptr<Entity> e2(new Entity("entity2"));
	std::shared_ptr<Entity> e3(new Entity("entity3"));
	std::shared_ptr<Entity> e4(new Entity("entity4"));
	s1->addEntity(e1).addEntity(e2).addEntity(e4).addEntity(e3);


	// Components
	const std::shared_ptr<TransformComponent>	c1(new TransformComponent());
	const std::shared_ptr<TransformComponent>	c2(new TransformComponent());
	const std::shared_ptr<TransformComponent>	c3(new TransformComponent());
	const std::shared_ptr<ColorComponent>		c4(new ColorComponent(8));
	const std::shared_ptr<ColorComponent>		c5(new ColorComponent(255));
	c1->setPosition(-50, 10, 12);
	c2->setPosition(80, 1540, -1);
	c3->setPosition(-5000430, -40, 78);
	e1->addComponent(c2).addComponent(c4);
	e2->addComponent(c3).addComponent(c4);
	e3->addComponent(c5);
	e4->addComponent(c1);

	// Systems
	const std::shared_ptr<SimplePrintSystem> sps(new SimplePrintSystem());
	s1->addSystem(sps);


}

void createScenesTests(Window& window)
{
	auto sceneManager = window.getSceneManager();
	// TESTS 
	// Scenes
	std::shared_ptr<Scene> s1(new Scene("scene1"));
	std::shared_ptr<Scene> s2(new Scene("scene2"));
	std::shared_ptr<Scene> s3(new Scene("scene3"));
	std::shared_ptr<Scene> s4(new Scene("scene4"));
	sceneManager->addScene(s1);
	sceneManager->addScene(s2);
	sceneManager->addScene(s3);
	sceneManager->addScene(s4);

	// Entities
	std::shared_ptr<Entity> e1(new Entity("entity1"));
	std::shared_ptr<Entity> e2(new Entity("entity2"));
	std::shared_ptr<Entity> e3(new Entity("entity3"));
	std::shared_ptr<Entity> e4(new Entity("entity4"));
	s1->addEntity(e1).addEntity(e2).addEntity(e4);
	s4->addEntity(e4).addEntity(e2);
	s3->addEntity(e3);

	// Components
	std::shared_ptr<TransformComponent> c2(new TransformComponent());
	std::shared_ptr<ColorComponent> c3(new ColorComponent(8));
	std::shared_ptr<TransformComponent> c4(new TransformComponent());

	std::cout << "x:" << c2->getX() << " y:" << c2->getY() << " z:" << c2->getZ() << std::endl;
	c2->setPosition(-50, 10, 12);
	std::cout << "x:" << c2->getX() << " y:" << c2->getY() << " z:" << c2->getZ() << std::endl;

	e1->addComponent(c2).addComponent(c3);
	e2->addComponent(c2).addComponent(c3);
	e4->addComponent(c4);

	TransformComponent* p1;
	if (s1->getEntityAt(0)->getComponent<TransformComponent>(p1))
	{
		std::cout << "x:" << p1->getX() << " y:" << p1->getY() << " z:" << p1->getZ() << std::endl;
	}

	EntityFilter<TransformComponent> ef;
	EntityFilter<ColorComponent> efT;
	std::cout << std::boolalpha << "entity 1 has Tcomponent: " << ef.hasAllComponents(*e1.get()) << std::endl;

	std::cout << std::boolalpha << "entity 2 has Tcomponent: " << ef.hasAllComponents(*e2.get()) << std::endl;
	std::cout << std::boolalpha << "entity 3 has color: " << efT.hasAllComponents(*e4.get()) << std::endl;

	std::shared_ptr<SimplePrintSystem> sps = std::shared_ptr<SimplePrintSystem>(new SimplePrintSystem());
	s1->addSystem(sps);

	auto allTransformed = ef.filterByComponents(s1->getEntities());
	auto allColored = efT.filterByComponents(s1->getEntities());

	std::cout << "all entities with TransformComponent:" << std::endl;
	for (auto& e : *allTransformed.get())
	{
		std::cout << "  " << e.get()->getName() << std::endl;
	}

	std::cout << "all entities with ColorComponent:" << std::endl;
	for (auto& e : *allColored.get())
	{
		std::cout << "  " << e.get()->getName() << std::endl;
	}


	sceneManager->removeScene(2);

	// END TESTS
}

int main(int argc, char** argv) {

	try {
		if (!glfwInit()) {
			throw std::exception("FATAL: Failed to initialize GLFW, terminating.");
		}

		std::stringstream title;
		title << "World v" << WORLD_VERSION_MAJOR << "." << WORLD_VERSION_MINOR;

		Window w = Window(title.str());
		createScene(w);

		w.run();

	}
	catch (std::exception& e) {
		printException(e);
	}

	std::cout << "Shutting down..." << std::endl;
	glfwTerminate();

	return 0;
}