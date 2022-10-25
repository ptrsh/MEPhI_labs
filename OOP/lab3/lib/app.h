#include <vector>
#include <functional>
#include "vector.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class App {
 private:
    bool active = false;

    std::vector<std::function<void(void)>> controllers;
    Vector vector;

    void printMenu() const;
    void exit();
    void getVector();
    void getNorm();
    void getAddition();
    void getSubstraction();
    void getMultiplication();
    void printVector() const;

 public:
    App();
    void start();
};



#endif