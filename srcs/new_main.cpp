#include <iostream>
#include <fstream>
#include <string>
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidjson/prettywriter.h"

#define MAX_FILE_NUM 1

// class JsonParser {
//     public:
//         JsonParser(std::string path);
//     pruvate:
//         rapidjson::Document document_;
// };

int main() {
    std::string init_dir = "./test-files/";
    std::string init_MsgBase = "init_message_";
	std::string init_MsgExt = ".txt";
    for(int i=0; i < MAX_FILE_NUM; i++) {
        std::string filename = init_dir + init_MsgBase + std::to_string(i) + init_MsgExt;
        std::ifstream file(filename);
        if (!file.is_open()) {   // file open check
            throw std::runtime_error("failed to open the file" + filename);
        }
        // Read file data
        std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        //Parse JSON
        rapidjson::Document doc;
        rapidjson:: ParseResult parse_result;
        parse_result = doc.Parse(json.c_str());
        
    }
}