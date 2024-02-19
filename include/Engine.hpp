#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <iostream>
#include <random>
#include <map>

class Engine {    
    public:
        int getRandInt(int x, int y);
        int getIndex(int a, int b);

};

class Simulator : public Engine {
        public:
            void eden();
            void next();
            void clear();
            void printPlayground();
            void checks(int i, int j);
            void overPop();
            void resurrection();
            
            //Maps used to determine each creature's behaviour per cycle
            std::map<std::pair<int, int>, bool> possibleResurr;
            std::map<std::pair<int, int>, bool> possibleMoves;
            std::map<std::pair<int, int>, bool> possibleMates;
            std::map<std::pair<int, int>, bool> possibleFood;
            std::map<std::pair<int, int>, bool> overPopRabbitsDeaths;
            std::map<std::pair<int, int>, bool> overPopFoxesDeaths;

        private:            
    };

    class Evaluator : public Engine {
        public:
            void getData();
            void writeReportFile(std::string date);
            void clearData();

            double averageLevelGrass;
            double averageAgeRabbit;
            double averageAgeFox;
            int changeOfEmpty;
            int changeOfGrass;
            int changePopRabbit;
            int changePopFox;
            int oldNrEmpty;
            int oldNrGrass;
            int oldNrRabbits;
            int oldNrFoxes;
            int nrFemaleRabbits;
            int nrMaleRabbits;
            int nrFemaleFoxes;
            int nrMaleFoxes;
        private:
                       
    };

    class Visualiser : public Engine {
        public:
            void showData(int day);
        private:
    };

    extern Engine eng;
    extern Simulator sim;
    extern Evaluator eva;
    extern Visualiser vis;

#endif