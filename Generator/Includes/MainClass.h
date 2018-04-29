/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:15:33
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 17:54:39
 */


#ifndef MAINCLASS_H_
#define MAINCLASS_H_

#include "AMain.h"

class MainClass : public AMain {

public:
    MainClass(int argc, char *argv[]);
    virtual ~MainClass();

protected:
    virtual ArgParser::parser setupArgParser() const;
    virtual bool Run(ArgParser::parser_results const &args);

private:
    bool checkArgument(ArgParser::parser_results const &args) const;
    void generator_and(int count) const;
    void generator_or(int count) const;
    void generator_xor(int count) const;

private:
    std::map <std::string, std::function<void(int count)>> _generators;

};


#endif /*MAINCLASS_H_*/
