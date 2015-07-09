//
//  main.cpp
//  APM_reader
//
//  Created by Louis Faury on 02/07/2015.
//  Copyright (c) 2015 Louis Faury. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Serial.h"
#include <string>

const std::string initial_path_to_file = "/home/louis/Documents/C++/APM_LOG/";
const char* APM_port_name = "/dev/tty.ACM0";
char buffer[128];

int main(int argc, const char * argv[]) {
    
    // User interaction to create file
    std::string path_ending, log_ending;
    
    // Main reading file path
    std::cout << "Enter path final extension" << std::endl;
    std::cin >> path_ending;
    std::string path_to_file = initial_path_to_file + path_ending;
    
    // LOG reading file path
    std::cout << "Enter log final extension" << std::endl;
    std::cin >> log_ending;
    std::string path_to_log = initial_path_to_file + log_ending;

    
    
    // Opening files
    std::ofstream file(path_to_file.c_str());
    std::ofstream log(path_to_log.c_str());
    
    // Reading datas from APM
    if (file && log){
        try {
            Serial APM(APM_port_name,115200);
            for (int i=0; i<2000 ; i++){
                APM.readLine(buffer);
                
                // If starts with $ stored in main file
                if (buffer[0]=='$'){
                    file << buffer;
                }
                //else stored in logger
                else log << buffer <<std::endl;
                std::cout << buffer;
            }
            APM.Close();
        } catch(std::exception const& e){
            std::cerr << "ERR : "<< APM_port_name << " : " << e.what() << " ! " << std::endl;
        }
    }
    
    else std::cout << "Error while opening file" << std::endl;

}
