#include "sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int createSem()
{
    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);

    if(semid == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    return semid;
}

void initSem(int semid, int val)
{
    if(semctl(semid, 0, SETVAL, val))
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }
}

void up(int semid)
{
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;

    if(semop(semid, &op, 1) == -1)
    {
        perror("semop");
        exit(EXIT_FAILURE);
    }
}


void down(int semid)
{
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;

    if(semop(semid, &op, 1) == -1)
    {
        perror("semop");
        exit(EXIT_FAILURE);
    }
}

void removeSem(int semid)
{
    if(semctl(semid, 0, IPC_RMID) == -1)
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }
}