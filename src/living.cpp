#include "Living.hpp"
#include "ProjectHandler.hpp"
#include "Engine.hpp"

#include <iostream>
#include <string>
#include <map>
#include <iterator>

Engine eng;

//Getters from the config file
int Grass::getMaxLevel() const {return ph.params["maxLevelGrass"];}

int Rabbit::getMaxAge() const {return ph.params["maxAgeRabbit"];}
int Rabbit::getMaxHunger() const {return ph.params["maxHungerRabbit"];}


int Fox::getMaxAge() const {return ph.params["maxAgeFox"];}
int Fox::getMaxHunger() const {return ph.params["maxHungerFox"];}

int Living::getMaxAmountRabbits() const {return ph.params["maxAmountRabbits"];}
int Living::getMaxAmountFoxes() const {return ph.params["maxAmountFoxes"];}

int Rabbit::getMinAgeMateRabbit() const {return ph.params["minAgeMateRabbit"];}
int Fox::getminAgeMateFox() const {return ph.params["minAgeMateFox"];}

/*
*   Constructor for a Grass object
*/
Grass::Grass() {
    setLevel(1);
}

/*
*   Cosntructor for a Rabbit object
*/
Rabbit::Rabbit(bool initialGender) {
    setAge(0);
    setTookTurn(true);
    setHorny(false);
    setHunger(0);
    setGender(initialGender);    
}

/*
*   Constructor for a Fox object
*/
Fox::Fox(bool initialGender) {
    setAge(0);
    setTookTurn(true);
    setHorny(false);
    setHunger(0);
    setGender(initialGender);
}

/*
*   Deletes the object that has been killed
*/
void Living::die(int i, int j, bool isEnding) {
    if(ph.objectsMapGrass[{i,j}] != 0 && isEnding) {        
        delete this;
        ph.objectsMapGrass[{i,j}] = 0;              
    }
    else if(ph.objectsMapRabbit[{i,j}] != 0) {
        if(ph.objectsMapGrass[{i,j}] != 0) {
            delete this;
            ph.objectsMapRabbit[{i,j}] = 0;
            ph.playground[i][j] = ProjectHandler::GRASS;
        }
        else {
            delete this;
            ph.objectsMapRabbit[{i,j}] = 0;
            ph.playground[i][j] = ProjectHandler::EMPTY;
        }       
    }
    else if(ph.objectsMapFox[{i,j}] != 0) {
        if(ph.objectsMapGrass[{i,j}] != 0) {
            delete this;
            ph.objectsMapFox[{i,j}] = 0;
            ph.playground[i][j] = ProjectHandler::GRASS;
        }
        else {
            delete this;
            ph.objectsMapFox[{i,j}] = 0;
            ph.playground[i][j] = ProjectHandler::EMPTY;
        }       
    }
}

/*
*   This function updates each Rabbit, based in the input it gets form checks()
*   Rabbit mates, Rabbit moves, updates hunger and age
*/
void Rabbit::updateCreature(int i, int j) {

    if(this->getAge() > this->getMaxAge()) {this->die(i,j,false); return;}
    if(this->getHunger() > this->getMaxHunger()) {this->die(i,j,false); return;}

    if(!sim.possibleMoves.empty()) {
        //moves the Rabbit to random spot in 'sim.possibleMoves'       
        auto move = sim.possibleMoves.begin();
        std::advance(move, eng.getRandInt(0, static_cast<int>(sim.possibleMoves.size())-1));
        std::pair<int, int> NewSpot = move->first;
        if(ph.playground[NewSpot.first][NewSpot.second] == ProjectHandler::GRASS) ph.objectsMapGrass[NewSpot]->setLevel(-2);
        ph.objectsMapRabbit[{NewSpot}] = ph.objectsMapRabbit[{i,j}];
        ph.objectsMapRabbit[{i,j}] = 0;
        if(ph.objectsMapGrass[{i,j}] != 0) {
            ph.playground[i][j] = ProjectHandler::GRASS;
            ph.objectsMapGrass[{i,j}]->setLevel(-2);
        }
        else ph.playground[i][j] = ProjectHandler::EMPTY;
        ph.playground[NewSpot.first][NewSpot.second] = ProjectHandler::RABBIT;
    }
    if(!sim.possibleMates.empty()) { //creates a new rabbit on an empty spot around the mating fox
        int end; 
        if(sim.possibleMates.size() > 1) end = eng.getRandInt(1,2);
        else end = 1;
        for(int x = 1; x <= end; x++) {    
            auto pair = sim.possibleMates.begin();
            std::advance(pair, eng.getRandInt(0, static_cast<int>(sim.possibleMates.size())-1));
            std::pair<int, int> NewBorn = pair->first;
            Rabbit* creature = new Rabbit(static_cast<bool>(eng.getRandInt(0,1)));
            ph.objectsMapRabbit[{NewBorn}] = creature;
            ph.playground[NewBorn.first][NewBorn.second] = ProjectHandler::RABBIT;
            sim.possibleMates.erase(NewBorn);
        }         
    }
    this->setHunger(this->getHunger()+1);
    this->setAge(this->getAge()+1);
    this->setTookTurn(true);
    return;
}

