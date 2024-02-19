#include "ProjectHandler.hpp"
#include "Engine.hpp"

ProjectHandler ph;
Visualiser vis;
Simulator sim;
Evaluator eva;
Living living;

/*
*   Creates a new evenly distributed playground. Then runs the first day cycle
*   Foxes are more rare for balancing matter
*/
void Simulator::eden() {
    ph.playground.resize(ph.getPlaygroundSize());

    for (int i = 0; i < ph.getPlaygroundSize(); ++i) {
        ph.playground[i].resize(ph.getPlaygroundSize());
    }
    //initialises playingfield with random spawn seed
    for (int i = 0; i < ph.getPlaygroundSize(); i++) {
        for (int j = 0; j < ph.getPlaygroundSize(); j++) {
            ProjectHandler::Role input = static_cast<ProjectHandler::Role>(eng.getRandInt(1, 4));
            switch (input) {
                case ProjectHandler::EMPTY: {                                     
                    ph.playground[i][j] = input; 
                    ph.objectsMapEmpty[{i,j}] = 0;
                    ph.objectsMapGrass[{i,j}] = 0;
                    ph.objectsMapRabbit[{i,j}] = 0;                    
                    ph.objectsMapFox[{i,j}] = 0;                   
                    break;
                }
                 case ProjectHandler::GRASS: {
                    Grass* creature = new Grass();
                    ph.playground[i][j] = input; 
                    ph.objectsMapEmpty[{i,j}] = 0;
                    ph.objectsMapGrass[{i,j}] = creature;
                    ph.objectsMapRabbit[{i,j}] = 0;
                    ph.objectsMapFox[{i,j}] = 0;
                    break;
                 }
                 case ProjectHandler::RABBIT: {
                    Rabbit* creature = new Rabbit(static_cast<bool>(getRandInt(0,1)));
                    ph.playground[i][j] = input;
                    ph.objectsMapEmpty[{i,j}] = 0;
                    ph.objectsMapGrass[{i,j}] = 0;
                    ph.objectsMapRabbit[{i,j}] = creature;
                    ph.objectsMapFox[{i,j}] = 0;
                    break;
                 }
                 case ProjectHandler::FOX: {
                    if(j%3 == 0) {
                        Fox* creature = new Fox(static_cast<bool>(getRandInt(0,1)));
                        ph.playground[i][j] = input;
                        ph.objectsMapEmpty[{i,j}] = 0;
                        ph.objectsMapGrass[{i,j}] = 0;
                        ph.objectsMapRabbit[{i,j}] = 0;
                        ph.objectsMapFox[{i,j}] = creature;                        
                    }
                    else {
                        Rabbit* creature = new Rabbit(static_cast<bool>(getRandInt(0,1)));
                        ph.playground[i][j] = ProjectHandler::RABBIT;
                        ph.objectsMapEmpty[{i,j}] = 0;
                        ph.objectsMapGrass[{i,j}] = 0;
                        ph.objectsMapRabbit[{i,j}] = creature;
                        ph.objectsMapFox[{i,j}] = 0;
                    }                    
                    break;
                }
                default:
                    break;
            }            
        }
    }    
    return;
}

