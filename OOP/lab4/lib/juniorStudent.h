#ifndef JUNIORSTUDENT_H
#define JUNIORSTUDENT_H
#include "student.h"

class JuniorStudent : public Student {
public:
    JuniorStudent(std::string inpSurname = "", std::string inpInitials = "");
};

#endif //JUNIORSTUDENT_H
