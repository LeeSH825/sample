#include <iostream>
#include <string>
#include <filesystem>
#include "../includes/rapidjson/document.h"
#include "../includes/rapidjson/istreamwrapper.h"
#include <fstream>
#include <sstream>
#include <vector>

#include "../includes/controller.h"
#include "../includes/neuron.h"

namespace fs = std::filesystem;

int main()
{
	std::cout << "MARVELS: SNN Simulator" << std::endl;
	
	std::string directory;
	std::cout << "Enter the file directory: ";
	// std::getline(std::cin, directory);
	
	// DBG
	directory = "../data";

	fs::path filePath(directory);

	controller _controller;

	for (const auto& entry : fs::directory_iterator(filePath))
	{
		if (entry.is_regular_file())
		{
			std::string filename = entry.path().filename().string();
			std::string prefix = "message";
			std::string type = "init"/* TODO: Extract the type from the filename */;
			// std::string number = "0"/* TODO: Extract the number from the filename */;
			
			if (filename.find(prefix) == 0 && filename.find(type) != std::string::npos != std::string::npos && filename.find(".json") != std::string::npos)
			{
				// Process the file
				std::cout << std::endl << "Found file: " << filename << std::endl;

				// Read the JSON file
				std::ifstream file(entry.path());
				if (file.is_open())
				{
					std::stringstream buffer;
					buffer << file.rdbuf();
					std::string jsonStr = buffer.str();

					// Parse the JSON string
					rapidjson::Document document;
					document.Parse(jsonStr.c_str());

					// Check if parsing was successful
					if (!document.HasParseError())
					{
						// TODO: Process the JSON data
						// Example: Accessing a value from the JSON document
						if (document.HasMember("type"))
						{
							// Target Column
							const rapidjson::Value& column = document["target_column"];
							int columnValue;
							if (column.IsInt()) {
								columnValue = column.GetInt();
							} else {
								std::cout << "Invalid value for target_column" << std::endl;
								columnValue = 0;
							}

							// Target Neuron
							const rapidjson::Value& neuron = document["target_neuron"];
							int neuronValue;
							if (neuron.IsInt()) {
								neuronValue = neuron.GetInt();
							} else {
								std::cout << "Invalid value for target_neuron" << std::endl;
								neuronValue = 0;
							}

							// Data
							const rapidjson::Value& data = document["data"];
							double weightValue;
							int spike_time;
							if (data.IsDouble()) {
								weightValue = data.GetDouble();
							}
							else if (data.IsInt()) {
								spike_time = data.GetInt();
							}
							else {
								std::cout << "Invalid value for data" << std::endl;
								weightValue = 0;
								spike_time = 0;
							}

							// Data Block
							const rapidjson::Value& dataBlock = document["data_block"];
							int detailValue;
							if (dataBlock.IsObject()) {
								const rapidjson::Value& detail = dataBlock["detail"];
								if (detail.IsInt()) {
									detailValue = detail.GetInt();
								} else {
									std::cout << "Invalid value for detail" << std::endl;
									detailValue = 0;
								}
							} else {
								std::cout << "Invalid value for data_block" << std::endl;
								detailValue = 0;
							}

							// Type
							const rapidjson::Value& type = document["type"];
							if (type.IsString()) {
								std::string typeStr = type.GetString();
								std::cout << "type: " << typeStr << std::endl;
								if (typeStr == "weight") {
									std::cout << "target_column: " << columnValue << " target_neuron: " << neuronValue << " detail: " << detailValue << " weight: " << weightValue << std::endl;
									_controller.setWeight(columnValue, neuronValue, detailValue, weightValue);
								}
								else if (typeStr == "block") {
									// Forward
									const rapidjson::Value& forward = dataBlock["forward"];
									if (forward.IsObject()) {
										for (int i = 0; i <= NUM_MAX_NEURON; i++) {
											std::string keyName = std::to_string(i);
											if (forward.HasMember(keyName.c_str())) {
												const rapidjson::Value& value = forward[keyName.c_str()];
												// Process the array of integer values
												if (value.IsArray()) {
													std::vector<int> block;
													for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
														if (value[i].IsInt()) {
															block.push_back(value[i].GetInt());
															// TODO: Process the integer value
															// std::cout << "Integer value: " << intValue << std::endl;
														}
													}
													_controller.setForwardTableRow(columnValue, i, block);
													std::vector<int>().swap(block);
												} else {
													std::cout << "Invalid value for forward name" << std::endl;
												}
											}
										}
									}
									else
									{
										std::cout << "Invalid value for forward" << std::endl;
									}

									// Backward
									const rapidjson::Value& backward = dataBlock["backward"];
									if (backward.IsObject()) {
										for (int i = 0; i <= NUM_MAX_NEURON; i++) {
											std::string keyName = std::to_string(i);
											if (backward.HasMember(keyName.c_str())) {
												const rapidjson::Value& value_back = backward[keyName.c_str()];
												// Process the array of integer values
												if (value_back.IsArray()) {
													std::vector<int> block_back;
													for (rapidjson::SizeType i = 0; i < value_back.Size(); i++) {
														if (value_back[i].IsInt()) {
															block_back.push_back(value_back[i].GetInt());
															// TODO: Process the integer value
															// std::cout << "Integer value: " << intValue << std::endl;
														}
													}
													_controller.setBackwardTableRow(columnValue, i, block_back);
													std::vector<int>().swap(block_back);
												} else {
													std::cout << "Invalid value for forward name" << std::endl;
												}
											}
										}
									}
									else
									{
										std::cout << "Invalid value for forward" << std::endl;
									}

									// md_block
									const rapidjson::Value& mdBlock = dataBlock["md_block"];
									if (mdBlock.IsArray()) {
										std::vector<int> block_md;
										for (rapidjson::SizeType i = 0; i < mdBlock.Size(); i++) {
											const rapidjson::Value& value = mdBlock[i];
											// Process the array of integer values
											if (value.IsInt()) {
												block_md.push_back(value.GetInt());
											}
										}
										_controller.setMDBlock(columnValue, block_md);
									} else {
										std::cout << "Invalid value for md_block" << std::endl;
									}
									// DBG
									std::cout << "ForwardTable:" << std::endl;
									_controller.checkForwardTable(0);
									std::cout << "BackwardTable:" << std::endl;
									_controller.checkBackwardTable(0);
									std::cout << "MDTable:" << std::endl;
									_controller.checkMDTable(0);

								}
								else if (typeStr == "param"){
									std::cout << "target_column: " << columnValue << " target_neuron: " << neuronValue << " detail: " << detailValue << " param_value: " << weightValue << std::endl;
									_controller.setParam(columnValue, neuronValue, detailValue, weightValue);
								}
								else if (typeStr == "spike") {		// spike
									// Code for other string case
									_controller.sendSpike(columnValue, neuronValue, spike_time);
								}
								else {
									std::cout << "Wrong Type";
								}
							}
						}
						else { std::cout << "no weight"; }
					}
					else
					{
						std::cout << "Failed to parse JSON file: " << entry.path() << std::endl;
					}
				}
				else
				{
					std::cout << "Failed to open JSON file: " << entry.path() << std::endl;
				}
			}
		}
	}
	
	return 0;
}
