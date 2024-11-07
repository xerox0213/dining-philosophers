
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../library/sem.h"

const int N = 5;
int forks[N];
int mutex;

void philosopher(int i);
void think(int i);
void takeFork(int i);
void eat(int i);
void putFork(int i);

int main(void)
{
    mutex = createSem();
    initSem(mutex, 1);

    for(int i = 0; i < N; i++)
    {
        forks[i] = createSem();
        initSem(forks[i], 1);
    }

    for(int i = 0; i < N; i++)
    {
        if(fork() == 0)
        {
            philosopher(i);
        }
    }

    for (int i = 0; i < N; i++) wait(NULL);
    removeSem(mutex);
    for(int i = 0; i < N; i++) removeSem(forks[i]);
}

void philosopher(int i)
{
    while (1)
    {
        think(i);
        down(mutex);
        takeFork(i);
        takeFork((i + 1) % N);
        eat(i);
        putFork(i);
        putFork((i + 1) % N);
        up(mutex);
    }
}

void think(int i)
{
    printf("Philosophe n°%d : Je pense...\n", i);
    sleep(1);
}

void takeFork(int i)
{
    int fork = forks[i];
    down(fork);
}

void eat(int i)
{
    printf("Philosophe n°%d : yum-yum spaghetti\n", i);
    sleep(1);
}

void putFork(int i)
{
    int fork = forks[i];
    up(fork);
}