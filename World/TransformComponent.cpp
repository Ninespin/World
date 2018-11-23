#include "TransformComponent.h"

TransformComponent::TransformComponent()
	: Component(CLASS_NAME)
	, m_position{ 0,0,0 }
{

}

void TransformComponent::setPosition(int pos[3])
{
	setPosition(pos[0], pos[1], pos[2]);
}

void TransformComponent::setPosition(int x, int y, int z)
{
	m_position[0] = x;
	m_position[1] = y;
	m_position[2] = z;
}

int* TransformComponent::getPosition()
{
	return m_position;
}

int TransformComponent::getX()const
{
	return m_position[0];
}
int TransformComponent::getY()const
{
	return m_position[1];
}
int TransformComponent::getZ()const
{
	return m_position[2];
}

void TransformComponent::setX(const int x)
{
	m_position[0] = x;
}
void TransformComponent::setY(const int y)
{
	m_position[1] = y;
}
void TransformComponent::setZ(const int z)
{
	m_position[2] = z;
}