#include "database.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "logger.hpp"

using namespace std;

Database::Database(Logger& _logger, const string& _id, const string& _extension)
    : logger(_logger),
      id(_id),
      extension(_extension),
      isInitialized(false),
      readCount(0),
      writeCount(0) {
  string _filePath = _id + "." + _extension;
  filePath = _filePath;

  initialize();
};

void Database::initialize() {
  reader.open(filePath);
  bool isFileExist = reader.is_open();

  if (isFileExist) {
    originalData = read();  // save data
  } else {
    writer.open(filePath);  // initialize data
    writer.close();
  }

  isInitialized = true;
  logger.header("INITIALIZED", "Reading " + filePath +
                                   " is successfully initialized " +
                                   getCurrentTime());
}

string Database::read() {
  readCount += 1;

  if (isInitialized)
    logger.header("READ",
                  "Read<" + to_string(readCount) + "> " + getCurrentTime());

  bool isReaderClosed = !reader.is_open();
  if (isReaderClosed) {
    reader.open(filePath);
  }
  string prevContents;
  string line;
  while (std::getline(reader, line)) {
    if (reader.eof()) {
      prevContents += line;
    } else {
      prevContents += line + '\n';
    }
  }

  // Remove the trailing newline character if it's present
  if (!prevContents.empty() && prevContents.back() == '\n') {
    prevContents.pop_back();
  }

  reader.close();
  return prevContents;
};

void Database::write(string data) {
  try {
    writeCount += 1;

    writer.open(filePath);
    string saveTarget;
    bool isDbEmpty = originalData == "";

    if (isDbEmpty) {
      saveTarget = data;
    } else {
      saveTarget = originalData + '\n' + data;
    }

    writer << saveTarget;

    if (writer.fail()) {
      logger.header("WRITE_ERROR", "Writing failed " + getCurrentTime());
    } else {
      logger.header("WRITE",
                    "write<" + to_string(writeCount) + "> " + getCurrentTime());
    }

    originalData = saveTarget;
    writer.clear();
    writer.close();
  } catch (const std::bad_alloc& e) {
    logger.header("DISK_CAPACITY_ERROR",
                  "Disk capacity is full, make sure you have empty space to "
                  "store data.\n");
    cout << e.what() << endl;
  } catch (const std::exception& e) {
    logger.header("WRITE_ERROR",
                  "Unknown writing error occured. Read message below.");
    cout << e.what() << endl;
  }
}

void Database::reset() {
  originalData = "";
  write("");
  logger.header("RESET", "Reset completed " + getCurrentTime());
  destroy();
}

void Database::destroy() {
  reader.clear();
  reader.close();

  writer.clear();
  writer.close();
}

Database::~Database() { destroy(); }

void Database::print() {
  string currentData = read();
  logger.header("PRINT", "current " + filePath + " state " + getCurrentTime());
  logger.log(currentData);
}

string Database::getCurrentTime() {
  std::time_t currentTime = time(nullptr);
  std::tm* localTime = localtime(&currentTime);

  if (localTime == nullptr) {
    return "can't get current time";
  }

  stringstream timeString;
  timeString << put_time(localTime, "%Y-%m-%d %H:%M:%S");
  return "@" + timeString.str();
}
