#ifndef SENIORSTUDENT_H
#define SENIORSTUDENT_H

#include "student.h"


/*
* @class SeniorStudent
*
* Derived from Student class
*/
class SeniorStudent: public Student {
protected:
	std::string topicERW{};
	std::string placeERW{};
	int markERW{};
public:
	SeniorStudent(std::string inpSurname = "", std::string inpInitials = "");
	
	std::string getTopicERW() override;
	std::string getPlaceERW() override;
	int getMarkERW() override;
	void setTopicERW(std::string) override;
	void setPlaceERW(std::string) override;
	void setMarkERW(int) override;
    void clearMarks() override;

};

#endif 
