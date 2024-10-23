#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../library/sem.h"

const int N = 5;
int forks[N];

void philosopher(int i);
void think(int i);
void takeFork(int i);
void eat(int i);
void putFork(int i);

int main(void)
{

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
}

void philosopher(int i)
{
    while (1)
    {
        // Pense pendant un certain temps
        think(i);
        
        // Tente de prendre la fourchette à gauche de son plat de spaghetti
        takeFork(i);

        // Tente de prendre la fourchette à droite de son plat de spaghetti
        takeFork((i + 1) % N);

        // Arrivée ici il a les deux fourchettes, il peut donc manger son plat
        eat(i);

        // Redépose la fourchette de gauche
        putFork(i);

        // Redépose la fourchette de droite
        putFork((i + 1) % N);
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