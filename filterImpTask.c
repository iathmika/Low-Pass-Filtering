#include "filterIncludes.h"
#include "filterExterns.h"

/* global variables */
SEM_ID semfilterImp;

/* function prototypes */
void filterImptask(void);

/* function body for implementing the filtering functions 
 * description: This function implements the respective filtering function whether average, first order or second order 
 * filter for each channel and prints the output to the user */ 
void filterImptask(void)
{
	semfilterImp = semBCreate(SEM_Q_FIFO, SEM_FULL); /* semaphore creation */

	while(1)
	{
		semTake(semfilterImp, WAIT_FOREVER); /* acquiring semaphore */
		int i = 0, j = 0;
		int length = 0;
		float value = 0;
		float value1 = 0;
		float value2 = 0;
		
		for (i = 0; i < noOfChannels; i++)
		{
			length = valueArray[i][1];
			printf("CHANNEL %d\n", i);
			if (valueArray[i][j] == 1)
			{
				value = averageFilter(i); /* function call to average filtering */
				printf("Average filter\n");
				printf("Output: %f\n", value); 
			}
			else if (valueArray[i][j] == 2)
			{
				printf("first order filter\n");
				value1 = firstOrder(i, constants[i][0], constants[i][1],
						constants[i][2], constants[i][3]); /* function call to first order filtering */
				printf("Output: %f\n", value1);
			}
			else if (valueArray[i][j] == 3)
			{
				printf("Second order filter\n");
				/* obtaining the output of second order filter */
				value2 = secondOrder(i, constants[i][0], constants[i][1],
						constants[i][2], constants[i][3], constants[i][4],
						constants[i][5]);
				printf("Output: %f\n", value2);
			}
			else
			{
				printf("No filter\n");
			}
			printf("\n");

		}
		
	}
}

