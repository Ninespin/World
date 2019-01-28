#ifndef DRAW_SYSTEM_H
#define DRAW_SYSTEM_H

#include "System.h"

class DrawSystem : public System
{
public:
	DrawSystem();
	~DrawSystem();

protected:
	bool onStarting() override;
	bool onStopping() override;
	bool onUpdate() override;
};

#endif
