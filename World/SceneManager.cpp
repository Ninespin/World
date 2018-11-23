#include "SceneManager.h"
#include <exception>


SceneManager::SceneManager()
	: m_sceneManagerCRUD(m_scenes)
	, m_currentScene(nullptr)
{
}


SceneManager::~SceneManager()
{
}

SceneManagerCRUD::Object_t SceneManager::getCurrentScene() const
{
	return m_currentScene;
}

void SceneManager::setCurrentScene(SceneManagerCRUD::Index_t index)
{
	try {
		if (!m_sceneManagerCRUD.read(index, m_currentScene)) {
			throw;
		}
	}
	catch (...) {
		std::throw_with_nested(std::string("No scene at index "+index));
	}
}

SceneManager& SceneManager::removeScene(SceneManagerCRUD::Index_t index)
{
	try {
		if (!m_sceneManagerCRUD.del(index)) {
			throw;
		}
	}
	catch (...) {
		std::throw_with_nested(std::exception("Failed to remove scene at index " + index));
	}
	return *this;
}

SceneManager & SceneManager::addScene(SceneManagerCRUD::Object_t  scene)
{
	try {
		if (!m_sceneManagerCRUD.create(scene)) {
			throw;
		}
	}
	catch (...) {
		std::throw_with_nested(std::exception("Failed to add scene to SceneManager's scenes"));
	}
	return *this;
}

SceneManagerCRUD::Object_t SceneManager::getSceneAt(SceneManagerCRUD::Index_t index) const
{
	SceneManagerCRUD::Object_t scene;
	m_sceneManagerCRUD.read(index, scene);
	return scene;
}

size_t SceneManager::getNumScenes() const
{
	return m_scenes.size();
}
