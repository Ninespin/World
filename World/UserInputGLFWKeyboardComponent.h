#pragma once
#include "Component.h"
#include <GLFW/glfw3.h>
#include "IUserInputHandler.h"

//scrap
/// \class UserInputKeyboardComponent
/// \brief Class in charge of keeping track of glfw keyboard input events.
///
class UserInputKeyboardComponent : public Component, public IUserInputHandler
{
private:
	UserInputKeyboardComponent();
	~UserInputKeyboardComponent();

public:
	void updateInputStates() override;
	input_type_t getInvalidTypeConstant()const override;
	input_value_t getInvalidValueConstant()const override;
	void hookWindow(GLFWwindow* window);

	static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static UserInputKeyboardComponent* instance();
	static void destroyInstance();


private:
	static UserInputKeyboardComponent* _instance;
	GLFWwindow* m_boundWindow; /// The GLFW window from which to get the input events.
};
