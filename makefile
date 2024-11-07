CC = gcc
CFLAGS = -Wall -I./library
LIBRARY_OBJS = library/sem.c library/shm.c

all: no_sol_1/no_sol_1_demo no_sol_3/no_sol_3_demo tanenbaum_sol/tanenbaum_sol_demo

no_sol_1/no_sol_1_demo: no_sol_1/demo.c $(LIBRARY_OBJS)
	$(CC) $(CFLAGS) -o no_sol_1/no_sol_1_demo no_sol_1/demo.c $(LIBRARY_OBJS)

no_sol_3/no_sol_3_demo: no_sol_3/demo.c $(LIBRARY_OBJS)
	$(CC) $(CFLAGS) -o no_sol_3/no_sol_3_demo no_sol_3/demo.c $(LIBRARY_OBJS)

tanenbaum_sol/tanenbaum_sol_demo: tanenbaum_sol/demo.c $(LIBRARY_OBJS)
	$(CC) $(CFLAGS) -o tanenbaum_sol/tanenbaum_sol_demo tanenbaum_sol/demo.c $(LIBRARY_OBJS)

clean:
	rm -f no_sol_1/no_sol_1_demo no_sol_3/no_sol_3_demo tanenbaum_sol/tanenbaum_sol_demo
