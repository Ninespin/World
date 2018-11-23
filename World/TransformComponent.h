#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Component.h"


class TransformComponent : public Component
{
	inline static const char* CLASS_NAME = "TransformComponent";
public:
	TransformComponent();

	int* getPosition();
	int getX()const;
	int getY()const;
	int getZ()const;

	void setPosition(int pos[3]);
	void setPosition(int x, int y, int z);
	void setX(const int x);
	void setY(const int y);
	void setZ(const int z);


protected:
	int m_position[3];

};



#endif