//
// main.cpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP/BasicNeural/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Apr 23 18:55:56 2017 Sousa Victor
// Last update Tue May  2 01:17:46 2017 Sousa Victor
//

#include <iostream>

#include "NetworkTrainer.hpp"
#include "Network.hpp"

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "Usage:\t" << argv[0] << "\tpath_to_input_file.txt" << std::endl;
        return (-1);
    }

    Neural::NetworkTrainer trainer(argv[1]);
    Neural::Network network(trainer.getTopology());

    network.train(trainer);

    std::cout << network;
}
