#include "logger.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

Logger::Logger(const bool _autoEnter): autoEnter(_autoEnter) {};

void Logger::log(string message){
    if(autoEnter) {
        cout << message << endl;
    } else {
        cout << message;
    }
};

void Logger::logOptions(Options& options) {
    for (int i = 0; i < options.size(); i++) {
        const int listNumber = i + 1;
        cout << listNumber << ". " << options[i] << endl;
    }
};

void Logger::header(string heading, string subHeading){
    cout << "[ " << heading << " ]: " << right << subHeading << endl;
};

void Logger::tab() {
    cout << "   ";
};

void Logger::enter() {
    cout << "\n";
};

void Logger::prettify(int logSpace) {
    setw(logSpace);
    setfill("");
}


