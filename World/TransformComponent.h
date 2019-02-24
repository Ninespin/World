#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Component.h"


class TransformComponent : public Component
{
	inline static const char* CLASS_NAME = "TransformComponent";
public:
	TransformComponent();

	float* getPosition();
	float getX()const;
	float getY()const;
	float getZ()const;

	float* getRotation();
	float getRX()const;
	float getRY()const;
	float getRZ()const;

	void setPosition(float pos[3]);
	void setPosition(float x, float y, float z);
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);

	void setRotation(float rot[3]);
	void setRotation(float x, float y, float z);
	void setRX(const float x);
	void setRY(const float y);
	void setRZ(const float z);


protected:
	float m_position[3];
	float m_rotation[3];

};



#endif