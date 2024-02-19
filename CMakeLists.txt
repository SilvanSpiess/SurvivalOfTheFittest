if(APPLE)
    # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
    # CMake function
    cmake_minimum_required(VERSION 3.20)

    # CMake function that sets variable PROJECT_NAME
    project(fittest_APPLE)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    set(SOURCES src/main.cpp src/Engine.cpp src/Living.cpp src/FileHandler.cpp src/ProjectHandler.cpp)

    #inlcude the header files .hpp
    include_directories(include)

    #define the targeted folder
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

    #Add compliers flags if applicable
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    endif()

    #creates the executable
    add_executable(${PROJECT_NAME} ${SOURCES})
    # EOF
endif(APPLE)

if(UNIX AND NOT APPLE)
    # for Linux, BSD, Solaris, Minix
    # CMake version
    cmake_minimum_required(VERSION 3.20)

    # Project name and language
    project(fittest CXX)

    set(CMAKE_CXX_COMPILER g++)

    add_compile_options(-O0 -ggdb -Wall -Wextra -Wpedantic -std=c++20 -Wconversion -Wshadow -Wnull-dereference -Wformat)

    # Source files
    set(SOURCES src/main.cpp src/Engine.cpp src/Living.cpp src/FileHandler.cpp src/ProjectHandler.cpp)

    # Include header files
    include_directories(include)

    # Define the output directory
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

    # Create the executable
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()
