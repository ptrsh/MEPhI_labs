#include <iostream>
#include <algorithm>
#include <string>
#include "student.h"
#define NODATA "No data"
#define NODATA_NUM 0

using namespace std;

Student::Student(string inpSurname, string inpInitials)
        : surname(inpSurname), initials(inpInitials), marksNumberNow(0) {
    vector<Mark> ptrMarks{};
}

string Student::getSurname() {return surname;}
string Student::getInitials() {return initials;}
string Student::getFullName() {return string (surname + " " + initials);}
int Student::getMarksNumberMax() {return marksNumberMax;}
int Student::getMarksNumberNow() {return marksNumberNow;}
vector<Mark>& Student::getMarks() {return Marks;}
string Student::getTypeStudent() {return typeStudent;}
string Student::getTopicERW() {return NODATA;}
string Student::getPlaceERW() {return NODATA;}
int Student::getMarkERW() {return NODATA_NUM;}
bool Student::isThereDiscipline(std::string inDiscipline) {
    for (int i = 0; i < marksNumberNow; ++i) {
        if (Marks[i].discipline == inDiscipline) return true;
    }
    return false;
}
int Student::getNumberEmptyMarks() {
    int res = 0;
    for (int i = 0; i < marksNumberNow; ++i) {
        if (Marks[i].mark == 0) ++res;
    }
    return res;
}

void Student::setSurname(string inpSurname) {surname = inpSurname;}
void Student::setInitials(string inpInitials) {initials = inpInitials;}
void Student::setMarksNumberMax(int inpNumber) {marksNumberMax = inpNumber;}
void Student::setTypeStudent(std::string inpType) {typeStudent = inpType;}
void Student::setTopicERW(string inp) {}
void Student::setPlaceERW(string inp) {}
void Student::setMarkERW(int inp) {}

bool compMarks(Mark a, Mark b) {
    int res = a.discipline.compare(b.discipline);
    if (res < 0) return true;
    else return false;
}
void Student::insertMark(Mark inpMark) {
    for (int i = 0; i < marksNumberNow; ++i) {
        if (inpMark.discipline == Marks[i].discipline) {
            Marks[i].mark = inpMark.mark;
            return;
        }
    }
    if (marksNumberNow < marksNumberMax) {
        Marks.push_back(inpMark);
        ++marksNumberNow;
        sort(Marks.begin(), Marks.end(), compMarks);
    }
}
void Student::insertMarksVector(std::vector<Mark> inMarks) {Marks = inMarks; marksNumberNow = inMarks.size();}

void Student::clearMarks() {
    marksNumberNow = 0;
    vector<Mark> newMarks;
    Marks = newMarks;
}