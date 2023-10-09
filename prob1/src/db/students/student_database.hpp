#ifndef student_database_hpp
#define student_database_hpp

#include <stdio.h>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "database.hpp"
#include "logger.hpp"
#include "student.hpp"

using namespace std;

class StudentDatabase : public Database {
 public:
  StudentDatabase(Logger &_logger, const string &_id, const string &_extension);

  void addStudent(Student &newStudent);

  enum SearchOption {
    s_name,
    s_id,
    s_admissionYear,
    s_department,
    s_all,
  };
  void searchStudent(SearchOption option, string queryString);

  enum SortOption { t_name, t_id, t_admissionYear, t_department };
  void sortStudents(SortOption option);

  void logAllStudents();

 private:
  vector<Student> students;
  SortOption sortingOption;
  string sortingOptionLabel;

  Student transformRawDbStringToStudent(string &studentString);
  string transformStudentToRawDbString(Student &student);
  Logger logger;

  void loadStudentsFromDB();
  void saveStudents();

  vector<Student> findStudentBy(function<bool(Student)> queryFilter);

  void logStudent(Student &student);
  void logStudents(vector<Student> &students);
};

#endif
