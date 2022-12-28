
#include <functional>
#include "groupTable.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class App {
 private:
    bool active = false;

    std::vector<std::function<void(void)>> controllers;
    GroupsTable groupsTable;

    void printMenu() const;
    void exit();
    
    void ShowGroups();
    void ShowGroup();
    void AddGroup();
    void AddStudent();
    void AddMark();
    void EnterERW();
    void ShowERW();
    void GetAverageMark();
    void TransferGroup();

 public:
    App();
    void start();
};

#endif
