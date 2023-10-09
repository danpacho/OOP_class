#ifndef helper_hpp
#define helper_hpp

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace helper {
class Transformer {
 public:
  struct Int {
    bool success;
    int value;
    Int(bool _success, int _value);
  };
  struct UnsignedInt {
    bool success;
    unsigned int value;
    UnsignedInt(bool _success, unsigned int _value);
  };
  struct UnsignedLongInt {
    bool success;
    unsigned long int value;
    UnsignedLongInt(bool _success, unsigned long int _value);
  };

  static Int stringToInt(string &targetString);
  static UnsignedInt stringToUnsignedInt(string &targetString);
  static UnsignedLongInt stringToUnsignedLongInt(string &targetString);
};

class String {
 public:
  static vector<string> split(string &input, char splitterChar);
  static string join(vector<string> &strings, string joinChar);
  static bool includes(string &target, string &mightBeIncluded);
};

class Sizer {
 public:
  static bool isFit(string &target, int expectedSize);
  static bool isInRange(string &target, int min, int max);
};

class Validator {
 public:
  static bool year(string &target);
};
};  // namespace helper

#endif /* helper_hpp */
