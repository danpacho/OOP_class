#ifndef database_hpp
#define database_hpp

#include <stdio.h>

#include <fstream>
#include <string>
#include <vector>

#include "logger.hpp"

using namespace std;

class Database {
 public:
  Database(Logger& logger, const string& _id, const string& _extension);
  ~Database();

  static string format;
  string filePath;

  string read();
  void write(string data);
  void reset();
  void destroy();
  void print();

 private:
  string id;
  string extension;

  string originalData;
  ofstream writer;
  ifstream reader;

  int readCount;
  int writeCount;

  Logger logger;

  bool isInitialized;
  void initialize();
  string getCurrentTime();
};

#endif /* database_hpp */
