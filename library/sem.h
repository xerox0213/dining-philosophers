int createSem();
void initSem(int semid, int val);
void up(int semid);
void down(int semid);
void removeSem(int semid);