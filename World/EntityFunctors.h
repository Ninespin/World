#ifndef ENTITY_FUNCTORS_H
#define ENTITY_FUNCTORS_H

#include <vector>
#include "CRUDFunctor.h"
#include "Component.h"

class EntityCRUD : public CRUDFunctor<std::vector<std::shared_ptr<Component>>, std::shared_ptr<Component>, size_t> {
public:
	EntityCRUD(Container_t& container)
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

};



#endif
