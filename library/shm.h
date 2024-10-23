#include <stdio.h>

int createShm(size_t size);
void * attachShm(int shmid);
void removeShm(int shmid);