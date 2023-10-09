#include "helper.hpp"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

using namespace helper;

Transformer::Int::Int(bool _success, int _value)
    : success(_success), value(_value){};
Transformer::Int Transformer::stringToInt(string& targetString) {
  try {
    int num = std::stoi(targetString);
    return {true, num};
  } catch (const invalid_argument& e) {
    cerr << "Can't transform " << targetString << "into int" << e.what()
         << endl;
    return {false, 0};
  } catch (const out_of_range& e) {
    cerr << "Out of range," << targetString << e.what() << endl;
    return {false, 0};
  }
};

Transformer::UnsignedInt::UnsignedInt(bool _success, unsigned int _value)
    : success(_success), value(_value){};
Transformer::UnsignedInt Transformer::stringToUnsignedInt(
    string& targetString) {
  try {
    unsigned int num = std::stoi(targetString);
    return {true, num};
  } catch (const invalid_argument& e) {
    cerr << "Can't transform " << targetString << "into int" << e.what()
         << endl;
    return {false, 0};
  } catch (const out_of_range& e) {
    cerr << "Out of range," << targetString << e.what() << endl;
    return {false, 0};
  }
}

Transformer::UnsignedLongInt::UnsignedLongInt(bool _success,
                                              unsigned long int _value)
    : success(_success), value(_value){};
Transformer::UnsignedLongInt Transformer::stringToUnsignedLongInt(
    string& targetString) {
  try {
    unsigned long int num = std::stoul(targetString);
    return {true, num};
  } catch (const invalid_argument& e) {
    cerr << "Can't transform " << targetString << "into int" << e.what()
         << endl;
    return {false, 0};
  } catch (const out_of_range& e) {
    cerr << "Out of range," << targetString << e.what() << endl;
    return {false, 0};
  }
}

vector<string> String::split(string& input, char splitterChar) {
  vector<string> tokens;
  istringstream iss(input);
  string token;

  while (getline(iss, token, splitterChar)) {
    tokens.push_back(token);
  }

  return tokens;
}

string String::join(vector<string>& strings, string joinString) {
  string result;

  for (size_t i = 0; i < strings.size(); ++i) {
    result += strings[i];

    if (i < strings.size() - 1) {
      result += joinString;
    }
  }

  return result;
}

bool String::includes(string& target, string& mightBeIncluded) {
  return target.find(mightBeIncluded) != std::string::npos;
}

bool Sizer::isFit(string& target, int expectedSize) {
  return target.size() == expectedSize;
};

bool Sizer::isInRange(string& target, int min, int max) {
  size_t size = target.size();
  if (size < min || size > max) return false;
  return true;
};

bool Validator::year(string& mightBeYear) {
  const int YEAR_DIGIT_COUNT = 4;
  if (!Sizer::isFit(mightBeYear, YEAR_DIGIT_COUNT)) return false;

  const int CURRENT_YEAR = 2023;
  Transformer::Int year = Transformer::stringToInt(mightBeYear);

  if (!year.success) return false;
  if (year.value > CURRENT_YEAR || year.value <= 0) return false;

  return true;
};
