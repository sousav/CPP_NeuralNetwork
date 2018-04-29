/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:17:52
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:00:44
 */


#include "MainClass.h"

MainClass::MainClass(int argc, char *argv[]): AMain(argc, argv, "MainClass") {

}

MainClass::~MainClass() {

}


ArgParser::parser MainClass::setupArgParser() const {
    return ArgParser::parser {{
        { "help", {"-h", "--help"}, "Shows this help message.\n", 0},
        { "type", {"-t", "--type"}, KRED + "[required]" + KNRM + " Specify the generator type.\n", 1},
        { "count", {"-c", "--count"}, "            Specify how many example the data set will contains." + KYEL + "\n\tdefault: 50000\n" + KNRM, 1},
        { "list_type", {"-l", "--list"}, "            List all project type possibilities.\n", 0}
    }};
}

bool MainClass::Run(ArgParser::parser_results const &args) {

    this->_generators["and"] = std::bind(&MainClass::generator_and, this, std::placeholders::_1);
    this->_generators["or"] = std::bind(&MainClass::generator_or, this, std::placeholders::_1);
    this->_generators["xor"] = std::bind(&MainClass::generator_xor, this, std::placeholders::_1);

    if (!this->checkArgument(args)) {
        return false;
    }


    if (this->_generators.find(args["type"].as<std::string>()) == this->_generators.end() ) {
        std::cout << "Usage: " << " [or || xor]" << std::endl;
        return false;
    }

    this->_generators[args["type"].as<std::string>()](args["count"].as<int>(50000));

    return true;
}

bool MainClass::checkArgument(ArgParser::parser_results const &args) const {
    if (args["help"]) {
        ArgParser::fmt_ostream(std::cerr) << "Usage:" << std::endl << this->setupArgParser();
        return false;
    }

    if (args["list_type"]) {
        this->logger.info() << "Possible generator type:";
        for (auto const &e: this->_generators) {
            this->logger.info() << e.first;
        }
        return false;
    }

    if (!args["type"]) {
        ArgParser::fmt_ostream(std::cerr) << KRED + "\nYou must provide a generator type -t or --type\n" + KNRM << std::endl << this->setupArgParser();
        return false;
    }

    return true;
}

void MainClass::generator_and(int count) const {
    // random traning sets for AND -- two inputs and one output
	std::cout << "topology: 2 4 1" << std::endl;
	for (int i = count; i > 0; --i) {
		int n1 = (int)(2.0 * rand() / double(RAND_MAX));
		int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int t = n1 && n2; // should be 0 or 1
		std::cout << "in: " << n1 << ".0 " << n2 << ".0 " << std::endl;
		std::cout << "out: " << t << ".0" << std::endl;
	}
}

void MainClass::generator_or(int count) const {
    // random traning sets for OR -- three inputs and one output
	std::cout << "topology: 3 4 1" << std::endl;
	for (int i = count; i > 0; --i) {
		int n1 = (int)(2.0 * rand() / double(RAND_MAX));
		int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int n3 = (int)(2.0 * rand() / double(RAND_MAX));
		int t = n1 || n2 || n3; // should be 0 or 1
		std::cout << "in: " << n1 << ".0 " << n2 << ".0 " << n3 << ".0 " << std::endl;
		std::cout << "out: " << t << ".0" << std::endl;
	}
}

void MainClass::generator_xor(int count) const {
    // random traning sets for XOR -- two inputs and one output
    std::cout << "topology: 2 4 8 4 1" << std::endl;
    for (int i = count; i > 0; --i) {
        int n1 = (int)(2.0 * rand() / double(RAND_MAX));
        int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int t = n1 ^ n2; // should be 0 or 1
        std::cout << "in: " << n1 << ".0 " << n2 << ".0 " << std::endl;
        std::cout << "out: " << t << ".0" << std::endl;
    }
}
