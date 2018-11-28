#ifndef JOB_H
#define JOB_H

#include "EntityFilter.h"

class IJob
{

public:
	enum class JOB_STATE
	{
		STOPPED,  // not running
		RUNNING,  // currently running
		SUCCESS,  // done running, no error, task successful
		FAILURE,  // done running, no error, task unsuccessful
		ERROR,	  // done running, error
		STARTING, // not runningm, but starting
		STOPPING  // running but stopping
	};

protected:
	IJob(const char* name)
		: m_name(name)
		, m_state(JOB_STATE::STOPPED){}

public:
	/**
	* \brief Starts the job process cleanly. if the onStarting method fails, will set the state to ERROR and attempt to stop
	* \return Execution success
	*/
	bool start()
	{
		setState(JOB_STATE::STARTING);
		if (onStarting())
		{
			setState(JOB_STATE::RUNNING);
		}
		else
		{
			setState(JOB_STATE::ERROR);
			return stop();
		}
		return true;
	}

	/**
	* \brief Stop the job process cleanly
	* \return Execution success
	*/
	bool stop()
	{
		JOB_STATE initialState = m_state;
		onStopping();

		if (JOB_STATE::ERROR == initialState)
		{
			m_state = JOB_STATE::ERROR;
			return false;
		}
		return true;
	}

	/**
	* \brief Update method: do what the job has to do per iteration
	* \return Execution success
	*/
	bool update()
	{
		if (JOB_STATE::RUNNING == m_state)
		{
			try
			{
				onUpdate();
			}
			catch (...)
			{
				setState(JOB_STATE::ERROR);
			}

		}

		if (JOB_STATE::ERROR == m_state || JOB_STATE::STOPPING == m_state)
		{
			stop();
		}

		return JOB_STATE::ERROR != m_state;
	}

	/**
	* \brief Gets the current state of the Job
	* \return The current state of the Job
	*/
	JOB_STATE getState()const
	{
		return m_state;
	}

	/**
	* \brief Gets the Job's name
	* \return The Job's name
	*/
	std::string getName()const
	{
		return m_name;
	}

	/**
	* \brief Clears then re-builds the entity list that the job uses
	* \param allEntities All entities from which to filter entities
	*/
	virtual void rebuildEntityTargetList(EntityList_t& allEntities) = 0;

protected:

	/**
	* \brief Start event: initialization & setup code
	* \return Success state
	*/
	virtual bool onStarting() = 0;

	/**
	* \brief Stop event: cleanup code
	* \return Success state
	*/
	virtual bool onStopping() = 0;

	/**
	* \brief Update event: called every iteration if the job is running
	* \return  Success state
	*/
	virtual bool onUpdate() = 0;

	/**
	* \brief Sets the state of this job
	* \param state The new state to set
	*/
	void setState(JOB_STATE state)
	{
		m_state = state;
	}

protected:
	std::string m_name;
	JOB_STATE m_state;
	std::shared_ptr<EntityList_t> m_targetEntities;

};

template<typename Tt, class... TComponents> class Job: public IJob
{

public:
	Job(const char* name)
		: IJob(name)
		, m_entityFilter()
	{
	}

	virtual ~Job()
	{
	}

	void rebuildEntityTargetList(EntityList_t& allEntities) override
	{
		if (m_targetEntities) {
			m_targetEntities->clear();
		}
		m_targetEntities = m_entityFilter.filterByComponents(allEntities);
		
	}


protected:
	EntityFilter<Tt, TComponents...> m_entityFilter;

};

#endif