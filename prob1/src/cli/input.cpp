#include "input.hpp"
#include "logger.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

CliInput::CliInput(const Logger &logger): logger(logger) {};

unsigned int CliInput::getOption(Logger::Options &options){
    logger.logOptions(options);
    int selectedOption;
    cin >> selectedOption;
    
    const size_t numberOfOptions = options.size();
    bool isInValidOption = (selectedOption > numberOfOptions || selectedOption <= 0);
    while (isInValidOption) {
        string errorMessage = to_string(selectedOption) + " is not supported option. Please choose correct option.";
        logger.log(errorMessage);
        if(!logger.autoEnter) {
            logger.enter();
        }
        cin >> selectedOption;
        isInValidOption = (selectedOption > numberOfOptions || selectedOption <= 0);
    };
    
    string successMessage = options[selectedOption - 1] + " is selected.";
    logger.log(successMessage);
    if(!logger.autoEnter) {
        logger.enter();
    }
    return selectedOption;
};

string CliInput::getInput(string message, const function<bool(string&)>& getCondition) {
    logger.log(message);
    
    string input;
    
    bool isFirstInput = true;
    
    bool isValidInput = false;
    while (!isValidInput) {
        cin.clear();
        
        if(!isFirstInput) {
            string errorMessage = input + " is not valid. Please type correct value.";
            logger.log(errorMessage);
        }
        
        if(!logger.autoEnter) {
            logger.enter();
        }
        
        getline(cin, input);
        if(input != "") {
            isValidInput = getCondition(input);
            isFirstInput = false;
        }
    };
    
    string successMessage = input + " is recorded.";
    logger.log(successMessage);
    if(!logger.autoEnter) {
        logger.enter();
    }
    
    return input;
};

