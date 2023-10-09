//
//  terminal_io.hpp
//  proj2
//
//  Created by 장준성 on 10/3/23.
//

#ifndef input_hpp
#define input_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <functional>

#include "logger.hpp"

using namespace std;

class CliInput {
public:
    explicit CliInput(const Logger &logger);
    
    unsigned int getOption(Logger::Options &options);
    
    string getInput(string message, const function<bool(string&)>& getCondition);
    
private:
    Logger logger;
};

#endif