/*
*   This function updates each Fox, based in the input it gets form checks()
*   Fox eats, Fox moves, Fox mates, updates hunger and age
*   Note: After eating a Rabbit, the Fox moves to the spot, where it ate the Rabbit
*/
void Fox::updateCreature(int i, int j) {   
    if(this->getAge() > this->getMaxAge()) {this->die(i,j,false); return;}
    if(this->getHunger() > this->getMaxHunger()) {this->die(i,j,false); return;}

    if(!sim.possibleFood.empty()) {  //Fox eats a random rabbit in range
        auto food = sim.possibleFood.begin();
        std::advance(food, eng.getRandInt(0, static_cast<int>(sim.possibleFood.size())-1));
        std::pair<int, int> eaten = food->first;
        ph.objectsMapRabbit[{eaten}]->die(eaten.first,eaten.second,false);     
        ph.objectsMapFox[{eaten}] = ph.objectsMapFox[{i,j}];
        ph.objectsMapFox[{i,j}] = 0;
        ph.objectsMapFox[{eaten}]->setHunger(0);
        if(ph.objectsMapGrass[{i,j}] != 0) {
            ph.playground[i][j] = ProjectHandler::GRASS;
            ph.objectsMapGrass[{i,j}]->setLevel(-2);
        }
        else ph.playground[i][j] = ProjectHandler::EMPTY;
        ph.playground[eaten.first][eaten.second] = ProjectHandler::FOX;
    }
    else {
        if(!sim.possibleMoves.empty()) { //moves the Fox to random spot in 'sim.possibleMoves' 
            auto move = sim.possibleMoves.begin();
            std::advance(move, eng.getRandInt(0, static_cast<int>(sim.possibleMoves.size())-1));
            std::pair<int, int> NewSpot = move->first;
            ph.objectsMapFox[{NewSpot}] = ph.objectsMapFox[{i,j}];
            ph.objectsMapFox[{i,j}] = 0;
            if(ph.objectsMapGrass[{i,j}] != 0) {
                ph.playground[i][j] = ProjectHandler::GRASS;
                ph.objectsMapGrass[{i,j}]->setLevel(-2);
            }
            else ph.playground[i][j] = ProjectHandler::EMPTY;
            ph.playground[NewSpot.first][NewSpot.second] = ProjectHandler::FOX;
    }    

    if(!sim.possibleMates.empty()) { //creates a new fox on an empty spot around the mating fox
        int end; 
        if(sim.possibleMates.size() > 1) end = eng.getRandInt(1,2);
        else end = 1;
        for(int x = 1; x <= end; x++) {     
            auto pair = sim.possibleMates.begin();
            std::advance(pair, eng.getRandInt(0, static_cast<int>(sim.possibleMates.size())-1));
            std::pair<int, int> NewBorn = pair->first;
            Fox* creature = new Fox(static_cast<bool>(eng.getRandInt(0,1)));
            ph.objectsMapFox[{NewBorn}] = creature;
            ph.playground[NewBorn.first][NewBorn.second] = ProjectHandler::FOX;
            sim.possibleMates.erase(NewBorn);
        }
    }
    this->setHunger(this->getHunger()+1);
    this->setAge(this->getAge()+1);
    this->setTookTurn(true);    
    return;
    }
}