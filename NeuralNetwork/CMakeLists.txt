cmake_minimum_required(VERSION 3.9)
set(NAME NeuralNetwork)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


## Setup Logger library
if (NOT TARGET Logger)
    add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/Logger)
    include_directories(${PROJECT_SOURCE_DIR}/Lib/Logger/Includes/)
endif()

## Setup Argument parsing library
if (NOT TARGET ArgParser)
    add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/ArgParser)
    include_directories(${PROJECT_SOURCE_DIR}/Lib/ArgParser/Includes/)
endif()


## Setup the source files
set(Sources
    ${PROJECT_SOURCE_DIR}/Sources/main.cpp

    ${PROJECT_SOURCE_DIR}/Includes/IMain.h
    ${PROJECT_SOURCE_DIR}/Includes/AMain.h
    ${PROJECT_SOURCE_DIR}/Sources/AMain.cpp

    ${PROJECT_SOURCE_DIR}/Includes/IClass.h
    ${PROJECT_SOURCE_DIR}/Includes/AClass.h
    ${PROJECT_SOURCE_DIR}/Sources/AClass.cpp

    ${PROJECT_SOURCE_DIR}/Includes/MainClass.h
    ${PROJECT_SOURCE_DIR}/Sources/MainClass.cpp


    ${PROJECT_SOURCE_DIR}/Includes/NeuralNetwork/NetworkException.hpp

    ${PROJECT_SOURCE_DIR}/Includes/NeuralNetwork/ANetworkData.hpp
    ${PROJECT_SOURCE_DIR}/Sources/NeuralNetwork/ANetworkData.cpp
    ${PROJECT_SOURCE_DIR}/Includes/NeuralNetwork/Network.hpp
    ${PROJECT_SOURCE_DIR}/Sources/NeuralNetwork/Network.cpp
    ${PROJECT_SOURCE_DIR}/Includes/NeuralNetwork/NetworkTrainer.hpp
    ${PROJECT_SOURCE_DIR}/Sources/NeuralNetwork/NetworkTrainer.cpp

    ${PROJECT_SOURCE_DIR}/Includes/NeuralNetwork/Layer.hpp
    ${PROJECT_SOURCE_DIR}/Includes/NeuralNetwork/Neuron.hpp
    ${PROJECT_SOURCE_DIR}/Sources/NeuralNetwork/Neuron.cpp

)


## Setup default include path
include_directories(
        ${PROJECT_SOURCE_DIR}/Includes/
        ${PROJECT_SOURCE_DIR}/Includes/NeuralNetwork
)

## Setup link path
link_directories(
        ${PROJECT_BINARY_DIR}/Lib/Logger/
)

## Create executables
add_executable(${NAME} ${Sources})


## Setup used library
target_link_libraries(${NAME}
        Logger
        ArgParser
)
