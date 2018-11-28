#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "SceneManager.h"

class Window
{
public:
	static const int DEFAULT_WIDTH = 1200;
	static const int DEFAULT_HEIGHT = 800;

public:
	Window(const std::string& title, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, GLFWmonitor* monitor = nullptr, GLFWwindow* shareWindow = nullptr);
	~Window();
	void run();
	std::shared_ptr<SceneManager> getSceneManager()const;

private:
	int init();
	void tick();
	void start();
	void stop();

private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;
	std::string m_title;
	GLFWmonitor* m_monitor;
	GLFWwindow* m_shareWindow;

	std::shared_ptr<SceneManager> m_sceneManager;
};

#endif