/*
*   Simulates the next cycle (day) by first resetting the creatures turn-specific stats, then runs checks() und updateCreature() for each creature
*   Note that Grass is handled as a special type of creature (has checks(), but no updateCreature())
*/
void Simulator::next() {
    for (int i = 0; i < ph.getPlaygroundSize(); i++) {
        for (int j = 0; j < ph.getPlaygroundSize(); j++) { 
            if(ph.playground[i][j] == ProjectHandler::FOX) {
                if (ph.objectsMapFox[{i,j}] != nullptr) {
                    ph.objectsMapFox[{i,j}]->setTookTurn(false);
                    ph.objectsMapFox[{i,j}]->setHorny(true);
                }
                else std::cout << ph.colorRed << "nullptr case reset FOX at: " << i << j << std::endl;                
            }
            else if(ph.playground[i][j] == ProjectHandler::RABBIT) {
                if (ph.objectsMapRabbit[{i,j}] != nullptr) {
                    ph.objectsMapRabbit[{i,j}]->setTookTurn(false);
                    ph.objectsMapRabbit[{i,j}]->setHorny(true);
                }
                else std::cout << ph.colorRed << "nullptr case reset RABBIT at: " << i << j << std::endl;
            }
        }
    }

    for (int i = 0; i < ph.getPlaygroundSize(); i++) {
        for (int j = 0; j < ph.getPlaygroundSize(); j++) { 
            if(ph.playground[i][j] == ProjectHandler::RABBIT) {
                if(ph.objectsMapRabbit[{i,j}] != 0) {
                    if(!ph.objectsMapRabbit[{i,j}]->getTookTurn()) {
                        checks(i,j);
                        ph.objectsMapRabbit[{i,j}]->updateCreature(i,j);
                    }
                }
                else std::cout << ph.colorRed << "nullptr case RABBIT at: " << i << j << std::endl;               
            }            
        }
    }

    for (int i = 0; i < ph.getPlaygroundSize(); i++) {
        for (int j = 0; j < ph.getPlaygroundSize(); j++) { 
            if(ph.playground[i][j] == ProjectHandler::FOX) {
                if(ph.objectsMapFox[{i,j}] != 0) {
                    if (!ph.objectsMapFox[{i,j}]->getTookTurn()) {
                        checks(i,j);
                        ph.objectsMapFox[{i,j}]->updateCreature(i,j);
                    }
                }
                else std::cout << ph.colorRed << "nullptr case FOX at: " << i << j << std::endl;                                
            }            
        }
    }
   
    for (int i = 0; i < ph.getPlaygroundSize(); i++) {
        for (int j = 0; j < ph.getPlaygroundSize(); j++) { 
            if(ph.playground[i][j] == ProjectHandler::GRASS) {
                if(ph.objectsMapGrass[{i,j}] != 0) checks(i,j);
                else std::cout << ph.colorRed << "nullptr  case GRASS at: " << i << j << std::endl;
            }
        }
    } 
}

