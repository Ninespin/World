#include "UserInputGLFWKeyboardComponent.h"

UserInputKeyboardComponent* UserInputKeyboardComponent::_instance = nullptr;

UserInputKeyboardComponent::UserInputKeyboardComponent()
	: Component("GLFWKeyboardInput")
	, m_boundWindow(nullptr)
{
}


UserInputKeyboardComponent::~UserInputKeyboardComponent()
{
}

void UserInputKeyboardComponent::updateInputStates()
{
}

IUserInputHandler::input_type_t UserInputKeyboardComponent::getInvalidTypeConstant() const
{
	return -1;
}

IUserInputHandler::input_value_t UserInputKeyboardComponent::getInvalidValueConstant() const
{
	return -1;
}

void UserInputKeyboardComponent::hookWindow(GLFWwindow* window)
{
	m_boundWindow = window;
	glfwSetKeyCallback(m_boundWindow, glfwKeyCallback);
}

void UserInputKeyboardComponent::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(UserInputKeyboardComponent::_instance)
	{
		UserInputKeyboardComponent::_instance->setInputValue(key, action);
	}
	
}

UserInputKeyboardComponent* UserInputKeyboardComponent::instance()
{
	if(!UserInputKeyboardComponent::_instance)
	{
		UserInputKeyboardComponent::_instance = new UserInputKeyboardComponent();
	}
	return UserInputKeyboardComponent::_instance;
}

void UserInputKeyboardComponent::destroyInstance()
{
	if(UserInputKeyboardComponent::_instance)
	{
		if(UserInputKeyboardComponent::_instance->m_boundWindow != nullptr)
		{
			glfwSetKeyCallback(UserInputKeyboardComponent::_instance->m_boundWindow, NULL);
		}
		delete UserInputKeyboardComponent::_instance;
	}
}
