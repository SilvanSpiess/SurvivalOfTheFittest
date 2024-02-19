#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <time.h>
#include <algorithm>
//#include <string>
class FileHandler {    
    public:
        void init();
        void readFromFile();
        int checkValues();
        void createReport();
        std::string consoleOutput{""};
    private:
};

#endif