/*
*   Checks for each creature what is around (in a 1-block radius) and updates creaturespecific Maps, which are processed in updateCreature()
*   Grass gets updated in checks(), for simplicity
*/
void Simulator::checks(int i, int j) {
    switch (ph.playground[i][j]) {
        case ProjectHandler::EMPTY:
            //empty space, nothing to check
            break;
        /*
        *   Checks what is around Grass
        */  
        case ProjectHandler::GRASS:
            for (int a = (i-1); a <= (i+1); a++) {
                for(int b = (j-1); b <= (j+1); b++) {
                    if(a < 0 || b < 0 || a >= ph.getPlaygroundSize() || b >= ph.getPlaygroundSize()) continue; //Border

                    else if (ph.objectsMapRabbit[{a,b}] != 0 || ph.objectsMapFox[{a,b}] != 0) continue; //Fox or Rabbit around

                    else if(a == i && b == j) {   //itself                      
                        if(ph.objectsMapGrass[{a,b}]->getLevel() == ph.objectsMapGrass[{a,b}]->getMaxLevel()-1 || ph.objectsMapGrass[{a,b}]->getLevel() <= 0) ph.objectsMapGrass[{a,b}]->setLevel(ph.objectsMapGrass[{a,b}]->getLevel()+1);
                        else if(ph.objectsMapGrass[{a,b}]->getLevel() == ph.objectsMapGrass[{a,b}]->getMaxLevel()) continue;
                        else ph.objectsMapGrass[{a,b}]->setLevel(ph.objectsMapGrass[{a,b}]->getLevel()+2);                    
                    }
                    else if(ph.playground[a][b] == ProjectHandler::EMPTY) {
                        Grass* creature = new Grass();
                        ph.objectsMapGrass[{a,b}] = creature;
                        ph.playground[a][b] = ProjectHandler::GRASS;                        
                    }
                    else if(ph.playground[a][b] == ProjectHandler::GRASS) {
                        if(ph.objectsMapGrass[{a,b}]->getLevel() < ph.objectsMapGrass[{a,b}]->getMaxLevel() && ((a==i-1 && b==j) || (a==i && b!=j) || (a==i+1 && b==j)) && ph.objectsMapGrass[{a,b}]->getLevel() > 0) 
                            ph.objectsMapGrass[{a,b}]->setLevel(ph.objectsMapGrass[{a,b}]->getLevel()+1);
                    }
                    else if(ph.playground[a][b] == ProjectHandler::RABBIT) {continue;}
                    else if(ph.playground[a][b] == ProjectHandler::FOX) {continue;}
                }
            }
            break;
        /*
        *   Checks what is around a Rabbit
        */
        case ProjectHandler::RABBIT:
            sim.possibleMoves.clear();
            sim.possibleMates.clear();
            for (int a = (i-1); a <= (i+1); a++) {
                for(int b = (j-1); b <= (j+1); b++) {
                    if(a < 0 || b < 0 || a >= ph.getPlaygroundSize() || b >= ph.getPlaygroundSize()) continue; //Border

                    else if(a == i && b == j) continue; //itself

                    else if(ph.playground[a][b] == ProjectHandler::EMPTY) sim.possibleMoves[{a,b}] = true;

                    else if(ph.playground[a][b] == ProjectHandler::GRASS) {
                        if(ph.objectsMapGrass[{a,b}]->getLevel() <= 2 && ph.objectsMapRabbit[{a,b}] == 0 && ph.objectsMapFox[{a,b}] == 0) sim.possibleMoves[{a,b}] = true;
                        if(ph.objectsMapGrass[{a,b}]->getLevel() > 1 && ph.objectsMapRabbit[{a,b}] == 0 && ph.objectsMapFox[{a,b}] == 0) {
                            ph.objectsMapGrass[{a,b}]->setLevel(ph.objectsMapGrass[{a,b}]->getLevel()-1);
                            ph.objectsMapRabbit[{i,j}]->setHunger(-1);
                        }
                        else if (ph.objectsMapGrass[{a,b}]->getLevel() == 1 && ph.objectsMapRabbit[{a,b}] == 0 && ph.objectsMapFox[{a,b}] == 0) {
                            ph.objectsMapGrass[{a,b}]->setLevel(-2);
                            ph.objectsMapRabbit[{i,j}]->setHunger(-1);
                        }
                    }
                    else if(ph.playground[a][b] == ProjectHandler::RABBIT) {
                        if(ph.objectsMapRabbit[{a,b}]->getGender() != ph.objectsMapRabbit[{i,j}]->getGender() && 
                            ph.objectsMapRabbit[{i,j}]->getAge() >= ph.objectsMapRabbit[{i,j}]->getMinAgeMateRabbit() && ph.objectsMapRabbit[{a,b}]->getAge() >= ph.objectsMapRabbit[{a,b}]->getMinAgeMateRabbit() &&
                            ph.objectsMapRabbit[{a,b}]->getHorny() && ph.objectsMapRabbit[{i,j}]->getHorny()) {
                            for (int x = (i-1); x <= (i+1); x++) {
                                for(int y = (j-1); y <= (j+1); y++) {                                    
                                    if(x >= 0 && y >= 0 && x < ph.getPlaygroundSize() && y < ph.getPlaygroundSize() && (ph.playground[x][y] == ProjectHandler::EMPTY || (ph.playground[x][y] == ProjectHandler::GRASS && ph.objectsMapGrass[{x,y}]->getLevel() <= 5))) {
                                        sim.possibleMates[{x,y}] = true;
                                        ph.objectsMapRabbit[{i,j}]->setHorny(false);
                                        //ph.objectsMapRabbit[{a,b}]->setHorny(false);
                                    }
                                }                         
                            }
                        }
                    }
                }
            }
            break;
        /*
        *   Checks what is around a Fox
        */
        case ProjectHandler::FOX:
            sim.possibleMoves.clear();
            sim.possibleMates.clear();
            sim.possibleFood.clear();
            for (int a = (i-1); a <= (i+1); a++) {
                for(int b = (j-1); b <= (j+1); b++) {                    
                    if(a < 0 || b < 0 || a >= ph.getPlaygroundSize() || b >= ph.getPlaygroundSize()) continue; //Border

                    else if(a == i && b == j) continue; //itself

                    else if(ph.playground[a][b] == ProjectHandler::EMPTY) sim.possibleMoves[{a,b}] = true;

                    else if(ph.playground[a][b] == ProjectHandler::GRASS) {
                        if(ph.objectsMapGrass[{a,b}]->getLevel() <= 4 && ph.objectsMapRabbit[{a,b}] == 0 && ph.objectsMapFox[{a,b}] == 0) sim.possibleMoves[{a,b}] = true;
                    }
                    else if(ph.playground[a][b] == ProjectHandler::RABBIT && ph.objectsMapFox[{i,j}]->getHunger() > 2) sim.possibleFood[{a,b}] = true;

                    else if(ph.playground[a][b] == ProjectHandler::FOX) {
                        if(ph.objectsMapFox[{a,b}]->getGender() != ph.objectsMapFox[{i,j}]->getGender() && 
                            ph.objectsMapFox[{i,j}]->getAge() >= ph.objectsMapFox[{i,j}]->getminAgeMateFox() && ph.objectsMapFox[{a,b}]->getAge() >= ph.objectsMapFox[{a,b}]->getminAgeMateFox() &&
                            ph.objectsMapFox[{i,j}]->getHorny() && ph.objectsMapFox[{a,b}]->getHorny()) {
                            for (int x = (i-1); x <= (i+1); x++) {
                                for(int y = (j-1); y <= (j+1); y++) {
                                    if(x >= 0 && y >= 0 && x < ph.getPlaygroundSize() && y < ph.getPlaygroundSize() && 
                                        (ph.playground[x][y] == ProjectHandler::EMPTY || (ph.playground[x][y] == ProjectHandler::GRASS && ph.objectsMapGrass[{x,y}]->getLevel() <= 5))) {
                                        sim.possibleMates[{x,y}] = true;
                                        ph.objectsMapFox[{i,j}]->setHorny(false);
                                        //ph.objectsMapFox[{a,b}]->setHorny(false);
                                    }
                                }                         
                            }
                        }
                    }
                }
            }
            break;
        
        default:
            break;
    }   
}

