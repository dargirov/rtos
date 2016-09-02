#include "mutex.h"

mutex_t MutexCreate()
{
	mutex_t mutex;
	mutex.flag_in_use = 0;
	return mutex;
}

uint32_t MutexTake(mutex_t *mutex)
{
	// variable to hold STREX status
	uint32_t status; 
	// Get the lock status and see if it is already locked
	if (__LDREXW(&mutex->flag_in_use) == 0) 
	{
		// if not locked, try set lock to 1
		status = __STREXW(1, &mutex->flag_in_use);
		if (status == 0)
		{
			// return success status
			return 1;
		}
	}
	
	// return fail status
	return 0;
}

uint32_t MutexGive(mutex_t *mutex)
{	
	// variable to hold STREX status
	uint32_t status; 
	// Get the lock status and see if it is already locked
	if (__LDREXW(&mutex->flag_in_use) == 1) 
	{
		// if not locked, try set lock to 1
		status = __STREXW(0, &mutex->flag_in_use);
		if (status == 0)
		{
			// return success status
			return 1;
		}
	}
	
	// return fail status
	return 0; 
}