#ifndef MAIN_CPP
# define MAIN_CPP
#include <iostream>
#include <fstream>
#include <string>

#include "./controller.cpp"
#include "./neuron.cpp"

#endif

using namespace std;

int main() {
	Controller MC_sample_controller;

	string init_MsgBase = "init_message_";
	string init_MsgExt = ".txt";
	int init_Msg_start = 0;
	int init_Msg_end = 1;

	// 파일 파싱
	for(int i = init_Msg_start; i < init_Msg_end; i++) {
		string filename = init_MsgBase + std::to_string(i) + init_MsgExt;
		ifstream file(filename);
		if (!file.is_open()) {
			cout << filename << "파일 열기 실패";
			continue;
		}
		else {
			cout << filename << "파일 열기 성공";
			s_initialization_protocol message;
			string single_line;

			// 데이터 받기
			getline(file, single_line);
			message.type = std::stoi(single_line);
			getline(file, single_line);
			message.target_column = std::stoi(single_line);
			getline(file, single_line);
			message.target_neuron = std::stoi(single_line);
			getline(file, single_line);
			message.data = std::stoi(single_line);
			
			std::cout << std::endl << message.type << "|" << message.target_column << "|" << message.target_neuron << "|" << message.data << std::endl;
			std::cout << "MD Block:" << std::endl;

			// MD Block 채워넣기
			for (int j=0; j < MAX_NUM_OF_NEURON; j++) {
				if (getline(file, single_line)) {	// 있으면
					message.data_block.md_block.is_MD[j] = stoi(single_line);
					std::cout << message.data_block.md_block.is_MD[j] << std::endl;
				}
				else {
					break;
				}
			}
			// Controller로 전달
			MC_sample_controller.inputDataFromRAM(message);
		}
	}
	// 모듈 초기화 끝
	///////////////////

	// 첫 Spike
	// spike message => 
	// MC_sample_controller.inputDataFromRAM(spike_message);



}