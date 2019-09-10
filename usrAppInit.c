/* usrAppInit.c - stub application initialization routine */

/* Copyright (c) 1998,2006 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 modification history
 --------------------
 01b,16mar06,jmt  Add header file to find USER_APPL_INIT define
 01a,02jun98,ms   written
 */

/*
 DESCRIPTION
 Initialize user application code.
 */

/* #includes */
#include <vxWorks.h>
#include "stdio.h"
#include "taskLib.h"
#include "sysLib.h"
#include "usrLib.h"
#include "filterExterns.h"

/* externs */
extern int valueArray[50][102];
extern int noOfChannels;
extern int prevOutput[50][2];
extern float constants[50][6];

/* global variables */
SEM_ID semBinaryOne;
SEM_ID semfilterImp;

/* function prototypes */
void pushRawDataTask(void);
void controllingTask(void);
extern void filterImptask(void);

#if defined(PRJ_BUILD)
#include "prjParams.h"
#endif /* defined PRJ_BUILD */

/******************************************************************************
 *
 * usrAppInit - initialize the users application
 */

void usrAppInit(void)
{
#ifdef	USER_APPL_INIT
	USER_APPL_INIT; /* for backwards compatibility */
#endif

	/*Initalisation*/
	configg();
	int iter1 = 0, iter2 = 0;
	int length = 0;
	int taskId1, taskId2, taskId3; /* creating three tasks */
	printf("VALUE ARRAY:\n");
	printf("type\tLength\n");
	
/* printing the 2-D value array */
	for (iter1 = 0; iter1 < noOfChannels; iter1++)
	{
		length = valueArray[iter1][1];
		for (iter2 = 0; iter2 < length + 2; iter2++)
		{
			printf("%d\t", valueArray[iter1][iter2]);
		}
		printf("\n");
	}
	/* semaphore creation */
	semBinaryOne = semBCreate(SEM_Q_FIFO, SEM_FULL);
	semfilterImp = semBCreate(SEM_Q_FIFO, SEM_FULL);
	/* spawning the three tasks */
	taskId1 = (int)(taskSpawn("pushD", 102, 0x100, 20000, (FUNCPTR) pushRawDataTask, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0));
	taskId2 = (int)(taskSpawn("filter", 103, 0x100, 20000, (FUNCPTR) filterImptask, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0));
	taskId3 = (int)(taskSpawn("schedule", 101, 0x100, 20000, (FUNCPTR) controllingTask, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0)); 	
}

/* task for getting rawdata and pushing data into channels */
void pushRawDataTask(void)
{
	semTake(semBinaryOne,WAIT_FOREVER); /* acquiring semaphore */
	int i = 0,j = 0;
	int rawData = 0; 
	for(i=0;i<noOfChannels;i++)
	{
		for(j=0;j<100;j++)
		{
			rawData = getRawData(); /* function call to get random data inout */
			pushData(i,rawData); /* function call to pushData function passing rawData as parameter*/
		}
	}
}

/* task to control pushRawDataTask and filterImpTask
 * description: this task releases the semaphores acquired by the two other tasks */
void controllingTask(void)
{
	/* releasing the semaphores */
	semGive(semBinaryOne);
	semGive(semfilterImp);
	
}
