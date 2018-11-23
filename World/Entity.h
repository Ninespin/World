#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <set>
#include "EntityFunctors.h"
#include "Component.h"

class Entity
{
public:
	Entity(const char* name);
	virtual ~Entity();
	std::string getName()const;
	void setName(std::string& name);

	Entity& removeComponentAt(EntityCRUD::Index_t index);
	Entity& addComponent(EntityCRUD::Object_t entity);
	EntityCRUD::Object_t getComponentAt(EntityCRUD::Index_t index) const;

	/**
	 * \brief Gets a component of a given type
	 * \tparam C A component subclass
	 * \param outComponent A given pointer in which to store the found component 
	 * \return Whether or not the desired component was found
	 */
	template <class C> bool getComponent( C*& outComponent)const {
		bool success = false;
		C* result;
		for (auto& component : m_components) {
			result = dynamic_cast<C*>(component.get());
			if (result) {
				outComponent = result;
				success = true;
				break;
			}
		}

		return success;
	}

	
	/**
	 * \brief Verifies if a component of a given type is present in the entity
	 * \tparam C A component subclass
	 * \return Whether or not the desired component was found
	 */
	template <class C> bool hasComponent()const {
		bool success = false;
		C* result;
		for (auto& component : m_components) {
			result = dynamic_cast<C*>(component.get());
			if (result) {
				success = true;
				break;
			}
		}

		return success;
	}




protected:
	std::string m_name; 
	EntityCRUD::Container_t m_components;
	EntityCRUD m_entityCRUD;
};


#endif


