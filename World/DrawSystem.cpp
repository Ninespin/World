#include "DrawSystem.h"
#include "DrawJob.h"
#include <iostream>


DrawSystem::DrawSystem()
	:System("DrawSystem")
{
	std::shared_ptr<IJob> sdj = std::shared_ptr<IJob>(new DrawJob());
	m_jobs.push_back(sdj);
}


DrawSystem::~DrawSystem()
{
}

bool DrawSystem::onStarting()
{
	return true;
}

bool DrawSystem::onStopping()
{
	return true;
}

bool DrawSystem::onUpdate()
{
	//std::cout << "Updating jobs for " << getName() << std::endl;
	try {

		for (auto& job : m_jobs)
		{
			if (!job->update())
			{
				std::cout << "Error while updating DrawSystem's job: " << job->getName() << std::endl;
				break;
			}
		}

	}
	catch (...)
	{
		std::cout << "Error while updating DrawSystem's jobs" << std::endl;
		return false;
	}
	return true;
}
