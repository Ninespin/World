#include "Component.h"
#include <iostream>


Component::Component(const char* name)
	: m_name(name)
	, m_id(++Component::CURRENT_AVAILABLE_ID)
{
	std::cout << "created component " << m_name << std::endl;
}

Component::~Component()
{
	std::cout << "destroyed component " << m_name << std::endl;
}


std::string Component::getName() const
{
	return m_name;
}

unsigned int Component::getID() const
{
	return m_id;
}


