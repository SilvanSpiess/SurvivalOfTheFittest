#include "ProjectHandler.hpp"
#include "FileHandler.hpp"

#include <thread>
#include <chrono>

namespace fs = std::filesystem;

/*
*   Initialises the files (config.yml and report.csv). If conifg.yml empty or not available: fills new config.yml with default parameters
*/
void FileHandler::init() {
    // Check if directory exists, create it if it doesn't
    if (!fs::exists(ph.getDirectoryName())) {
        fs::create_directory(ph.getDirectoryName());
    }

    //Check if configfile exists in directory, create it, if non existing
    if (!fs::exists(ph.getConfigFileName())) {
        std::ofstream newfile(ph.getConfigFileName());
        newfile.close();
    }

    createReport();

    //check if file is empty
    if(fs::is_empty(ph.getConfigFileName())) {
        //load defaults into file        
        std::ofstream file(ph.getConfigFileName());
        // Check if file was opened successfully
        if (!file.is_open()) {
            FileHandler::consoleOutput.append(ph.colorAqua + "[FILEHANDLER] " + ph.colorRed + "Error opening file \n");
            return;
        }
        FileHandler::consoleOutput.append(ph.colorAqua + "[FILEHANDLER] " + ph.colorYellow + "Empty file detected, writing config with defaults...\n");
        for(auto x: ph.defaults) {
            std::string writeLine = x.first + ": " + std::to_string(x.second);
            file << writeLine << std::endl; 
        }
        file.close();
        FileHandler::consoleOutput.append(ph.colorAqua + "[FILEHANDLER] " + ph.colorGreen + "Written to config file successfully! \n"); 
    }

    // Open the file for reading and writing
    std::fstream file(ph.getConfigFileName(), std::ios::in | std::ios::out);

    // Check if file was opened successfully
    if (!file.is_open()) {
        FileHandler::consoleOutput.append(ph.colorAqua + "[FILEHANDLER] " + ph.colorRed + "Error opening file \n");
    }
    else {
        FileHandler::consoleOutput.append(ph.colorAqua + "[FILEHANDLER] " + ph.colorGreen + "Directory initialised successfully! \n");
    }
    file.close();
}

/*
*   Reads and sets the simulation paramters from config.yml for later use
*/
void FileHandler::readFromFile() {
    try {
        // Open the file for reading and writing
        std::ifstream file(ph.getConfigFileName());
        // Check if file was opened successfully
        if (!file.is_open()) {
            FileHandler::consoleOutput.append(ph.colorAqua + "[FILEHANDLER] " + ph.colorRed + "Error opening file \n");
            return;
        }
        std::setprecision(1);
        // Read from the file 
        FileHandler::consoleOutput.append(ph.colorAqua + "[FILEHANDLER] " + ph.colorWhite + "starts reading file... \n");
        FileHandler::consoleOutput.append(ph.colorAqua + "[FILEHANDLER] " + ph.colorWhite + "Loading parameters... \n");
        std::cout << FileHandler::consoleOutput;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::string lineRead;

        std::string loadbar{"loading  |"};
        std::string endBar{"________________________________________________|"};      
        while(std::getline(file, lineRead)){        
            std::string key = lineRead.substr(0, lineRead.find(ph.getDelimiter()));
            std::string value = lineRead.substr(lineRead.find(ph.getDelimiter())+1, lineRead.length());
            ph.params.insert(std::pair<std::string, int>(key, stoi(value)));
            //Printing params
            loadbar.append("****");
            endBar.erase(0,4);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::system("clear");
            std::cout << FileHandler::consoleOutput;
            std::cout << ph.colorWhite << loadbar << endBar << std::endl;
            for (const std::pair<std::string, int> p : ph.params) {
                std::cout << "          " << ph.colorMagenta << p.first << " = " << p.second << std::endl;
            }           
        } 
        std::cout << ph.colorAqua << "[FILEHANDLER] " << ph.colorGreen << "Data initialised successfully!" << std::endl;
    }
    catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }        
}

/*
*   Creates the report.csv file. Filename includes the current time for individual reports per simulation run
*/
void FileHandler::createReport() {
    try {
        //gets current time
        time_t now = time(0);
        std::string dt = ctime(&now);
        //replaces " " and ":" with "_"
        std::replace_if(dt.begin(), dt.end(), [](char c) {
            return std::isspace(c) || c == ':';
        }, '_');
        //std::cout << "time: " << dt << std::endl;
        ph.currentTimeDateStream << ph.getReportFileNameStart() << dt.substr(0, dt.length() - 1) << ".csv";
        //creates the new csv file
        std::ofstream newfile(ph.currentTimeDateStream.str());
        newfile.close();
        //write first line
        std::ofstream reportFile; reportFile.open(ph.currentTimeDateStream.str(), std::ios::in | std::ios::out);
        for (std::string indice : ph.reportIndices) reportFile << indice << ";"; 
        reportFile << std::endl;
        reportFile.close();
        FileHandler::consoleOutput.append(ph.colorAqua +  "[FILEHANDLER] " + ph.colorGreen + "Report file created successfully! \n");
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
