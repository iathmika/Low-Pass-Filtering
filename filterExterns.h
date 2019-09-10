#include "filterIncludes.h"
#include "filterGlobals.h"

extern void filterImptask(void);
extern void pushData(int chNo, int inputValue);
extern float averageFilter(int chNo);
extern float firstOrder(int chNo, float a0,float a1,float b0,float b1);
extern float secondOrder(int chNo,float a0,float a1,float a2,float b0, float b1,float b2);
extern void pushData(int chNo, int inputValue);

extern SEM_ID semfilterImp;

extern int valueArray[MAX_FILTER_CH][MAX_AVERAGE_LENGTH+2];
extern int position[MAX_FILTER_CH];
extern int noOfChannels;
extern int prevOutput[MAX_FILTER_CH][2];
extern int noOfChannels;;
extern float constants[MAX_FILTER_CH][6];
