#ifndef SCENE_FUNCTORS_H
#define SCENE_FUNCTORS_H

#include <vector>
#include "CRUDFunctor.h"
#include "Entity.h"

class SceneCRUD : public CRUDFunctor<std::vector<std::shared_ptr<Entity>>, std::shared_ptr<Entity>, size_t> {
public:
	SceneCRUD(Container_t& container)
		: CRUDFunctor(container)
	{

	}

	bool create(Object_t& objectToAdd) override
	{
		bool success = true;
		try {
			m_container.push_back(objectToAdd);
		}
		catch (...) {
			return success = false;
		}
		return success;
	}

	bool read(const Index_t& index, Object_t& outData) const override
	{
		bool success = true;
		try {
			outData = m_container.at(index);
		}
		catch (...) {
			return success = false;
		}
		return success;
	}

	bool update(const Index_t& index, Object_t& newData) override
	{
		bool success = true;
		try {
			m_container.at(index) = newData;
		}
		catch (...) {
			return success = false;
		}
		return success;
	}

	bool del(const Index_t& index) override
	{
		bool success = true;
		try {
			m_container.erase(std::next(m_container.begin(), index));
		}
		catch (...) {
			return success = false;
		}
		return success;
	}


	bool readByName(const std::string& name, Object_t& outData) const
	{
		bool success = true;
		try {

			for(auto& entity: m_container)
			{
				if(name == entity->getName())
				{
					outData = entity;
					break;
				}
			}
		}
		catch (...) {
			return success = false;
		}
		return success;
	}

};



#endif
