#include <iostream>
#include "app.h"

using namespace std;

void handleInvalidInput(std::istream &input) {
    std::cout << "Invalid input! Try again!\n";
    input.clear();
    input.ignore(1024, '\n');
}

template<typename T>
T scan(std::istream &input, const std::string &message) {
    T value;
    bool fail;
    do {
        if (!message.empty()) std::cout << message << ": ";
        input >> value;
        if ((fail = input.fail())) handleInvalidInput(input);
    } while (fail);
    return value;

}

App::App() {
    controllers = {
        [this]() { ShowGroups(); },
        [this]() { ShowGroup(); },
        [this]() { AddGroup(); },
        [this]() { AddStudent(); },
        [this]() { AddMark(); },
        [this]() { EnterERW(); },
        [this]() { ShowERW(); },
        [this]() { GetAverageMark(); },
        [this]() { TransferGroup(); },
        [this]() { exit(); }
    };
        
}

void App::exit() { active = false; }

void App::start() {
    
    active = true;
    while (active) {
        printMenu();
        int command = scan<int>(std::cin, ":") - 1;
        if (command >= controllers.size()) {
            handleInvalidInput(std::cin);
        } else controllers[command]();
    }
}

Mark& enterMark(std::vector<Mark> inMarks);

void App::printMenu() const{
    std::cout << "\nMenu:\n";
    std::cout << "1) Show groups\n";
    std::cout << "2) Show group \n";
    std::cout << "3) Add group \n";
    std::cout << "4) Add student \n";
    std::cout << "5) Add mark\n";
    std::cout << "6) Enter ERW\n";
    std::cout << "7) Show student's ERW\n";
    std::cout << "8) Get average mark\n";
    std::cout << "9) Transfer group\n";
    std::cout << "10) Exit\n\n";
}

void App::ShowGroups() {
    groupsTable.showGroups();
}

void App::ShowGroup() {
    const char *errmsg = "";
    groupsTable.showGroups();
    int choice = scan<int>(std::cin, "Enter group id");
    if (groupsTable.findGroupInTable(choice) == -1) std::cout << "No such group exists\n";
    else groupsTable.getGroupByID(choice).showGroup();
    
}

void App::AddGroup() {
    int inId = scan<int>(std::cin, "Enter group's id");

    if (groupsTable.findGroupInTable(inId) != -1)
        std::cout << "Group is already in table!\n";
    else {
        Group* inGroup = new Group;
        inGroup->setGroupIndex(inId);

        std::string inType = scan<string>(std::cin, "Enter type of students:\n0. Juniors\n1. Seniors\n");
        inGroup->setTypeStudents(inType);

        int inMaxMarksNumber = scan<int>(std::cin, "Enter max number of marks");;
        inGroup->setGroupMaxNumberMarks(inMaxMarksNumber);

        groupsTable.addGroup(inGroup);
    }
    
}

void App::AddStudent() {
    groupsTable.showGroups();
    int inId = scan<int>(std::cin, "Enter group's id");

   
    if (groupsTable.findGroupInTable(inId) == -1)
        std::cout << "No such group exists!\n";
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

        student->setSurname(scan<string>(std::cin, "Enter surname"));
        student->setInitials(scan<string>(std::cin, "Enter initials"));
        student->setMarksNumberMax(group.getMarksNumberMax());
        student->setTypeStudent(group.getTypeStudents());

        if (group.getSize() != 0) {
            Student& filledStudent = group.getStudentByPos(0);
            std::vector<Mark> copiedMarks = filledStudent.getMarks();
            student->insertMarksVector(copiedMarks);

            for (int i = 0; i < student->getMarks().size(); ++i) {
                student->getMarks()[i].mark = 0;
            }
        }
        group.addStudent(student);
    }
    
}

void App::AddMark() {
    groupsTable.showGroups();
    int inId = scan<int>(std::cin, "Enter group's id");;
   

    if (groupsTable.findGroupInTable(inId) == -1)
        std::cout << "No such group exists!\n"; 
    else {
        Group &group = groupsTable.getGroupByID(inId);
        for (int i = 0; i < group.getSize(); ++i) std::cout << group.getStudentByPos(i).getSurname() << std::endl;
        std::string inSurname = scan<string>(std::cin, "Enter surname");
        if (group.isStudentInGroup(inSurname)) {
            Student &student = group.getStudentBySurname(inSurname);
            Mark inMark = enterMark(student.getMarks());
            student.insertMark(inMark);

            if (group.getSize() == 1) return;
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
    
}

void App::EnterERW() {
    groupsTable.showSeniorsGroups();
    int inId = scan<int>(std::cin, "Enter group's id");;
   
    if (groupsTable.findGroupInTable(inId) == -1)
        std::cout << "No such group exists!\n";
    else if (groupsTable.getGroupByID(inId).getTypeStudents() == SenS) {
        Group &group = groupsTable.getGroupByID(inId);
        for (int i = 0; i < group.getSize(); ++i) std::cout << group.getStudentByPos(i).getSurname() << std::endl;
        std::string inSurname = scan<string>(std::cin, "Enter surname");
        if (group.isStudentInGroup(inSurname)) {
            std::string inTopic = scan<string>(std::cin, "Enter ERW topic");
            std::string inPlace = scan<string>(std::cin, "Enter ERW place");
            int inMark = scan<int>(std::cin, "Enter ERW mark");;

            Student& student = group.getStudentBySurname(inSurname);
            student.setTopicERW(inTopic);
            student.setPlaceERW(inPlace);
            student.setMarkERW(inMark);
        }
    }
   
}

void App::ShowERW() {
    groupsTable.showSeniorsGroups();
    int inId = scan<int>(std::cin, "Enter group's id");;

    if (groupsTable.findGroupInTable(inId) == -1)
        std::cout << "No such group exists!\n";
    else if (groupsTable.getGroupByID(inId).getTypeStudents() == SenS) {
        Group& group = groupsTable.getGroupByID(inId);
        for (int i = 0; i < group.getSize(); ++i) std::cout << group.getStudentByPos(i).getSurname() << std::endl;
        std::string inSurname = scan<string>(std::cin, "Enter surname");
        if (group.isStudentInGroup(inSurname)) {
            Student& student = group.getStudentBySurname(inSurname);
            std::cout << "Topic: " << student.getTopicERW() << std::endl;
            std::cout << "Place: " << student.getPlaceERW() << std::endl;
            std::cout << "Mark: " << student.getMarkERW() << std::endl;
        }
    }
   
}

void App::GetAverageMark() {
    groupsTable.showGroups();
    int inId = scan<int>(std::cin, "Enter group's id");;
    if (groupsTable.findGroupInTable(inId) == -1)
        std::cout << "No such group exists!\n";
    else {
        Group& group = groupsTable.getGroupByID(inId);
        std::cout << group.getAverageMark();
    }
    
}

void App::TransferGroup() {
    groupsTable.showGroups();
    int inId = scan<int>(std::cin, "Enter group's id");;

   
    if (groupsTable.findGroupInTable(inId) == -1)
        std::cout << "No such group exists!\n";
    else {
        Group& oldGroup = groupsTable.getGroupByID(inId);
        int changeTypeGroup = scan<int>(std::cin, "Change type of group?\n0. No\n1. Yes\n");;
        int inMaxMarksNumber = scan<int>(std::cin, "Enter max number of marks");;
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choiceMark <= 0);

    Mark* ptrRes = new Mark;
    ptrRes->discipline = choice;
    ptrRes->mark = choiceMark;
    return *ptrRes;
}