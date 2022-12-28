#include <iostream>
#include <algorithm>
#include <vector>

#include "group.h"

using namespace std;

bool compPtrStudents(Student* a, Student* b) {
    int res = (*a).getSurname().compare((*b).getSurname());
    if (res < 0) return true;
    else return false;
}

int Group::getIndexGroup() {return indexGroup;}

int Group::getMarksNumberMax() {return marksNumberMax;}

string Group::getTypeStudents() {return typeStudents;}

int Group::getSize() {return ptrStudents.size();}

bool Group::isStudentInGroup(const std::string& inSurname) {
    for (int i = 0; i < ptrStudents.size(); ++i) {
        if (ptrStudents[i]->getSurname() == inSurname)
            return true;
    }
    return false;
}

Student& Group::getStudentBySurname(const std::string& inSurname) {
    for (int i = 0; i < ptrStudents.size(); ++i) {
        if (ptrStudents[i]->getSurname() == inSurname)
            return *(ptrStudents[i]);
    }
}

Student& Group::getStudentByPos(int pos) {return *(ptrStudents[pos]);}
int Group::getStudentPos (const std::string& inSurname) {
    for (int i = 0; i < ptrStudents.size(); ++i)
        if (ptrStudents[i]->getSurname() == inSurname) return i;
    throw Group::UnknownStudentException();
    return -1;
}

void Group::addStudent(Student* ptrStudent) {
    ptrStudents.push_back(ptrStudent);
    sort(ptrStudents.begin(), ptrStudents.end(), compPtrStudents);
}

void Group::showGroup() {
    if (ptrStudents.size() == 0) return;
    vector<Student*>::const_iterator it{ptrStudents.begin()};

    while (it != ptrStudents.end()) {
        if (it == ptrStudents.begin()) {
            cout << "Name      ";
            for (int i = 0; i < (**it).getMarksNumberNow(); ++i)
                cout << (**it).getMarks()[i].discipline << "  ";
            if (typeStudents == SenS) cout << "ERW";
            cout << endl;
        }

        cout << (*it)->getFullName() << "  ";

        vector<Mark>::const_iterator markIt;
        markIt = (*it)->getMarks().cbegin();
        while (markIt != (*it)->getMarks().end()) {
            cout  << (*markIt).mark << "     ";
            ++markIt;
        }
        if (typeStudents == SenS) cout << (*it)->getMarkERW();
        cout << endl;
        ++it;
    }

}

void Group::setGroupIndex (int id) {
    indexGroup = id;
}
void Group::setGroupMaxNumberMarks (int num) {
    marksNumberMax = num;
}
void Group::setTypeStudents (std::string in) {
    typeStudents = in;
}

float Group::getAverageMark() {
    float res = 0;
    float number = 0;
    for (int i = 0; i < ptrStudents.size(); ++i) {
        vector<Mark>::iterator it;
        vector<Mark> marks = ptrStudents[i]->getMarks();
        it = marks.begin();
        while (it != marks.end()) {
            res += it->mark;
            ++number;
            ++it;
        }
        if (typeStudents == SenS) {
            res += ptrStudents[i]->getMarkERW();
            ++number;
        }
    }
    return res/number;
}
