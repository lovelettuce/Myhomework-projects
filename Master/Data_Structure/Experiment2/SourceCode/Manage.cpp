//
// Created by YangYujie on 2023/11/1.
//
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include "Manage.h"

#define SUCCESS true
#define FAIL false

using namespace std;

void updateIndex (StudentList &L) {
    StudentNode* p = L; int i = 0;
    while (p->next) {
        p = p->next;
        i++;
        p->length = i;
    }
    L->length = i;
}

void inputStudent (StudentList &L) {
    cout << "\n<addStudent>\n";
    Student newStudent; static bool flag1;
    do {
        cout << "Name: ";
        fflush(stdout);
        scanf("%s", newStudent.name);
        //输入的ID:全数字、长度为10
        static bool isLengthValid, isInputValid;
        do {
            isLengthValid = false;
            isInputValid = true;
            printf("ID: ");
            fflush(stdout);
            // 限制输入ID的格式为全数字，且ID长度固定为10
            char *inputID = new char[24];
            scanf("%s", inputID);
            // 输入长度超过11则停止输入(包括字符'/0')
            char *id = inputID;// 检查指针。
            if (strlen(inputID) == 10) {
                isLengthValid = true;
            } // 输入ID的长度小于10则不满足输出，应重新输出
            while (id && *id!='\0') {
                // p指针每次后移检查字符是否为数字
                if (*id < '0' || *id > '9') {
                    isInputValid = false;
                    break;
                }
                id++;
            }
            if (isInputValid && isLengthValid) {
                strcpy(newStudent.ID, inputID);
            } else {
                if (!isInputValid) {
                    cout << "ID Input Invalid\n"<<"Please type in again!\n";
                }
                if (!isLengthValid) {
                    cout << "ID Length Invalid\n"<<"Please type in again!\n";
                }
            }
            delete[] inputID;
        }   while (!isLengthValid || !isInputValid);
        //输入的成绩：大于等于0且小于等于100
        static bool isGradeValid = true;
        do {
            cout << "grade: ";
            cin >> newStudent.grade;
            if (newStudent.grade < 0 || newStudent.grade > 100) {
                isGradeValid = false;
                cout << "Grade Invalid\n" << "Please type in again!\n";
            }
        } while (!isGradeValid);

        flag1 = addStudent(L, newStudent);
        if (flag1) {
            cout << "\n<addStudent> SUCCESS!\n";
        } else {
            cout << "\n<addStudent> FAILED! ID REPETITION!\n"
                 << "Please type in new data.\n";
        }
    } while (!flag1);
}

char* locateID (StudentList L, int index) {
    //第一个元素的下标记作1。
    StudentNode* p = L;  char *targetID = new char[16];
    if (index > L->length) {
        return targetID;
    }
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    strcpy(targetID, (p->info).ID);
    return targetID;
}

bool addStudent (StudentList &L, const Student &information) {
    //采用头插法建立链表。
    for (int i = 1; i <= L->length; i++) {
        if (strcmp(information.ID, locateID(L, i)) == 0) {
            return false;
        }
    }
    auto *NewStudent = new StudentNode;
    NewStudent->next = L->next;
    L->next = NewStudent;
    strcpy((NewStudent->info).name, information.name);
    strcpy((NewStudent->info).ID, information.ID);
    (NewStudent->info).grade = information.grade;
    updateIndex(L);
    return true;
}

void showStudent (StudentList L) {
    StudentNode *p = L->next;
    int i = 1;
    cout << "<showStudent>\n";
    cout << "—————————————————————————————————————————————\n";
    cout << "| INDEX |    ID    |      NAME      | GRADE |\n";
    cout << "—————————————————————————————————————————————\n";
    while (p) {
        if (i < 10) {
            cout << "| <00"<<i<<"> |";
        } else if (i < 100) {
            cout << "| <0"<<i<<"> |";
        } else {
            cout << "| <"<<i<<"> |";
        }
        printf("%-10s|%-16s|%-7.2f|\n", (p->info).ID, (p->info).name, (p->info).grade);
        p = p->next;
        i++;
    }
    cout << "—————————————————————————————————————————————\n";
    printf("Numbers of student: %d\n\n", L->length);
}

