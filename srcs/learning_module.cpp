#include "../includes/learning_module.h"

learning_module::learning_module(/* args */)
{
}

learning_module::~learning_module()
{
}

float learning_module::updateWeight(int spike_time_1[MAX_SAVE_TIME], int spike_time_2[MAX_SAVE_TIME]) {
	float A_PRE = 1.0;
	float A_POST = 1.0;
	float T_PRE = 10.0;
	float T_POST = 10.0;
	float delta_weight = 0;
	for (int i=0; i < MAX_SAVE_TIME; i++) {
		for (int j=0; j < MAX_SAVE_TIME; j++) {
			float delta = spike_time_2[j] - spike_time_1[i];
			delta_weight += A_PRE * std::exp(delta/T_PRE) - A_POST * std::exp(-delta/T_POST);
		}
	}
	return delta_weight;
}