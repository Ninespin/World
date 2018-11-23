#pragma once
#include "Component.h"

class ColorComponent :
	public Component
{
public:
	ColorComponent(int color)
		: Component("ColorComponent")
		, m_color(color)
	{
	}

	virtual ~ColorComponent()
	{
	}

	void setColor(int color)
	{
		m_color = color;
	}

	int getColor()const
	{
		return m_color;
	}

protected:
	int m_color;
};

