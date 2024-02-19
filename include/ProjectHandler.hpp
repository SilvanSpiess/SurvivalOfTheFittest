#ifndef PROJECTHANDLER_H
#define PROJECTHANDLER_H

#include "Engine.hpp"
#include "FileHandler.hpp"
#include "Living.hpp"

#include <map>
#include <vector>
#include <string>
#include <sstream>

class ProjectHandler {
    
public:
    //The Roles creatures can take
    enum Role {EMPTY, GRASS, RABBIT, FOX};

    #ifdef _WIN32
    // Console colors for Windows 32bit/64bit
    const std::string colorAqua = "\033[1;36m";
    const std::string colorYellow = "\033[38;2;248;219;57m";
    const std::string colorRed = "\033[1;31m";
    const std::string colorMagenta = "\033[38;2;255;0;255m";
    const std::string colorPurple = "\033[38;2;90;91;159m";
    const std::string colorGreen = "\033[38;2;134;174;75m";
    const std::string colorWhite = "\033[0m";
    const std::string colorBrown = "\033[38;2;139;69;19m";
    #elif defined __unix__
    // Console colors for Unix
    const std::string colorAqua = "\033[1;36m";
    const std::string colorYellow = "\033[38;2;248;219;57m";
    const std::string colorRed = "\033[1;31m";
    const std::string colorMagenta = "\033[38;2;255;0;255m";
    const std::string colorPurple = "\033[38;2;90;91;159m";
    const std::string colorGreen = "\033[38;2;134;174;75m";
    const std::string colorWhite = "\033[0m";
    const std::string colorBrown = "\033[38;2;139;69;19m";
    #elif defined __APPLE__
    // Console colors mac   
    const std::string colorAqua =  "\x1b[96m";
    const std::string colorYellow =  "\x1b[33m";
    const std::string colorRed =  "\x1b[91m";
    const std::string colorMagenta =  "\x1b[35m";
    const std::string colorPurple =  "\x1b[34m";
    const std::string colorGreen =  "\x1b[32m";
    const std::string colorWhite =  "\x1b[37m";
    const std::string colorBrown =  "\x1b[97m";
    #endif

    //Getter for playgroundSize (from the config.yml)
    int getPlaygroundSize() {
        playgroundSize = params["playgroundSize"];
        return playgroundSize;
    }
    
    int launcher();
    void printBegin();
    std::vector<std::vector<Role>> playground;

    //Strings used in FileHandler
    std::string getDirectoryName() const {return directoryName;}
    std::string getConfigFileName() const {return configFileName;}
    std::string getReportFileNameStart() const {return reportFileNameStart;}
    std::string getReportFileName() const {return reportFileName;}
    std::string getDelimiter() const {return delimiter;}

    std::stringstream currentTimeDateStream;
    std::stringstream summaryStream;
    //The indices (data) collected in the report file
    const std::string reportIndices[16] = {"Day","nrEmpty","nrGrass","nrRabbits","nrFemaleRabbits","nrMaleRabbits",
                                            "nrFoxes","nrFemaleFoxes","nrMaleFoxes",
                                            "av.LevelGRass","av.AgeRabbit","av.AgeFox",
                                            "changeOfEmpty","changeOfGrass","changeOfRabbit","changeOfFox"};
    //The 4 creature maps
    std::map<std::pair<int, int>, Empty*> objectsMapEmpty;
    std::map<std::pair<int, int>, Grass*> objectsMapGrass;
    std::map<std::pair<int, int>, Rabbit*> objectsMapRabbit;
    std::map<std::pair<int, int>, Fox*> objectsMapFox;
    std::map<std::pair<int, int>, std::pair<Role, int>> tempMap;

    //The Default values map for the config.yml
    const std::map<std::string, int> defaults = {{"playgroundSize", 20},{"simCycles", 50},{"simDelay", 300},{"maxLevelGrass", 5},
                                                    {"maxAgeRabbit", 7},{"maxHungerRabbit", 2},{"maxAmountRabbits", 7},{"minAgeMateRabbit", 2},
                                                    {"maxAgeFox", 9},{"maxHungerFox", 5},{"maxAmountFoxes", 5},{"minAgeMateFox", 3}};
    //Custom config values get loaded into this map
    std::map<std::string, int> params;
    int getSimCycles() const;
    int getSimDelay() const;
    int nrEmpty, nrGrass, nrRabbits, nrFoxes{0};

private:
    const std::string directoryName = "target";
    const std::string configFileName = "target/config.yml";
    const std::string reportFileNameStart = "target/report_";
    const std::string delimiter = ": ";
    std::string reportFileName;
    int playgroundSize;    
};
extern ProjectHandler ph;
#endif