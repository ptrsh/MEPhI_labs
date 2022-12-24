
#include <iostream>
#include "student.h"
#include "seniorStudent.h"
#include "juniorStudent.h"
#include "group.h"
#include "groupTable.h"
#include "container.h"

#include <functional>

#ifndef APPLICATION_H
#define APPLICATION_H


void ignoreLine ();
int scan (const char *msgs[], int N);

class App {
    private:
        bool active = false;
    public:
        App() = default;
        void start();

};


#endif