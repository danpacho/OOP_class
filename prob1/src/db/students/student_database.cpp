#include "student_database.hpp"

#include <stdio.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "logger.hpp"
#include "student.hpp"

using namespace std;
using namespace helper;

StudentDatabase::StudentDatabase(Logger& _logger, const string& _id,
                                 const string& _extension)
    : Database(logger, _id, _extension),
      students({}),
      logger(_logger),
      sortingOptionLabel("name - alphabatically") {
  loadStudentsFromDB();
};

Student StudentDatabase::transformRawDbStringToStudent(string& studentString) {
  vector<string> splitted = String::split(studentString, '|');

  string name = splitted[0];
  string id = splitted[1];
  string department = splitted[2];
  string birthYear = splitted[3];
  string telephone = splitted[4];

  return Student(name, department, id, birthYear, telephone);
};

string StudentDatabase::transformStudentToRawDbString(Student& student) {
  vector<string> studentVector = {
      student.name, to_string(student.id), student.department,
      to_string(student.birthYear), to_string(student.telephone)};

  const string JOIN_SPACE = "|";
  return String::join(studentVector, JOIN_SPACE);
};

void StudentDatabase::addStudent(Student& newStudent) {
  string newStudentRaw = transformStudentToRawDbString(newStudent);
  string newStudentId = to_string(newStudent.id);

  auto isDuplicated = [newStudentId](Student target) -> bool {
    string id = to_string(target.id);
    return id == newStudentId;
  };

  bool isDuplicatedId = findStudentBy(isDuplicated).size() >= 1;
  if (isDuplicatedId) {
    logger.log("Error: " + newStudentId + " is already inserted.");
    return;
  }

  write(newStudentRaw);
  this->students.push_back(newStudent);
  sortStudents(sortingOption);
  logger.log(newStudentId + " is added");
}

vector<Student> StudentDatabase::findStudentBy(
    function<bool(Student)> queryFilter) {
  vector<Student> queriedStudents;
  for (int i = 0; i < students.size(); i++) {
    Student target = students[i];
    bool isTarget = queryFilter(target);
    if (isTarget) queriedStudents.push_back(target);
  }
  return queriedStudents;
}

void StudentDatabase::searchStudent(SearchOption option, string queryString) {
  auto logMatchedStudent = [this,
                            queryString](vector<Student> matched) -> void {
    if (matched.size() == 0) {
      cout << "can't find student." << endl;
      return;
    }

    string resultLog = "query: <" + queryString + "> matched student found.";
    logger.enter();
    logger.log(resultLog);

    this->sortStudents(this->sortingOption);
    this->logStudents(matched);
  };

  switch (option) {
    case SearchOption::s_name: {
      auto findByName = [&queryString](Student target) -> bool {
        return String::includes(target.name, queryString);
      };
      logMatchedStudent(findStudentBy(findByName));

      return;
    }
    case SearchOption::s_id: {
      auto findById = [&queryString](Student target) -> bool {
        string id = to_string(target.id);
        return queryString == id;
      };
      logMatchedStudent(findStudentBy(findById));

      return;
    }
    case SearchOption::s_admissionYear: {
      auto findByAdmissionYear = [&queryString](Student target) -> bool {
        string year = Student::getAdmissionYearById(target.id);
        return queryString == year;
      };
      logMatchedStudent(findStudentBy(findByAdmissionYear));

      return;
    }
    case SearchOption::s_department: {
      auto findByDepartment = [&queryString](Student target) -> bool {
        return String::includes(target.department, queryString);
      };
      logMatchedStudent(findStudentBy(findByDepartment));

      return;
    }
    case SearchOption::s_all: {
      logAllStudents();
      return;
    }
    default:
      return;
  }
}

void StudentDatabase::sortStudents(SortOption option) {
  switch (option) {
    case SortOption::t_name: {
      auto sortByName = [](const Student& a, const Student& b) -> bool {
        return a.name < b.name;
      };
      sort(students.begin(), students.end(), sortByName);
      sortingOption = SortOption::t_name;
      sortingOptionLabel = "name - alphabetically";
      return;
    };
    case SortOption::t_id: {
      auto sortById = [](const Student& a, const Student& b) -> bool {
        return a.id > b.id;
      };
      sort(students.begin(), students.end(), sortById);
      sortingOption = SortOption::t_id;
      sortingOptionLabel = "id - descending";
      return;
    };
    case SortOption::t_department: {
      auto sortByDepartment = [](const Student& a, const Student& b) -> bool {
        return a.department < b.department;
      };
      sort(students.begin(), students.end(), sortByDepartment);
      sortingOption = SortOption::t_department;
      sortingOptionLabel = "department - alphabetically";
      return;
    };
    case SortOption::t_admissionYear: {
      auto sortByAdmissionYear = [](Student& a, Student& b) -> bool {
        return Student::getAdmissionYearById(a.id) >
               Student::getAdmissionYearById(b.id);
      };
      sort(students.begin(), students.end(), sortByAdmissionYear);
      sortingOption = SortOption::t_admissionYear;
      sortingOptionLabel = "admission year - descending";
      return;
    };

    default:
      break;
  }

  saveStudents();  // save sorted students to DB
}

void StudentDatabase::saveStudents() {
  reset();  // reset db;

  string studentsRaw;
  size_t studentsSize = students.size();

  for (int i = 0; i < studentsSize; i++) {
    studentsRaw += transformStudentToRawDbString(students[i]);
  }
  write(studentsRaw);
}

void StudentDatabase::loadStudentsFromDB() {
  string dbStudents = read();
  vector<string> studentsString = String::split(dbStudents, '\n');

  vector<Student> loadedStudents;
  for (int i = 0; i < studentsString.size(); i++) {
    Student student = transformRawDbStringToStudent(studentsString[i]);
    loadedStudents.push_back(student);
  }

  this->students = loadedStudents;
  sortStudents(SortOption::t_name);
}

void StudentDatabase::logStudent(Student& student) {
  cout << setw(20) << left << student.name << setw(10) << student.id << setw(20)
       << right << student.department << setw(10) << right << student.birthYear
       << setw(15) << student.telephone << endl;
}

void StudentDatabase::logStudents(vector<Student>& students) {
  logger.enter();
  logger.header("STUDENT TABLE", "data stored at " + filePath);

  cout << setw(20) << left << "Name" << setw(10) << right << "StudentID"
       << setw(20) << "Department" << setw(10) << right << "BirthYear"
       << setw(15) << "Tel" << endl;

  for (int i = 0; i < students.size(); i++) {
    logStudent(students[i]);
  }

  string endLogger = "TOTAL " + to_string(students.size()) + " STUDENTS";
  string showSortingOption = "sorting option, " + sortingOptionLabel;
  logger.header(endLogger, showSortingOption);
  logger.enter();
}

void StudentDatabase::logAllStudents() { logStudents(students); }
