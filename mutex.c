/* usrAppInit.c - stub application initialization routine */

/* Copyright 1984-1998 Wind River Systems, Inc. */

/*
 modification history
 --------------------
 01a,02jun98,ms   written
 */

/*
 DESCRIPTION
 Initialize user application code.
 */

/******************************************************************************
 *
 * usrAppInit - initialize the users application
 */
/*#include*/
#include "taskLib.h"
#include "sysLib.h"
#include "usrLib.h"
#include "vxWorks.h"

/*Global variables*/
SEM_ID semMutexOne;
SEM_ID semMutexTwo;

int var1 = 5;
int var2 = 10;

/*Function declaration*/
void taskOne1(void);
void taskTwo2(void);

void taskIniti();

void mutex(void)
{
#ifdef USER_APP_INIT
	USER_APP_INIT;
#endif
	printf("Helo world\n");
	taskIniti();
}

/* Function:
 * Input:
 * Output:
 * Description:
 * */
void taskIniti(void)
{
	int taskIdOne1, taskIdTwo2;

	taskIdOne1 = taskSpawn("tt1", 102, 0x100, 20000, (FUNCPTR) taskOne1, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0);
	taskIdTwo2 = taskSpawn("tt1", 103, 0x100, 20000, (FUNCPTR) taskTwo2, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0);	
}

/* Task 1 */
void taskOne1(void)
{
	semMutexOne = semMCreate(SEM_Q_FIFO);

	while (1)
	{
		semTake(semMutexOne, WAIT_FOREVER);
		var1++;
		printf("Task 1 acquired semaphore\n");
		printf("variable 1: %d\n", var1);

		semGive(semMutexOne);
		printf("Task 1 released\n");
		taskDelay(400);
	}
	
}

/* Task 2 */
void taskTwo2(void)
{
	semMutexTwo = semMCreate(SEM_Q_FIFO);

	while (1)
	{
		semTake(semMutexTwo, WAIT_FOREVER);
		var2++;
		printf("Task 2 Acquired Semaphore\n");
		printf("Variable 2: %d\n", var2);
		semGive(semMutexTwo);
		printf("Task 2 released semaphore\n");
		taskDelay(400);
	}
	
}



