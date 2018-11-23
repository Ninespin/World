#include "Scene.h"

#include <iostream>

Scene::Scene(const char* name)
	: m_name(name)
	, m_sceneCRUD(m_entities)
{
	std::cout << "created scene: " << m_name << std::endl;
}


Scene::~Scene()
{
	std::cout << "destroyed scene: " << m_name << std::endl;
}

std::string Scene::getName() const
{
	return m_name;
}

void Scene::setName(std::string & name)
{
	m_name = name;
}



Scene& Scene::removeEntity(SceneCRUD::Index_t index)
{
	try {
		if (!m_sceneCRUD.del(index)) {
			throw;
		}
	}
	catch (...) {
		std::throw_with_nested(std::exception("Failed to remove Entity at index " + index));
	}
	return *this;
}

Scene& Scene::addEntity(SceneCRUD::Object_t  entity)
{
	try {
		if (!m_sceneCRUD.create(entity)) {
			throw;
		}
	}
	catch (...) {
		std::throw_with_nested(std::exception("Failed to add Entity to scene"));
	}
	return *this;
}

SceneCRUD::Container_t& Scene::getEntities()
{
	return m_entities;
}

SceneCRUD::Object_t Scene::getEntityAt(SceneCRUD::Index_t index) const
{
	SceneCRUD::Object_t entity;
	try {
		if (!m_sceneCRUD.read(index, entity)) {
			throw;
		}
	}
	catch (...) {
		std::throw_with_nested(std::exception("Failed to get Entity at index " + index));
	}
	;
	return entity;
}

SceneCRUD::Object_t Scene::getEntityByName(std::string name) const
{
	SceneCRUD::Object_t entity;
	try {
		if (!m_sceneCRUD.readByName(name, entity)) {
			throw;
		}
	}
	catch (...) {
		std::throw_with_nested(std::exception(( std::string("Failed to get Entity with name ")+ name).c_str() ));
	}
	;
	return entity;
}

size_t Scene::getNumScenes() const
{
	return m_entities.size();
}
