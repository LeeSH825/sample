#ifndef NEURON_CPP
# define NEURON_CPP
#include "./learning_module.cpp"

#define FORWARD 0
#define BACKWARD 1

#define MAX_NEURON 100
#define MAX_SAVE 3

#define THRESHOLD 100
#endif

typedef struct t_neural_protocol {
	int spike_time;
	int spike_neuron;
	int type;		// Forward, Backward
} s_neural_protocol;

class Neuron {
	private:
		s_neural_protocol spike_data;
		Learning_Module STDP_Learning_Module;
		int received_spike_time;

		int last_spiked_time;

		int my_spike_time[MAX_SAVE];
		int my_spike_time_idx;
		int other_spike_time[MAX_NEURON][MAX_SAVE];			
		int other_spike_time_idx[MAX_NEURON];
		int weight;
		void inc_spike_idx(int idx) { if (idx == MAX_SAVE) {idx == 0;} else { idx = idx+1; } }

		int membranePotential;
		int calcMembranePotential();
		int neuronModel_calc(int time);
		void recordSpikeTime();

		void setSpikeIndicator();
		int SpikeIndicator;
	public:
		void input_Spike_time(s_neural_protocol data) { this->spike_data = data; this-> received_spike_time = data.spike_time; this->action_neuron();};
		void action_neuron();
		int calcMembranePotential();
		int checkSpikeIndicator();
};

void Neuron::action_neuron() {
	// Spike 시간 기록
	other_spike_time[this->spike_data.spike_neuron][other_spike_time_idx[this->spike_data.spike_neuron]];	
	inc_spike_idx(other_spike_time_idx[spike_data.spike_neuron]);
	int new_weight = STDP_Learning_Module.calcWeight(this->my_spike_time, this->other_spike_time[this->spike_data.spike_neuron]);
	this->weight = new_weight;		// weight 갱신
	int is_spike = calcMembranePotential();
	if (this->spike_data.type == FORWARD) {
		
	}
}

int Neuron::calcMembranePotential() {
	this->membranePotential += this->neuronModel_calc(this->spike_data.spike_time);
	if (this->membranePotential >= THRESHOLD) {		// Threshold를 넘기면
		recordSpikeTime();
		setSpikeIndicator();
	}
}

int Neuron::neuronModel_calc(int time) {
	return (this->last_spiked_time - time);
}

void Neuron::recordSpikeTime() {
	this->my_spike_time[this->my_spike_time_idx] = this->spike_data.spike_time;
	inc_spike_idx(my_spike_time_idx);
}

void Neuron::setSpikeIndicator() {
	this->SpikeIndicator = 1;
}

int Neuron::checkSpikeIndicator() {
	if (this->SpikeIndicator == 1) {
		this->SpikeIndicator = 0;
		return 1;
	}
	else {
		return 0;
	}
}
