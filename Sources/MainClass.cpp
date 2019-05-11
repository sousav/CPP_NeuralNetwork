/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:17:52
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:07:48
 */


#include "MainClass.h"

MainClass::MainClass(int argc, char *argv[]): AMain(argc, argv, "MainClass") {

}

MainClass::~MainClass() {

}


ArgParser::parser MainClass::setupArgParser() const {
    return ArgParser::parser {{
                                      { "help", {"-h", "--help"}, "Shows this help message.\n", 0},
                                      { "dataset", {"-d", "--dataset"}, KRED + "[required]" + KNRM + " Specify the path to the data set.\n", 1}
                              }};
}

bool MainClass::Run(ArgParser::parser_results const &args) {

    if (!this->checkArgument(args)) {
        return false;
    }

    Neural::NetworkTrainer trainer(args["dataset"].as<std::string>());
    Neural::Network network(trainer.getTopology());

    network.train(trainer);
    std::cout << network;
    //network.saveTo("./samples_save/or_gate.txt");

    //Neural::Network network2(std::vector<unsigned> {});
    //network2.loadFrom("./samples_save/or_gate.txt");

    return true;
}

bool MainClass::checkArgument(ArgParser::parser_results const &args) const {
    if (args["help"]) {
        ArgParser::fmt_ostream(std::cerr) << "Usage:" << std::endl << this->setupArgParser();
        return false;
    }

    if (!args["dataset"]) {
        ArgParser::fmt_ostream(std::cerr) << KRED + "\nYou must provide a path to a data set using -d or --dataset\n" + KNRM << std::endl << this->setupArgParser();
        return false;
    }

    return true;
}
