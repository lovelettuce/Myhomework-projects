//
// Created by 杨雨劼 on 2023/11/13.
//
#include <iostream>

#ifndef EXPERIMENT4_MYTUPLE_H
#define EXPERIMENT4_MYTUPLE_H

//方阵大小
#define SIZE 3

using std::cout, std::cin, std::endl;

namespace TUPLE {
    class TupleNode {
        //声明三元组结点类
        int row_;
        int column_;
        double value_;
        TupleNode *next_;
    public:
        TupleNode() {}; //默认构造函数
        TupleNode(int row, int column, double value):
        row_(row), column_(column), value_(value), next_(nullptr) {}   //含参构造函数：列表初始化结点

        friend class Mytuple;   //友元类：Mytuple
        friend class Mymatrix;  //友元类：Mymatrix
    };

    class Mytuple {
        //声明三元组链表类
        TupleNode *header_;
        int length_;
    public:
        Mytuple(): header_(nullptr), length_(0) {}  //列表初始化链表
        ~Mytuple() {
            delete header_;
        }//析构函数

        static void transpose(Mytuple &A);  //转置三元组
        static void reloadTuple(Mytuple &A);    //更新链表信息和删去链表中零元素结点
        //运算符重载
        Mytuple &operator + (const Mytuple &B);
        Mytuple &operator - (const Mytuple &B);
        Mytuple operator * (double multiplier) const;
        //'*'运算符重载：使用友元函数成为非类成员函数，左操作数可以不为类，返回另一种重载实现double * 三元组
        friend Mytuple operator * (double multiplier, const Mytuple &B) {
            return B * multiplier;
        }
        Mytuple& operator = (const Mytuple &B);

        friend class Mymatrix;  //友元类：Mymatrix
    };

    class Mymatrix {
        //声明方阵类
        double matrix[SIZE][SIZE];
    public:

        Mymatrix(); //构造函数
        ~Mymatrix() {}; //析构函数

        void getRandomMatrix(); //随机生成非零方阵
        void storeInTuple(Mytuple &T);  //将方阵信息存储到三元组中
        void showMatrix (Mytuple &T);   //通过三元组打印方阵
        friend class Mytuple;   //友元类：Mytuple
    };
}
#endif //EXPERIMENT4_MYTUPLE_H
