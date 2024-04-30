#ifndef LEARNING_MODULE_H
#define LEARNING_MODULE_H

#include <cmath>

// Your code goes here
#define MAX_SAVE_TIME 3



// file
class learning_module
{
private:
	/* data */
public:
	learning_module(/* args */);
	~learning_module();
	float updateWeight(int spike_time_1[MAX_SAVE_TIME], int spike_time_2[MAX_SAVE_TIME]);
};




#endif // LEARNING_MODULE_H