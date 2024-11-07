#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../library/sem.h"
#include "../library/shm.h"

const int N = 5;
int * states;
int mutex;
int philosophers[N];

enum { THINKING, HUNGRY, EATING } state;

void philosopher(int i);
void think();
void takeForks(int i);
void eat(int i);
void putForks(int i);
int left(int i);
int right(int i);
bool isHungry(int i);
bool isEating(int i);

int main(void)
{
    int shmid = createShm(sizeof(int) * N);
    int * states = attachShm(shmid);

    for(int i = 0; i < N; i++)
    {
        states[i] = THINKING;
        philosophers[i] = createSem();
        initSem(philosophers[i], 1);
    }

    int mutex = createSem();

    for(int i = 0; i < N; i++)
    {
        if(fork() == 0)
        {
            philosopher(i);
        }
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
    down(mutex);
    states[i] = HUNGRY;
    canEat(i);
    up(mutex);
    down(philosophers[i]);
}

void eat(int i)
{
    printf("Philosophe n°%d : yum-yum spaghetti\n", i);
    sleep(1);
}

void putForks(int i)
{
    down(mutex);
    states[i] = THINKING;
    canEat(left(i));
    canEat(right(i));
    up(mutex);
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
        states[i] = EATING;
        up(philosophers[i]);
    }
}

bool isEating(int i)
{
    return states[i] == EATING;
}

bool isHungry(int i)
{
    return states[i] == HUNGRY;
}