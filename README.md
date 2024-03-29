# World of the Fittest Simulation
**Silvan Spiess** <silvan.spiess@students.bfh.ch>

**Bela Lauter** <bela.lauter@students.bfh.ch>

**Nicola Pulvirenti** <nicola.pulvirenti@students.bfh.ch> 

## Introduction
This project is a C++ simulator that models the interaction of different creatures in a fictional world. The world contains instances of a class Living, 
which serves as the base class for all creatures and nature elements within this world. The following living things exist in this fictional world:
* **Empty**
* **Grass**
* **Rabbits**
* **Foxes**

Every form of life multiplies according to certain biological patterns. The individual life forms are either predator (Foxes) or prey (Rabbits). 
The visualization heavily depends on your personal preferences. In the config.yml file, the characteristics of each creature can be adjusted, which leads to several different outcomes of the simulation. 
There exist two modes, one is to cycle quickly through a predefined amount of steps, the other mode is to progress one cycle at the time. This allows to trace back the Lifes of certain creatures.

## Installation 
### Step 1: Clone
Clone the repository:
*git clone git@gitlab.ti.bfh.ch:btf2232/students_fs23/project/wotf-grp-09.git*

#### Pre-requisites Windows:
Make sure you have a c++ compiler as well as Cmake installed. Else:

Download and install Cygwin *https://www.cygwin.com/*

Install packages: *cmake*, *make*, *gcc-g++*

#### Pre-requisites MacOS
Make sure you have a c++ compiler as well as Cmake installed. Else: 

Compiler: check if available *g++ --version*

Brew: *https://brew.sh/*

Cmake: *brew cmake*

#### Pre-requisites Linux
Make sure you have a c++ compiler as well as Cmake installed. Else:

Compiler: *sudo apt install build-essential*

cmake: *sudo apt install cmake*

### Step 2: Build
Go into the project directory: *cd wotf-grp-09*

Create a build directory: *mkdir build* && *cd build*
(if one already exists, delete it)

Run CMake to generate the build files: *cmake ..*

Build the application with: *make*

## Usage
Run the application from the folder location: *./fittest.exe* (Windows) and *./fittest* (MacOS and Linux)

On your own risk, you can run the files, by double clicking them
(Windows yes, Linux no, MacOS with side effects)

Follow the CLI prompts to configure the simulation.

View the simulation statistics and properties at the end of each cycle.

There are two files generated:
* *config.yml* : Parameters such as world size or the creatrues max age can be altered and played with.
* *report.csv* : Important data is exported into a seperate file for each time the simulation is started.

## Documentation
Documentation is generated using Doxygen. To generate the documentation, run:
(Doxygen installation reuired: *https://www.doxygen.nl/manual/install.html*)

*doxygen README.md*

This will generate the documentation in the doc directory.

## License
This project is licensed under the BFH License.
