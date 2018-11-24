#ifndef SIMPLE_PRINT_JOB_H
#define SIMPLE_PRINT_JOB_H

#include "Job.h"
#include "TransformComponent.h"

class SimplePrintJob: public Job<TransformComponent>
{
public:
	SimplePrintJob();
	~SimplePrintJob();


protected:
	bool onStarting() override;
	bool onStopping() override;
	bool onUpdate() override;
};

#endif