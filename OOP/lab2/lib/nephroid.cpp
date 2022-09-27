#include "nephroid.h"
#include <cmath>
#include <string>

#define PI 3.141592

void Nephroid::setRadius(double radius) {
    if (radius < 0) throw InvalidRadiusException();
    this -> radius = radius;
}

double Nephroid::getRadiusOfCurvature(double t) const { 
    if ((t < 0) || (t > 360)) throw InvalidParameterException();
    return abs(3 * radius * sin(t)); 
}

double Nephroid::getArea() const { return 12 * PI * pow(radius, 2.0); }

double Nephroid::getLength() const { return 24 * radius; }

std::string Nephroid::getEquation() const {
    std::string equation = "(x^2 + y^2 - " + \
    std::to_string(4 * pow(radius, 2.0)) + \
    ")^3 = " + std::to_string(108 * pow(radius, 4.0)) + \
    " * y^2";
    return equation;
}

std::string Nephroid::getXY(double t) const {
    if ((t < 0) || (t > 360)) throw InvalidParameterException();
    double x = 6 * radius * cos(t) - 4 * radius * pow(cos(t), 3.0);
    double y = 4 * radius * pow(sin(t), 3.0);
    return "x = " + std::to_string(x) + '\n' + \
    "y = " + std::to_string(y) + '\n';
}

