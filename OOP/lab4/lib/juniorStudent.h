#ifndef JUNIORSTUDENT_H
#define JUNIORSTUDENT_H

#include "student.h"

/*
* @class JuniorStudent
*
* Derived from Student class
*/
class JuniorStudent : public Student {
 public:
     JuniorStudent(std::string inpSurname = "", std::string inpInitials = "") : Student(inpSurname, inpInitials) {};
};

#endif 
