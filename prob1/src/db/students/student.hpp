#ifndef student_hpp
#define student_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Student {
public:
    using Id = unsigned long int;

    Student(string& _name, string& _department, Id _id, unsigned int _birthYear, Id _telephone);
    Student(string& _name, string& _department, string& _id, string& _birthYear, string& _telephone);
    string name;
    string department;
    Id id;
    unsigned int birthYear;
    Id telephone;
    
    static bool isValidId(string& targetId);
    static bool isValidBirthYear(string& targetBirthYear);
    static bool isValidTelephone(string& targetTelephone);
    static string getAdmissionYearById(Id& id);
};

#endif /* student_hpp */
