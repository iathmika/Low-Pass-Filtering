/* #includes */
#include <filterIncludes.h>
#include <filterExterns.h>
#include <filterGlobals.h>

/* global variables */
int prevOutput[MAX_FILTER_CH][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
/* declaring a gloabal array and inititalising all elements of the array to 2 to store position 
 * where value is next to be inserted in the queue */
int position[MAX_FILTER_CH] =
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
				2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
				2, 2, 2, 2, 2, 2 };

/* function prototypes */
float averageFilter(int chNo);
float firstOrder(int chNo, float a0,float a1,float b0,float b1);
float secondOrder(int chNo,float a0,float a1,float a2,float b0, float b1,float b2);
void pushData(int chNo, int inputValue);

/* function body of average filter
 * description: This function take the channel number as the input, maintains a queue and 
 * calculates the average if the queue is full, else it returns the latest instantaneous
 *  value in the queue */
float averageFilter(int chNo)
{
	int Qlength = 0;
	int it;
	float sum = 0.0;
	float average = 0.0;
	float OutputValue;
	Qlength = valueArray[chNo][1];
	printf("Queue length :%d\n",Qlength);
	
	/* if Queue full then calculate average */
	if(Qlength+1 ==  position[chNo]-1)
	{
		/* for loop for calculating the sum */
		for(it=2 ; it<Qlength+2 ; it++)
		{
			sum=sum+(float)valueArray[chNo][it];
		}
		average = sum/Qlength;
		return average;
	}
	else /* return latest instantaneous value in the Queue as output */
	{
		OutputValue = valueArray[chNo][position[chNo]-1];
		return OutputValue;
	}
}

/* function body of first order filtering
 * description:  This function 4 constants and channel no. as parameters and generates the
 * output by using an array that stores the previous output t*/
float firstOrder(int chNo, float a0,float a1,float b0,float b1)
{
	/* declaration and initialisation of variable for storing output data */
	float outputData;
	outputData = (float)(a0 * valueArray[chNo][3] + a1 * valueArray[chNo][2] + b1 * prevOutput[chNo][PREV_INDEX]) / b0;
	prevOutput[chNo][1] = outputData;
	return outputData;
}

/* function body for second order filtering 
 * description: This function 6 constants and channel no. as parameters and generates the
 * output by using an array that stores the previous output and previous to previous output */
float secondOrder(int chNo,float a0,float a1,float a2,float b0,float b1,float b2)
{
	/* declaration and initialisation of variable for storing output data */
	float outputData = 0.0;
	/* calculating the output using the six constants */
	outputData = (a0 * valueArray[chNo][4] + a1 * valueArray[chNo][3] +
			a2 * valueArray[chNo][2] + b1*prevOutput[chNo][PREVtoPREV_INDEX]) + b2 * prevOutput[chNo][PREV_INDEX];
	prevOutput[chNo][1] = outputData;
	return outputData;
}

/* Function : pushData
 * Description: This function takes 2 parameters - the channel number, the input value
 * and stores the value in the value array in the respective position depending on channel no.
 * and queue length */
void pushData(int chNo, int inputValue)
{
	int iter = 0;
	int length = valueArray[chNo][1];
	
	/* if queue is full*/
	if (position[chNo] - 2 == length)
	{
		for (iter = 2; iter < (length + 2); iter++)
		{
			valueArray[chNo][iter] = valueArray[chNo][iter + 1];
		}
		valueArray[chNo][length + 1] = inputValue;
	}
	/* if queue is not full, push data directly to the latest empty position */
	else
	{
		valueArray[chNo][position[chNo]] = inputValue;
		position[chNo]++;
	}

#if FILTER_DEBUG
	printf("Data pushed successfully: %d\n", inputValue);
	printf("Value Array: \n");
	printf("type\tLength\n");

	for (iter1 = 0; iter1 < noOfChannels; iter1++)
	{
		length = valueArray[iter1][1];
		for (iter2 = 0; iter2 < length + 2; iter2++)
		{
			printf("%d\t", valueArray[iter1][iter2]);
		}
		printf("\n");

	}
#endif
}
