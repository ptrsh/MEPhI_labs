#include <vector>
#include <functional>
#include "nephroid.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class App {
 private:
    bool active = false;

    std::vector<std::function<void(void)>> controllers;
    Nephroid nephroid;

    void printMenu() const;
    void exit();
    void setRadius();
    void getLength() const;
    void getRadiusOfCurvature() const;
    void getArea() const;
    void getXY() const;
    void getEquation() const;

 public:
    App();
    void start();
};

#endif

