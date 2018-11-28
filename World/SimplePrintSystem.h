#ifndef SIMPLE_PRINT_SYSTEM
#define SIMPLE_PRINT_SYSTEM

#include "System.h"

class SimplePrintSystem: public System
{
public:
	SimplePrintSystem();
	~SimplePrintSystem();

protected:
	bool onStarting() override;
	bool onStopping() override;
	bool onUpdate() override;
};

#endif