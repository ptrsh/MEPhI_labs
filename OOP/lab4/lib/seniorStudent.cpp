#include "seniorStudent.h"
#include <iostream>
using namespace std;

SeniorStudent::SeniorStudent (std::string inpSurname, std::string inpInitials) : Student(inpSurname, inpInitials) {};
string SeniorStudent::getTopicERW() {return topicERW;}
string SeniorStudent::getPlaceERW() {return placeERW;}
int SeniorStudent::getMarkERW() {return markERW;}

void SeniorStudent::setTopicERW(string inpTopic) {topicERW = inpTopic;}
void SeniorStudent::setPlaceERW(string inpPlace) {placeERW = inpPlace;}
void SeniorStudent::setMarkERW(int inpMark) {markERW = inpMark;}
void SeniorStudent::clearMarks() {
    marksNumberNow = 0;
    vector<Mark> newMarks;
    Marks = newMarks;
    string newTopicERW;
    string newPlaceERW;
    topicERW = newTopicERW, placeERW = newPlaceERW;
    markERW = 0;

}