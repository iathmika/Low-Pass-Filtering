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
#include <filterIncludes.h>
#include <filterGlobals.h>
#include <filterExterns.h>

/* #defines */
#define MAX_FIRSTORDER 25;

/* global variables */
int valueArray[MAX_FILTER_CH][MAX_AVERAGE_LENGTH + 2];
int noOfChannels;
float constants[MAX_FILTER_CH][6];

/* Function declarations */
float getRawData(void);

/* config function for taking inputs, choosing filter and getting output data */
/* Description: This function opens the text file where all the inputs are stored, reads the data of the text file and accordingly makes choices on 
 * the type of filtering and displays the output for each channel */

void configg(void)
{
#if 1
	/* variable declarations */
	int index = 0; /* index for iterating through for loop */
	noOfChannels = 0; /* variable for storing number of channels use meaningful name of variable */
	int chNo = 0; /* variable for storing channel number */
	
	char buf[BUFFER_MAX] = { 0 };
	
	/* creating file pointer and opening AIconfig text file to read the input*/
	FILE* fp = fopen("readAIconfig.txt", "r");

	/* if function pointer points to NULL value */
	if (fp == NULL)
	{
		printf("No such file exists\n");
	}
	else
	{
		/* reading AIconfig file for getting input number of channels */

		if (fgets(buf, BUFFER_MAX, fp) != NULL)/* getting the input no. of channels as string */
		{
			sscanf(buf, "%d", &noOfChannels); /* converting string to integer */
			printf("%s \n", buf);
		}

		if (noOfChannels > CHANNEL_LIMIT) /* the max number of channels is limited to 50 */
		{
			printf("Error. Invalid number of channels. Number of channels has to be between 1 and 50 \n");
		}
		else
		{
			printf("The number of channels is %d\n", noOfChannels);
			/* for loop for each channel */
			for (index = 1; index <= noOfChannels; index++)
			{
				/* reading channel number */
				fscanf(fp, "%s", buf);
				/* convertng the string to integer using sscanf */
				sscanf(buf, "%d", &chNo);
				printf("Channel %d\n", chNo);
				fscanf(fp, "%[^\n]", buf); /* string till the end of line */
				printf("Filter chosen and inputs are %s\n", buf);
				int length = 0;
				/* average filter */
				if (((buf[1] == 'a')|| (buf[1] == 'A')) && ((buf[2] == 'v') || (buf[2] == 'V'))
						&& ((buf[3] == 'g') || (buf[3] == 'G')) && buf[4]
						== ' ')																		/*Capital or small letters*/
				{
					
					printf("Average filter chosen\n");
						char s[CHANNEL_LIMIT] = { 0 };
						if(buf[5]!=" ") {
						strcat(s,&buf[5]); }
						
						printf("%s",s);
						if(buf[6]!=" ") {
						strcat(s,&buf[6]); }
						printf("%s",s);
						
						if(buf[7]!=" ") {
						strcat(s,&buf[7]); }
						printf("%s",s);
						sscanf(s,"%d",&length);
						printf("Queue length is %d\n", length);
						valueArray[chNo][0] = AVERAGE_FILTER;
						valueArray[chNo][1] = length;
						}
					
				/* first order Low Pass Filter */
				else if (buf[1] == 'F' && buf[2] == 's' && buf[3] == 't' && buf[4] == ' ')
				{
					length = 2;
					if(strlen(buf)> 25)
					{
						printf("Error. There can only be four inputs\n");
					}
					else
					{
						float a0, a1, b0, b1;
						int inc = 5;
						valueArray[chNo][0]=FIRST_ORDER_FILTER;
						valueArray[chNo][1]=length;
						printf("First order filtering\n");
						printf("Enter the value of constants a0,a1,b0,b1:\n");
						printf("a0:  ");
						a0 = buf[inc] - '0' + 0.1 * (buf[inc + 2] - '0') + 0.01
								* (buf[inc + 3] - '0');
						/* buf[inc]-'0' is done to get the integer value by subtrracting the ascii value of 0 from the ascii value of character */
						printf("%f\n", a0);

						inc += 5; /* inc+5 is done to move on to the next constant */
						printf("a1:  ");
						a1 = buf[inc] - '0' + 0.1 * (buf[inc + 2] - '0') + 0.01
								* (buf[inc + 3] - '0');
						printf("%f\n", a1);

						inc += 5;
						printf("b0:  ");
						b0 = buf[inc] - '0' + 0.1 * (buf[inc + 2] - '0') + 0.01
								* (buf[inc + 3] - '0');
						printf("%f\n", b0);

						inc += 5;
						printf("b1:  ");
						b1 = buf[inc] - '0' + 0.1 * (buf[inc + 2] - '0') + 0.01
								* (buf[inc + 3] - '0');
						printf("%f\n", b1);
						
						/* storing the constants in a 2-D array for each channel */
						constants[chNo][0]=a0;
						constants[chNo][1]=a1;
						constants[chNo][2]=b0;
						constants[chNo][3]=b1;
						
						/* firstOrder(a0, a1, b0, b1); */
						strcpy(buf, ""); /* re initialising the string */
					}
				}
				/* Second order LPF */
				else if (buf[1] == 'S' && buf[2] == 'n' && buf[3] == 'd'
						&& buf[4] == ' ')
				{
					if (strlen(buf) > 35)
						printf("Error. There can only be 6 inputs.\n");
					else
					{
						float a0, a1, a2, b0, b1, b2;
						valueArray[chNo][0]= SECOND_ORDER_FILTER;
						valueArray[chNo][1]= 3 ;
						printf("Second order filtering\n");
						printf("Enter the value of constants a0,a1,a2,b0,b1,b2:\n");
						int cnt = 5;
						printf("a0:  ");
						a0 = buf[cnt] - '0' + 0.1 * (buf[cnt + 2] - '0') + 0.01
								* (buf[cnt + 3] - '0');
						/* buf[inc]-'0' is done to get the integer value by subtrracting the ascii value of 0 from the ascii value of character */
						printf("%f\n", a0);

						cnt += 5;
						printf("a1:  ");
						a1 = buf[cnt] - '0' + 0.1 * (buf[cnt + 2] - '0') + 0.01
								* (buf[cnt + 3] - '0');
						printf("%f\n", a1);

						cnt += 5;
						printf("a2: ");
						a2 = buf[cnt] - '0' + 0.1 * (buf[cnt + 2] - '0') + 0.01
								* (buf[cnt + 3] - '0');
						printf("%f\n", a2);

						cnt += 5; /* incrementing cnt by 5 to move on to the next constant */
						printf("b0:  ");
						b0 = buf[cnt] - '0' + 0.1 * (buf[cnt + 2] - '0') + 0.01
								* (buf[cnt + 3] - '0');
						printf("%f\n", b0);

						cnt += 5;
						printf("b1:  ");
						b1 = buf[cnt] - '0' + 0.1 * (buf[cnt + 2] - '0') + 0.01
								* (buf[cnt + 3] - '0');
						printf("%f\n", b1);

						cnt += 5;
						printf("b2: ");
						b2 = buf[cnt] - '0' + 0.1 * (buf[cnt + 2] - '0') + 0.01
								* (buf[cnt + 3] - '0');
						printf("%f\n", b2);
						constants[chNo][0] = a0;
						constants[chNo][1] = a1;
						constants[chNo][2] = a2;
						constants[chNo][3] = b0;
						constants[chNo][4] = b1;
						constants[chNo][5] = b2;
						/* secondOrder(a0, a1, a2, b0, b1, b2);  function call with 6 parameteres */

						/* reinitializing the string */
						strcpy(buf, "");
					}
				}

				else if (buf[1] == 'N' && buf[2] == 'o') /* in case of no filtering */
				{
					valueArray[chNo][0]=NO_FILTER;
					valueArray[chNo][1]=0;
					
					printf("No filtering\n");
					
					int countint = 0;
					printf("Raw data: \n");
					/* in no filtering */
					/* simply get the raw data and the same will be the output */
					while (countint != 10)
					{
						printf("%f\t", getRawData());
						countint++;
					}
					printf("\n");

					/* re initialising the buffer */
					strcpy(buf, "");
				}
				else
					printf("Option invalid\n");
			}
		}
		fclose(fp); /* closing the file */
	}
#endif
}

/* function to get random data for the filter channels */
float getRawData(void)
{
	int x =((float) (rand() % 80) + 1.0); /* generating random number between 0 to 80 */
	return x;
}


