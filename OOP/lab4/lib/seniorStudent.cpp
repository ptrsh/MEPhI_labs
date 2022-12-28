#include "seniorStudent.h"

SeniorStudent::SeniorStudent (std::string inpSurname, std::string inpInitials) : Student(inpSurname, inpInitials) {};
std::string SeniorStudent::getTopicERW() {return topicERW;}
std::string SeniorStudent::getPlaceERW() {return placeERW;}
int SeniorStudent::getMarkERW() {return markERW;}
void SeniorStudent::setTopicERW(std::string inpTopic) {topicERW = inpTopic;}
void SeniorStudent::setPlaceERW(std::string inpPlace) {placeERW = inpPlace;}
void SeniorStudent::setMarkERW(int inpMark) {markERW = inpMark;}

void SeniorStudent::clearMarks() {
    marksNumberNow = 0;
    std::vector<Mark> newMarks;
    Marks = newMarks;
    topicERW = "", placeERW = "";
    markERW = 0;

}