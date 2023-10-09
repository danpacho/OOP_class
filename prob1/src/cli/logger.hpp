//
//  logger.hpp
//  proj2
//
//  Created by 장준성 on 10/3/23.
//

#ifndef logger_hpp
#define logger_hpp

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Logger {
public:
    using Options = vector<string>;
    
    Logger(bool _autoEnter);
    
    void log(string message);
    void logOptions(Options& options);
    void header(string heading, string subHeading);
    void tab();
    void enter();
    void prettify(int logSpace);

    bool autoEnter;
};

#endif /* logger_hpp */
