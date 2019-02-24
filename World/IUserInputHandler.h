#ifndef USER_INPUT_HANDLER_H
#define USER_INPUT_HANDLER_H

#include <map>
#include <mutex>

///
/// \class IUserInputHandler
/// \brief Interface managing user input states.
///
class IUserInputHandler
{
public:
	typedef int input_type_t;
	typedef int input_value_t;
	typedef std::map<const input_type_t, input_value_t> input_map_t;
	typedef std::pair<const input_type_t, input_value_t> input_map_pair_t;

private:
	/// \brief Gets a copy of the input type and value pair from the internal map. 
	/// \param inputType The input type to find.
	/// \return A copy of the desired pair or a pair containing the "invalidType" type and "invalidValue" as a value upon failure.
	/// \see IUserInputHandler::getInvalidTypeConstant()
	/// \see IUserInputHandler::getInvalidValueConstant()
	input_map_pair_t findInputPairByType(const input_type_t& inputType) const
	{
		const auto match = m_internalMap.find(inputType);
		if(match != m_internalMap.end())
		{
			return *match;
		}
		return input_map_pair_t(getInvalidTypeConstant(), getInvalidValueConstant());
	}

protected:
	IUserInputHandler() = default;
	virtual ~IUserInputHandler() = default;

public:

	///
	/// \brief Sets the stored value of a given input type if its not of the invalid type.
	/// \param inputType The input type to set the value of.
	/// \param value The value to set.
	/// \see IUserInputHandler::getInvalidTypeConstant()
	void setInputValue(const input_type_t& inputType, const input_value_t& value)
	{
		if (inputType != getInvalidTypeConstant())
		{
			m_internalMap_mutex.lock();
			m_internalMap[inputType] = value;
			m_internalMap_mutex.unlock();
		}
	}

	/// \brief Gets the stored value for a given input type.
	/// \param inputType The input type to get the value of.
	/// \return The stored value for the given input type. Upon failure (or if inputType is the "invalidType" constant), "invalidValue" will be returned.
	/// \see IUserInputHandler::getInvalidTypeConstant()
	/// \see IUserInputHandler::getInvalidValueConstant()
	input_value_t getInputValue(const input_type_t& inputType) const
	{
		if(inputType == getInvalidTypeConstant())
		{
			return getInvalidValueConstant();
		}
		return findInputPairByType(inputType).second;

	}

	/// \brief Updates the values for pertinent input types. Should be a locking operation.
	virtual void updateInputStates() = 0;

	/// \brief Gets the invalid type input_type_t for the implementation. Invalid type is an input_type_t representing an error.
	virtual input_type_t getInvalidTypeConstant()const = 0;

	/// \brief Gets the invalid value input_value_t for the implementation. Invalid value is an input_value_t representing an error.
	virtual input_value_t getInvalidValueConstant()const = 0;

protected:
	std::mutex m_internalMap_mutex; /// The internal input state map's mutex.
	input_map_t m_internalMap; /// Internal input state map.

};


#endif

