#ifndef CONTROLLER_CPP
# define CONTROLLER_CPP
#include <iostream>
#include <string>
#include "./neuron.cpp"

#define MAX_NUM_OF_NEURON 100

#define SPIKE 0
#define PARAM 1

#define SOMA 0
#define SYNAPSE 1
#define LEARNING_MODULE 2

#define WEIGHT 0
#define PARAM 1
#define BLOCK 2
#define SPIKE 3

#endif
#include <random>

typedef struct t_connection_table {
	int control_bit[MAX_NUM_OF_NEURON];
	int src[MAX_NUM_OF_NEURON];
	int dst[MAX_NUM_OF_NEURON];
} s_connection_table;

typedef struct t_MD_block {
	int is_MD[MAX_NUM_OF_NEURON];
} s_MD_block;

typedef struct t_BLOCK {
	s_connection_table forward;
	s_connection_table backward;
	s_MD_block md_block;
} s_BLOCK;

typedef struct t_column_internal_protocol {
	int spike_or_param;
	int MD_or_ordinary;
	int param_destination;
	int addr;
	int data;
} s_column_internal_protocol;

typedef struct t_initialization_protocol {
	int type;	// Weight, or param or Block or spike
	int target_column;
	int target_neuron;
	int data;
	s_BLOCK data_block;
} s_initialization_protocol;

class Initializaition_Decoder_Inside_Column {
	private:
		s_initialization_protocol initializaition_data;
		s_BLOCK reference_table;
		int if_MD(char num_of_neuron);
	public:
		s_column_internal_protocol inputDataFromRAM(s_initialization_protocol data){ this->initializaition_data = data; 
		std::cout << "type: " << initializaition_data.type << "MD node: " << initializaition_data.data_block.md_block.is_MD[1] << std::endl; 
		this->outputDataFromRAM(); };
		s_column_internal_protocol outputDataFromRAM();

};

int Initializaition_Decoder_Inside_Column::if_MD(char num_of_neuron){		// MD 뉴런인지 찾기
	for(int i=0; i<MAX_NUM_OF_NEURON; i++){
		if (this->reference_table.md_block.is_MD[i] == num_of_neuron){
			return 1;
		}
	}
	return 0;
}

s_column_internal_protocol Initializaition_Decoder_Inside_Column::outputDataFromRAM() {
		if (this->initializaition_data.type == BLOCK){	// Table 초기화
			this->reference_table = this->initializaition_data.data_block;
			std::cout << "block:" << reference_table.md_block.is_MD[1] << std::endl;
			s_column_internal_protocol ret;
			return ret; 	// return null (단순 초기화이기 때문에 전달할 필요 없음)
		}
		else if (this->initializaition_data.type == WEIGHT){	// Weight 초기화
			s_column_internal_protocol ret;
			// parma이라고 알려줌
			ret.spike_or_param = PARAM;
			// Destination도 Synapse 쪽이라고 알려줘야??
			ret.param_destination = SYNAPSE;
			// 전달해야 하는 뉴런 주소 설정
			ret.addr = this->initializaition_data.target_neuron;

			// MD면 그대로, Ordinary면 LSB만 랜덤하게
			if (this->if_MD(this->initializaition_data.target_neuron)) {
					// MD면 그대로
				ret.data = this->initializaition_data.data;
				std::cout << "weight: " << ret.data << std::endl;
			}
			else {
					// Ordinary면 랜덤하게
				std::random_device rd;
				std::mt19937 mt(rd());
				std::uniform_int_distribution<int> dist(0,99);
				ret.data = dist(mt);
				std::cout << "weight: " << ret.data << std::endl;
			}
			return ret;
		}
		else if (this->initializaition_data.type == PARAM) {
			s_column_internal_protocol ret;
			ret.spike_or_param = PARAM;
			ret.param_destination = SOMA;	// or learning module?
			ret.addr = this->initializaition_data.target_neuron;
			ret.data = this->initializaition_data.data;
			return ret;
		}
		else if (this->initializaition_data.type == SPIKE) {
			s_column_internal_protocol ret;
			ret.spike_or_param = SPIKE;
			ret.param_destination = SOMA;
			ret.addr = this->initializaition_data.target_neuron;
			ret.data = this->initializaition_data.data;	// 여기선 Spike time data
			return ret;
		}
}

typedef struct t_array_block {
	int data[100];
} s_array_block;

class Spike_Decoder_Inside_Column {
	private:
		int reference_table[100];
	public:
		s_array_block checkForward(int num_of_neuron);
		s_array_block checkBackward(int num_of_neuron);
};

s_array_block Spike_Decoder_Inside_Column::checkForward(int num_of_neuron) {
	s_array_block propagation_table;
	for (int i=0; i < MAX_NEURON; i++) {
		if (reference_table[i] == 1) {
			propagation_table.data[i] = 1;
		}
	}
	return propagation_table;
}

s_array_block Spike_Decoder_Inside_Column::checkBackward(int num_of_neuron) {
	s_array_block propagation_table;
	for (int i=0; i < MAX_NEURON; i++) {
		if (reference_table[i] == 1) {
			propagation_table.data[i] = 1;
		}
	}
	return propagation_table;
}


class Controller {
	private:
		char spike_indicator[MAX_NUM_OF_NEURON];
		s_initialization_protocol initialization_data;
		Initializaition_Decoder_Inside_Column init_decoder;
		Neuron neuron[100];
		Spike_Decoder_Inside_Column Spike_Decoder;
		int SpikeIndicator_idx;
		int ForwardPropagationReg[100];
		int BackwardPropagationReg[100];
	public:
		void inputSpikeOndicator(int num_of_neuron){ this->spike_indicator[num_of_neuron] = 1; };

		void inputDataFromRAM(s_initialization_protocol data){ this->initialization_data = data; outputDataFromRAM(); };
		void outputDataFromRAM();
		void checkSpikeofNeuron();

};

void Controller::outputDataFromRAM() {	
	s_column_internal_protocol internal_message;
	internal_message = init_decoder.inputDataFromRAM(this->initialization_data);
	if (internal_message.spike_or_param == SPIKE) {
		std::strcpy(ForwardPropagationReg, Spike_Decoder.checkForward(internal_message.addr).data);	//internal message에 있는 neuron의 주소를 보고 forward propagation register 업데이느
	}
}

void Controller::checkSpikeofNeuron() {
	while (1){
		if (neuron[1].checkSpikeIndicator()) {	// SPike 했다면
			ForwardPropagationReg = *Spike_Decoder.checkForward(neuron[1].checkSpikeIndicator());	// Forward Reg 설정
			BackwardPropagationReg = *Spike_Decoder.checkForward(neuron[1].checkSpikeIndicator());	// Backward Reg 설정
			// 한 클럭 기다리고,
		}
		increaseIDX(SpikeIndicator_idx);
	}
}


