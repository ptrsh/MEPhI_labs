#include "app.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;



void ignoreLine () {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
int scan (const char *msgs[], int N) {
    const char *errmsg = "";
    int i, n;

    do {
        cout << errmsg << endl;
        errmsg = "You are wrong. Repeate, please!";

        for (i = 0; i < N; ++i)
            cout << (msgs[i]) << endl;;
        cout << "Make your choice: --> ";
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            ignoreLine();
            n = -1;
        }

    } while (n < 0 || n >= N);
    ignoreLine();
    return n;
}

int enterId () {
    const char *errmsg = "";
    int choice = -1;
    do {
        if (errmsg != "")
            cout << errmsg << endl;
        errmsg = "You are wrong. Repeate, please!";

        cout << "Enter group's id: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            ignoreLine();
            choice = -1;
        }
    } while (choice < 0);
    return choice;
}
string enterTypeStudents () {
    const char *errmsg = "";
    int choice = -1;
    do {
        if (errmsg != "")
            cout << errmsg << endl;
        errmsg = "You are wrong. Repeate, please!";

        cout << "Enter type of students:\n0. Juniors\n1. Seniors\n";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            ignoreLine();
            choice = -1;
        }
    } while (choice < 0 || choice > 1);
    if (choice == 0) return JunS;
    else return SenS;
}
int enterMaxMarksNumber () {
    const char *errmsg = "";
    int choice = 0;
    do {
        cout << errmsg << endl;
        errmsg = "You are wrong. Repeate, please!";

        cout << "Enter max number of marks: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            ignoreLine();
        }
    } while (choice <= 0);
    return choice;
}
Mark& enterMark(vector<Mark> inMarks) {
    const char *errmsg = "";
    std::string choice{};
    for (int i = 0; i < inMarks.size(); ++i) cout << inMarks[i].discipline << ": " << inMarks[i].mark << endl;
    do {
        cout << errmsg << endl;
        errmsg = "You are wrong. Repeate, please!";
        cout << "Enter discipline: ";

        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            ignoreLine();
        }
    } while (choice.empty());

    errmsg = "";
    int choiceMark = 0;
    do {
        cout << errmsg << endl;
        errmsg = "You are wrong. Repeate, please!";

        cout << "Enter mark: ";
        cin >> choiceMark;
        if (cin.fail()) {
            cin.clear();
            ignoreLine();
        }
    } while (choiceMark <= 0);

    Mark* ptrRes = new Mark;
    ptrRes->discipline = choice;
    ptrRes->mark = choiceMark;
    return *ptrRes;
}
int enterMarkERW() {
    const char *errmsg = "";
    int choice = -1;
    do {
        cout << errmsg << endl;
        errmsg = "You are wrong. Repeate, please!";

        cout << "Enter ERW mark: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            ignoreLine();
            choice = -1;
        }
    } while (choice < 0);
    return choice;
}
string enterString (const string& message) {
    const char *errmsg = "";
    std::string res{};

    do {
        cout << errmsg << endl;
        errmsg = "You are wrong. Repeate, please!";

        cout << "Enter " << message << ": ";
        cin >> res;
        if (cin.fail()) {
            cin.clear();
            ignoreLine();
        }
    } while (res.empty());
    return res;
}
int enterChangeType() {
    const char *errmsg = "";
    int choice = -1;
    do {
        cout << errmsg << endl;
        errmsg = "You are wrong. Repeate, please!";

        cout << "Change type of group?\n0. No\n1. Yes\n";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            ignoreLine();
            choice = -1;
        }
    } while (choice < 0 || choice > 1);
    return choice;
}



int showGroups_D (GroupsTable& groupsTable) {
    groupsTable.showGroups();
    return 1;
}
int showGroup_D (GroupsTable& groupsTable) {
    const char *errmsg = "";
    int choice = 0;
    do {
        if (errmsg != "")
            cout << errmsg << endl;
        errmsg = "You are wrong. Repeate, please!";

        groupsTable.showGroups();
        cout << "Enter group's id: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            ignoreLine();
        }
    } while (choice <= 0);
    ignoreLine();
    if (groupsTable.findGroupInTable(choice) == -1) cout << "No such group exists\n";
    else groupsTable.getGroupByID(choice).showGroup();
    return 1;
}

