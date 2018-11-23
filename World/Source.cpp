
#include <iostream>
#include <string>
#include <sstream>
#include "Window.h"

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

int main(int argc, char** argv) {

	try {
		if (!glfwInit()) {
			throw std::exception("FATAL: Failed to initialize GLFW, terminating.");
		}

		std::stringstream title;
		title << "World v" << WORLD_VERSION_MAJOR << "." << WORLD_VERSION_MINOR;

		Window w = Window(title.str());

		w.run();

	}
	catch (std::exception& e) {
		printException(e);
	}

	std::cout << "Shutting down..." << std::endl;
	glfwTerminate();

	return 0;
}