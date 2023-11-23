//
// Created by YangYujie on 2023/10/31.
//
#include <iostream>
#include "Manage.h"
using namespace std;
int main() {
    StudentList test;
    cout << "< Student Grades Management System >\n\n";
    initializeList(test);
    cout << "The system is successfully initialized!\n\n";
    int command;
    do {
        cout << "Command:\n"
             << "<0>——————showStudent\n"
             << "<1>——————addStudent\n"
             << "<2>——————removeStudent\n"
             << "<3>——————findStudent\n"
             << "<4>——————sortStudentsAscending\n"
             << "<5>——————programTerminate\n\n"
             << "Please input the command: ";
        cin >> command;
            switch (command) {
                default: {
                    cout << "Command Invalid!\n"
                         << "Please input the valid command!\n";
                }
                    break;

                case 0: {
                    showStudent(test);
                }
                    break;

                case 1: {
                    inputStudent(test);
                    showStudent(test);
                }
                    break;

                case 2: {
                    removeStudent(test);
                    showStudent(test);
                }
                    break;

                case 3: {
                    findStudent(test);
                }
                    break;

                case 4: {
                    sortStudentsAscending(test, test->length);
                    showStudent(test);
                }
                    break;

                case 5: {
                    cout << "The program terminated!\n";
                }   break;
            }
    } while (command != 5);
    return 0;
}