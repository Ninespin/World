#include "TransformComponent.h"

TransformComponent::TransformComponent()
	: Component(CLASS_NAME)
	, m_position{ 0,0,0 }
	, m_rotation{ 0,0,0 }
{

}

void TransformComponent::setPosition(float pos[3])
{
	setPosition(pos[0], pos[1], pos[2]);
}

void TransformComponent::setPosition(float x, float y, float z)
{
	m_position[0] = x;
	m_position[1] = y;
	m_position[2] = z;
}

void TransformComponent::setRotation(float rot[3])
{
	setRotation(rot[0], rot[1], rot[2]);
}

void TransformComponent::setRotation(float x, float y, float z)
{
	m_rotation[0] = x;
	m_rotation[1] = y;
	m_rotation[2] = z;
}

float* TransformComponent::getPosition()
{
	return m_position;
}

float TransformComponent::getX()const
{
	return m_position[0];
}
float TransformComponent::getY()const
{
	return m_position[1];
}
float TransformComponent::getZ()const
{
	return m_position[2];
}

float* TransformComponent::getRotation()
{
	return m_rotation;
}

float TransformComponent::getRX() const
{
	return m_rotation[0];
}

float TransformComponent::getRY() const
{
	return m_rotation[1];
}

float TransformComponent::getRZ() const
{
	return m_rotation[2];
}

void TransformComponent::setX(const float x)
{
	m_position[0] = x;
}
void TransformComponent::setY(const float y)
{
	m_position[1] = y;
}
void TransformComponent::setZ(const float z)
{
	m_position[2] = z;
}

void TransformComponent::setRX(const float x)
{
	m_rotation[0] = x;
}
void TransformComponent::setRY(const float y)
{
	m_rotation[1] = y;
}
void TransformComponent::setRZ(const float z)
{
	m_rotation[2] = z;
}