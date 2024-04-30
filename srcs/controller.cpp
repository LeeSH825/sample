#include "../includes/controller.h"

controller::controller(/* args */) {
	for (int col_idx = 0; col_idx < NUM_MAX_COLUMN; col_idx++) {
		for (int i = 0; i < NUM_MAX_NEURON; i++) {
			for (int j = 0; j < NUM_MAX_NEURON; j++) {
				this->_forward_table[col_idx].neuron[i][j] = 0;
			}
		}
	}
	for (int col_idx = 0; col_idx < NUM_MAX_COLUMN; col_idx++) {
		for (int i = 0; i < NUM_MAX_NEURON; i++) {
			for (int j = 0; j < NUM_MAX_NEURON; j++) {
				this->_backward_table[col_idx].neuron[i][j] = 0;
			}
		}
	}
	for (int col_idx = 0; col_idx < NUM_MAX_COLUMN; col_idx++) {
		for (int i = 0; i < NUM_MAX_NEURON; i++) {
			this->_md_block[col_idx].neuron[i] = 0;
		}
	}

	for (int i=0; i < NUM_MAX_NEURON; i++) {
		this->spike_indicator[i] = 0;
	}
}

controller::~controller() {
}

int controller::setWeight(int target_column, int target_neuron, int post_neuron, float weight) {
	neurons[target_column][target_neuron].setWeight(post_neuron, weight);
	return 1;
}

int controller::setParam(int target_column, int target_neuron, int type, float value) {
	if (type == THRESHOLD) {
		neurons[target_column][target_neuron].setThreshold(value);
		return 1;
	}
	else if (type == AXIONAL_DELAY) {
		neurons[target_column][target_neuron].setAxonDelay(value);
		return 1;
	}
	else if (type == REFRACTORY_TIME) {
		neurons[target_column][target_neuron].setRefTime(value);
		return 1;
	}
	return 0;
}

int controller::setForwardTableRow(int target_column, int src, std::vector<int> v) {
	for (int idx = 0; idx < v.size(); idx++) {
		this->_forward_table[target_column].neuron[src][v[idx]] = 1;
	}
	return 1;
}

int controller::setBackwardTableRow(int target_column, int src, std::vector<int> v) {
	for (int idx = 0; idx < v.size(); idx++) {
		this->_backward_table[target_column].neuron[src][v[idx]] = 1;
	}
	return 1;
}

int controller::setMDBlock(int target_column, std::vector<int> v) {
	for (int idx = 0; idx < v.size(); idx++) {
		this->_md_block[target_column].neuron[v[idx]] = 1;
	}
	return 1;
}


int controller::sendSpike(int target_column, int target_neuron, int spike_time) {
	
	for (int post_neuron = 0; post_neuron < NUM_MAX_NEURON; post_neuron++) {			// Forward Propagation
		if (this->_forward_table[target_column].neuron[target_neuron][post_neuron] == 1) {
			std::cout << "Forward Spike to " << post_neuron << std::endl;
			spike_indicator[target_neuron] = neurons[target_column][post_neuron].getSpike(target_neuron, spike_time, FORWARD);
		}
	}
	for (int pre_neuron = 0; pre_neuron < NUM_MAX_NEURON; pre_neuron++) {				// Backward Propagation
		if (this->_backward_table[target_column].neuron[target_neuron][pre_neuron] == 1) {
			std::cout << "Backward Spike to " << pre_neuron << std::endl;
			neurons[target_column][pre_neuron].getSpike(target_neuron, spike_time, BACKWARD);
		}
	}

	for (int idx = 0; idx < NUM_MAX_NEURON; idx++) {
		if (spike_indicator[idx] != 0) {
			int spike_time = spike_indicator[idx];
			spike_indicator[idx] = 0;
			sendSpike(target_column, idx, spike_time);
			
		}
	}

	return 1;
}


// DBG
void controller::checkForwardTable(int target_column) {
	for (int i = 0; i < NUM_MAX_NEURON; i++) {
		for (int j = 0; j < NUM_MAX_NEURON; j++) {
			std::cout << static_cast<int>(this->_forward_table[target_column].neuron[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return ;
}

void controller::checkBackwardTable(int target_column) {
	for (int i = 0; i < NUM_MAX_NEURON; i++) {
		for (int j = 0; j < NUM_MAX_NEURON; j++) {
			std::cout << static_cast<int>(this->_backward_table[target_column].neuron[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return ;
}

void controller::checkMDTable(int target_column) {
	for (int i = 0; i < NUM_MAX_NEURON; i++) {
		std::cout << this->_md_block[target_column].neuron[i];
		std::cout << static_cast<int>(this->_md_block[target_column].neuron[i]);
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return ;
}