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
SEM_ID semBinary1;
SEM_ID semBinary2;

int v1 = 5;
int v2 = 10;

/*Function declaration*/
void taskOne(void);
void taskTwo(void);
void taskThree(void);
void taskInitialisation();

extern void taskOne1(void);
extern void taskTwo2(void);
extern void mutex();
extern void taskIniti();

void usrAppInit(void)
{
#ifdef USER_APP_INIT
	USER_APP_INIT;
#endif
	printf("Helo world\n");
	/* taskInitialisation(); */
	mutex();
}

/* Function:
 * Input:
 * Output:
 * Description:
 * */
void taskInitialisation(void)
{
	int taskIdOne, taskIdTwo, taskIdThree;

	taskIdOne = taskSpawn("t1", 102, 0x100, 20000, (FUNCPTR) taskOne, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0);
	taskIdTwo = taskSpawn("t2", 103, 0x100, 20000, (FUNCPTR) taskTwo, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0);

	taskIdThree = taskSpawn("t3", 101, 0x100, 20000, (FUNCPTR) taskThree, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0);
}

/* Task 1 */
void taskOne(void)
{
	semBinary1 = semBCreate(SEM_Q_FIFO, SEM_FULL);

	while (1)
	{
		semTake(semBinary1, WAIT_FOREVER);
		v1++;
		printf("Task 1 acquired semaphore\n");
		printf("variable 1: %d\n", v1);

		/*taskThree();*/
	}
}

/* Task 2 */
void taskTwo(void)
{
	semBinary2 = semBCreate(SEM_Q_FIFO, SEM_FULL);

	while (1)
	{
		semTake(semBinary2, WAIT_FOREVER);
		v2++;
		printf("Task 2 Acquired Semaphore\n");
		printf("Variable 2: %d\n", v2);
		printf("\n");

		/*taskThree();*/
	}
}

void taskThree(void)
{
	while (1)
	{
		semGive(semBinary1);
		printf("Task 1 released semaphore\n");
		semGive(semBinary2);
		printf("Task 2 released semaphore\n\n");
		taskDelay(500);
	}
}

