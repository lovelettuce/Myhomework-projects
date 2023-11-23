//
// Created by YangYujie on 2023/11/1.
//
#ifndef MANAGE_H
#define MANAGE_H

typedef struct Student {
    char name[24]{};
    char ID[24]{};
    double grade{};
} Student;

typedef struct StudentNode {
    Student info;
    int length{};
    //头结点的length表示信息条数，学生结点的length表示下标（从1开始）
    struct StudentNode* next{};
} StudentNode, *StudentList;

void updateIndex (StudentList &L);//更新结点index的信息
void inputStudent (StudentList &L);//输入学生信息
char* locateID (StudentList L, int index);//查找表内给定序号的学生ID，返回ID
bool addStudent (StudentList &L, const Student &information);//添加学生成员信息
void showStudent (StudentList L);//展示系统内信息
void initializeList (StudentList &L);//初始化学生链表
void removeStudent (StudentList &L);//删除学生成员信息
Student* findStudent (StudentList &L);//查找给定ID的学生信息，返回学生信息
void sortStudentsAscending (StudentList &L, int length);//将学生信息按成绩升序排序
#endif //MANAGE_H