int addGroup_D (GroupsTable& groupsTable) {
    int inId = enterId();

    ignoreLine();
    if (groupsTable.findGroupInTable(inId) != -1)
        cout << "Group is already in table!\n";
    else {
        Group* inGroup = new Group;
        inGroup->setGroupIndex(inId);

        std::string inType = enterTypeStudents();
        inGroup->setTypeStudents(inType);

        int inMaxMarksNumber = enterMaxMarksNumber();
        inGroup->setGroupMaxNumberMarks(inMaxMarksNumber);

        groupsTable.addGroup(inGroup);
    }
    return 1;
}
int addStudent_D (GroupsTable& groupsTable) {
    groupsTable.showGroups();
    int inId = enterId();

    ignoreLine();
    if (groupsTable.findGroupInTable(inId) == -1)
        cout << "No such group exists!\n";
    else {
        Group& group = groupsTable.getGroupByID(inId);
        Student* student;
        if (group.getTypeStudents() == SenS) {
            SeniorStudent* whichStudent = new SeniorStudent;
            student = whichStudent;
        }
        else {
            JuniorStudent* whichStudent = new JuniorStudent;
            student = whichStudent;
        }

        student->setSurname(enterString("surname"));
        student->setInitials(enterString("initials"));
        student->setMarksNumberMax(group.getMarksNumberMax());
        student->setTypeStudent(group.getTypeStudents());

        if (group.getSize() != 0) {
            Student& filledStudent = group.getStudentByPos(0);
            vector<Mark> copiedMarks = filledStudent.getMarks();
            student->insertMarksVector(copiedMarks);

            for (int i = 0; i < student->getMarks().size(); ++i) {
                student->getMarks()[i].mark = 0;
            }
        }
        group.addStudent(student);
    }
    return 1;
}
int addMark_D (GroupsTable& groupsTable) {
    groupsTable.showGroups();
    int inId = enterId();

    ignoreLine();
    if (groupsTable.findGroupInTable(inId) == -1)
        cout << "No such group exists!\n";
    else {
        Group &group = groupsTable.getGroupByID(inId);
        for (int i = 0; i < group.getSize(); ++i) cout << group.getStudentByPos(i).getSurname() << endl;
        std::string inSurname = enterString("surname");
        if (group.isStudentInGroup(inSurname)) {
            Student &student = group.getStudentBySurname(inSurname);
            Mark inMark = enterMark(student.getMarks());
            student.insertMark(inMark);

            if (group.getSize() == 1) return 1;
            else {
                int anotherStudentPos = group.getStudentPos(student.getSurname()) + 1;
                if (anotherStudentPos >= group.getSize()) anotherStudentPos -= 2;

                if (!group.getStudentByPos(anotherStudentPos).isThereDiscipline(inMark.discipline)) {
                    Mark emptyMark = inMark;
                    emptyMark.mark = 0;
                    for (int i = 0; i < group.getSize(); ++i) {
                        if (i != group.getStudentPos(student.getSurname()))
                            group.getStudentByPos(i).insertMark(emptyMark);
                    }
                }
            }
        }
    }
    return 1;
}