void initializeList (StudentList &L) {
    L = new StudentNode;
    //头结点的创建和命名。
    L->next = nullptr;
    L->length = 0;  //头结点成员length存储学生信息数目，学生结点length存储下标（从1开始）
    (L->info).grade = 0;
}

void removeStudent (StudentList &L) {
    cout << "\n<removeStudent>\n";
    char *rTargetID = new char[24];
    static bool flag2;
    do {
        flag2 = FAIL;
        cout << "removeID: "; cin>>rTargetID;
        StudentNode *p = L->next;
        StudentNode *pre = L; //pre指向p指向结点的前驱结点
        while (p) {
            if (strcmp(rTargetID, (p->info).ID) == 0) {
                flag2 = SUCCESS;
                cout << "\n<removeStudent> SUCCESS!\n";
                pre->next = p->next;
                updateIndex(L);
            }
            p = p->next;
            pre = pre->next;
        }
        if (!flag2) {
            int commandR;
            cout << "\n<removeStudent> FAILED!\n"
                 << "Do you want to quit?";
            do {
                cout << "\nType: <0> to QUIT/ <1> to CONTINUE.\n";
                cin >> commandR;
                if (commandR != 0 && commandR != 1) {
                    cout << "Command Error!\n";
                } else if (commandR == 1){
                    cout << "CONTINUE!\n";
                } else {
                    cout << "QUIT!\n";
                    flag2 = true;
                }
            } while (commandR != 0 && commandR != 1);
        }
        delete p;
    } while (!flag2);
    delete[] rTargetID;
}

Student* findStudent (StudentList &L) {
    static bool flag3;
    static Student *key;
    do {
        flag3 = FAIL;
        char* fTargetID = new char[24];
        cout << "Find ID: ";
        cin >> fTargetID;
        StudentNode *p = L->next;
        while (p) {
            if(strcmp((p->info).ID, fTargetID) == 0) {
                flag3 = SUCCESS;
                cout << "<Instruction> FOUND!\n";
                cout << "\nID: " << (p->info).ID
                     << "\nName: " << (p->info).name
                     << "\nGrade: " << (p->info).grade << endl << endl;
                break;
            }
            p = p->next;
        }
        if (!flag3) {
            int commandF;
            cout << "<Instruction> NOT FOUND!\n"
                 << "Do you want to quit?";
            do {
                cout << "\nType: <0> to QUIT/ <1> to CONTINUE.\n";
                cin >> commandF;
                if (commandF != 0 && commandF != 1) {
                    cout << "Command Error!\n";
                } else if (commandF == 1){
                    cout << "CONTINUE!\n";
                } else {
                    cout << "QUIT!\n";
                    flag3 = true;
                }
            } while (commandF != 0 && commandF != 1);
        }
        delete[] fTargetID;
    } while (!flag3);
    return key;
}

void sortStudentsAscending (StudentList &L, int length) {
    //使用冒泡排序的递归算法。
    //递归出口：待排序的表长为0
    if (length == 0) {
        updateIndex(L);
        cout << "\n<sortStudentAscending>\n";
        cout << "Data has been sorted.\n\n";
        return;
    }
    StudentList p = L->next;    int i = 1; bool isSorted = false;
    while (p->next) {
        if ((p->info).grade > (p->next->info).grade) {
            auto *temp = new Student;
            Student *a = &p->info;
            Student *b = &(p->next->info);
            *temp = *a;
            *a = *b;
            *b = *temp;
            delete temp;
            isSorted = true;
        }
        p = p->next;
        i++;
        if (i == length) {
            break;
        }
    }
    if (!isSorted) {
        return;
    }
    //排序好表长为length的一趟后，从头排序表长为length-1一趟，以此递归
    sortStudentsAscending(L, length-1);
}