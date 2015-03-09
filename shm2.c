/*
 * shm2.c
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
int main(void) {
	int runing = 1;
	void *shared_memory = (void *) 0;
	struct shared_use_st * shared_stuff;
	char buffer[BUFSIZ];
	int shmid;
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
	while(runing)
	{
		while(shared_stuff->written_by_you == 1)
		{
			sleep(1);
			printf("waiting for client...\n");
		}
		printf("Enter some text: \n");
		fgets(buffer, BUFSIZ, stdin);
		strncpy(shared_stuff->some_text, buffer, TEXT_SIZE);
		shared_stuff->written_by_you = 1;
		if(strncmp(buffer,"end", 3) == 0)
		{
			runing = 0;
		}
	}
	if(shmdt(shared_memory) == -1)
	{
		perror("shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

