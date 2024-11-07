CC = gcc
CFLAGS = -Wall -I./library
LIBRARY_OBJS = library/sem.c library/shm.c

all: no_sol_1/demo no_sol_2/demo tanenbaum_sol/demo

no_sol_1/demo: no_sol_1/demo.c $(LIBRARY_OBJS)
	$(CC) $(CFLAGS) -o no_sol_1/demo no_sol_1/demo.c $(LIBRARY_OBJS)

no_sol_2/demo: no_sol_2/demo.c $(LIBRARY_OBJS)
	$(CC) $(CFLAGS) -o no_sol_2/demo no_sol_2/demo.c $(LIBRARY_OBJS)

tanenbaum_sol/demo: tanenbaum_sol/demo.c $(LIBRARY_OBJS)
	$(CC) $(CFLAGS) -o tanenbaum_sol/demo tanenbaum_sol/demo.c $(LIBRARY_OBJS)

clean:
	rm -f no_sol_1/demo no_sol_2/demo tanenbaum_sol/demo
