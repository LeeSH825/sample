#ifndef NEURON_H
#define NEURON_H

#include <iostream>

#include "../includes/learning_module.h"

// Your code goes here
#define NUM_POST_NEURON 33
#define NUM_NEURON_CONNECTION 33
#define MAX_SAVE_TIME 3

#define FORWARD 0
#define BACKWARD 1

// file
class neuron
{
private:
	learning_module exp_STDP_learning_module;

	// Parameter
	float threshold;
	float axon_delay;
	float ref_time;

	//internal variable - synapse
	float weight[NUM_POST_NEURON];

	// internal variable - spike
	int spike_time[NUM_NEURON_CONNECTION][MAX_SAVE_TIME];
	int my_spike_time[MAX_SAVE_TIME];
	char spike_idx[NUM_NEURON_CONNECTION];
	char my_spike_idx;
	int increaseSpikeIdx(int idx);

	// internal variable - membrane
	float membrane_potential;
	int isSpike(int target_neuron);
	
	
public:
	neuron(/* args */);
	~neuron();
	int setWeight(int post_neuron, float weight){ this->weight[post_neuron] = weight; return 1; };
	int setThreshold(float value) { this->threshold = value; return 1; };
	int setAxonDelay(float value) { this->axon_delay = value; return 1; };
	int setRefTime(float value){ this->ref_time = value; return 1; };

	int getSpike(int target_neuron, int spike_time, int type);
	int spike(int spike_time);
};

#endif // NEURON_H