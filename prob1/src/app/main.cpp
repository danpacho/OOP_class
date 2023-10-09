
#include <iostream>
#include <vector>
#include <string>

#include "logger.hpp"
#include "input.hpp"
#include "student_database.hpp"
#include "helper.hpp"

using namespace std;
using namespace helper;

bool isPositive(string &input) {
   return input.size() > 10;
};

class StudentManager {
public:
    StudentManager(const string& _id, const string& _extension): logger(true), input(logger), db(logger, _id, _extension) {}
    
    void start() {
        mainMenuMode();
    };
    
private:
    Logger logger;
    CliInput input;
    StudentDatabase db;
    
    static bool isValidInputString(string& input) {
        return Sizer::isInRange(input, 2, 15);
    }
    void mainMenuMode() {
        Logger::Options mainOptions = {
            "Insertion",
            "Search",
            "SortingOption",
            "Exit"
        };
        int selectedMode = input.getOption(mainOptions);
        
        switch (selectedMode) {
            case 1:
                insertStudentMode();
                break;
            case 2:
                searchStudentsMode();
                break;
            case 3:
                sortStudentsMode();
                break;
            case 4:
                exitMode();
                break;
            default:
                break;
        }
    };
    
    void insertStudentMode() {
        string name = input.getInput("Name ?", isValidInputString);
        string id = input.getInput("Student ID (10 digits) ?", Student::isValidId);
        string birthYear = input.getInput("Birth Year (4 digits) ?", Student::isValidBirthYear);
        string department = input.getInput("Department ?", isValidInputString);
        string telephone = input.getInput("Tel ?", Student::isValidTelephone);
    
        Student newStudent(name, department, id, birthYear, telephone);
        
        db.addStudent(newStudent);
        
        mainMenuMode();
    };
    
    void searchStudentsMode() {
        Logger::Options searchOptions = {
            "Search by name",
            "Search by student ID (10 numbers)",
            "Search by admission year (4 numbers)",
            "Search by department name",
            "List All"
        };
        int selectedMode = input.getOption(searchOptions);

        switch (selectedMode) {
            case 1: {
                string queryString = input.getInput("Search name value", isValidInputString);
                db.searchStudent(StudentDatabase::SearchOption::s_name, queryString);
                break;
            }
            case 2: {
                string queryString = input.getInput("Search department name keyword", Student::isValidId);
                db.searchStudent(StudentDatabase::SearchOption::s_id, queryString);
                break;
            }
            case 3: {
                string queryString = input.getInput("Search admission year", Student::isValidBirthYear);
                db.searchStudent(StudentDatabase::SearchOption::s_admissionYear, queryString);
                break;
            }
            case 4: {
                string queryString = input.getInput("Search department", isValidInputString);
                db.searchStudent(StudentDatabase::SearchOption::s_department, queryString);
                break;
            }
            case 5: {
                db.searchStudent(StudentDatabase::SearchOption::s_all, "");
                break;
            }
            default:
                break;
        }
        
        mainMenuMode(); // back to main menu
    };
    void sortStudentsMode() {
        Logger::Options sortingOptions = {
            "Sort by Name",
            "Sort by Student ID",
            "Sort by Admission Year",
            "Sort by Department name"
        };
        int selectedMode = input.getOption(sortingOptions);
        
        switch (selectedMode) {
            case 1:
                db.sortStudents(StudentDatabase::SortOption::t_name);
                break;
            case 2:
                db.sortStudents(StudentDatabase::SortOption::t_id);
                break;
            case 3:
                db.sortStudents(StudentDatabase::SortOption::t_admissionYear);
                break;
            case 4:
                db.sortStudents(StudentDatabase::SortOption::t_department);
                break;
            default:
                break;
        }
        
        mainMenuMode();
    };
    
    int exitMode() {
        logger.log("Student manager is over.");
        return 0;
    };
};

int main(int argc, char** argv) {
    string dbSource = argv[1];
    string dbId = String::split(dbSource, '.')[0];
    cout << "Selected DB: " << dbId << endl;
    
    StudentManager app(dbId, "txt");
    app.start();
    
    return 0;
}
