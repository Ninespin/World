#include "SimplePrintJob.h"
#include <iostream>


SimplePrintJob::SimplePrintJob()
	: Job("SimplePrintJob")
{
}


SimplePrintJob::~SimplePrintJob()
{
}

bool SimplePrintJob::onStarting()
{
	std::cout << "Job " << getName() << " started." << std::endl;
	return true;
}

bool SimplePrintJob::onStopping()
{
	std::cout << "Job " << getName() << " stopped." << std::endl;
	return true;
}

bool SimplePrintJob::onUpdate()
{
	std::cout << "Job " << getName() << " update:" << std::endl;
	for(auto& entity: *m_targetEntities.get())
	{
		TransformComponent* tcomponent;
		entity->getComponent(tcomponent);

		if(tcomponent)
		{
			std::cout << "    entity: " << entity->getName() << "\tx:" << tcomponent->getX() << "\ty:" << tcomponent->getY() << "\tz:" << tcomponent->getZ() << std::endl;
		}
	}
	return true;

}
