#include "Entity.h"
#include <iostream>


Entity::Entity(const char * name)
	: m_name(name)
	, m_entityCRUD(m_components)
{
	std::cout << "created entity: " << m_name << std::endl;
}

Entity::~Entity()
{
	std::cout << "destroyed entity: " << m_name << std::endl;
}

std::string Entity::getName() const
{
	return m_name;
}

void Entity::setName(std::string & name)
{
	m_name = name;
}

Entity& Entity::removeComponentAt(EntityCRUD::Index_t index)
{
	try {
		if (!m_entityCRUD.del(index)) {
			throw;
		}
	}
	catch (...) {
		std::throw_with_nested(std::exception("Failed to remove Component at index " + index));
	}
	return *this;
}

Entity& Entity::addComponent(EntityCRUD::Object_t entity)
{
	try {
		if (!m_entityCRUD.create(entity)) {
			throw;
		}
	}
	catch (...) {
		std::throw_with_nested(std::exception("Failed to add Component to Entity"));
	}
	return *this;
}

EntityCRUD::Object_t Entity::getComponentAt(EntityCRUD::Index_t index) const
{
	EntityCRUD::Object_t entity;
	try {
		if (!m_entityCRUD.read(index, entity)) {
			throw;
		}
	}
	catch (...) {
		std::throw_with_nested(std::exception("Failed to get Component at index " + index));
	}
	
	return entity;
}