/*
*   Prints the fancy grid of the playground
*   Features: Grass shows specific level, Emojis are implemented for Rabbits and Foxes. Genders are shown too
*/
void Simulator::printPlayground() {
    std::cout << ph.colorBrown << "[Engine] " << ph.colorPurple << "The Playground!!" << std::endl;
    int c = 0; //compensator
    for (int i = 0; i <= (ph.getPlaygroundSize()*2); i++) {
        if(i != 0 && i != (ph.getPlaygroundSize()*2) && i%2 != 0) std::cout << ph.colorWhite << " |";
        if(i%2 == 0) std::cout << ph.colorWhite << " ";
        if(i%2 != 0)  c++;
        for (int j = 0; j < ph.getPlaygroundSize(); j++) {
            if(i == ph.getPlaygroundSize()*2) std::cout << ph.colorWhite << " ----";            
            else {
                switch(ph.playground[(i-c)][j]) {
                    case ProjectHandler::EMPTY: {
                        if(i%2 == 0) std::cout << " ----";
                        else std::cout << ph.colorWhite << "    " << ph.colorWhite << "|"; 
                        break;
                    }
                    case ProjectHandler::RABBIT: {
                        if(i%2 == 0) std::cout << " ----";
                        else {
                            if(ph.objectsMapRabbit[{i-c,j}]->getGender() == 1) std::cout << ph.colorBrown << "🐰" << ph.colorWhite << "\u2640" << " " << "|";                            
                            else std::cout << ph.colorBrown << "🐰" << ph.colorWhite << "\u2642" << " " << "|";                                                   
                        }
                        break;
                    }
                    case ProjectHandler::FOX: {
                        if(i%2 == 0) std::cout << " ----";
                        else {
                            if(ph.objectsMapFox[{i-c,j}]->getGender() == 1) std::cout << ph.colorRed << "🦊"  << ph.colorWhite << "\u2640" << " " << "|";
                            else std::cout << ph.colorRed << "🦊" << ph.colorWhite << "\u2642" << " " << "|";                            
                        }                        
                        break;
                    }
                    case ProjectHandler::GRASS: {
                        if(i%2 == 0) std::cout << " ----";
                        else {
                            if(ph.objectsMapGrass[{i-c,j}]->getLevel()== 1) std::cout << ph.colorGreen << " .. " << ph.colorWhite << "|";
                            else if (ph.objectsMapGrass[{i-c,j}]->getLevel()== 2)std::cout << ph.colorGreen << " :: " << ph.colorWhite << "|";
                            else if (ph.objectsMapGrass[{i-c,j}]->getLevel()== 3)std::cout << ph.colorGreen << " ⁝⁝ " << ph.colorWhite << "|";
                            else if (ph.objectsMapGrass[{i-c,j}]->getLevel()== 4)std::cout << ph.colorGreen << " ⦙⦙ " << ph.colorWhite << "|";
                            else if (ph.objectsMapGrass[{i-c,j}]->getLevel()== 5)std::cout << ph.colorGreen << " || " << ph.colorWhite << "|";
                            else std::cout << ph.colorBrown << " .. " << ph.colorWhite << "|";
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }        
        std::cout << std::endl;
    } 
}

/*
*   Runs the overpopulation checks (based on the config parameters) Kills the Rabbits and Foxes that exceed this amount (randomly decided, which get killed)
*/
void Simulator::overPop() {
    for (int i = 0; i < ph.getPlaygroundSize(); i++) {
        for (int j = 0; j < ph.getPlaygroundSize(); j++) {
            sim.overPopRabbitsDeaths.clear();
            sim.overPopFoxesDeaths.clear();
            switch (ph.playground[i][j]) {
            case ProjectHandler::RABBIT:
                for (int a = (i-1); a <= (i+1); a++) {
                    for(int b = (j-1); b <= (j+1); b++) {
                        if(a < 0 || b < 0 || a >= ph.getPlaygroundSize() || b >= ph.getPlaygroundSize()) continue; //Border
                        if(ph.objectsMapRabbit[{a,b}] != 0) sim.overPopRabbitsDeaths[{a,b}] = true;
                    }
                }
                //Kills as many Rabbits, until the overpopulation is resolved
                while (sim.overPopRabbitsDeaths.size() >= static_cast<size_t>(living.getMaxAmountRabbits())) {
                    auto death = sim.overPopRabbitsDeaths.begin();
                    std::advance(death, eng.getRandInt(0, static_cast<int>(sim.overPopRabbitsDeaths.size())-1));
                    std::pair<int, int> NewDeathSpot = death->first;
                    ph.objectsMapRabbit[{NewDeathSpot}]->die(NewDeathSpot.first, NewDeathSpot.second, false);
                    if(ph.objectsMapGrass[{NewDeathSpot}] != 0) {
                        ph.playground[NewDeathSpot.first][NewDeathSpot.second] = ProjectHandler::GRASS;
                        ph.objectsMapGrass[{NewDeathSpot}]->setLevel(-2);
                    }
                    else ph.playground[NewDeathSpot.first][NewDeathSpot.second] = ProjectHandler::EMPTY;
                    sim.overPopRabbitsDeaths.erase(NewDeathSpot);
                }
                
                break;
                case ProjectHandler::FOX:
                for (int a = (i-1); a <= (i+1); a++) {
                    for(int b = (j-1); b <= (j+1); b++) {
                        if(a < 0 || b < 0 || a >= ph.getPlaygroundSize() || b >= ph.getPlaygroundSize()) continue; //Border
                        if(ph.objectsMapFox[{a,b}] != 0) sim.overPopFoxesDeaths[{a,b}] = true;
                    }
                }
                //Kills as many Foxes, until the overpopulation is resolved
                while (sim.overPopFoxesDeaths.size() >= static_cast<size_t>(living.getMaxAmountFoxes())) {
                    auto death = sim.overPopFoxesDeaths.begin();
                    std::advance(death, eng.getRandInt(0, static_cast<int>(sim.overPopFoxesDeaths.size())-1));
                    std::pair<int, int> NewDeathSpot = death->first;
                    ph.objectsMapFox[{NewDeathSpot}]->die(NewDeathSpot.first, NewDeathSpot.second, false);
                    if(ph.objectsMapGrass[{NewDeathSpot}] != 0) {
                        ph.playground[NewDeathSpot.first][NewDeathSpot.second] = ProjectHandler::GRASS;
                        ph.objectsMapGrass[{NewDeathSpot}]->setLevel(-2);
                    }
                    else ph.playground[NewDeathSpot.first][NewDeathSpot.second] = ProjectHandler::EMPTY;
                    sim.overPopFoxesDeaths.erase(NewDeathSpot);
                }
                break;            
            default:
                break;
            }
        }
    }
}

/*
*   Writes the data collected in this cycle as a new line in the reportfile
*/
void Evaluator::writeReportFile(std::string date) {
    ph.summaryStream.str("");
    ph.summaryStream << date << ";" << ph.nrEmpty << ";" << ph.nrGrass << ";" << ph.nrRabbits << ";" << eva.nrFemaleRabbits << ";" << eva.nrMaleRabbits << ";" 
                     << ph.nrFoxes << ";" << eva.nrFemaleFoxes << ";" << eva.nrMaleFoxes << ";"
                     << eva.averageLevelGrass << ";" << eva.averageAgeRabbit << ";" << eva.averageAgeFox << ";"
                     << eva.changeOfEmpty << ";" << eva.changeOfGrass << ";" << eva.changePopRabbit << ";" << eva.changePopFox << std::endl;
    std::ofstream reportFile; reportFile.open(ph.currentTimeDateStream.str(), std::ios::in | std::ios::app);
    reportFile.clear();
    reportFile << ph.summaryStream.str();
    reportFile.close();
}

/*
*   Collects all possible data "gatherable" from the simulation. Stored in global variables, reset every cycle
*/
void Evaluator::getData() {
    eva.clearData();
    for (int i = 0; i < ph.getPlaygroundSize(); i++) {
        for (int j = 0; j < ph.getPlaygroundSize(); j++) {    
            switch(ph.playground[i][j]) {
                case ProjectHandler::EMPTY:
                    ph.nrEmpty++;
                    break;
                case ProjectHandler::GRASS: {
                    if (ph.objectsMapGrass[{i,j}] != nullptr) {
                        if (ph.objectsMapGrass[{i,j}]->getLevel() >= 0) {
                            eva.averageLevelGrass += ph.objectsMapGrass[{i,j}]->getLevel();
                            ph.nrGrass++;
                        }
                        else ph.nrGrass++;
                        
                    } 
                    else std::cout << ph.colorRed << "nullptr at (case 2): " << i << j << std::endl;
                    break;
                }
                case ProjectHandler::RABBIT: {
                    if (ph.objectsMapRabbit[{i,j}] != nullptr) {
                        eva.averageAgeRabbit += ph.objectsMapRabbit[{i,j}]->getAge();
                        if(ph.objectsMapRabbit[{i,j}]->getGender() == 1) eva.nrFemaleRabbits++;
                        ph.nrRabbits++; 
                    }
                    else std::cout << ph.colorRed << "nullptr at (case 3): " << i << j << std::endl;
                    break;
                }
                case ProjectHandler::FOX: {
                    if (ph.objectsMapFox[{i,j}] != nullptr) {
                        eva.averageAgeFox += ph.objectsMapFox[{i,j}]->getAge();
                        if(ph.objectsMapFox[{i,j}]->getGender() == 1) eva.nrFemaleFoxes++;
                        ph.nrFoxes++;
                    }
                    else std::cout << ph.colorRed << "nullptr at (case4): " << i << j << std::endl;
                    break;
                }
                default:
                    break;
            }
        }
    }
    //Mean Level and Age computations
     if(ph.nrGrass!=0) {
        eva.averageLevelGrass /= ph.nrGrass;
        eva.averageLevelGrass = round(eva.averageLevelGrass*100)/100;     
    } else  eva.averageLevelGrass = 0;
     if(ph.nrRabbits!=0) {
        eva.averageAgeRabbit /= ph.nrRabbits;
        eva.averageAgeRabbit = round(eva.averageAgeRabbit*100)/100;         
    } else eva.averageAgeRabbit = 0;
    if(ph.nrFoxes!=0) {
        eva.averageAgeFox /= ph.nrFoxes;
        eva.averageAgeFox = round(eva.averageAgeFox*100)/100;        
    } else eva.averageAgeFox = 0;

    //Gender of Foxes
    eva.nrMaleRabbits = ph.nrRabbits - eva.nrFemaleRabbits;
    eva.nrMaleFoxes = ph.nrFoxes - eva.nrFemaleFoxes; 

    //Stats with prev cycle
    eva.changeOfEmpty = ph.nrEmpty-eva.oldNrEmpty;
    eva.changeOfGrass = ph.nrGrass-eva.oldNrGrass;
    eva.changePopRabbit = ph.nrRabbits-eva.oldNrRabbits;
    eva.changePopFox = ph.nrFoxes-eva.oldNrFoxes;
}

/*
*   Prints interesting data below the playground, to add contect to what happens in the playground
*/
void Visualiser::showData(int day) {
    std::cout << std::endl << ph.colorMagenta << "   STATISTICS for day " << day << std::endl;

    std::cout << ph.colorWhite << "   Number of Empty fields: " << ph.nrEmpty << " |  Number of Grass fields: " << ph.colorGreen << ph.nrGrass << std::endl;
    std::cout << ph.colorWhite << "   Number of Rabbits:      " << ph.colorBrown << ph.nrRabbits << ph.colorWhite << " |  Number of Foxes:        " << ph.colorRed << ph.nrFoxes << std::endl;
    
    std::cout << std::endl << "                            ";
    if((eva.changeOfEmpty) > 0) std::cout << ph.colorWhite << "  |  Change of Empty spaces from last cycle: " << ph.colorGreen << (eva.changeOfEmpty) << std::endl;
    else if ((eva.changeOfEmpty) < 0) std::cout << ph.colorWhite << "  |  Change of Empty spaces from last cycle: " << ph.colorRed << (eva.changeOfEmpty) << std::endl;
    else std::cout << ph.colorWhite << "  |  Change of Empty spaces from last cycle: " << ph.colorWhite << (eva.changeOfEmpty) << std::endl;

    std::cout << ph.colorWhite << "   Average Level of Grass:  " << ph.colorAqua << eva.averageLevelGrass;
    if((eva.changeOfGrass) > 0) std::cout << ph.colorWhite << " |  Change of Grass from last cycle:        " << ph.colorGreen << (eva.changeOfGrass) << std::endl;
    else if ((eva.changeOfGrass) < 0) std::cout << ph.colorWhite << " |  Change of Grass from last cycle:        " << ph.colorRed << (eva.changeOfGrass) << std::endl;
    else std::cout << ph.colorWhite << " |  Change of Grass from last cycle:        " << ph.colorWhite << (ph.nrGrass-eva.oldNrGrass) << std::endl;

    std::cout << ph.colorWhite << "   Average age of Rabbits:  " << ph.colorAqua << eva.averageAgeRabbit;
    if((eva.changePopRabbit) > 0) std::cout << ph.colorWhite << " |  Change of Rabbits from last cycle:      " << ph.colorGreen << (eva.changePopRabbit) << ph.colorWhite << " (\u2640: " << eva.nrFemaleRabbits << " and \u2642: " << eva.nrMaleRabbits << ")" << std::endl;
    else if ((eva.changePopRabbit) < 0) std::cout << ph.colorWhite << " |  Change of Rabbits from last cycle:      " << ph.colorRed << (eva.changePopRabbit) << ph.colorWhite << " (\u2640: " << eva.nrFemaleRabbits << " and \u2642: " << eva.nrMaleRabbits << ")" << std::endl;
    else std::cout << ph.colorWhite << " |  Change of Rabbits from last cycle:      " << ph.colorWhite << (eva.changePopRabbit) << std::endl;

    std::cout << ph.colorWhite << "   Average age of Foxes:    " << ph.colorAqua << eva.averageAgeFox;
    if((eva.changePopFox) > 0) std::cout << ph.colorWhite << " |  Change of Foxes from last cycle:        " << ph.colorGreen << (eva.changePopFox) << ph.colorWhite << " (\u2640: " << eva.nrFemaleFoxes << " and \u2642: " << eva.nrMaleFoxes << ")" << std::endl;
    else if ((eva.changePopFox) < 0) std::cout << ph.colorWhite << " |  Change of Foxes from last cycle:        " << ph.colorRed << (eva.changePopFox) << ph.colorWhite << " (\u2640: " << eva.nrFemaleFoxes << " and \u2642: " << eva.nrMaleFoxes << ")" << std::endl;
    else std::cout << ph.colorWhite << " |  Change of Foxes from last cycle:        " << ph.colorWhite << (eva.changePopFox) << std::endl;
}

/*
*   Revives up to 3 couples of the creatures that got extinct (Rabbits or Foxes)
*   They get randomly distributed on Empty fields or Grass
*/
void Simulator::resurrection() {
    sim.possibleResurr.clear();
    bool possibleSpot;
    if(ph.nrRabbits <= 0) {        
        for (int i = 2; i < ph.getPlaygroundSize()-2; i++) {
            for (int j = 2; j < ph.getPlaygroundSize()-2; j++) {
                possibleSpot = true;
                if(ph.objectsMapFox[{i,j}] == 0) {
                    for (int a = (i-2); a <= (i+2); a++) {
                        for (int b = (j-2); b <= (j+2); b++) {
                            if(!(ph.objectsMapFox[{a,b}] == 0)) possibleSpot = false;
                        }
                    }
                    if(possibleSpot) sim.possibleResurr[{i,j}] = true;
                }
            }
        }
        int newCouples = 0;
        while(!sim.possibleResurr.empty() && newCouples <= 2) {
            auto spawn = sim.possibleResurr.begin();
            std::advance(spawn, eng.getRandInt(0, static_cast<int>(sim.possibleResurr.size())-1));
            std::pair<int, int> NewBorn = spawn->first;
            std::pair<int, int> NewSpawn;
            for(int u = 0; u < 2; u++) {
                Rabbit* creature = new Rabbit(static_cast<bool>(u));
                NewSpawn.first = static_cast<int>(NewBorn.first+u);
                NewSpawn.second = static_cast<int>(NewBorn.second);
                ph.objectsMapRabbit[NewSpawn] = creature;
                ph.playground[NewSpawn.first][NewSpawn.second] = ProjectHandler::RABBIT;
            }
            sim.possibleResurr.erase(NewSpawn);
            newCouples++;
        }
    }
    else if(ph.nrFoxes <= 0) {
        for (int i = 2; i < ph.getPlaygroundSize()-2; i++) {
            for (int j = 2; j < ph.getPlaygroundSize()-2; j++) {
                possibleSpot = true;
                if(ph.objectsMapRabbit[{i,j}] == 0) {
                    for (int a = (i-2); a <= (i+2); a++) {
                        for (int b = (j-2); b <= (j+2); b++) {
                            if(!(ph.objectsMapRabbit[{a,b}] == 0)) possibleSpot = false;
                        }
                    }
                    if(possibleSpot) sim.possibleResurr[{i,j}] = true;
                }
            }
        }
        int newCouples = 0;
        while(!sim.possibleResurr.empty() && newCouples <= 2) {
            auto spawn = sim.possibleResurr.begin();
            std::advance(spawn, eng.getRandInt(0, static_cast<int>(sim.possibleResurr.size())-1));
            std::pair<int, int> NewBorn = spawn->first;
            std::pair<int, int> NewSpawn;
            for(int u = 0; u < 2; u++) {
                Fox* creature = new Fox(static_cast<bool>(u));
                NewSpawn.first = static_cast<int>(NewBorn.first+u);
                NewSpawn.second = static_cast<int>(NewBorn.second);
                ph.objectsMapFox[{NewSpawn}] = creature;
                ph.playground[NewSpawn.first][NewSpawn.second] = ProjectHandler::FOX;
            }
            sim.possibleResurr.erase(NewSpawn);
            newCouples++;
        }
    }
    else return;
}

/*
*   Clears the global variables that are updated every cycle in getData()
*/
void Evaluator::clearData() {
    eva.averageLevelGrass = 0;
    eva.averageAgeRabbit = 0;
    eva.averageAgeFox = 0;
    eva.changeOfEmpty = 0;
    eva.changeOfGrass = 0;
    eva.changePopRabbit = 0;
    eva.changePopFox = 0;
    eva.oldNrEmpty = ph.nrEmpty;
    eva.oldNrGrass = ph.nrGrass;
    eva.oldNrRabbits = ph.nrRabbits;
    eva.oldNrFoxes = ph.nrFoxes;
    eva.nrFemaleRabbits = 0;
    eva.nrMaleRabbits = 0;
    eva.nrFemaleFoxes = 0;
    eva.nrMaleFoxes = 0;
    ph.nrEmpty = 0;
    ph.nrGrass = 0;
    ph.nrRabbits = 0;
    ph.nrFoxes = 0;
}

/*
*   Clears the playground
*/
void Simulator::clear() {
    try {
        for (int i = 0; i < ph.getPlaygroundSize(); i++) {
            for (int j = 0; j < ph.getPlaygroundSize(); j++) {
                if (ph.objectsMapGrass[{i,j}] != 0) ph.objectsMapGrass[{i,j}]->Living::die(i,j,true);
                else if (ph.objectsMapRabbit[{i,j}] != 0) ph.objectsMapRabbit[{i,j}]->Living::die(i,j,false);
                else if (ph.objectsMapFox[{i,j}] != 0) ph.objectsMapFox[{i,j}]->Living::die(i,j,false);
            }
        }
    }
    catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }   
    
    ph.playground.clear();
    ph.objectsMapEmpty.clear();
    ph.objectsMapGrass.clear();
    ph.objectsMapRabbit.clear();
    ph.objectsMapFox.clear();
    std::cout << ph.colorBrown << "[Engine] " << ph.colorGreen << "World cleared successfully!" << std::endl;
}

/*
*   Produces a random integer in the given range
*   Used for determining Creatures randomly and determining the gender of Rabbits and Foxes
*/
int Engine::getRandInt(int x, int y) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(x, y);
    return distr(gen);
}
    