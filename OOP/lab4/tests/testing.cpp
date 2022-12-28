#include <gtest/gtest.h>
#include "../lib/app.h"

#define SHOW_GROUPS "1"
#define SHOW_GROUP "2"
#define ADD_GROUP "3"
#define ADD_STUDENT "4"
#define ADD_MARK "5"
#define ENTER_ERW "6"
#define SHOW_ERW "7"
#define GET_AVERAGE_MARK "8"
#define TRANSFER_GROUP "9"
#define EXIT "10"

std::string run(std::string commands) {
    testing::internal::CaptureStdout();
    std::cin.rdbuf(std::istringstream(commands).rdbuf());
    App app;
    app.start();
    std::string output = testing::internal::GetCapturedStdout();
    return output;
}

TEST(App, AddAndShowGroup) { 
    ASSERT_NO_THROW(App app);
}

TEST(Application, InvalidCommand) {
  std::string commands;
  commands += "-1";
  commands += "\n";
  commands += EXIT;
  std::string output = run(commands);
  ASSERT_NE(output.find("Invalid input! Try again!"), -1);
}

TEST(Application, AddSeniorGroup) {
    std::string commands;
    commands += ADD_GROUP;
    commands += "\n";
    commands += "100";
    commands += "\n";
    commands += "1";
    commands += "\n";
    commands += "10";
    commands += "\n";
    commands += SHOW_GROUPS;
    commands += "\n";
    commands += EXIT;

    std::string output = run(commands);
    ASSERT_NE(output.find("1 Group #100"), -1);
}

TEST(Application, AddJuniorGroup) {
    std::string commands;
    commands += ADD_GROUP;
    commands += "\n";
    commands += "100";
    commands += "\n";
    commands += "0";
    commands += "\n";
    commands += "10";
    commands += "\n";
    commands += SHOW_GROUPS;
    commands += "\n";
    commands += EXIT;

    std::string output = run(commands);
    ASSERT_NE(output.find("0 Group #100"), -1);
}

TEST(Application, TransferStudentToJunior) {
    std::string commands;
    commands += ADD_GROUP;
    commands += "\n";
    commands += "100";
    commands += "\n";
    commands += "0";
    commands += "\n";
    commands += "10";
    commands += "\n";
    commands += TRANSFER_GROUP;
    commands  += "\n";
    commands += "100";
    commands += "\n";
    commands += "1";
    commands += "\n";
    commands += "1";
    commands += "\n";
    commands += "1";
    commands += "\n";
    commands += EXIT;
        
    std::string output = run(commands);
    ASSERT_NE(output.find("0 Group #100"), -1);
}

TEST(Application, AddStudentToGroup) {
  std::string commands;
  commands += ADD_GROUP;
  commands += "\n";
  commands += "100";
  commands += "\n";
  commands += "0";
  commands += "\n";
  commands += "10";
  commands += "\n";
  commands += ADD_STUDENT;
  commands += "\n";
  commands += "100";
  commands += "\n";
  commands += "Ivanov";
  commands += "\n";
  commands += "O.A.";
  commands += "\n";
  commands += SHOW_GROUP;
  commands += "\n";
  commands += "100";
  commands += "\n";
  commands += EXIT;
  std::string output = run(commands);
  ASSERT_NE(output.find("Ivanov O.A."), -1);
}

TEST(Student, Initialization) {
  Student student("Ivan", "Ivanov");
  std::string fullName= "Ivan Ivanov";
  EXPECT_EQ(student.getFullName(), fullName);
}

TEST(Student, SetSurname) {
  Student student;
  student.setSurname("Volkov");
  EXPECT_EQ(student.getSurname(), "Volkov");
}

TEST(Student, AddMarks) {
  Student student;
  Mark mark_math = {"math", 50};
  std::vector <Mark> marks = {mark_math};
  student.insertMarksVector(marks);
  ASSERT_EQ(student.Marks[0].mark, 50);
  EXPECT_EQ(student.Marks[0].discipline, "math");
}

TEST(Group, Initialization) {
  Group group;
  ASSERT_EQ(group.getIndexGroup(), 0);
  ASSERT_EQ(group.getMarksNumberMax(), 0);
  ASSERT_EQ(group.getSize(), 0);
}

TEST(Group, FindUndefinedStudent) {
  Group group;
  Student student1("Kirill", "Kirillov");
  group.addStudent(&student1);
  ASSERT_THROW(group.getStudentPos("Ivanov"), Group::UnknownStudentException);
}

TEST(Group, GetByPosition) {
  Group group;
  Student student1("Kirill", "Kirillov");
  group.addStudent(&student1);
  Student student2 = group.getStudentByPos(0);
  EXPECT_EQ(student1.getFullName(), student2.getFullName());
}

int main(){
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}