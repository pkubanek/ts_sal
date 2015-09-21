#include <semaphore.h>
class ScopedLock{
    sem_t *sem;
public:
    ScopedLock(const char* name) : sem(0)
    {
    	sem = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
    	if (sem == SEM_FAILED)
    	{
    		printf("Error opening semaphore : %s\n", last_error_message());
    		throw "failed to create semaphore";
    	}

    	printf("locking interprocess lock...\n");
    	if (-1 == sem_wait(sem))
    	{
    		printf("Error locking semaphore : %s\n", last_error_message());
    		throw "failed to lock semaphore";
    	}
    	printf("interprocess lock locked\n");
    }

    ~ScopedLock()
    {
    	if (sem)
    	{
    		sem_post(sem);
    		printf("interprocess lock unlocked\n");
    	}
    }

    // static destroy function, use for cleanup
    static void destroy(const char *name)
    {
    	sem_t *sem = sem_open(name, O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    	if (sem != SEM_FAILED)
    	{
    		sem_post(sem);
    		sem_destroy(sem);
    	}

    	if (-1 == sem_unlink(name))
    	{
    		printf("Error destroying semphore: %s\n", last_error_message());
    	}
    }
};

