#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "../library/sem.h"

#define N 5
int forkSemaphores[N];
int mutexSemaphore;

void philosopher(int i);
void think(int i);
void takeFork(int i);
void eat(int i);
void putFork(int i);

int main(void)
{
    mutexSemaphore = createSem();
    initSem(mutexSemaphore, 1);

    for(int i = 0; i < N; i++)
    {
        forkSemaphores[i] = createSem();
        initSem(forkSemaphores[i], 1);
    }

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
        down(mutexSemaphore);
        takeFork(i);
        takeFork((i + 1) % N);
        eat(i);
        putFork(i);
        putFork((i + 1) % N);
        up(mutexSemaphore);
    }
}

void think(int i)
{
    printf("Philosophe n°%d : Je pense...\n", i);
    sleep(1);
}

void takeFork(int i)
{
    int forkSemaphore = forkSemaphores[i];
    down(forkSemaphore);
}

void eat(int i)
{
    printf("Philosophe n°%d : yum-yum spaghetti\n", i);
    sleep(1);
}

void putFork(int i)
{
    int forkSemaphore = forkSemaphores[i];
    up(forkSemaphore);
}