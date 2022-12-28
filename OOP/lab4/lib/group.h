#ifndef GROUP_H
#define GROUP_H
#include "student.h"
#include "seniorStudent.h"
#include "juniorStudent.h"

class Group {
private:
    int indexGroup;
    int marksNumberMax;
    std::string typeStudents;
    std::vector<Student*> ptrStudents; 
public:
    class UnknownStudentException : std::exception {};
    Group() : indexGroup(0), marksNumberMax(0) {};
    int getIndexGroup();
    int getMarksNumberMax();
    std::string getTypeStudents();
    int getSize();
    void addStudent(Student*);
    void showGroup();
    float getAverageMark();
    bool isStudentInGroup(const std::string& inSurname);
    Student& getStudentBySurname(const std::string& inSurname);
    Student& getStudentByPos(int pos);
    int getStudentPos (const std::string& inSurname);

    void setGroupIndex (int id);
    void setGroupMaxNumberMarks (int num);
    void setTypeStudents (std::string in);

};

#endif 
