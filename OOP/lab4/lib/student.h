#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#include "container.h"
#define SenS "SENIOR"
#define JunS "JUNIOR"

struct Mark {
    std::string discipline{};
    int mark;
};

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
    std::string getSurname();
    std::string getInitials();
    std::string getFullName();
    int getMarksNumberMax();
    int getMarksNumberNow();
    std::vector<Mark>& getMarks();
    std::string getTypeStudent(); //virtual
    virtual std::string getTopicERW();
    virtual std::string getPlaceERW();
    virtual int getMarkERW();
    bool isThereDiscipline(std::string inDiscipline);
    int getNumberEmptyMarks();

    void setSurname(std::string);
    void setInitials(std::string);
    void setMarksNumberMax(int);
    void setTypeStudent(std::string);
    void insertMark(Mark);
    void insertMarksVector(std::vector<Mark> inMarks);
    virtual void setTopicERW(std::string);
    virtual void setPlaceERW(std::string);
    virtual void setMarkERW(int);

    virtual void clearMarks();
};

#endif //STUDENT_H
