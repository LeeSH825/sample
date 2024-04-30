#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <iostream>

// #define NUM_MAX_NEURON 10000
#define NUM_MAX_NEURON 33
#define NUM_MAX_COLUMN 1

#define THRESHOLD 0
#define AXIONAL_DELAY 1
#define REFRACTORY_TIME 2

// Your code goes here
#include "../includes/neuron.h"

// file

typedef struct t_forward_table {
	bool neuron[NUM_MAX_NEURON][NUM_MAX_NEURON];	// src, dst
} s_forward_table;

typedef struct t_backward_table {
	bool neuron[NUM_MAX_NEURON][NUM_MAX_NEURON];	// src, dst
} s_backward_table;

typedef struct t_md_block {
	bool neuron[NUM_MAX_NEURON];
} s_md_block;

class controller {
private:
	neuron neurons[NUM_MAX_COLUMN][NUM_MAX_NEURON];
	s_forward_table _forward_table[NUM_MAX_COLUMN];
	s_backward_table _backward_table[NUM_MAX_COLUMN];
	s_md_block _md_block[NUM_MAX_COLUMN];
	bool spike_indicator[NUM_MAX_NEURON];
public:
	controller(/* args */);
	~controller();
	int setWeight(int target_column, int target_neuron, int post_neuron, float weight);
	int setParam(int target_column, int target_neuron, int type, float value);
	int setForwardTableRow(int target_column, int src, std::vector<int> v);
	int setBackwardTableRow(int target_column, int src, std::vector<int> v);
	int setMDBlock(int target_column, std::vector<int> v);

	int sendSpike(int target_column, int target_neuron, int spike_time);

	//DBG
	void checkForwardTable(int target_column);
	void checkBackwardTable(int target_column);
	void checkMDTable(int target_column);
};

#endif // CONTROLLER_H