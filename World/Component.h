#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component
{
protected:
	Component(const char* name);


public:
	virtual ~Component();
	std::string getName()const;
	unsigned int getID()const;

protected:
	inline static unsigned int CURRENT_AVAILABLE_ID = 0;

	std::string m_name;
	const unsigned int m_id;
};



#endif