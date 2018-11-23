#ifndef SCENE_H
#define SCENE_H

#include <string>
#include "SceneFunctors.h"

class Scene
{
public:
	Scene(const char* name);
	virtual ~Scene();
	std::string getName()const;
	void setName(std::string& name);
	Scene& removeEntity(SceneCRUD::Index_t index);
	Scene& addEntity(SceneCRUD::Object_t entity);
	SceneCRUD::Container_t& getEntities();
	SceneCRUD::Object_t getEntityAt(SceneCRUD::Index_t index)const;
	SceneCRUD::Object_t getEntityByName(std::string name) const;
	size_t getNumScenes()const;

protected:
	std::string m_name;
	SceneCRUD::Container_t m_entities;
	SceneCRUD m_sceneCRUD;



};


#endif