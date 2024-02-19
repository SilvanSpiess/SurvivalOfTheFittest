#include "ProjectHandler.hpp"
#include "FileHandler.hpp"

#include <thread>
#include <chrono>
int ProjectHandler::getSimCycles() const{return ph.params["simCycles"];}
int ProjectHandler::getSimDelay() const{return ph.params["simDelay"];}

/*
*   Runs the Simulation
*   User can decide between a given amount of cycles being simulated or
*   simulating each cylce individually by Pressing 'Enter'
*/
int ProjectHandler::launcher() {
    FileHandler fh;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::system("clear");
    fh.init();
    fh.readFromFile();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ph.printBegin(); 
    int choice;
    choice = getchar();
    getchar();

    /*
    *   Procedure to loop through a predefined amount of cycles (from the config file), given also a delay per cycle from the config file
    */
    if(choice == 78 || choice == 110) { 
        sim.eden();
        sim.overPop();
        sim.printPlayground();    
        eva.getData();
        eva.writeReportFile("Initial Day");
        vis.showData(0);

        std::cout << ph.colorMagenta << "   Press 'Enter' to start the simualtion with " << getSimCycles() << " cycles";
        std::cin.ignore();
        
        for (int day = 1; day <= getSimCycles(); day++) {
            sim.next();
            sim.overPop();
            std::this_thread::sleep_for(std::chrono::milliseconds(getSimDelay()));
            eva.getData();
            if(ph.nrRabbits <= 0 || ph.nrFoxes <= 0) sim.resurrection();
            eva.writeReportFile(std::to_string(day));
            std::system("clear");
            sim.printPlayground();       
            vis.showData(day);
        }
    }
    /*
    *   Procedure to loop manually through the simulation
    */
    else if(choice == 77 || choice == 109) {
        sim.eden();
        sim.overPop();
        sim.printPlayground();    
        eva.getData();
        eva.writeReportFile("Initial Day");
        vis.showData(0);

        std::cout << ph.colorMagenta << "   Press 'Enter' to sleep for the first night";
        std::cin.ignore();
        bool run{true}; 
        int day{0};
        
        while(run) {     
            sim.next();
            sim.overPop();        
            eva.getData();
            if(ph.nrRabbits <= 0 || ph.nrFoxes <= 0) sim.resurrection();
            eva.writeReportFile(std::to_string(++day));
            sim.printPlayground();
            vis.showData(day);

            std::cout << ph.colorMagenta << "   Press 'Enter' to sleep for the night or 'esc' to stop the simulation " << ph.colorWhite;
            int input;
            input = std::cin.get();
            //std::cin.ignore();
            if (input == 13 || input == 92) run = true;
            else if (input == 27) run = false;
            else std::cout << "Invalid input. Try again." << std::endl;
        }
    }
    else std::cout << ph.colorRed << "   Invalid input " << ph.colorWhite;
    sim.clear();
    return 0;
}

void ProjectHandler::printBegin() {
    std::cout << ph.colorBrown << "[Engine] - " << ph.colorGreen << "World was created successfully!" << std::endl;
    std::cout << ph.colorWhite << "\n***********************************************************************\n"<<std::endl;
    std::cout << ph.colorRed <<    "  _	       _   ___	 _        ___     __	 __      __   ___ "<<std::endl;
    std::cout <<                  "  \\\\    /\\    //  |  _|	| |	 / __|   /  \\	|  \\    /  | |  _|"<<std::endl;
    std::cout <<                  "   \\\\  //\\\\  //	  | |_	| |	| |	/ /\\ \\	| |\\\\  //| | | |_ "<<std::endl;
    std::cout <<                  "    \\\\//  \\\\//	  | |_	| |__	| |__	\\ \\/ /	| | \\\\// | | | |_ "<<std::endl;
    std::cout <<                  "     \\/    \\/	  |___|	|____|	 \\___|   \\__/	|_|  \\/  |_| |___|"<<std::endl;        
    std::cout << ph.colorAqua<<                 "\n                     🐰🐰  Survival of the fittest  🦊🦊"<<std::endl;
    std::cout << ph.colorWhite << "***********************************************************************\n"<<std::endl;
    std::cout << ph.colorMagenta << "Please choose one of the following options, by pressing their corresponding keys: " << std::endl;
    std::cout << ph.colorWhite << " - Press \"n\" to cycle automatically through " << getSimCycles() << " loops." << std::endl;
    std::cout << ph.colorWhite << " - Press \"m\" to cycle manually through the simulation. " << std::endl;
}
    
 