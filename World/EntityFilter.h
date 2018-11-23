#pragma once
#include "Entity.h"
#include <vector>
#include <algorithm>

/**
 * \brief Filters entities based on certain characteristics (i.e. by Components).  Filters are used by services.
 */
class EntityFilter
{
public:
	EntityFilter();
	~EntityFilter();


	/**
	 * \brief Checks if a given entities has all the given component types
	 * \tparam TComponents The component classes to check
	 * \param entity The entity to scan
	 * \return Whether or not the entity has all the components
	 */
	template<class... TComponents> bool hasAllComponents(const Entity& entity)const
	{
		bool successState = true;

		for(auto found: { entity.hasComponent<TComponents>()... })
		{
			successState &= found;
		}

		return successState;
	}


	/**
	 * \brief Filters a given entity vector and returns only the entities having ALL given components
	 * \tparam TComponents The component classes to check
	 * \param entityContainer The vector containing the entities to scan
	 * \return A vector containing pointers to the entities that contain ALL given components
	 */
	template<class... TComponents> std::shared_ptr<std::vector<std::shared_ptr<Entity>>> filterByComponents(std::vector<std::shared_ptr<Entity>>& entityContainer)const
	{
		std::shared_ptr<std::vector<std::shared_ptr<Entity>>> result( new std::vector<std::shared_ptr<Entity>>() );
		std::copy_if(
			entityContainer.begin(), 
			entityContainer.end(), 
			std::back_inserter(*result.get()), 
			[=](const std::shared_ptr<Entity> e)
			{
				return hasAllComponents<TComponents...>(*e.get());
			});
		return result;
	}
	
};

