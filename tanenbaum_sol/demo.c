#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../library/sem.h"
#include "../library/shm.h"

#define N 5
int * philosopherStates;
int mutexSemaphore;
int philosopherSemaphores[N];

enum { THINKING, HUNGRY, EATING } state;

void philosopher(int i);
void think(int i);
void takeForks(int i);
void eat(int i);
void putForks(int i);
int left(int i);
int right(int i);
bool isHungry(int i);
bool isEating(int i);
void canEat(int i);

int main(void)
{
    int shmid = createShm(sizeof(int) * N);
    philosopherStates = attachShm(shmid);

    for(int i = 0; i < N; i++)
    {
        philosopherStates[i] = THINKING;
        philosopherSemaphores[i] = createSem();
        initSem(philosopherSemaphores[i], 0);
    }

    mutexSemaphore = createSem();
    initSem(mutexSemaphore, 1);

    for(int i = 0; i < N; i++)
    {
        if(fork() == 0)
        {
            philosopher(i);
        }
    }


    for (int i = 0; i < N; i++)
    {
        wait(NULL);
    }
    
}

void philosopher(int i)
{
    while (true)
    {
        think(i);
        takeForks(i);
        eat(i);
        putForks(i);
    }
}

void think(int i)
{
    printf("Philosophe n°%d : Je pense...\n", i);
    sleep(1);
}

void takeForks(int i)
{
    down(mutexSemaphore);
    philosopherStates[i] = HUNGRY;
    canEat(i);
    up(mutexSemaphore);
    down(philosopherSemaphores[i]);
}

void eat(int i)
{
    printf("Philosophe n°%d : yum-yum spaghetti\n", i);
    sleep(1);
}

void putForks(int i)
{
    down(mutexSemaphore);
    philosopherStates[i] = THINKING;
    canEat(left(i));
    canEat(right(i));
    up(mutexSemaphore);
}

int left(int i)
{
    return (i + N - 1) % N;
}

int right(int i)
{
    return (i + 1) % N;
}

void canEat(int i)
{
    if(isHungry(i) && !isEating(left(i)) && !isEating(right(i)))
    {
        philosopherStates[i] = EATING;
        up(philosopherSemaphores[i]);
    }
}

bool isEating(int i)
{
    return philosopherStates[i] == EATING;
}

bool isHungry(int i)
{
    return philosopherStates[i] == HUNGRY;
}