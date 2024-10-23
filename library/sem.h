int createSem();
void initSem(int semid, int val);
void up(int semid);
void down(int semid);
int getVal(int semid);
void removeSem(int semid);