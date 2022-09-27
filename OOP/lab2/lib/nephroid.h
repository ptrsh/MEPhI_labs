#include <iostream>
#include <string>

#ifndef NEPHROID_H
#define NEPHROID_H

class Nephroid {
 private:
    double radius = 0.0;

 public:
    class InvalidRadiusException : std::exception {};
    class InvalidParameterException : std::exception {};

    void setRadius(double radius);
    double getRadiusOfCurvature(double t) const;
    double getArea() const;
    double getLength() const;
    std::string getXY(double t) const;
    std::string getEquation() const;

    friend std::istream &operator>>(std::istream &input, Nephroid &nephroid);
};

#endif

