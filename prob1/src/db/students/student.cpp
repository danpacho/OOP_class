#include "student.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "helper.hpp"

using namespace std;
using namespace helper;

Student::Student(string &_name, string &_department, Student::Id _id, unsigned int _birthYear, Student::Id _telephone)
        : name(_name),
          department(_department),
          id(_id),
          birthYear(_birthYear),
          telephone(_telephone){};

Student::Student(string &_name, string &_department, string &_id, string &_birthYear, string &_telephone): name(_name), department(_department) {
      bool isValidStudentString = Student::isValidId(_id) &&
                                  Student::isValidTelephone(_telephone) &&
                                  Student::isValidBirthYear(_birthYear);
      vector<string> studentInfo = {_name, _department, _id};
      if (!isValidStudentString)
        throw invalid_argument(String::join(studentInfo, " ") + "is not valid");

      id = Transformer::stringToUnsignedLongInt(_id).value;
      birthYear = Transformer::stringToUnsignedInt(_birthYear).value;
      telephone = Transformer::stringToUnsignedLongInt(_telephone).value;
}

bool Student::isValidId(string &targetId) {
    const int ID_DIGIT_COUNT = 10;
    if (!Sizer::isFit(targetId, ID_DIGIT_COUNT)) return false;

    string year = targetId.substr(0, 4);
    if (!Validator::year(year)) return false;

    return true;
};

bool Student::isValidBirthYear(string &targetBirthYear) {
    const int YEAR_DIGIT_COUNT = 4;
    if (!Sizer::isFit(targetBirthYear, YEAR_DIGIT_COUNT)) return false;

    return Validator::year(targetBirthYear);
}

bool Student::isValidTelephone(string &targetTelephone) {
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 12;

    Transformer::UnsignedLongInt isUnsignedLongInt = Transformer::stringToUnsignedLongInt(targetTelephone);
    if (!isUnsignedLongInt.success) return false;

    return Sizer::isInRange(targetTelephone, MIN_LENGTH, MAX_LENGTH);
}

string Student::getAdmissionYearById(Student::Id &id) {
    const int ADMISSION_DIGIT = 4;
    return to_string(id).substr(0, ADMISSION_DIGIT);
};
