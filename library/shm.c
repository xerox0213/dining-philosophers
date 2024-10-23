#include "shm.h"
#include <sys/shm.h>
#include <stdlib.h>

int createShm(size_t size)
{
    int shmid = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666);

    if(shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    return shmid;
}

void * attachShm(int shmid)
{
    void * p = shmat(shmid, NULL, 0);

    if(p == (void *) - 1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    return p;
}

void removeShm(int shmid)
{
    if(shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
}