#ifndef DRAW_JOB_H
#define DRAW_JOB_H

#include "Job.h"
#include "TransformComponent.h"
#include "MeshComponent.h"

class DrawJob : public Job<TransformComponent, MeshComponent>
{
public:
	DrawJob();
	~DrawJob();



protected:
	bool onStarting() override;
	bool onStopping() override;
	bool onUpdate() override;
	virtual bool  draw(const TransformComponent* tc, const MeshComponent* mc);

};

#endif