#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <string>
#include <vector>
#include "Entity.h"
#include "Job.h"

class System
{
public:
	enum class SYSTEM_STATE
	{
		STOPPED,  // not running
		RUNNING,  // currently running
		SUCCESS,  // done running, no error, task successful
		FAILURE,  // done running, no error, task unsuccessful
		ERROR,	  // done running, error
		STARTING, // not runningm, but starting
		STOPPING  // running but stopping
	};

	System(const char* name);

	virtual ~System();


	/**
	* \brief Starts the System's jobs processes cleanly. if the onStarting method fails, will set the state to ERROR and attempt to stop
	* \return Execution success
	*/
	bool start();

	/**
	* \brief Stop the System's jobs processes cleanly
	* \return Execution success
	*/
	bool stop();

	/**
	* \brief Update method: run job updates per iteration
	* \return Execution success
	*/
	bool update();

	/**
	* \brief Gets the current state of the System
	* \return The current state of the System
	*/
	SYSTEM_STATE getState()const;

	/**
	* \brief Gets the System's name
	* \return The System's name
	*/
	std::string getName()const;

	/**
	* \brief Clears then re-builds the entity list that the jobs use
	*/
	virtual void rebuildEntityTargetList();

	/**
	 * \brief Gets the Scene entities to which this System is bound
	 * \return The Scene entities to which this System is bound
	 */
	std::vector<std::shared_ptr<Entity>>& getBoundSceneEntities();

	/**
	 * \brief Sets the Scene to which's entities this System is bound
	 * \param scene The Scene which's entities to bind this System to
	 */
	void setBoundScene(std::vector<std::shared_ptr<Entity>>& scene);

protected:

	/**
	* \brief Start event: initialization & setup code
	* \return Success state
	*/
	virtual bool onStarting() { return true; };

	/**
	* \brief Stop event: cleanup code
	* \return Success state
	*/
	virtual bool onStopping() { return true; };

	/**
	* \brief Update event: called every iteration if the system is running
	* \return  Success state
	*/
	virtual bool onUpdate() { return true; };

	/**
	* \brief Sets the state of this System
	* \param state The new state to set
	*/
	void setState(SYSTEM_STATE state)
	{
		m_state = state;
	}

protected:
	std::string m_name;
	SYSTEM_STATE m_state;
	std::vector<std::shared_ptr<IJob>> m_jobs;
	std::vector<std::shared_ptr<Entity>> m_boundSceneEntities;
};

#endif