#include "../includes/neuron.h"

neuron::neuron(/* args */) {
	this->membrane_potential = 0.0;
	this->threshold = 9.02;
	this->axon_delay = 1.0;
	this->ref_time = 1.0;

	for (int i = 0; i < NUM_POST_NEURON; i++) {
		this->weight[i] = 0.0;
	}
	for (int i = 0; i < NUM_NEURON_CONNECTION; i++) {
		for (int j = 0; j < MAX_SAVE_TIME; j++) {
			this->spike_time[i][j] = 0;
		}
		this->spike_idx[i] = 0;
	}
	for (int i = 0; i < MAX_SAVE_TIME; i++) {
		my_spike_time[i] = 0;
	}
}

neuron::~neuron() {
}

int neuron::increaseSpikeIdx(int idx) {
	std::cout << "DBG: spike_idx: " << idx << std::endl;
	if (idx == MAX_SAVE_TIME - 1) {
		return 0;
	}
	else {
		return idx + 1;
	}
}

int neuron::getSpike(int target_neuron, int spike_time, int type) {
	std::cout << " spike_time: " << spike_time << std::endl;
	this->spike_time[target_neuron][spike_idx[target_neuron]] = spike_time;	// record spike time 
	this->spike_idx[target_neuron] = this->increaseSpikeIdx(this->spike_idx[target_neuron]);
	this->weight[target_neuron] = exp_STDP_learning_module.updateWeight(my_spike_time, this->spike_time[target_neuron]);
	std::cout << "neuron: " << target_neuron << "weight: " << this->weight[target_neuron] << std::endl;

	if (type == FORWARD) {
		if (this->isSpike(target_neuron)) {
			this->membrane_potential = 0;
			return this->spike(spike_time);
		}
		else {
			this->membrane_potential = this->membrane_potential + weight[target_neuron];
		}
	}
	return 0;
}

int neuron::spike(int spike_time) {
	this->my_spike_time[my_spike_idx] = spike_time + this->axon_delay;
	this->my_spike_idx = this->increaseSpikeIdx(this->my_spike_idx);
	return spike_time + this->axon_delay;
}

int neuron::isSpike(int target_neuron) {
	float next_mem_potential = this->membrane_potential + weight[target_neuron];
	if (next_mem_potential > this->threshold) {
		std::cout << "!!!!Spiked: " << target_neuron << std::endl << std::endl;
		return 1;
	}
	else {
		return 0;
	}
}