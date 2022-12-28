#include <gtest/gtest.h>

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

#define SenS "SENIOR"
#define JunS "JUNIOR"

struct Mark {
    std::string discipline{};
    int mark;
};


/*
* @class Student
*
* Base class
*/
class Student {
protected:
    std::string surname{};
    std::string initials{};
    int marksNumberMax{};
    int marksNumberNow{};
    std::vector<Mark> Marks;
    std::string typeStudent{};
public:
    Student(std::string inpSurname = "Noname", std::string inpInitials = "Noname");
    std::vector<Mark>& getMarks();
    std::string getSurname();
    std::string getInitials();
    std::string getFullName();
    int getMarksNumberMax();
    int getMarksNumberNow();
    int getNumberEmptyMarks();
    bool isThereDiscipline(std::string inDiscipline);

    void setSurname(std::string inpSurname);
    void setInitials(std::string inpInitials);
    void setMarksNumberMax(int inpNumber);
    void setTypeStudent(std::string inpInitials);
    void insertMark(Mark inpMark);
    void insertMarksVector(std::vector<Mark> inMarks);

    virtual std::string getTypeStudent(); 
    virtual std::string getTopicERW();
    virtual std::string getPlaceERW();
    virtual int getMarkERW();
    virtual void setTopicERW(std::string inpInitials);
    virtual void setPlaceERW(std::string inp);
    virtual void setMarkERW(int);
    virtual void clearMarks();

    FRIEND_TEST(Student, AddMarks);
};

#endif 
