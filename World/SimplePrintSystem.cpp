#include "SimplePrintSystem.h"
#include <iostream>
#include "SimplePrintJob.h"

SimplePrintSystem::SimplePrintSystem()
	: System("SimplePrintSystem")
{
	std::cout << "Creating " << m_name << std::endl;
	std::shared_ptr<IJob> spj = std::shared_ptr<IJob>( new SimplePrintJob());
	m_jobs.push_back(spj);
}


SimplePrintSystem::~SimplePrintSystem()
{
	std::cout << "Destroying " << m_name << std::endl;
}

bool SimplePrintSystem::onStarting()
{
	std::cout << "Starting " << m_name << std::endl;
	return true;
}

bool SimplePrintSystem::onStopping()
{
	std::cout << "Stopping " << m_name << std::endl;
	return true;
}

bool SimplePrintSystem::onUpdate()
{
	std::cout << "Updating jobs for " << m_name << std::endl;
	try {

		for (auto& job : m_jobs)
		{
			if(!job->update())
			{
				std::cout << "Error while updating SimplePrintSystem's job: " << job->getName() << std::endl;
				break;
			}
		}

	}catch(...)
	{
		std::cout << "Error while updating SimplePrintSystem's jobs" << std::endl;
		return false;
	}
	return true;
}
