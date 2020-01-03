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

    //PandasDF df;
    //df.read(args["dataset"].as<const char *>(), hmdf::io_format::csv);

    Neural::Network network;

    network
    << Neural::Layer(2)
    << Neural::Layer(4)
    << Neural::Layer(1);


    std::cout << network;

    Neural::NetworkTrainer trainer(args["dataset"].as<std::string>());
    network.train(trainer);

    network.errorPlot();

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
