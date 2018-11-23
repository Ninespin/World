#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <vector>
#include "SceneManagerFunctors.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	SceneManagerCRUD::Object_t getCurrentScene() const;
	void setCurrentScene(SceneManagerCRUD::Index_t index);
	SceneManager& removeScene(SceneManagerCRUD::Index_t index);
	SceneManager& addScene(SceneManagerCRUD::Object_t scene);
	SceneManagerCRUD::Object_t getSceneAt(SceneManagerCRUD::Index_t index)const;
	size_t getNumScenes()const;



private:
	SceneManagerCRUD::Container_t m_scenes;
	SceneManagerCRUD::Object_t m_currentScene;
	SceneManagerCRUD m_sceneManagerCRUD;
};

#endif
