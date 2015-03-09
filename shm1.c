/*
 * shm1.c
 *
 *  Created on: Mar 10, 2015
 *      Author: shane
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/shm.h>

#include"shm_com.h"

int main(void)
{
	int runing = 1;
	void *shared_memory = (void *) 0;
	struct shared_use_st * shared_stuff;
	int shmid;
	srand((unsigned int) getpid());
	shmid = shmget((key_t) 1234, sizeof(struct shared_use_st),
			0666 | IPC_CREAT);
	if (shmid == -1) {
		perror("shmget error\n");
		exit(EXIT_FAILURE);
	}
	shared_memory = shmat(shmid, (void *) 0, 0);
	if (shared_memory == (void *) -1) {
		perror("shmat error\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory arrached at %X\n", (int) shared_memory);
	shared_stuff = (struct shared_use_st *) shared_memory;
	shared_stuff->written_by_you = 0;
	while (runing) {
		if (shared_stuff->written_by_you) {
			printf("you wrote: %s\n", shared_stuff->some_text);
			sleep(rand()%4);
			shared_stuff->written_by_you = 0;
			if(strncmp(shared_stuff->some_text,"end", 3) == 0)
			{
				runing = 0;
			}
		}
	}
	if(shmdt(shared_memory) == -1)
	{
		perror("shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	if(shmctl(shmid, IPC_RMID, 0) == -1){
		perror("shmit failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}/*end by shm1.c*/

