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

const std::string initial_path_to_file = "/Users/louisfaury/Documents/C++/APM_LOG/";
const char* APM_port_name = "/dev/tty.usbmodem1421";
char buffer[128];


int main(int argc, const char * argv[]) {
    
// User interaction to create file
    
    
    
    // Main reading file path
    std::string path_ending;
    std::cout << "Enter path final extension" << std::endl;
    std::cin >> path_ending;
    std::string path_to_file = initial_path_to_file + path_ending; // Be sure to check your file is created already
    
    // Declaring text files names
    std::string acc_file_name = path_to_file + "/acc.txt";
    std::string gyro_file_name = path_to_file + "/gyro.txt";
    std::string gps_file_name = path_to_file + "/gps.txt";
    std::string mag_file_name = path_to_file + "/mag.txt";
    std::string log_file_name = path_to_file + "/log.txt";
    
    
    // Declaring text files
    std::ofstream acc_file(acc_file_name.c_str());
    std::ofstream gyro_file(gyro_file_name.c_str());
    std::ofstream gps_file(gps_file_name.c_str());
    std::ofstream mag_file(mag_file_name.c_str());
    std::ofstream log_file(log_file_name.c_str());
    
    
    // Reading datas from APM
    if (acc_file && gyro_file && gps_file && mag_file && log_file){
        try {
            Serial APM(APM_port_name,115200);
            for (int i=0; i<10000 ; i++){
                APM.readLine(buffer);
                
                // If starts with $ : stored in main files
                if (buffer[0]=='$'){
                    switch (buffer[1]){
                        case 'A' :
                            acc_file << buffer;
                            acc_file.flush();
                            break;
                        case 'G' :
                            if (buffer[2] == 'P') {
                                gps_file << buffer;
                                gps_file.flush();
                            }
                            else {
                                gyro_file << buffer;
                                gyro_file.flush();
                            }
                            break;
                        case 'M' :
                            mag_file << buffer;
                            mag_file.flush();
                            break;
                        default:
                            std::cout << "Couldn't store : " << buffer << std::endl;
                            break;
                    }
                }
               
                //else stored in logger
                else log_file << buffer <<std::endl;
                std::cout << buffer;
            }
            APM.Close();
        } catch(std::exception const& e){
            std::cerr << "ERR : "<< APM_port_name << " : " << e.what() << " ! " << std::endl;
        }
    }
    
    else std::cout << "Error while opening file" << std::endl;

}