int enterERW_D (GroupsTable& groupsTable) {
    groupsTable.showSeniorsGroups();
    int inId = enterId();

    ignoreLine();
    if (groupsTable.findGroupInTable(inId) == -1)
        cout << "No such group exists!\n";
    else if (groupsTable.getGroupByID(inId).getTypeStudents() == SenS) {
        Group &group = groupsTable.getGroupByID(inId);
        for (int i = 0; i < group.getSize(); ++i) cout << group.getStudentByPos(i).getSurname() << endl;
        std::string inSurname = enterString("surname");
        if (group.isStudentInGroup(inSurname)) {
            string inTopic = enterString("ERW topic");
            string inPlace = enterString("ERW place");
            int inMark = enterMarkERW();

            Student& student = group.getStudentBySurname(inSurname);
            student.setTopicERW(inTopic);
            student.setPlaceERW(inPlace);
            student.setMarkERW(inMark);
        }
    }
    return 1;
}
int showERW_D (GroupsTable& groupsTable) {
    groupsTable.showSeniorsGroups();
    int inId = enterId();

    ignoreLine();
    if (groupsTable.findGroupInTable(inId) == -1)
        cout << "No such group exists!\n";
    else if (groupsTable.getGroupByID(inId).getTypeStudents() == SenS) {
        Group& group = groupsTable.getGroupByID(inId);
        for (int i = 0; i < group.getSize(); ++i) cout << group.getStudentByPos(i).getSurname() << endl;
        std::string inSurname = enterString("surname");
        if (group.isStudentInGroup(inSurname)) {
            Student& student = group.getStudentBySurname(inSurname);
            cout << "Topic: " << student.getTopicERW() << endl;
            cout << "Place: " << student.getPlaceERW() << endl;
            cout << "Mark: " << student.getMarkERW() << endl;
        }
    }
    return 1;
}
int getAverageMark_D (GroupsTable& groupsTable) {
    groupsTable.showGroups();
    int inId = enterId();

    ignoreLine();
    if (groupsTable.findGroupInTable(inId) == -1)
        cout << "No such group exists!\n";
    else {
        Group& group = groupsTable.getGroupByID(inId);
        cout << group.getAverageMark();
    }
    return 1;
}
int transferGroup_D (GroupsTable& groupsTable) {
    groupsTable.showGroups();
    int inId = enterId();

    ignoreLine();
    if (groupsTable.findGroupInTable(inId) == -1)
        cout << "No such group exists!\n";
    else {
        Group& oldGroup = groupsTable.getGroupByID(inId);
        int changeTypeGroup = enterChangeType();
        int inMaxMarksNumber = enterMaxMarksNumber();
        if ((oldGroup.getTypeStudents() == JunS) && (changeTypeGroup == 1)) {
            Group *newGroup = new Group;
            newGroup->setGroupIndex(oldGroup.getIndexGroup());
            newGroup->setTypeStudents(SenS);
            newGroup->setGroupMaxNumberMarks(inMaxMarksNumber);

            for (int i = 0; i < oldGroup.getSize(); ++i) {
                Student *student = new SeniorStudent;
                student->setSurname(oldGroup.getStudentByPos(i).getSurname());
                student->setInitials(oldGroup.getStudentByPos(i).getInitials());
                student->setTypeStudent(SenS);
                student->setMarksNumberMax(inMaxMarksNumber);
                newGroup->addStudent(student);
            }
            groupsTable.replaceByNewGroup(inId, newGroup);
        }
        else {
            for (int i = 0; i < oldGroup.getSize(); ++i) {
                oldGroup.getStudentByPos(i).clearMarks();
                oldGroup.getStudentByPos(i).setMarksNumberMax(inMaxMarksNumber);
            }
        }
    }
    return 1;
}



void App::start() {
    active = true;
    int rc = 1;
    const char *msgs[] = {"0. Quit", "1. Show groups", "2. Show group", "3. Add group", "4. Add student",
                          "5. Add mark", "6. Enter ERW", "7. Show student's ERW",
                          "8. Get average mark", "9. Transfer group"
    };
    int (*fptr[])(GroupsTable &) = {NULL, showGroups_D, showGroup_D,
                                    addGroup_D, addStudent_D, addMark_D, enterERW_D, showERW_D,
                                    getAverageMark_D, transferGroup_D};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

    GroupsTable groupsTable{};
    while (active) {
        try {
            while (rc = scan(msgs, NMsgs)) {
                cout << "*********" << endl;
                if (!fptr[rc](groupsTable)) active = false;
            }
        } catch (const char *str) {
            cout << str << endl;
            while (rc = scan(msgs, NMsgs)) {
                cout << "*********" << endl;
                if (!fptr[rc](groupsTable)) active = false;
            }
        }
    }

}
