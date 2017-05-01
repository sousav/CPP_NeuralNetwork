//
// or_generator.cpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP/BasicNeural/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May  1 00:10:56 2017 Sousa Victor
// Last update Mon May  1 03:51:06 2017 Sousa Victor
//

#include <iostream>
#include <cstdlib>
#include <map>

void gen_or() {
    // random traning sets for OR -- two inputs and one output
	std::cout << "topology: 3 4 1" << std::endl;
	for (int i = 100000; i >= 0; --i) {
		int n1 = (int)(2.0 * rand() / double(RAND_MAX));
		int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int n3 = (int)(2.0 * rand() / double(RAND_MAX));
		int t = n1 || n2 || n3; // should be 0 or 1
		std::cout << "in: " << n1 << ".0 " << n2 << ".0 " << n3 << ".0 " << std::endl;
		std::cout << "out: " << t << ".0" << std::endl;
	}
}

void gen_xor() {
    // random traning sets for XOR -- two inputs and one output
    std::cout << "topology: 2 4 8 4 1" << std::endl;
    for (int i = 50000; i >= 0; --i) {
        int n1 = (int)(2.0 * rand() / double(RAND_MAX));
        int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int t = n1 ^ n2; // should be 0 or 1
        std::cout << "in: " << n1 << ".0 " << n2 << ".0 " << std::endl;
        std::cout << "out: " << t << ".0" << std::endl;
    }
}

int main(int ac, char **av) {
    std::map <std::string, std::function<void()>> map;

    //OR TYPO
    map["or"] = std::bind(gen_or);
    map["OR"] = std::bind(gen_or);

    //XOR TYPO
    map["xor"] = std::bind(gen_xor);
    map["XOR"] = std::bind(gen_xor);

    if (ac != 2 || map.find(av[1]) == map.end() ) {
        std::cout << "Usage: " << av[0] << " [or || xor]" << std::endl;
        return -1;
    }

    map[av[1]]();
    return 0;
}
