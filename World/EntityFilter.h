#pragma once
#include "Entity.h"
#include <vector>
#include <algorithm>


typedef std::vector<std::shared_ptr<Entity>> EntityList_t;

/**
 * \brief Filters entities based on certain characteristics (i.e. by Components).  Filters are used by services.
 * \tparam TComponents The component classes to check
 */
template <typename Tt, typename... TComponents> class EntityFilter
{
public:

	/**
	 * \brief Checks if a given entities has all the given component types
	 * \param entity The entity to scan
	 * \return Whether or not the entity has all the components
	 */
	bool hasAllComponents(const Entity& entity)const
	{
		bool successState = true;

		for(auto found: { entity.hasComponent<Tt>(), entity.hasComponent<TComponents>()... })
		{
			successState &= found;
		}

		return successState;
	}


	/**
	 * \brief Filters a given entity vector and returns only the entities having ALL given components
	 * \param entityContainer The vector containing the entities to scan
	 * \return A vector containing pointers to the entities that contain ALL given components
	 */
	std::shared_ptr<EntityList_t> filterByComponents(EntityList_t& entityContainer)const
	{
		std::shared_ptr<EntityList_t> result( new EntityList_t() );
		std::copy_if(
			entityContainer.begin(), 
			entityContainer.end(), 
			std::back_inserter(*result.get()), 
			[=](const std::shared_ptr<Entity> e)
			{
				return hasAllComponents(*e.get());
			});
		return result;
	}

	
};

