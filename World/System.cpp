#include "System.h"


System::System(const char* name)
	: m_state(SYSTEM_STATE::STOPPED)
	, m_name(name)
{
}

System::~System()
{
}

bool System::start()
{
	setState(SYSTEM_STATE::STARTING);
	try
	{
		const bool started = onStarting();
		if (started)
		{
			for (auto& job : m_jobs)
			{
				job->start();
			}
			setState(SYSTEM_STATE::RUNNING);
		}else
		{
			throw std::exception("Exception while starting system (System.onStart)");
		}
	}catch(std::exception& e)
	{
		try
		{

			stop();
			setState(SYSTEM_STATE::ERROR);
		}catch(std::exception& e2)
		{
			setState(SYSTEM_STATE::ERROR);
			std::throw_with_nested(e2);
		}
		std::throw_with_nested(e);
	}

	return true;
}

bool System::stop()
{
	const SYSTEM_STATE initialState = m_state;
	try {
		onStopping();

		if (SYSTEM_STATE::ERROR == initialState)
		{
			m_state = SYSTEM_STATE::ERROR;
		}
	}catch(std::exception& e)
	{
		std::throw_with_nested(e);
	}
	return  SYSTEM_STATE::ERROR != m_state;
}

bool System::update()
{
	if (SYSTEM_STATE::RUNNING == m_state)
	{
		try
		{
			onUpdate();
		}
		catch (...)
		{
			setState(SYSTEM_STATE::ERROR);
		}

	}

	if (SYSTEM_STATE::ERROR == m_state || SYSTEM_STATE::STOPPING == m_state)
	{
		stop();
	}

	return SYSTEM_STATE::ERROR != m_state;
}

System::SYSTEM_STATE System::getState()const
{
	return m_state;
}

std::string System::getName()const
{
	return m_name;
}

std::vector<std::shared_ptr<Entity>>& System::getBoundSceneEntities()
{
	return m_boundSceneEntities;
}

void System::setBoundScene(std::vector<std::shared_ptr<Entity>>& scene)
{
	m_boundSceneEntities = scene;
	rebuildEntityTargetList();
	
}

void System::rebuildEntityTargetList()
{
	for(auto& job: m_jobs)
	{
		job->rebuildEntityTargetList(m_boundSceneEntities);
	}
}