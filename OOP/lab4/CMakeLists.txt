cmake_minimum_required(VERSION 3.24)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp lib/app.cpp lib/app.h lib/student.h lib/student.cpp lib/seniorStudent.cpp lib/seniorStudent.h lib/juniorStudent.cpp lib/juniorStudent.h lib/group.cpp lib/group.h lib/groupTable.cpp lib/groupTable.h lib/container.inl lib/container.h lib/app.cpp lib/app.h)
