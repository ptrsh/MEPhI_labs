#include "groupTable.h"
#include <iostream>
#include <vector>
#include <algorithm>

bool compPtrGroups(Group* a, Group* b) {
    if ((*a).getIndexGroup() < (*b).getIndexGroup()) return true;
    else return false;
}

void GroupsTable::showGroups() {
    for (int i = 0; i < ptrGroups.size(); ++i) {
        std::cout << ptrGroups[i]->getTypeStudents() << " " << "Group #" << ptrGroups[i]->getIndexGroup() << std::endl;
    }
}

void GroupsTable::showSeniorsGroups() {
    for (int i = 0; i < ptrGroups.size(); ++i) {
        if (ptrGroups[i]->getTypeStudents() == SenS)
            std::cout << ptrGroups[i]->getTypeStudents() << " " << "Group #" << ptrGroups[i]->getIndexGroup() << std::endl;
    }
}

int GroupsTable::findGroupInTable(int id) {
    for (int i = 0; i < ptrGroups.size(); ++i) {
        if (ptrGroups[i]->getIndexGroup() == id)
            return i;
    }
    return -1;
}

Group& GroupsTable::getGroupByPos(int pos) {
    return *(ptrGroups[pos]);
}

Group& GroupsTable::getGroupByID(int id) {
    return getGroupByPos(findGroupInTable(id));
}

void GroupsTable::addGroup(Group* inGroup) {
    ptrGroups.push_back(inGroup);
    std::sort(ptrGroups.begin(), ptrGroups.end(), compPtrGroups);
}

void GroupsTable::replaceByNewGroup(int id, Group* newGroup) {
    ptrGroups[findGroupInTable(id)] = newGroup;
}
