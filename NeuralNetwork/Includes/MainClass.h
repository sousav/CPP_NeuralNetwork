/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:15:33
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:08:23
 */


#ifndef MAINCLASS_H_
#define MAINCLASS_H_

#include "AMain.h"
#include "NetworkTrainer.hpp"
#include "Network.hpp"
#include "Layer.hpp"

#include <DataFrame/DataFrame.h>
typedef hmdf::StdDataFrame<unsigned long> PandasDF;

class MainClass : public AMain {

public:
    MainClass(int argc, char *argv[]);
    virtual ~MainClass();

protected:
    virtual ArgParser::parser setupArgParser() const;
    virtual bool Run(ArgParser::parser_results const &args);

private:
    bool checkArgument(ArgParser::parser_results const &args) const;

};


#endif /*MAINCLASS_H_*/
