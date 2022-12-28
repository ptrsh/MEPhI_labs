#ifndef GROUPTABLE_H
#define GROUPTABLE_H
#include "group.h"

class GroupsTable {
private:
    std::vector<Group*> ptrGroups;
public:
    void addGroup(Group*);
    void showGroups();
    void showSeniorsGroups();
    int findGroupInTable(int id);
    Group& getGroupByPos(int pos);
    Group& getGroupByID(int id);
    void replaceByNewGroup(int id, Group* newGroup);
};

#endif 
